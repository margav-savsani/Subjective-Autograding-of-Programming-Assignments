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

#include <cassert>

using namespace std;

template <typename T>
bool insert_in_lists(const T &obj, listOfObjects<T>* &l){   //inserts an element obj in the list l only if the element is not already present.
                                          //If already present then return false
  listOfObjects<T> *currIndex = l;
    
  while (currIndex->next != nullptr) {
    if(currIndex->object == obj){   //element already present
      return false;
    }
    currIndex = currIndex->next;
  }
  if(currIndex->object == obj){   //element already present
    return false; 
  }
  currIndex->next = new listOfObjects<T>(obj);   //add element
  return true;
}


Trie::Trie(Dictionary<int> *nameToIndex) {
  nameDict = nameToIndex;
  root = new TrieNode();
  if (root == nullptr) {
    cout << "Memory allocation failure." << endl;
    exit(-1);
  }
  // for(int i = 0; i < NUM_CHARS; i++){
  //   root->branch[i] = nullptr;
  // }
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

bool Trie::insert(string wordInName, int indexOfName) {   //inserts a word in the trie, also stores indexOfName in its indices
  TrieNode *currNode = root;
  int len = wordInName.length();
  // Insert your code here
  for(int i = 0; i < len; i++){    
    char ch = tolower(wordInName.at(i));
    int index = (int)(ch) -(int)('a');   //insert the ith character od th word in the trie
    if(currNode->branch[index] != nullptr){   //branch already present, just traverse
      currNode = currNode->branch[index];
    }
    else{    //branch not already present, make one
      currNode->numNonNullBranches += 1;
      currNode->branch[index] = new TrieNode();
      currNode = currNode->branch[index];
    }
  }
  currNode->isWord = true;   
  if(currNode->indices == nullptr){    //if no indices exist, make one
      currNode->indices = new listOfObjects<int>(indexOfName);
      return true;
  }
  return insert_in_lists(indexOfName, currNode->indices);     //indices array exists, insert in that
  
}

bool Trie::del(string wordInName, string name) {
  
  TrieNode *currNode = root;
  TrieNode *lastBranchNode = nullptr;
  int lastBranchChar = -1;
  int len = wordInName.length();

  // Insert your code here
  int del_depth = 0;    //max depth from the root after which delete can be performed(to take care of branching nodes)
  for(int i = 0; i < len; i++){
    
    char ch = tolower(wordInName.at(i));
    int index = (int)(ch) -(int)('a');
    if(currNode->branch[index] != nullptr){    //checkout to the branch
      // for(int j = 0; j < NUM_CHARS; j++){      //if curr node has more than 1 branches?
      //   if(j != index && currNode->branch[j] != nullptr){

      //     del_depth = i+1;   //at level i+1 from the root, there is a split
      //     break;
      //   }
      // }
      if(currNode->numNonNullBranches >= 2) del_depth = i+1;
      currNode = currNode->branch[index];
    }
    else{    //branch doesn't exist
      return false; //word doesn't exist  
    }
  }  
  
  assert(currNode->isWord == true);   //only words can be deleted
  listOfObjects<int>* temp_id = currNode->indices;    //temp variable for traversing indices list
  listOfObjects<int>* prev = nullptr;
  bool multiple = (temp_id != nullptr && temp_id->next != nullptr);   //check if the node has multiple indices stored
  bool found = false;    //check if the name is present in the indices
  while(temp_id != nullptr){
    if(nameDict->getKeyAtIndex(temp_id->object) == name){    //assuming that the word is first deleted from trie and then deleted from dictionary
      
      if(prev != nullptr){
        prev->next = temp_id->next;  
      }
      else{
        currNode->indices = temp_id->next;
      }
      delete temp_id;
      found = true;   //assuming each station name is inserted only once
      
      break;
    }
    prev = temp_id;
    temp_id = temp_id->next;
  }
  if(!found){    //name not found, deletion not possible
    return false;
  }
   
  bool hasNext = false;   //check if word is a prefix of another word in trie, cant delete the whole thing
  // for(int i = 0; i < NUM_CHARS; i++){
  //   if(currNode->branch[i] != nullptr){
  //     hasNext = true;
  //     break;
  //   }
  // }
  if(currNode->numNonNullBranches > 0) hasNext = true;
  if(!multiple && hasNext){   //word is a prefix, dont delete
    currNode->isWord = false;
  }
  if(!multiple && !hasNext){   //word is not a prefix, delete till del_depth
    currNode = root;
    for(int i = 0; i < len; i++){
      char ch = tolower(wordInName.at(i));
      int index = (int)(ch) -(int)('a');
      TrieNode* nextnode = currNode->branch[index];
      if(i == del_depth-1){
        currNode->branch[index] = nullptr;
        currNode->numNonNullBranches -= 1;
      }
      if(i >= del_depth){
        if(i == 0){
          currNode->branch[index] = nullptr;
          currNode->numNonNullBranches -= 1;
        }
        else{
          delete currNode;
        }
      }
      currNode = nextnode;
    }
  }
  return true;
}

listOfObjects<string>* Trie::completions(string prefix) {  //does this take a word as an input o a prefic of the word?
  TrieNode *currNode = root;
  int len = prefix.length();
  listOfObjects<string> *currCompletions = nullptr;

  // Insert your code here
  for(int i = 0; i < len; i++){     
    char ch = tolower(prefix.at(i));
    int index = (int)(ch) -(int)('a');
    if(currNode->branch[index] == nullptr){
      cout << "Word not present in trie" << endl;
      return nullptr;
    }
    currNode = currNode->branch[index];
  }
  recursiveAddCompletions(currNode, currCompletions);
  
  return currCompletions;

  
}

bool Trie::recursiveAddCompletions(TrieNode *node, listOfObjects<string>* &currCompletions){
  
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

bool Trie::addCompletions(TrieNode *node, listOfObjects<string>* &currCompletions) {
  //the function declaration has been changed to passing pointer by reference to take care of the case when currCompletions is a nullptr
  // Insert your code here
  assert(node->isWord);     //add completions only when you are at a word node
  listOfObjects<string>* trav = currCompletions;
  if(trav != nullptr){
    while(trav->next != nullptr){
      trav = trav->next;
    }
  }
  listOfObjects<int>* temp_ind = node->indices;
  
  while(temp_ind != nullptr){    //append the strings corresponding to indices to currCompletions
    string name = nameDict->getKeyAtIndex(temp_ind->object);  //find the string corresponding to iindex
    if(!isPresentInCompletions(currCompletions, name)){   //check if the word is already present
      if(currCompletions == nullptr){   //make a currCompletions list
        currCompletions = new listOfObjects<string>(name);
        trav = currCompletions;
        temp_ind = temp_ind->next;
        continue;
      }
      trav->next = new listOfObjects<string>(name);
    }
    temp_ind = temp_ind->next;
    trav = trav->next;
  }

  return true;
}

bool Trie::isPresentInCompletions(listOfObjects<string> *completions, string name) { //checks if name is already present in comletions
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


#endif
