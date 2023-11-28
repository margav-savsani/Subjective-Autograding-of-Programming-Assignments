#ifndef TRIE_CPP
#define TRIE_CPP

#ifndef STD_HEADERS
#include "std_headers.h"
#endif

#ifndef DICTIONARY_H
#include "dictionary.h"
#endif

#ifndef TRIE_H
#include "Trie.h"
#endif

using namespace std;

Trie::Trie(Dictionary<int> *nameToIndex) {
  nameDict = nameToIndex;
  root = new TrieNode();
  if (root == nullptr) {
    cout << "Memory allocation failure." << endl;
    exit(-1);
  }
}

Trie::~Trie() {
  recursiveDelete(root);
}

void Trie::recursiveDelete(TrieNode *node) {
  if (node == nullptr) {
    return;
  }
  else {
    for (int i = 0; i < NUM_CHARS; i++) {
      TrieNode *currNode = node->branch[i];
      recursiveDelete(currNode);
      node->branch[i] = nullptr;
    }
    if (node != root) {
      delete node;
    }
    return;
  }
}

bool Trie::insert(string wordInName, int indexOfName) {
  TrieNode *currNode = root;
  int len = wordInName.length();
  
  for (int i = 0; i < wordInName.length() ; i++){
    //index of the alphabet next to current node
    int alphabet_index = int(wordInName[i]) - int('A');
    if(currNode->branch[alphabet_index]==nullptr){//create new node if it is nullptr
      TrieNode* newNode = new TrieNode;
      currNode->branch[alphabet_index]=newNode;
      currNode->numNonNullBranches++;
    }
    //traverse the trie till the end of wordInName
    currNode=currNode->branch[alphabet_index];

  }
  /*
  planner.cpp uses this insert function as:
  1) if (!stnNamesTrie->insert(currWord->object, freeIndex)) {
    logFile << "Failed to insert \"" <<
  2) else {
    logFile << "Successfully inserted \""
  So false is the node already exists and true after inserting the complete word.
  */
  
  listOfObjects<int> * trailing_pointer=nullptr;
  listOfObjects<int> * iterator = currNode->indices; //iterator for traversing the indices
  //iterating through the linked list till we find the null ptr or till the station name already exists.
  while(iterator!=nullptr && iterator->object!=indexOfName){
    trailing_pointer=iterator; //stores history of iterator
    iterator=iterator->next;
  }
  if(iterator!=nullptr && iterator->object==indexOfName) return false; //if the while loop breaks because the second condition is false, then execute this condition
  if(iterator==nullptr && trailing_pointer!=nullptr) { //if while loop breaks due to first condition, store the address the next ptr in the tail.
    iterator = new listOfObjects<int>(indexOfName);
     /* following things happen in following two lines:
        1) allocating memory
        2) setting next ptr of iterator to null
        3) storing indexOfName in object
      */
    trailing_pointer->next=iterator; //stores ptr of iterator in its previous indices' next
    //following two lines should get executed on their own bcz allocation is done using constructor (but I am not sure, so adding these two to be on safer side for now)
    iterator->object = indexOfName;
    iterator->next = nullptr;
  }
  
  currNode->isWord=true;
  return true;
}

