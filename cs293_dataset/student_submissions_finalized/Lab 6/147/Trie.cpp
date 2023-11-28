#ifndef TRIE_CPP
#define TRIE_CPP

#include "std_headers.h"
#include "dictionary.h"
#include "Trie.h"
using namespace std;

#define forBranch for(int i = 0; i < NUM_CHARS; i++)

Trie::Trie(Dictionary<int> *nameToIndex): nameDict(nameToIndex), root(new TrieNode){
  if (root == nullptr) {
    cout << "Memory allocation failure." << endl;
    exit(-1);
  }
}

Trie::~Trie() {
  recursiveDelete(root);
}

void Trie::recursiveDelete(TrieNode *node) {
  if (node == nullptr) return;

  for (int i = 0; i < NUM_CHARS; i++) {
      recursiveDelete(node->branch[i]); // delete the ith branch for node.
      node->branch[i] = nullptr; // prevent us from accessing ahead of node->branch[i] even by mistake.
  }
  delete node; // removed the if (node != root) condition since we must delete root as well.
  return;
}

// insert the word wordInName which is part of the string indexed by indexOfName.
bool Trie::insert(const string &wordInName, int indexOfName) {
  TrieNode *currNode = root;

  // Insert your code here
  for (int i = 0; i < wordInName.length(); i++){
      TrieNode *parent = currNode;
      currNode = currNode->branch[wordInName[i] - 'a'];
      if (!currNode){
          parent->numNonNullBranches++;
          currNode = new TrieNode; // Basically, add nodes as required, and reuse if available.
      }
  }
  currNode->isWord = true; // the square node in the lectures. Demarcates the end of a word.
  if (currNode->indices) currNode->indices->insert(indexOfName);
  else currNode->indices = new listOfObjects<int>(indexOfName);
  return true;
}

bool Trie::del(const string &wordInName, const string &name) {
  TrieNode *currNode = root;
  TrieNode *lastBranchNode = nullptr;
  int lastBranchChar = -1;
  int len = wordInName.length();

  // we go down the tree with the path specified by the word, and delete all TrieNodes which have just the one branch from them (just the one word from now on) i.e. numNonNullBranches=1
  for (char c: wordInName){
      currNode = currNode->branch[c - 'a'];
      if (!currNode) return false; // the word is not found (some branch is empty)
      if (currNode->numNonNullBranches == 1) break;
  }
  delete currNode;
  return true;
}

listOfObjects<string> * Trie::completions(const string &prefix) {
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

bool Trie::isPresentInCompletions(listOfObjects<string> *completions, const string &name) {
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

bool Trie::isPresent(const string &wordInName) {
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
