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
  for(int i=0; i<len; i++){
    int letter=toupper(wordInName.at(i))-'A';
    if(currNode->branch[letter]==NULL){
      currNode->branch[letter]=new TrieNode();
      if(currNode->branch[letter]==NULL){
        return false;
      }
      currNode->numNonNullBranches++;
      currNode=currNode->branch[letter];
    }
    else{
      currNode=currNode->branch[letter];     
    }
  }
  currNode->isWord=true;
  listOfObjects<int> *a;
  a=new listOfObjects<int>(indexOfName);
  listOfObjects<int> *p=currNode->indices;
  currNode->indices=a;
  a->next=p;
  return true;
}

bool Trie::del(string wordInName, string name) {
  TrieNode *currNode = root;
  TrieNode *lastBranchNode = nullptr;
  int lastBranchChar = -1;
  int len = wordInName.length();
  TrieNode* a;
  TrieNode* b;
  a=root;
  b=root;
  int k=0;
  int l=0;

  for(int i=0; i<len; i++){
    if(currNode->branch[toupper(wordInName.at(i))-'A']==NULL){
      return false;
    }
    if(currNode->numNonNullBranches>1){
      a=currNode;
      k=i;
    }
    if(currNode->isWord==true && i!=len-1){
      b=currNode;
      l=i;
    }
    currNode=currNode->branch[toupper(wordInName.at(i))-'A'];
  }

  if(currNode->isWord){
    listOfObjects<int>* p=currNode->indices;
    if(nameDict->getKeyAtIndex(p->object)==name){
      currNode->indices=currNode->indices->next;
    }
    else{
      while(p->next!=NULL){
        if(nameDict->getKeyAtIndex(p->next->object)==name){
          p->next=p->next->next;
          break;
        }
        p=p->next;
      }
    }
  }

  if(currNode->indices==NULL){
    if(currNode->numNonNullBranches==0){
      if(k>l){
        a->branch[toupper(wordInName[k])-'A']=nullptr;
        a->numNonNullBranches--;
      }
      if(l>=k){
        b->branch[toupper(wordInName[l])-'A']=nullptr;
        b->numNonNullBranches--;
      }
    }
    else{
      currNode->isWord=false;
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
  for(int i=0; i<len; i++){
    if(currNode->branch[toupper(prefix.at(i))-'A']==NULL){
      return NULL;
    }
    currNode=currNode->branch[toupper(prefix.at(i))-'A'];
  }
  
  currCompletions=new listOfObjects<string>("nnk");
  recursiveAddCompletions(currNode, currCompletions);
  return currCompletions->next;
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
  listOfObjects<int> *indi;
  indi=node->indices;
  while(indi!=NULL){
    listOfObjects<string>*cur=currCompletions->next;
    listOfObjects<string> *b;
    b=new listOfObjects<string>(nameDict->getKeyAtIndex(indi->object));
    currCompletions->next=b;
    b->next=cur;
    indi=indi->next;
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