bool Trie::del(string wordInName, string name) {
  TrieNode *currNode = root;
  TrieNode *lastBranchNode = nullptr;
  int lastBranchChar = -1;
  int len = wordInName.length();

  
  /**--------traversing through the trie---------**/
  for(int i = 0; i < len; i++){
    int index_in_name = int(name[i]) - int('A');
    if(currNode->branch[i]!=nullptr && currNode->isWord==false){
      currNode=currNode->branch[i];
    }
    else if(currNode->branch[i]==nullptr && i < len-1) return false;
  }
  /**----------------------**/
  int number_of_stations = 0 ;
  if(currNode!=nullptr && currNode->isWord==true){ //wordInName is successfully found in the trie
    //now check if name is there in indices
    listOfObjects<int> * iterator = currNode->indices;
    while(iterator!=nullptr){
      if(iterator->object!=nameDict->hashValue(name)){return false;}
      iterator=iterator->next;
      number_of_stations++;
    }
  }
  //Now the cases where the value does exist and we need to delete the node
  /*
  cases I assumed to delete:
  1) suppose I want to delete MUMBAI CENTRAL
  2) if there is only one station name having the keyword MUMBAI and it is MUMBAI CENTRAL itself then, delete that entry from dictionary, delete the linked list associated with leaf of MUMBAI and then delete the trie MUMBAI if it is not the prefix of any other word.
  3) if there are multiple stations having the keyword MUMABI suppose, MUMBAI CENTRAL and MUMABI WESTERN, then don't delete the trie node, just delete that entry in the dictionary, struct in the linked list. That's it.
  4) removing from dictionary is already implemented in planner.cpp so I just need to delete the struct.
  */

  listOfObjects<int>*iterator_for_deletion = currNode->indices;
  listOfObjects<int>*trailing_ptr;
 //I am taking > 1 because if my insert works correctly, there must be atleast one station name associated with that trie, if there are no station names associated with that trie then that trie must not exist
  if(number_of_stations>1){
    while(iterator_for_deletion!=nullptr && iterator_for_deletion->object!=nameDict->hashValue(name)){
      trailing_ptr=iterator_for_deletion;
      iterator_for_deletion=iterator_for_deletion->next;
    }
    if(iterator_for_deletion==nullptr)return false; //maybe this is repeated and not required
    if(iterator_for_deletion->object==nameDict->hashValue(name)){
      trailing_ptr->next = iterator_for_deletion->next; //changes ptrs, index prev to iterator_for_deletion now points directly to next of iterator_for_deletion
      delete iterator_for_deletion; //deallocates memory from heap
    }
  }
//in this case i need to delete the trie nodes as well if they have no branches.
  else if(number_of_stations==1){
    if(iterator_for_deletion->object==nameDict->hashValue(name)){
      delete iterator_for_deletion;//deallocates memory from heap
      //now deallocate the trie if no branches
      currNode->isWord=false;
      int length_after_deletion = len;
      
      while(length_after_deletion>0){
        TrieNode* master_node = root;
        TrieNode* iterator_node = master_node;
        for(int i = 0; i < length_after_deletion; i++){
          iterator_node=iterator_node->branch[i];
        }
        for(int j = 0; j < NUM_CHARS; j++){
          if(iterator_node->numNonNullBranches>0) break;
          else { recursiveDelete(iterator_node); length_after_deletion--;} //uses the recursivedelete function to delete a particular node if it has no branches.
        }
      }
    }
  }
  return true;
}
//a recursive function which goes in all the branches and modifies the linked list associated with currCompletions
// void Trie :: newFunction(TrieNode* node, listOfObjects<string> * currCompletions, listOfObjects<string> * root){
    
//     if (node!=nullptr && node->isWord==true){  //base case i.e when the node is the leaf
//     listOfObjects<int> * linked_list = node->indices; //iterator for linked list
//     listOfObjects<string> *trailing_ptr = nullptr; //stores history of currCompletion
//     while(linked_list!=nullptr){ //traverses till tail of the linked list at a particular leaf
//       listOfObjects<string> * copy_of_root=root; // stores the initial address of currCompletion
//       //if currCompletion is a null ptr, but the trailing ptr isn't allocate memory for currCompletions and point the trailing ptr at it
//       if(currCompletions==nullptr && trailing_ptr!=nullptr) {
//         currCompletions = new listOfObjects<string>("");
//         trailing_ptr->next=currCompletions;
      //   }
      // bool is_present = false; //check if the station name is already present in the currCompletion list
      // while(copy_of_root!=nullptr){
      //   if(copy_of_root->object!=nameDict->getKeyAtIndex(linked_list->object)){
      //     is_present = true;
      //     break;
      //   }
      //   copy_of_root = copy_of_root-> next;
      // }

      // if(!is_present){ //add the station name only if the object is not already present in the currCompletion
      //   currCompletions->object = nameDict->getKeyAtIndex(linked_list->object); //stores the station name at hash value given by object of linked list
      //   trailing_ptr=currCompletions;
      //   if(currCompletions!=nullptr){ // if the present index is non null only then move to next location (otherwise it can't)
      //     currCompletions->next=nullptr;
      //     currCompletions = currCompletions->next;
      //   }
      // }
      // linked_list=linked_list->next; //iterator for traversing the linked list
//     }
//     trailing_ptr=trailing_ptr->next; // i can't remember or identify why i added this line, but it doesn't seem to be causing any harm
//     linked_list=nullptr; //ensuring that ptrs are null before starting the loop again
//     trailing_ptr=nullptr;
//     }

//     int i;
//     for (i = 0; i < NUM_CHARS; i++){ //iterating through the branches of the node
//         if (node!=nullptr && node->branch[i]!=nullptr){ //entering the branch if it is non null
//             newFunction(node->branch[i], currCompletions, root);
//         }
//     }
// }

listOfObjects<string> * Trie::completions(string prefix) {
  TrieNode *currNode = root;
  int len = prefix.length();
  listOfObjects<string> *currCompletions = nullptr;

  for(int i =0; i < len ; i++){
    int index = int(prefix[i]) - int('A');
    if(currNode!=nullptr && currNode->isWord==false) currNode = currNode->branch[i];
    if(currNode==nullptr) return nullptr;
  }
  TrieNode * node = currNode;
  listOfObjects<string> *dummy_storage = currCompletions;

  recursiveAddCompletions(node, * &currCompletions);

  return currCompletions;
}

