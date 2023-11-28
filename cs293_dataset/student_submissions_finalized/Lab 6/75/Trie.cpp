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
  int index = 0;
  bool newWord = false;

  for(int i = 0; i < len; i++){
    index = wordInName[i] - 'a';
    if (currNode -> branch[index] == NULL){ // the node corresponding to the current alphabet is not present in the trie
      currNode->branch[index] = new TrieNode; // creating a new node at the specific index if not already present
      currNode->numNonNullBranches++;// increment the number of branches from that node
      newWord = true;
    }

    currNode = currNode->branch[index]; // going to the next node
  }
  currNode->isWord = true;// to indicate that the word hasended at this node
  // update the listOfIndices to store the index to the full name of the station in the dictionary

  listOfObjects<int>* newNode = new listOfObjects<int>(indexOfName);
  newNode->next = currNode->indices;
  currNode->indices = newNode;

  return newWord;
}

bool Trie::del(string wordInName, string name) {
  TrieNode *currNode = root;
  TrieNode *lastBranchNode = nullptr;
  int lastBranchChar = -1;
  int len = wordInName.length();
  int index = 0;
  bool newWord = false;


  if (currNode == NULL){
    return false;
  }

  for (int i = 0; i<len;i++){
    index = wordInName[i] - 'a';
    if (currNode -> branch[index] == NULL){ // the node corresponding to the current alphabet is not present in the trie
      return false; // the word is not present in the trie
    }
    if (currNode->numNonNullBranches>1){
      lastBranchNode = currNode; // to store the node, which has the last branch corresponding to the word to be deleted
      lastBranchChar = index; // to store the last common alphabet that the word to be deleted has i common with the other branches
    }
    currNode = currNode->branch[index]; // going to the next node
  }

  // Two cases are possible - either the word to be delete has a unique branch at the end or it is a prefix to some other branch
  if (currNode->numNonNullBranches>=0){ // The given word is prefix to other word

  }
  else { // The given word has seperate branch corresponding to it at the end

  }

  // Update the number of indices stored in that node (or leaf)
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
