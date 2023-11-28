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
  for(int i=0; i<len; i++){
    int j=wordInName[i]-'A';
    if(j>25 || j<0){cout<<"name of the station should only contain capital letters"; return false;}
    else{
      if(currNode->branch[j]!=nullptr){
          currNode=currNode->branch[j];
      }
      else{
          currNode->branch[j]=new TrieNode();
          currNode->numNonNullBranches++;
          currNode=currNode->branch[j];
      }
    }
  }
  listOfObjects<int>* a=currNode->indices;
  currNode->isWord=true;
  if(currNode->indices==nullptr){
    currNode->indices=new listOfObjects<int>(indexOfName);
    currNode->size_of_indices=1;
  }
  else{
    while(currNode->indices->next!=nullptr){
      currNode->indices=currNode->indices->next;
    }
    currNode->indices->next=new listOfObjects<int>(indexOfName);
    currNode->indices=a;
    currNode->size_of_indices++;
  }
  return true;
}

bool Trie::del(string wordInName, string name) {
  TrieNode *currNode = root;
  TrieNode *delNode;
  int len = wordInName.length();
  int index_last=-1;
  for(int i=0; i<len; i++){
    int nxt_char=wordInName[i]-'A';
    if(nxt_char>25 || nxt_char<0){cout<<"name of string must only contain capital letters"; return false;}
    currNode=currNode->branch[nxt_char];
    if((currNode->numNonNullBranches>=2 && i!=len-1) || (currNode->size_of_indices>=1 && i!=len-1)){
      delNode=currNode;
      index_last=wordInName[i+1]-'A';
    }
  }
  if(currNode->numNonNullBranches==0 && index_last!=-1 && currNode->size_of_indices==1){
    delNode->branch[index_last]=nullptr;
    delNode->numNonNullBranches--;
  }
  else{
    if(index_last==-1 && currNode->numNonNullBranches==0 && currNode->size_of_indices==1){
      root->branch[wordInName[0]-'A']=nullptr;
      root->numNonNullBranches--;
    }
    else{
      int hash=nameDict->hashValue(name);
      while(nameDict->getKeyAtIndex(hash)!=name){
        hash=(hash+1)%64;
      }
      listOfObjects<int>* a=currNode->indices;
      listOfObjects<int>* b=currNode->indices;
      int i=0;
      while(currNode->indices->object!=hash && currNode->indices!=nullptr){
        currNode->indices=currNode->indices->next;
        i=i+1;
      }
      if(currNode->indices!=nullptr){
        if(i==0){
          currNode->indices=currNode->indices->next; 
          currNode->size_of_indices--;
          if(currNode->size_of_indices==0)currNode->isWord=false;
        }
        else{
            int k=0;
            while(k<i-1){
              a=a->next;
              k++;
            }
            a->next=currNode->indices->next;
            currNode->indices=b;
            currNode->size_of_indices--;
            if(currNode->size_of_indices==0)currNode->isWord=false;
        }
      }
      else return false;
    }
  }
  return true;
}

listOfObjects<string> * Trie::completions(string prefix) {
  TrieNode *currNode = root;
  int len = prefix.length();
  listOfObjects<string> *currCompletions = new listOfObjects<string>("HELLO");
  for(int i=0; i<len; i++){
    int nxt_char=prefix[i]-'A';
    currNode=currNode->branch[nxt_char];
  }
  recursiveAddCompletions(currNode,currCompletions);
  if(currCompletions->object=="HELLO")currCompletions=nullptr;
  return currCompletions; 
}

bool Trie::recursiveAddCompletions(TrieNode *node, listOfObjects<string> *currCompletions) {
  if (node->isWord) {
    if(!addCompletions(node, currCompletions)){
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
    listOfObjects<int>* c=node->indices;
    while(c!=nullptr){
      string a=nameDict->getKeyAtIndex(c->object);
      if(currCompletions->object=="HELLO"){
          currCompletions->object=a;
      }
      else{
          listOfObjects<string>* b=currCompletions;
          while(currCompletions->next!=nullptr){
            currCompletions=currCompletions->next;
          }
          currCompletions->next=new listOfObjects<string>(a);
          currCompletions=b;
      }
      c=c->next;
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