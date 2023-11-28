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

  // Insert your code here
  int i = 0;
  while(i < len){
    //Processing through the Trie till end of the word is reached
    int idx = toupper(wordInName.at(i)) - 'A';
    if(currNode->branch[idx] == nullptr){
      currNode->branch[idx] = new TrieNode();
      currNode->numNonNullBranches++;
    }
    currNode = currNode->branch[idx];
    i++;
  }
  if(!currNode->isWord){
    //Inserting the first index
    currNode->isWord = true;
    currNode->indices = new listOfObjects<int>(indexOfName);
    return true;
  }else{
    //Appending indices to the already existing list
    listOfObjects<int> *myObj = currNode->indices;
    while(myObj->next != nullptr){
      myObj = myObj->next;
    }
    myObj->next = new listOfObjects<int>(indexOfName);
    return true;
  }

  return false;
}

bool Trie::del(string wordInName, string name) {
  TrieNode *currNode = root;
  TrieNode *lastBranchNode = nullptr;
  int lastBranchChar = -1;
  int len = wordInName.length();

  // Insert your code here
  
  if(!isPresent(wordInName))return false;
  int i = 0;
  lastBranchNode = root;
  lastBranchChar = toupper(wordInName.at(i)) - 'A';
  while(i < len){
    int idx = toupper(wordInName.at(i)) - 'A';
    //Updating the last branch characteristics where the node diverges or is a word itself.
    if(currNode->isWord || currNode->numNonNullBranches > 1){
      lastBranchNode = currNode;
      lastBranchChar = idx;
    }
    currNode = currNode->branch[idx];
    i++;
  }
  listOfObjects<int> *myObj = currNode->indices;
  if(nameDict->getKeyAtIndex(myObj->object)==name){
    //Deleting the index if it is the first object to be deleted
    if(myObj->next != nullptr){
      currNode->indices = myObj->next;
      delete myObj;
    }else{
      //Deleting the entire linked list
      delete myObj;
      currNode->indices = nullptr;
      currNode->isWord = false;
      if(currNode->numNonNullBranches == 0){
        //Deleting the entire branch
        recursiveDelete(lastBranchNode->branch[lastBranchChar]);
        lastBranchNode->numNonNullBranches--;
        lastBranchNode->branch[lastBranchChar] = nullptr;
      }
    }
  }else{
    listOfObjects<int> *prevnode = myObj;
    while(nameDict->getKeyAtIndex(myObj->object)!=name){
      //Iterating through the indices till we get required index to be deleted
      prevnode = myObj;
      myObj=myObj->next;
      if(myObj == nullptr)break;
    }
    if(myObj != nullptr){
      //Linking the objects correctly
      prevnode->next = myObj->next;
      delete myObj;
    }
    
  }

  return true;
}

listOfObjects<string> * Trie::completions(string prefix) {
  TrieNode *currNode = root;
  int len = prefix.length();
  listOfObjects<string> *currCompletions = nullptr;

  // Insert your code here
  int i = 0;
  while(i < len){
    //Iterating through the nodes till we reach the last node of the prefix
    int idx = toupper(prefix.at(i)) - 'A';
    if(currNode->branch[idx] == nullptr){
      return currCompletions;
    }
    currNode = currNode->branch[idx];
    i++;
  }

  //Inserting the dummy node in the Linked list
  currCompletions = new listOfObjects<string>("qwerty");

  recursiveAddCompletions(currNode,currCompletions);
  //Returning the list after removing the dummy element
  return currCompletions->next;
  
}

bool Trie::recursiveAddCompletions(TrieNode *node, listOfObjects<string> *currCompletions) {
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

bool Trie::addCompletions(TrieNode *node, listOfObjects<string> *currCompletions) {

  // Insert your code here
  listOfObjects<int> *spot = node->indices; 
  while(spot != nullptr){
    //Appending all station names to the Linked list passed
    int index = spot->object;
    string station = nameDict->getKeyAtIndex(index);
    if(currCompletions == nullptr){
      currCompletions = new listOfObjects<string>(station);
    }else{
      //Appending at the last of the linked list
      listOfObjects<string> *mySt = currCompletions;
      while(mySt->next != nullptr){
        mySt = mySt->next;
      }
      mySt->next = new listOfObjects<string>(station);
    }
    spot = spot->next;
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
