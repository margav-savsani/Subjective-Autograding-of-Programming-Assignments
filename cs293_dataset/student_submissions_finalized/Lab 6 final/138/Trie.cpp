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

//Constructor which initialises the dictionary
Trie::Trie(Dictionary<int> *nameToIndex) {
  //initialising the trie
  nameDict = nameToIndex;
  root = new TrieNode();
  // if memory wasnt allocated
  if (root == nullptr) {
    cout << "Memory allocation failure." << endl;
    exit(-1);
  }
}

//recursively deletes the whole tree
Trie::~Trie() {
  recursiveDelete(root);
}

//recursively deletes the node and all of its branches
void Trie::recursiveDelete(TrieNode *node) {
  //base case for deletion
  if (node == nullptr) {
    return;
  }
  else {
    //frees space for all of the branches
    for (int i = 0; i < NUM_CHARS; i++) {
      TrieNode *currNode = node->branch[i];
      //deletion by recursion
      recursiveDelete(currNode);
      node->branch[i] = nullptr;
    }
    //ensuring that the root is not deleted
    if (node != root) {
      delete node;
    }
    return;
  }
}

//inserts a node in the trie
bool Trie::insert(string wordInName, int indexOfName) {
  TrieNode *currNode = root;
  int len = wordInName.length();
  //tracks the index of the last letter matched
  int j;
  //partial is true if the string partially matches with another string
  bool partial=false;
  // Insert your code here
  for(int i=0;i<len;i++){
    //search is made case insensitive
    int letter = toupper(wordInName.at(i)) - 'A';
    //partial match is found
    if (currNode->branch[letter] == nullptr) {
      partial=true;
      j=i;
      break;
    }
    //traversing the trie
    currNode = currNode->branch[letter];
  }
  //word is partially matched
  if(partial==true){
    //new node to be inserted
    TrieNode * to_insert;
    for(;j<len;j++){
      //inserting new nodes in the trie
      int letter = toupper(wordInName.at(j)) - 'A';
      to_insert=new TrieNode();
      currNode->numNonNullBranches+=1;
      currNode->branch[letter] = to_insert;
      //traversing the trie
      currNode=to_insert;
    }
    //storing the value in the list of Objects of the final node
    to_insert->isWord=true;
    listOfObjects<int> *occ=new listOfObjects<int>(indexOfName);
    to_insert->indices=occ;
  }
  // for handling cases like "Mumbai" and "Mumb" where a word fully matches with a prefix of another word
  else if(currNode->isWord==false){
    currNode->isWord=true;
    listOfObjects<int> *occ=new listOfObjects<int>(indexOfName);
    currNode->indices=occ;
  }
  //appending a node in the indice of the last node
  else{
    listOfObjects<int>* ptr=currNode->indices;
    while(ptr->next!=NULL){
      //traversing the linked 
      if(ptr->object==indexOfName){
        return false;
      }
      ptr=ptr->next;
    }
    listOfObjects<int> *occ=new listOfObjects<int>(indexOfName);
    ptr->next=occ;
  }

  return true;
}

// deleting a given string from a set of nodes
// this recursive function is used in deletion 
// it is used for those strings for which the nodes have only one or no non-null branch
void Trie::DeleteFurther(TrieNode *node, string str) {
  //base case
  if (node == nullptr) {
    return;
  }
  else {
      // all letters are stored by converting to upper case
      int i = toupper(str.at(0)) - 'A';
      TrieNode *currNode = node->branch[i];
      //recursive call
      DeleteFurther(currNode,str.substr(1));
      node->branch[i] = nullptr;

    //freeing space 
    if (node != root) {
      delete node;
    }
    return;
  }
}

