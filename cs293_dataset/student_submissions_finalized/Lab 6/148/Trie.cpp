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

int index(char c){
    return tolower(c)-'a';
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

  for (int i = 0; i < len; i++) {
          if(currNode->branch[index(wordInName[i])] == nullptr){
                  // First time encountered this pattern, need to make a new node
                  currNode->branch[index(wordInName[i])] = new TrieNode();
                  currNode->numNonNullBranches += 1;
          }
          // Update currNode
          currNode = currNode->branch[index(wordInName[i])];
  }
  currNode->isWord = true;
  //Add indexOfName to the end of indices
    
 listOfObjects<int> *list = currNode->indices;
 // Traverse the linked list
 if (list == nullptr){
    currNode->indices = new listOfObjects<int>(indexOfName);
    return true;
 }
 while(list->next!=nullptr){
    list = list->next;
 } 
 // Append at the end
 list->next = new listOfObjects<int>(indexOfName);
  return false;
}

bool Trie::del(string wordInName, string name) {
  TrieNode *currNode = root;
  TrieNode *lastBranchNode = nullptr;
  int lastBranchChar = -1;
  int len = wordInName.length();

  // Insert your code here
  for (int i = 0; i < len; i++) {
        currNode = currNode->branch[index(wordInName[i])];
        if(currNode == nullptr){
                // Prefix not found :(
                return false;
        }
  }
 listOfObjects<int> *list = currNode->indices;
 // Traverse the linked list
    if(nameDict->getKeyAtIndex(list->object) == name){
        currNode->indices = list->next;
        delete list;
        return true; 
    }
 while(list->next!=nullptr){
    if(nameDict->getKeyAtIndex(list->next->object) == name){
        delete list->next;
        list->next = list->next->next;
        
        return true;
    }
    list = list->next;
 } 

    if(nameDict->getKeyAtIndex(list->object) == name){
        currNode->indices = list->next;
        delete list;
        return true; 
    }
  // Traverse the linked list in currNode and delete our string if present

  return false;
}


listOfObjects<string> * Trie::completions(string prefix) {
  TrieNode *currNode = root;
  int len = prefix.length();
  listOfObjects<string> *currCompletions = nullptr;

  // Insert your code here
  for (int i = 0; i < len; i++) {
        currNode = currNode->branch[index(prefix[i])];
        if(currNode == nullptr){
                // Prefix not found :(
                return nullptr;
        }
  }
  recursiveAddCompletions(currNode, currCompletions);
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
  // adds the indices stored in node into the currCompletions list
  // Insert your code here
  if(!node->isWord) return false; // Can't add if not a word
  bool wasEmptyOriginally = false;
  listOfObjects<string> *starting = currCompletions;
  if(currCompletions == nullptr){
    currCompletions = new listOfObjects<string>(""); 
    wasEmptyOriginally = true;
    starting = currCompletions;
  }
  while(currCompletions->next != nullptr){
    currCompletions = currCompletions->next;
  }

  listOfObjects<int> *storedIndex = node->indices;
  while(storedIndex != nullptr){
    currCompletions->next = new listOfObjects<string>(nameDict->getKeyAtIndex(storedIndex->object));
    currCompletions->next = currCompletions->next;
    storedIndex = storedIndex->next;
  }
  if(wasEmptyOriginally){
          currCompletions = starting->next;
          delete starting;
  }
  else{
        currCompletions = starting;
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


#endif
