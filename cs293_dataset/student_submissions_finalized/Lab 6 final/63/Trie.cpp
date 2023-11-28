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
/**
 * @brief inserts a word to the trie
 * 
 * For example, suppose we insert Secuderabad Junction,
 * First insert(Secunderabad, #hash value) is called then insert(Junction, #hash value) is called.
 * Insert inserts individual words to the trie
 * @param wordInName 
 * @param indexOfName 
 * @return true if successful
 * @return false if fails
 */
bool Trie::insert(string wordInName, int indexOfName) {
  TrieNode *currNode = root;
  int len = wordInName.length();
  if (len == 0){
    return false;
  }
  else if (len == 1){       // base case
    int i = toupper(wordInName.at(0)) - 'A';
    if (root->branch[i] != nullptr){    // if branch is not empty
      if (!root->branch[i]->isWord){
        root->branch[i]->isWord = true;
        root->branch[i]->indices = new listOfObjects<int>(indexOfName);
      }
      else{
        listOfObjects<int> * B = root->branch[i]->indices;
        if (B == nullptr){
          root->branch[i]->indices = new listOfObjects<int>(indexOfName);
          root->branch[i]->isWord = 1;
          return 1;
        }
        while (B->next != nullptr){
          if (B->object == indexOfName){
            return 1;
          } 
          B = B->next;        
        }

        B->next = new listOfObjects<int>(indexOfName);
      }
      return 1;
    }
    // if branch is empty, we create a new branch
    TrieNode * B = new TrieNode();
    B->indices = new listOfObjects<int>(indexOfName);
    B->isWord = true;
    root->numNonNullBranches += 1;
    root->branch[i] = B;
    return 1;
  }
  else {    // recursive calls
    int i = toupper(wordInName.at(0)) - 'A';
    if (root->branch[i] == nullptr){
      root->numNonNullBranches += 1;
      TrieNode * B = new TrieNode();
      root->branch[i] = B;
      root = B;
      bool b = insert(wordInName.substr(1, len-1), indexOfName);
      root = currNode;
      return b;
    }
    else {
      int i = toupper(wordInName.at(0)) - 'A';
      root = root->branch[i];
      bool b = insert(wordInName.substr(1, len-1), indexOfName);  // recursive call
      root = currNode;
      return b;
    }
  }
  cout << "Some error occured" << endl;
  return false;
}
/**
 * @brief deletes a station from the trie
 * 
 * @param wordInName 
 * @param name 
 * @return true if successful
 * @return false if fails
 */
bool Trie::del(string wordInName, string name) {
  TrieNode *currNode = root;
  TrieNode *lastBranchNode = nullptr;
  int lastBranchChar = -1;
  int len = wordInName.length();
  int i = toupper(wordInName.at(0)) - 'A';
  if (len > 1){     // recursive calls
    root = root->branch[i];
    del(wordInName.substr(1, len-1), name);
    if (root->numNonNullBranches == 0 && !root->isWord){  
      /*if the branch doesn't have any word endings or further branches,
      cut it off! */     
      currNode->branch[i] = nullptr;
      currNode->numNonNullBranches -= 1;    
    }
    root = currNode;
    return 1;
  }
  else if (len == 1){   // base case
    listOfObjects<int>* A = root->branch[i]->indices;
    listOfObjects<int>* B = nullptr;
    while (A != nullptr){
      if (nameDict->getKeyAtIndex(A->object) == name){
        if (B == nullptr){
          root->branch[i]->isWord = 0;
          root->branch[i]->indices = A->next;
          if (root->branch[i]->numNonNullBranches == 0){
            root->branch[i] = nullptr;
            root->numNonNullBranches -= 1;
          }
          return 1;
        }
        B->next = A->next;
        delete A;
        return 1;
      }
      B = A;
      A = A->next;
    }
  }
  return 0;
}
/**
 * @brief Given a prefix returns a list of all completions
 * 
 * @param prefix 
 * @return listOfObjects<string>* 
 */
listOfObjects<string> * Trie::completions(string prefix) {
  /* in this function we assemble the code present in addCompletions and recursiveAddCompletions */
  TrieNode *currNode = root;
  int len = prefix.length();
  listOfObjects<string> *currCompletions = nullptr;
  if (len == 0){    // base case
    currCompletions = new listOfObjects<string>("");    // passing a nullpointer to recursiveAddCompletions causes problems...
    recursiveAddCompletions(root, currCompletions);   
    listOfObjects<string> * C = currCompletions;
    while (C->next->object != ""){
      C = C->next;
    }
    delete C->next;
    C->next = nullptr;
  }
  else{       // recursive calls
    int i = toupper(prefix.at(0)) - 'A';
    root = root->branch[i];
    currCompletions = completions(prefix.substr(1, len-1));
    root = currNode;
  }
  return currCompletions;
}
/**
 * @brief adds the completions from a given node to the list of completions
 * 
 * @param node 
 * @param currCompletions 
 * @return true 
 * @return false 
 */
bool Trie::recursiveAddCompletions(TrieNode *node, listOfObjects<string> *currCompletions) {
  if (node == nullptr){
    return 1;
  }
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
/**
 * @brief adds the completions in the current node to the list
 * 
 * @param node 
 * @param currCompletions 
 * @return true 
 * @return false 
 */
bool Trie::addCompletions(TrieNode *node, listOfObjects<string> *currCompletions) {

  if (!node->isWord){
    return false;
  }
  listOfObjects<string> *A = currCompletions;
  while (A->next != nullptr){
    A = A->next;
  }
  listOfObjects<int> * B = node->indices;
  while (B != nullptr){
    A->object = nameDict->getKeyAtIndex(B->object);
    A->next = new listOfObjects<string>("");
    A = A->next; 
    B = B->next;
  }
  return 1;
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
