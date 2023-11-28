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
  int i=0;
  while(i < len){
    wordInName[i] = toupper(wordInName[i]);
    if (currNode->branch[int(wordInName[i]) - 'A'] == nullptr){ 
      currNode->numNonNullBranches++;
      currNode->branch[int(wordInName[i]) - 'A'] = new TrieNode();
    }
    currNode = currNode->branch[int(wordInName[i]) -'A'];
    i++;
  }
  currNode->isWord = true;
  listOfObjects<int> *index;
  index = new listOfObjects<int>(indexOfName);
  index->next = currNode->indices;
  currNode->indices = index;
  return true;
}

bool Trie::del(string wordInName, string name) {
  TrieNode *currNode = root;
  TrieNode *lastBranchNode = nullptr;
  int lastBranchChar = -1;
  int len = wordInName.length(), i=0;
  while (i < len){
    wordInName[i] = toupper(wordInName[i]);
    currNode = currNode->branch[int(wordInName[i]) - 'A'];
    i++;
  }
  listOfObjects<int> *ind, *newInd;
  ind = currNode->indices;
  newInd = nullptr;
  bool found = false;
  int f=0;
  while(ind != nullptr){
    if (nameDict->getKeyAtIndex(ind->object) == name){
      found = true;
      ind = ind->next;
      break;
    }
    ind = ind->next;
    f++;
  }
  if (found) {
    if ((ind == nullptr) && (f==0)){
      currNode->isWord = false; 
    }
    return true;
  }
  return false;
}

listOfObjects<string> * Trie::completions(string prefix) {
  TrieNode *currNode = root;
  int len = prefix.length(), i=0;
  listOfObjects<string> *currCompletions;
  currCompletions = nullptr;
  while(i<len){
    prefix[i] = toupper(prefix[i]);
    currNode = currNode->branch[int(prefix[i]) - 'A'];
    i++;
  }
  addCompletions(currNode, currCompletions);
  return currCompletions; 
}

/*void * Trie::reccom(TrieNode *someNode, listOfObjects<string> *currCompletions){
  if (someNode != nullptr){
    if (someNode->isWord){
      if(currCompletions != nullptr){
        currCompletions->next = currCompletions;
      }
      currCompletions = new listOfObjects<string>(nameDict->getKeyAtIndex((someNode->indices)->object));
    }
    for (int j=0; j<NUM_CHARS; j++){
      if (someNode->branch[j] != nullptr){
        reccom(someNode->branch[j], currCompletions);
      }
    }
  }
  return;
}*/

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
  if (node == nullptr) { return false; }
  else {
    if (node->isWord){
      listOfObjects<string> *completion;
      completion = new listOfObjects<string>(nameDict->getKeyAtIndex((node->indices)->object));
      completion->next = currCompletions;
      currCompletions = completion;
    }
    for (int j=0; j<NUM_CHARS; j++){
        addCompletions(node->branch[j], currCompletions);
    }
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
