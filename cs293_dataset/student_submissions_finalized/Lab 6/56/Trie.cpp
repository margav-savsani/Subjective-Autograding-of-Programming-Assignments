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
void insert_in_lists(const T &obj, listOfObjects<T>* &l){   //what if the same index is being inserted twice? think about it
  listOfObjects<T> *currIndex = l;
    
    while (currIndex->next != nullptr) {
      if(currIndex->object == obj){
        return;
      }
      currIndex = currIndex->next;
    }
    if(currIndex->object == obj){
      return;
    }
    currIndex->next = new listOfObjects<T>(obj);
}

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
  for(int i = 0; i < len; i++){
    char ch = tolower(wordInName.at(i));
    int index = (int)(ch) -(int)('a');
    if(currNode->branch[index] != nullptr){
      currNode = currNode->branch[index];
    }
    else{
      currNode->numNonNullBranches += 1;
      currNode->branch[index] = new TrieNode();
      currNode = currNode->branch[index];
    }
  }
  currNode->isWord = true;
  if(currNode->indices == nullptr){
      currNode->indices = new listOfObjects<int>(indexOfName);
      return;
  }
  insert_in_lists(indexOfName, currNode->indices);
  return true;    //when does an insertion fail?
}

bool Trie::del(string wordInName, string name) {
  TrieNode *currNode = root;
  TrieNode *lastBranchNode = nullptr;
  int lastBranchChar = -1;
  int len = wordInName.length();

  // Insert your code here
  return false;
}

listOfObjects<string>* Trie::completions(string prefix) {
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
  if(!currNode->isWord){
    cout << "Unexpected error: Word not complete" << endl;
    return nullptr;
  }
  listOfObjects<int>* trav_indices = currNode->indices;
  while(trav_indices != nullptr){
    if(currCompletions == nullptr){
      currCompletions = new listOfObjects<string>(nameDict->getKeyAtIndex(trav_indices->object));
      continue;    
    }
    insert_in_lists(nameDict->getKeyAtIndex(trav_indices->object), currCompletions);
    trav_indices = trav_indices->next;
  }
  return currCompletions;
  
}

bool Trie::recursiveAddCompletions(TrieNode *node, listOfObjects<string> *currCompletions){
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
  assert(node->isWord);
  if(currCompletions == nullptr){
    return false;
  }
  listOfObjects<string>* trav = currCompletions;
  while(trav->next != nullptr){
    trav = trav->next;
  }
  listOfObjects<int>* temp_ind = node->indices;
  if(temp_ind == nullptr){
    return false;
  }
  // while(temp_ind != nullptr){
  //   trav->object = 
  // }

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


#endif
