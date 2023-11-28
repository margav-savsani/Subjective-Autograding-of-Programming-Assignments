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
      currNode->branch[ind]=new TrieNode();
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
    listOfObjects<int> *temp;
    temp=currNode->indices;
    while(temp->next!=nullptr && temp->object!=indexOfName)
      temp=temp->next;
    if(temp->object!=indexOfName){
      try{
        temp->next=new listOfObjects<int>(indexOfName);
      }
      catch(...){
        return false;
      }
    }
    return true;
  }
  else{
    currNode->isWord=true;
    try{
      currNode->indices=new listOfObjects<int>(indexOfName);
    }
    catch(...){
      return false;
    }
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
      if(currNode->numNonNullBranches!=1){
        lastBranchNode=currNode;
        lastBranchChar=ind;
      }
      currNode=currNode->branch[ind];
    }
  }
  if(currNode->isWord){
    if(nameDict->get(name)==nullptr)
      return false;
    ind=(nameDict->get(name))->value;

    //currNode->isWord=false;
    listOfObjects<int> *temp, *temp2;
    temp2=nullptr;
    temp=currNode->indices;
    while(temp->object!=ind && temp->next!=nullptr){
      temp2=temp;
      temp=temp->next;
    }
    if(temp->object==ind){
      if(temp2==nullptr){
        if(temp->next==nullptr){
          currNode->isWord=false;
          delete currNode->indices;
          currNode->indices=nullptr;
        }
        else{
          temp2->next=temp->next;
          delete temp;
        }
      }
    }
    bool check=true;
    for(int i=1;i<=wordInName.size() && check;i++){
      if(toupper(wordInName[wordInName.size()-i])!=toupper(name[name.size()-i]))
        check=false;
    }
    if(check){
      nameDict->remove(name);
    }
    if(currNode->numNonNullBranches==0){
      recursiveDelete(lastBranchNode->branch[lastBranchChar]);
    }
    return true;
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
  if(node->branch==nullptr)
    return false;
  else{
    listOfObjects<int> *temp=node->indices;
    while(temp!=nullptr){
      try{
        listOfObjects<string> *comp=new listOfObjects<string>(nameDict->getKeyAtIndex(temp->object));
        comp->next=currCompletions;
        currCompletions=comp;
      }
      catch(...){
        return false;
      }
    }
    return true;
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