bool Trie::recursiveAddCompletions(TrieNode *node, listOfObjects<string> * &currCompletions) {
  if (node->isWord) {
    if (!addCompletions(node, *&currCompletions)) {
      return false;
    }
  }

  TrieNode *currNode = node;
  for (int i = 0; i < NUM_CHARS; i++) {
    if (currNode->branch[i] != nullptr) {
      if (!recursiveAddCompletions(currNode->branch[i], *&currCompletions)) {
    return false;
      }
    }
  }

  return true;
}

bool Trie::addCompletions(TrieNode *node, listOfObjects<string> *&currCompletions) {
  TrieNode* currNode = node;
  listOfObjects<int> * linked_list = currNode->indices;
  listOfObjects<string> * trailing_ptr = nullptr; //to be able to store the value in next of a particular element of the linked list
  listOfObjects<string> * copy_of_root = currCompletions;
  if(linked_list==nullptr) return false;

  while(linked_list!=nullptr){ //completions' iteration is guided by linked_list
    if(currCompletions==nullptr && trailing_ptr!=nullptr) { //if present index is null and trailing index is non null, allocate memory at null space and store its address in the trailing ptr
      currCompletions = new listOfObjects<string>(""); //allocates memory
      trailing_ptr->next=currCompletions; //stores the address of next element of linked list
      }
      bool is_present = false; //check if the station name is already present in the currCompletion list
      while(copy_of_root!=nullptr){
        if(copy_of_root->object!=nameDict->getKeyAtIndex(linked_list->object)){
          is_present = true;
          break;
        }
        copy_of_root=copy_of_root->next;
      }
      if(!is_present){ //add the station name only if the object is not already present in the currCompletion
        currCompletions->object = nameDict->getKeyAtIndex(linked_list->object); //retrieves the station name using the hashvalue and stores it in object of currCompletions
        trailing_ptr=currCompletions;
        if(currCompletions!=nullptr){ // if the present index is non null only then move to next location (otherwise it can't)
          currCompletions->next=nullptr;
          currCompletions = currCompletions->next;
        }
      }
      linked_list=linked_list->next;
  }
  return true;
  
}

bool Trie::isPresentInCompletions(listOfObjects<string> *completions, string name) {
  listOfObjects<string> *currCompletion = completions;
  bool isPresent = false;
  while (currCompletion != nullptr) {
    if (currCompletion->object == name) {
      isPresent = true;
      break;
    }
    currCompletion = currCompletion->next;
  }
  return isPresent;
}

void Trie::freeCompletionList(listOfObjects<string> *completions) {
  listOfObjects<string> *currCompl = completions;
  while (currCompl != nullptr) {
    listOfObjects<string> *toDeleteCompl = currCompl;
    currCompl = currCompl->next;
    delete toDeleteCompl;
  }
  return;
}

bool Trie::isPresent(string wordInName) {
  TrieNode *currNode = root;
  int len = wordInName.length();

  for (int i = 0; i < len; i++) {
    int letter = toupper(wordInName.at(i)) - 'A';

    if (currNode->branch[letter] == nullptr) {
      return false;
    }
    currNode = currNode->branch[letter];
  }

  return currNode->isWord;
  
}

// Edit version 1: Added printTrie and recursivePrintTrie functions
// to help in debugging

void Trie::printTrie()
{
  recursivePrintTrie(root, "", -1, false);
}

// Adapted from Adrian Schneider's code on StackOverflow
// Basically a variation of the function we've been using
// print binary search trees in previous labs

void Trie::recursivePrintTrie(TrieNode *node, const string& prefix, int branchId, bool siblingsToRight)
{
  if (node != nullptr) {
    cout << prefix;
    
    cout << ((branchId == 0) ? "|-" : (branchId == -1)? " *":"|_" ) << (char) ((branchId != -1) ? 'A'+branchId: '*');
    cout << ((branchId == 0) ? '-' : (branchId == -1) ? '*':'_');
    
    // If this trie node has isWord set to true, print "(isWord)" and
    // also the list of complete station names (accessed through indices
    // in nameDict) associated with this trie node.
    if (node->isWord) {
      cout << "(isWord)";
      listOfObjects<int> *currIndices = node->indices;
      while (currIndices != nullptr) {
    cout << endl << prefix << "     " << nameDict->getKeyAtIndex(currIndices->object);
    currIndices = currIndices->next;
      }
    }
    else {
      cout << "()";
    }
    cout << endl;
    for (int i = 0; i < NUM_CHARS; i++) {
      TrieNode *currNode = node->branch[i];
      bool childrenToRight = false;
      for (int j = i+1; j < NUM_CHARS; j++) {
    if (node->branch[j] != nullptr) {
      childrenToRight = true;
      break;
    }
      }
      if (currNode != nullptr) {
    recursivePrintTrie(currNode, prefix + ((siblingsToRight) ? "│   " : "    "), i, childrenToRight);
      }
    }
  }
}
// End edit version 1

#endif

