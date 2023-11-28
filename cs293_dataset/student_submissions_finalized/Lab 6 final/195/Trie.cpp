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
  if(!isPresent(wordInName)){
  for(int i=0;i<len;i++){
    currNode->numNonNullBranches=currNode->numNonNullBranches+1;
    if(currNode->branch[int(wordInName[i])-65]==nullptr){
    currNode->branch[int(wordInName[i])-65]=new TrieNode();
    }
    currNode=currNode->branch[int(wordInName[i])-65];
  }
  currNode->isWord=true;
  if(currNode->indices!=nullptr){
  while(currNode->indices->next!=nullptr){
    currNode->indices=currNode->indices->next;
  }
  currNode->indices->next=new listOfObjects<int>(indexOfName);
  return true;
  }
  else{
    currNode->indices=new listOfObjects<int>(indexOfName);
    return true;
  }
  // Insert your code here
  }
else{
  for(int i=0;i<len;i++){
    currNode=currNode->branch[int(wordInName[i])-65];
  }
  if(currNode->indices!=nullptr){
    listOfObjects<int>* curr=currNode->indices;
  while(currNode->indices->next!=nullptr){
    currNode->indices=currNode->indices->next;
  }
  currNode->indices->next=new listOfObjects<int>(indexOfName);
  currNode->indices=curr;
  return true;
  }
  else{
    currNode->indices=new listOfObjects<int>(indexOfName);
    return true;
  }
}
}
bool Trie::del(string wordInName,string name) {
  TrieNode *currNode = root;
  TrieNode *lastBranchNode = nullptr;
  int lastBranchChar = -1;
  int i=0;
  int len = wordInName.length();
  string s=wordInName;
  if(!isPresent(wordInName)){
    return false;
  }
  if(verify(currNode,wordInName)){
    currNode->branch[int(wordInName[0])-65]=nullptr;
    currNode->numNonNullBranches--;
    return true;
  }
  while(i<len){
    int letter=int(wordInName[i])-65;
    currNode=currNode->branch[letter];
    s.erase(0,1);
    if(verify(currNode,s)){
      currNode->branch[int(s[0])-65]=nullptr;
      currNode->numNonNullBranches--;
      return true;
        
    }
    if(i==len-1 && currNode->indices->next!=nullptr){
      lastBranchNode=currNode;
      listOfObjects<int> *indices1;
      if(name==nameDict->getKeyAtIndex(currNode->indices->object)){
        indices1=currNode->indices->next;
        currNode->indices=indices1;
      }
      else{
        indices1=currNode->indices;
        listOfObjects<int> *start=indices1;
        while(nameDict->getKeyAtIndex(indices1->next->object)!=name){
          indices1=indices1->next;
        }
        indices1->next=indices1->next->next;
        currNode->indices=start;
      }
      if(currNode->indices==nullptr){
        currNode->isWord=false;
        return true;
      }
      return true;
    }
    if(i==len-1 && currNode->numNonNullBranches!=0){
      currNode->isWord=false;
      currNode->indices=nullptr;
      return true;
    }
    i++;
    }
  }
bool Trie::verify(TrieNode *curr,string s){
  int len=s.length();
  TrieNode* t=curr->branch[int(s[0])-65];
  int i=0;
  while(i<len){
    if(t->numNonNullBranches>1 && i<len-1){
      return false;
    }
    else if(i==len-1 && t->numNonNullBranches>0 || i==len-1 && t->indices->next!=nullptr){
      return false;
    }
    else if(i!=len-1){
      t=t->branch[int(s[i+1])-65];
    }
    else{
      return true;
    }
    i++;
  }
}
void Trie::words(TrieNode* start,listOfObjects<string>* store){
  if(start->numNonNullBranches==0){
    while(start->indices!=nullptr){
      if(store!=nullptr){
        while(store->next!=nullptr){
          store=store->next;
        }
        store->next=new listOfObjects<string>(nameDict->getKeyAtIndex(start->indices->object));
        start->indices=start->indices->next;
      }
      else{
        store=new listOfObjects<string>(nameDict->getKeyAtIndex(start->indices->object));
        start->indices=start->indices->next;
      }
    }
    return;
  }
  else{
    for(int i=0;i<26;i++){
      if(start->branch[i]!=nullptr){
        words(start->branch[i],store);
      }
    }
    return;
  }
}
listOfObjects<string> * Trie::completions(string prefix) {
  TrieNode *currNode = root;
  int len = prefix.length();
  listOfObjects<string> *currCompletions = nullptr;
  for(int i=0;i<len;i++){
    if(currNode->branch[int(prefix[i])-65]!=nullptr){
      currNode=currNode->branch[int(prefix[i])-65];
    }
    else{
      return nullptr;
    }
  }
  recursiveAddCompletions(currNode,currCompletions);
  // Insert your code here
  return currCompletions;
  
}

bool Trie::recursiveAddCompletions(TrieNode * node, listOfObjects<string> * &currCompletions) {
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

bool Trie::addCompletions(TrieNode * start1, listOfObjects<string> * &store) {
  TrieNode *start=start1;
  listOfObjects<int>* want=start1->indices;
  if(start->numNonNullBranches==0){
    while(start->indices!=nullptr){
      if(store!=nullptr){
        while(store->next!=nullptr){
          store=store->next;
        }
        store->next=new listOfObjects<string>(nameDict->getKeyAtIndex(start->indices->object));
        start->indices=start->indices->next;
      }
      else{
        store=new listOfObjects<string>(nameDict->getKeyAtIndex(start->indices->object));
        start->indices=start->indices->next;
      }
    }
    start1->indices=want;
    return true;
  }
  else{
    while(start->indices!=nullptr){
      if(store!=nullptr){
        while(store->next!=nullptr){
          store=store->next;
        }
        store->next=new listOfObjects<string>(nameDict->getKeyAtIndex(start->indices->object));
        start->indices=start->indices->next;
      }
      else{
        store=new listOfObjects<string>(nameDict->getKeyAtIndex(start->indices->object));
        start->indices=start->indices->next;
      }
    }
    start1->indices=want;
    return true;
  }

  // Insert your code here
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
    else{
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