// deletes a given name from a word in the name
bool Trie::del(string wordInName, string name) {
  TrieNode *currNode = root;
  int len = wordInName.length();

  //entry to be deleted
  Entry<int>* to_delete = nameDict->get(name);
  // if no such entry exists return false
  if(to_delete==NULL){
    return false;
  }

  //index to be deleted
  int index = to_delete->value;

  //finding the node
  for (int i = 0; i < len; i++) {
    int letter = toupper(wordInName.at(i)) - 'A';

    //if node does not exist
    if (currNode->branch[letter] == nullptr) {
      return false;
    }
    currNode = currNode->branch[letter];
  }

  //traversing the list of indices
  listOfObjects<int>* ptr=currNode->indices;
  listOfObjects<int>* parent=NULL;

  // looping till pointer doesnt become NULL
  while(ptr!=NULL){
      if(ptr->object==index){
        // in case first element in the linked list is to be deleted
        if(parent==NULL){
          currNode->indices=ptr->next;
          delete ptr;
          break;
        }
        // deleting an element from a linked list
        else{
          parent->next=ptr->next;
          delete ptr;
          break;
        }
      }

      //updation
      parent=ptr;
      ptr=ptr->next;
  }

  // if indices of last node are not empty
  if(currNode->indices!=NULL){
    return true;
  }

  //if indices of last node is empty
  else{
    //initialisation
    TrieNode *currNode = root;
    TrieNode *lastNode = root;
    //last node after which the string needs to be deleted
    TrieNode *lasttNode = root;
    int j=0;

    // looping fron top to bottom to find the last node with more than one non null branches or having isWord true
    // the nodes after this node are deleted using DeleteFurther function
    for (int i = 0; i < len; i++) {
      int letter = toupper(wordInName.at(i)) - 'A';
      //checking for such node
      if(currNode->numNonNullBranches>1 || currNode->isWord==true){
        //saving that specific node
        j=i;
        lasttNode=currNode;
        lastNode=currNode->branch[letter];
      }
      currNode = currNode->branch[letter];
    }

    //for last element
    //setting isWord to false for the last node
    currNode->isWord=false;
    // if the woord to be deleted is not a prefix of some other word
    if (currNode->numNonNullBranches==0){
      lasttNode->branch[toupper(wordInName.at(j)) - 'A']=NULL;
      //string ti be deleted
      string str=wordInName.substr(j);
      //recusrively deleting the string
      DeleteFurther(lastNode,str);
    } 
  }
  return true;
}

//returns the list of possible completions
listOfObjects<string> * Trie::completions(string prefix) {
  TrieNode *currNode = root;
  int len = prefix.length();
  listOfObjects<string> *currCompletions = nullptr;

  // Insert your code here

  //reaching the last node of the prefix that needs to be completed
  for (int i = 0; i < len; i++) {
    int letter = toupper(prefix.at(i)) - 'A';
    if (currNode->branch[letter] == nullptr) {
      return NULL;
    }
    currNode = currNode->branch[letter];
  }

  //calling recursve add function which returns the currCompletions
  recursiveAddCompletions(currNode,currCompletions);
  return currCompletions;
}


//boiler plate code that was provided it recursively goes to the end of all the words with the given prefix and calls the function
// addCompletion for all nodes which have isWord=true
// thus it returns currCompletions
bool Trie::recursiveAddCompletions(TrieNode *node, listOfObjects<string>* & currCompletions) {
  if (node->isWord) {
    if (!addCompletions(node, currCompletions)) {
      return false;
    }
  }
  TrieNode *currNode = node;
  for (int i = 0; i < NUM_CHARS; i++) {
    if (currNode->branch[i] != nullptr) {
      if (!recursiveAddCompletions(currNode->branch[i], currCompletions)) {
	return false;
      }
    }
  }
  return true;
}

// adds the Completion to currCompletions and returns it by reference
bool Trie::addCompletions(TrieNode *node, listOfObjects<string>* &currCompletions) {

  // Insert your code here
  listOfObjects<int>* ptr=node->indices;
  listOfObjects<string> * to_add=currCompletions;

  //reaching the last pointer whose next is null in currCompletions
  if(to_add!=NULL){
    while(to_add->next!=NULL){
      to_add=to_add->next;
    }
  }

  // loop to insert all elements in induced to currCompletions
  while(true){

    //finding the tstring to be inserted
    string to_insert=nameDict->getKeyAtIndex(ptr->object);

    // if the possible completion does not already exist in currCompletion
    if(!isPresentInCompletions(currCompletions,to_insert)){
      // this is ti be inserted in currCompletions
      listOfObjects<string>* ne=new listOfObjects<string>(to_insert);

      //base case for first addition
      if(to_add==NULL){
        to_add=ne;
        currCompletions=ne;
      }

      //addition of node to be inserted in currCompletion
      else{
        to_add->next=ne;
        to_add=ne;
      }
    }

    //breaking out of the loop
    if(ptr->next==NULL){
      break;
    }

    //updation
    ptr=ptr->next;
  }
  return true;
}

//boiler plate code that was provided
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

//boiler plate code that was provided
void Trie::freeCompletionList(listOfObjects<string> *completions) {
  listOfObjects<string> *currCompl = completions;
  while (currCompl != nullptr) {
    listOfObjects<string> *toDeleteCompl = currCompl;
    currCompl = currCompl->next;
    delete toDeleteCompl;
  }
  return;
}

//boiler plate code that was provided 
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


//boiler plate code that was provided
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
