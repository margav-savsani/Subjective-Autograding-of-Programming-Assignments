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
  for(int i=0;i<len;i++){
    int j = toupper(wordInName[i]) - 'A';
    if(currNode->branch[j] == nullptr){
      currNode->numNonNullBranches++;
      currNode->branch[j]=new TrieNode();
    }
    currNode=currNode->branch[j];
  }
  currNode->isWord=true;
  listOfObjects<int> *temp;
  if(currNode->indices == nullptr){
    currNode->indices = new listOfObjects<int> (indexOfName);
    return true;
  }
  else{
    listOfObjects<int>* temp = new listOfObjects<int>(indexOfName);
    temp->next = currNode->indices;
    currNode->indices = temp;
    return true;
  }
  return true;
}

bool Trie::del(string wordInName, string name) {
  TrieNode *currNode = root;
  TrieNode *lastBranchNode = nullptr;
  int lastBranchChar = -1;
  int len = wordInName.length();
  // Insert your code here
  int indexOfName = nameDict->hashValue(wordInName);
  int k = toupper(wordInName[0])-'A';
  bool Boolean; 
  for(int i=0;i<len;i++){
    int j = toupper(wordInName[i]) - 'A';
    if(currNode->numNonNullBranches > 1 && !Boolean){
      lastBranchNode=currNode;
      lastBranchChar=j;
    }
    if(currNode->isWord){
      lastBranchNode=currNode;
      lastBranchChar=j;
      Boolean = true;
    }
    if(currNode->branch[j] == nullptr){
      return false;
    }
    currNode=currNode->branch[j];
  }
  if(currNode->indices->next==nullptr){
    if(lastBranchNode==nullptr){
      root->branch[k]=nullptr;
    }
    else{
      lastBranchNode->branch[lastBranchChar]=nullptr;
      lastBranchNode->numNonNullBranches--;
    }
  }
   
  listOfObjects<int>* I = currNode->indices;
  listOfObjects<int>* temp = nullptr;
  while(I!=nullptr){
    if(nameDict->getKeyAtIndex(I->object)==name){
      if(temp == nullptr){
        currNode->indices = I->next;
        if(I->next == nullptr){currNode->isWord=false;}
        return true;
      }
      temp->next=I->next;
      return true;
    }
    temp=I;
    I=I->next;
  }
  
  return false;
}

listOfObjects<string> * Trie::completions(string prefix) {
  TrieNode *currNode = root;
  int len = prefix.length();
  listOfObjects<string> currCompletions("");
  // Insert your code here
  for(int i=0;i<len;i++){
    int j = toupper(prefix[i]) - 'A';
    if(currNode->branch[j] == nullptr){
      return nullptr;
    }
    currNode=currNode->branch[j];
  }
  recursiveAddCompletions(currNode,&currCompletions);
  return currCompletions.next;
  
}

bool Trie::recursiveAddCompletions(TrieNode *node, listOfObjects<string> *currCompletions) {
  if (node->isWord) {
    if(!addCompletions(node, currCompletions)){
      return false;
    };
  }
  TrieNode *currNode = node;
  for (int i = 0; i < NUM_CHARS; i++) {
    if (currNode->branch[i] != nullptr) {
      if(!recursiveAddCompletions(currNode->branch[i], currCompletions)){
        return false;
      };
      }
    }
  return true;
}

bool Trie::addCompletions(TrieNode *node, listOfObjects<string> *currCompletions) {
  // Insert your code here
  listOfObjects<string>* X = currCompletions;
  while(X->next != nullptr){
    X=X->next;
  }
  listOfObjects<int>* Y = node->indices;
  while(Y != nullptr){ 
    X->next = new listOfObjects<string>(nameDict->getKeyAtIndex(Y->object));
    Y = Y->next;
    X = X->next;
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
