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

listOfObjects<string> * x = nullptr;

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

  for (int i = 0; i < len; i++)
  {
    int index = toupper(wordInName.at(i)) - 'A';
    if (!currNode->branch[index]){
      currNode->branch[index] = new TrieNode();
      currNode->numNonNullBranches++;
    }
    currNode = currNode->branch[index];
  }
  // mark last node as leaf
  currNode->isWord = true;
  listOfObjects<int>* p = currNode->indices;
  if(p == nullptr) currNode->indices = new listOfObjects<int>(indexOfName);
  else{
    while(p->next != nullptr){
      if(p->object == indexOfName) return false;
      p = p->next;
    }
    if(p->object == indexOfName) return false;
    p->next = new listOfObjects<int>(indexOfName);
  }

  return true;
}

bool Trie::del(string wordInName, string name) {
  TrieNode *currNode = root;
  TrieNode *lastBranchNode = root;
  int lastBranchChar = 0;
  int len = wordInName.length();
  
  if(!isPresent(wordInName))return false;
  // Insert your code here
  for(int i=0; i< len; i++){
    if(i == 0) {
      lastBranchNode = root;
      lastBranchChar = toupper(wordInName.at(i)) - 'A';
    }

    int index = toupper(wordInName.at(i)) - 'A';
    if(currNode->numNonNullBranches > 1 || currNode->isWord == true){
      lastBranchNode = currNode;
      lastBranchChar = toupper(wordInName.at(i)) - 'A';
    }
    currNode = currNode->branch[index];

    if(i == len-1){
      if(currNode->numNonNullBranches > 0) {
        currNode->isWord = false;
        currNode->indices = nullptr;
        return true;
      }
      listOfObjects<int> * p = currNode->indices;
      if(!p->next){
        lastBranchNode->numNonNullBranches-=1;
        lastBranchNode->branch[lastBranchChar] = nullptr;
        return true;
      }
      if(nameDict->getKeyAtIndex(p->object) == name){
        currNode->indices = p->next;
        return true;
      }
      while(p->next){
        if(nameDict->getKeyAtIndex(p->next->object) == name){
          p->next = p->next->next;
        }
        else p = p->next;
      }
      return true;
    }
  }
  return false;
}

listOfObjects<string> * Trie::completions(string prefix) {
  TrieNode *currNode = root;
  int len = prefix.length();
  listOfObjects<string> *currCompletions = nullptr;
  for(int i=0;i<len;i++){
    int index = toupper(prefix.at(i)) - 'A';
    currNode=currNode->branch[index];
  }
  recursiveAddCompletions(currNode,x);
  currCompletions=x;
  listOfObjects<string>*y=currCompletions;
    while(y){
      cout<<y->object;
      y=y->next;
    }
  return currCompletions;
  
}

bool Trie::recursiveAddCompletions(TrieNode *node, listOfObjects<string> *currCompletions) {
  if (node->isWord) {
    if (!addCompletions(node,x)) {
      return false;
    }
  }
  
  TrieNode *currNode = node;
  for (int i = 0; i < NUM_CHARS; i++) {
    if (currNode->branch[i] != nullptr) {
      if (!recursiveAddCompletions(currNode->branch[i], x)) {
	      return false;
      }
    }
  }
  currCompletions=x;
  return true;
}

bool Trie::addCompletions(TrieNode *node, listOfObjects<string> *currCompletions) {

  // Insert your code here
  if(node->isWord==true){
    while(node->indices){
      string s=nameDict->getKeyAtIndex(node->indices->object);
      if(!currCompletions){
        currCompletions=new listOfObjects<string>(s);
      }
      else{
        listOfObjects<string>*temp=currCompletions;
        int r = 0;
        if(temp->object==s){r++;}
        while(temp->next){
          temp=temp->next;
          if(temp->object==s)r++;
        }
        if(r==0){
        temp->next=new listOfObjects<string>(s);}
      }
      node->indices=node->indices->next;
    }
    x=currCompletions;
    return true;
  }
  else{
    return false;
  }
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
