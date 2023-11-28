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
  if(len==0) return false;
  if(root->branch[wordInName[0]-65]==NULL){
    root->branch[wordInName[0]-65] = new TrieNode();
    root->numNonNullBranches++;
    if(len==1){
      root->branch[wordInName[0]-65]->isWord=true;
      root->branch[wordInName[0]-65]->indices = new listOfObjects<int>(indexOfName);
    }
    else{
      root = root->branch[wordInName[0]-65];
      insert(wordInName.substr(1,wordInName.length()-1),indexOfName);
    }
  }
  else if(!root->branch[wordInName[0]-65]->isWord){
    if(len==1){
      root->branch[wordInName[0]-65]->isWord=true;
      root->branch[wordInName[0]-65]->indices = new listOfObjects<int>(indexOfName);
    }
    else{
      root = root->branch[wordInName[0]-65];
      insert(wordInName.substr(1,wordInName.length()-1),indexOfName);
    }
  }
  else{
    if(len==1){
      listOfObjects<int>* nextptr = root->branch[wordInName[0]-65]->indices;
      while(nextptr->next!=NULL){
        nextptr = nextptr->next;
      }
      nextptr->next = new listOfObjects<int>(indexOfName);
    }
    else{
      root = root->branch[wordInName[0]-65];
      insert(wordInName.substr(1,wordInName.length()-1),indexOfName);
    }
  }
  root = currNode;
  return true;
}

bool Trie::del(string wordInName, string name) {
  TrieNode *currNode = root;
  TrieNode *lastBranchNode = root;
  int lastBranchChar = -1;
  int len = wordInName.length();
  for(int i = 0; i<wordInName.length(); i++){
    if(root->branch[wordInName[i]-65]==NULL) return false;
    root = root->branch[wordInName[i]-65];
    if(i!=wordInName.length()-1){
      if(root->numNonNullBranches>1||root->isWord){
        lastBranchChar = i;
        lastBranchNode = root;
      }
    }
    else{
      if(root->numNonNullBranches>0||root->indices->next!=NULL){
        lastBranchChar = i;
        lastBranchNode = root;
      }
    }
  }
  if(root->indices->next==NULL){
    root->isWord=false;
    delete root->indices;
    root->indices = NULL;
  }
  else{
    listOfObjects<int>* one = root->indices;
    listOfObjects<int>* two = root->indices->next;
    if(nameDict->getKeyAtIndex(one->object)==name){
      root->indices = two;
      delete one;
    }
    else{
      while(nameDict->getKeyAtIndex(two->object)!=name){
        one = one->next;
        two = two->next;
      }
      one->next = two->next;
      delete two;
    }
  }
  root = lastBranchNode;
  root->branch[wordInName[lastBranchChar+1]-65]=NULL;
  root = currNode;
  return true;
}

listOfObjects<string> * Trie::completions(string prefix) {
  TrieNode *currNode = root;
  int len = prefix.length();
  listOfObjects<string> *currCompletions = new listOfObjects<string>("");
  if(len==0) return NULL;
  if(len==1){
    if(root->branch[prefix[0]-65]==NULL) return NULL;
    recursiveAddCompletions(root->branch[prefix[0]-65], currCompletions);
  }
  else{
    if(root->branch[prefix[0]-65]==NULL) return NULL;
    root = root->branch[prefix[0]-65];
    delete currCompletions;
    currCompletions = completions(prefix.substr(1,prefix.length()-1));
  }
  root = currNode;
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
  listOfObjects<string>* initial = currCompletions;
  listOfObjects<int>* words = node->indices;
  if(currCompletions->object!=""){
    while(currCompletions->next!=NULL){
      currCompletions = currCompletions->next;
    }
  }
  else{
    currCompletions->object = nameDict->getKeyAtIndex(words->object);
    words = words->next;
  }
  while(words!=NULL){
    currCompletions->next = new listOfObjects<string>(nameDict->getKeyAtIndex(words->object));
    words = words->next;
    currCompletions = currCompletions->next;
  }
  currCompletions = initial;
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
