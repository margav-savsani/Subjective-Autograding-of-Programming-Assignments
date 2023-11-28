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
  int ind;
  // Insert your code here
  for(int i=0; i<len; i++){
    ind=toupper(wordInName.at(i))-'A';
    if (currNode->branch[ind]==nullptr){
      currNode->branch=new TrieNode();
      currNode->numNonNullBranches++;
      currNode=currNode->branch[ind];
      for(i++;i<len;i++){
        ind=toupper(wordInName.at(i))-'A';
        currNode->branch[ind]=new TrieNode();
        currNode->numNonNullBranches=1;
        currNode=currNode->branch[ind];
      }
    }
    else{
      currNode=currNode->branch[ind];
    }
  }
  if(currNode->isWord){
    int size=currNode->indices.size();
    currNode->indices.remove(indexOfName);
    size-=currNode->indices.size();
    currNode->push_back(indexOfName);
    if(size)
      return false;
    else
      return false;
  }
  else{
    currNode->isWord=true;
    currNode->indices=new list<int>;
    currNode->indices->push_back(indexOfName);
    return true;
  }
}

bool Trie::del(string wordInName, string name) {
  TrieNode *currNode = root;
  TrieNode *lastBranchNode = nullptr;
  int lastBranchChar = -1;
  int len = wordInName.length();
  int ind;
  // Insert your code here
  for(int i=0; i<len; i++){
    ind=toupper(wordInName.at(i))-'A';
    if(currNode->branch[ind]==nullptr)
      return false;
    else{
      if(!currNode->numNonNullBranches==1){
        lastBranchNode=currNode;
        lastBranchChar=i;
      }
      currNode=currNode->branch[ind];
    }
  }
  if(currNode->isWord){
    int size=nameDict.size();
    nameDict.remove(name);
    size-=nameDict.size();
    if(size){
      if(lastBranchChar!=len-1){
        currNode=root;
        for(int i=0; i<lastBranchChar; i++){
          ind=toupper(wordInName.at(i))-'A';
          currNode=currNode->branch[ind];
        }
        currNode->numNonNullBranches--;
        for(int i=lastBranchChar; i<len; i++){
          ind=toupper(wordInName.at(i))-'A';
          TrieNode *temp=lastBranchNode;
          lastBranchNode=lastBranchNode->branch[ind];
          delete temp;
        }
      }
      else if(currNode->indices.size()==0){
        if(currNode->numNonNullBranches==0){
          delete currNode;
          lastBranchNode->numNonNullBranches--;
        }
        else{
          currNode->isWord==false;
          delete currNode->indices;
        }
      }
      return true;
    }
    else{
      return false;
    }
  }
  else
    return false;
}

listOfObjects<string> * Trie::completions(string prefix) {
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


#endif
