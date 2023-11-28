#ifndef TRIE_CPP
#define TRIE_CPP

#ifndef STD_HEADERS
#include "std_headers.h"
#endif

#ifndef DICTIONARY_H
#include "dictionary.cpp"
#endif

#ifndef TRIE_H
#include "Trie.h"
#endif
#include<bits/stdc++.h>

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

bool Trie::insert(string wordInName, int indexOfName) {// inserting new words into the trie
  TrieNode *currNode = root;
  int len = wordInName.length();
  for(int i=0;i<len;i++){
    int ch=wordInName[i]-65;
    if(i==len-1){
      if(currNode->branch[ch]==NULL){
       
      currNode->branch[ch]=new TrieNode();
      currNode->numNonNullBranches++;
      currNode=currNode->branch[ch];
      currNode->isWord=true;
      currNode->indices= new listOfObjects<int>(indexOfName);
      }
      else{
        currNode=currNode->branch[ch];
        currNode->isWord=true;
        listOfObjects<int>* x=currNode->indices;
        if(x==NULL){
          currNode->indices= new listOfObjects<int>(indexOfName);
          return true;
        }
        else{
          while(true){
            if(x->object==indexOfName)return false;
            if(x->next==NULL)break;
            x=x->next;
          }
          x->next=new listOfObjects<int>(indexOfName);
        }
       
      }
    }
    
    else{
      if(currNode->branch[ch]==NULL){
      currNode->branch[ch]=new TrieNode();
      currNode->numNonNullBranches++;
      currNode=currNode->branch[ch];
    }
    else{
      currNode=currNode->branch[ch];
    }
    }
  }
  return true;
  

}

bool Trie::del(string wordInName,string name) {// deleting existing words from the trie and deleting nodes if required
  TrieNode *currNode = root;
  TrieNode *lastBranchNode = nullptr;
  int lastBranchChar = -1;
  int len = wordInName.length();
  int code=nameDict->get(name)->value;
  bool dele=false;
  for(int i=0;i<len;i++){
    int ch=wordInName[i]-65;
    if(currNode->branch[ch]==NULL)return false;
    else if(currNode->branch[ch]->numNonNullBranches<2 && (!currNode->branch[ch]->isWord || i==len-1)){
        if(lastBranchChar==-1){
          lastBranchChar=i;//delete from i including i 
          lastBranchNode=currNode;
        }
    }
    else{
        lastBranchChar=-1;//delete from i including i 
        lastBranchNode=NULL;
    }
    currNode=currNode->branch[ch];    
  }
  if(currNode->isWord==0)return false;
  listOfObjects<int>* x=currNode->indices;
  if(x->next==NULL){
    if(x->object==code){
      delete x;
      currNode->indices=NULL;
      currNode->isWord=false;
      if(currNode->numNonNullBranches==0){
        int a=wordInName[lastBranchChar]-65;
        recursiveDelete(lastBranchNode->branch[a]);
        lastBranchNode->branch[a]=NULL;
        
      }
      return true;
    }
    else return false;
  }
  else{
    if(x->object==code){
      currNode->indices=x->next;
      delete x; 
      return true;     
    }
    while(x->next!=NULL){
      if(x->next->object==code){
        listOfObjects<int>* u=x->next;
        x->next=u->next;
        delete u;
        return true;
      }
    }
  }
  return false;
  
}

listOfObjects<string> * Trie::completions(string prefix) {// returns the complete names of the given prefixes
  TrieNode *currNode = root;
  int len = prefix.length();
  listOfObjects<string> *currCompletions = new listOfObjects<string>("start");
  for(int i=0;i<len;i++){
    int ch=prefix[i]-65;
    if(currNode->branch[ch]==NULL)return NULL;
    currNode=currNode->branch[ch];

  }
  recursiveAddCompletions(currNode,currCompletions);
  listOfObjects<string> * s=currCompletions;
  delete s;
  currCompletions=currCompletions->next;
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

  listOfObjects<string>*x=currCompletions;
  listOfObjects<int>*u=node->indices;
  while(u!=NULL){
    string name=nameDict->getKeyAtIndex(u->object);
    while(true){
      if(x->object==name){
        break;
      }
      if(x->next==NULL){
        x->next=new listOfObjects<string>(name);
        break;
      }
      x=x->next;
    }
    u=u->next;
    
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

