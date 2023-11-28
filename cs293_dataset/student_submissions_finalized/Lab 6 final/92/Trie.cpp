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

bool Trie::insert(string wordInName, int indexOfName) {//insert function
  TrieNode *currNode = root;//insert function
  int len = wordInName.length();//insert function
  if(!isPresent(wordInName)){//insert function
  for(int i=0;i<len;i++){//insert function
    currNode->numNonNullBranches=currNode->numNonNullBranches+1;//insert function
    if(currNode->branch[int(wordInName[i])-65]==NULL){//insert function
      currNode->branch[int(wordInName[i])-65]=new TrieNode();}//insert function
    currNode=currNode->branch[int(wordInName[i])-65];//insert function
  }//insert function
  currNode->isWord=1;//insert function
  if(currNode->indices!=NULL){//insert function
    while(currNode->indices->next!=NULL){//insert function
      currNode->indices=currNode->indices->next;//insert function
    }//insert function
    currNode->indices->next=new listOfObjects<int>(indexOfName);//insert function
    return 1;//insert function
  }
  else{//insert function
    currNode->indices=new listOfObjects<int>(indexOfName);//insert function
    return 1;//insert function
  }}
  // Insert your code here
  else{
    for(int i=0;i<len;i++){
      currNode=currNode->branch[int(wordInName[i])-65];
    }
    if(currNode->indices!=NULL){
      while(currNode->indices->next!=NULL){
        currNode->indices=currNode->indices->next;
      }
      currNode->indices->next=new listOfObjects<int>(indexOfName);
    return 1;}
  
  else{currNode->indices=new listOfObjects<int>(indexOfName);
  return 1;}}
}

bool Trie::del(string wordInName, string name) {
  TrieNode *currNode = root;
  TrieNode *lastBranchNode = nullptr;
  int lastBranchChar = -1;
  int len = wordInName.length();

  // Insert your code here
  return false;
}

listOfObjects<string> * Trie::completions(string prefix) {
  TrieNode *currNode = root;
  int len = prefix.length();
  listOfObjects<string> *currCompletions = nullptr;
  for(int i=0;i<len;i++){
    if(currNode->branch[int(prefix[i])-65]!=nullptr){ currNode=currNode->branch[int(prefix[i])-65];}
    else{return nullptr;}}
  recursiveAddCompletions(currNode,currCompletions);
  return currCompletions;}

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
bool Trie::addCompletions(TrieNode * start1, listOfObjects<string> * &store) {
  TrieNode *start=start1;
  listOfObjects<int>* want=start1->indices;
  if(start->numNonNullBranches==0){
    while(start->indices!=nullptr){
      if(store!=nullptr){
        while(store->next!=nullptr){store=store->next;}
        store->next=new listOfObjects<string>(nameDict->getKeyAtIndex(start->indices->object));
        start->indices=start->indices->next;}
      else{store=new listOfObjects<string>(nameDict->getKeyAtIndex(start->indices->object));
        start->indices=start->indices->next;}}
    start1->indices=want;
    return true;}
  else{while(start->indices!=nullptr){
      if(store!=nullptr){
        while(store->next!=nullptr){store=store->next;}
        store->next=new listOfObjects<string>(nameDict->getKeyAtIndex(start->indices->object));
        start->indices=start->indices->next;}
      else{store=new listOfObjects<string>(nameDict->getKeyAtIndex(start->indices->object));
        start->indices=start->indices->next;}}
    start1->indices=want;
    return true;}}}

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
