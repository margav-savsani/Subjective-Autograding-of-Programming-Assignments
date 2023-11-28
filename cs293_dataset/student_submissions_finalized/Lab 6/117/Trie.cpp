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

bool Trie::insert(string wordInName, int indexOfName) {// branch[number n]  indicates the letter with ascii code 97 + n
  TrieNode *currNode = root;
  int len = wordInName.length();
  for(int i = 0; i < len; i++){// go down till last branch and if a branch is null, create it while going down
    
    if(currNode->branch[tolower(wordInName[i])-97] == nullptr){ 
      currNode->branch[tolower(wordInName[i])-97] = new TrieNode();
      currNode->numNonNullBranches++;  
    }
    currNode = currNode->branch[tolower(wordInName[i])-97];
  }
  currNode->isWord = true;// set isWord to true as now a word ends here
  listOfObjects<int>* insert = currNode->indices;// linked list, storing the indices
  while(insert!= nullptr) insert = insert->next;// stores indices recursively
  insert = new listOfObjects(indexOfName);// store new index
  return true;
}

bool Trie::del(string wordInName, string name) {// Karna baaki hai
  TrieNode *currNode = root;
  TrieNode *lastBranchNode = nullptr;
  TrieNode *branchToBeDeleted = nullptr;
  int lastBranchChar = -1;
  int len = wordInName.length();
  for(int i = 0; i < len; i++){
    if(currNode->branch[tolower(wordInName[i])-97] == nullptr) return false;
    lastBranchNode = currNode;
    currNode = currNode->branch[tolower(wordInName[i])-97];
    lastBranchChar = tolower(wordInName[i])-97;//a indicates 0, b->1 and so on till z->25
    if(lastBranchNode->numNonNullBranches != 1 && currNode->numNonNullBranches == 1){
      branchToBeDeleted = currNode;
    }
  }
  // Insert your code here
  return true;
}

listOfObjects<string> * Trie::completions(string prefix) {
  TrieNode *currNode = root;
  int len = prefix.length();
  listOfObjects<string> *currCompletions = nullptr;

  // Insert your code here
  return currCompletions;
  
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
  return false;
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


#endif
