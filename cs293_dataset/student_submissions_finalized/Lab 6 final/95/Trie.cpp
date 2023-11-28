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
  for(int i=0;i<len;i++){
    if(currNode->branch[int(wordInName[i])-65]!=NULL){
      
      if(i==len-1){
        currNode->branch[int(wordInName[i])-65]->isWord=true;
        listOfObjects<int>*a= currNode->branch[int(wordInName[i])-65]->indices;
         listOfObjects<int>*add=new listOfObjects<int>(indexOfName);
        if(a==NULL){
          currNode->branch[int(wordInName[i])-65]->indices=add;
          return true;
        }
        while (a->next!=NULL)
        {
          a=a->next;
        }
        a->next=add;
        return true;
      }
      currNode=currNode->branch[int(wordInName[i])-65];
    }
    else{
    TrieNode *ins=new TrieNode(wordInName[i]);
    currNode->branch[int(wordInName[i])-65]=ins;
    currNode->numNonNullBranches++;
    if(i==len-1){
        currNode->branch[int(wordInName[i])-65]->isWord=true;
        listOfObjects<int>*a= currNode->branch[int(wordInName[i])-65]->indices;
        listOfObjects<int>*add=new listOfObjects<int>(indexOfName);
        if(a==NULL){
          currNode->branch[int(wordInName[i])-65]->indices=add;
          return true;
        }
        while (a->next!=NULL)
        {
          a=a->next;
        }
        a->next=add;
        
      }
    currNode=currNode->branch[int(wordInName[i])-65];
    }
}
  

  return true;
}

bool Trie::del(string wordInName, string name) {
  TrieNode *currNode = root;
  TrieNode *lastBranchNode = nullptr;
  int lastBranchChar = -1;
  int len = wordInName.length();
  for(int i=0;i<len;i++){
    currNode=currNode->branch[int(wordInName[i])-65];
  }
  listOfObjects<int>*a=currNode->indices;
  if(nameDict->getKeyAtIndex(a->object)==name){
    currNode->indices=a->next;
    return true;
  }
  while(a->next!=NULL){
    if(nameDict->getKeyAtIndex(a->next->object)==name){
       a->next=a->next->next;
      return true;
    }
  }

  // Insert your code here
  return false;
}

listOfObjects<string> * Trie::completions(string prefix) {
  TrieNode *currNode = root;
  int len = prefix.length();
  listOfObjects<string> *currCompletions = nullptr;
for(int i=0;i<len;i++){
  // if(currNode==NULL){return nullptr;}
  currNode=currNode->branch[int(prefix[i])-65];
}

addCompletions(currNode,currCompletions);
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

bool Trie::addCompletions(TrieNode *node, listOfObjects<string> *&currCompletions) {
  if(node==NULL){
    return true;
  }
    else if(node->isWord==true){
      listOfObjects<int>*a=node->indices;
      while(a!=NULL){
        if(!isPresentInCompletions(currCompletions,nameDict->getKeyAtIndex(a->object))){
          listOfObjects<string>*name_of_station=new listOfObjects<string>(nameDict->getKeyAtIndex(a->object));
          if(currCompletions==NULL){
            currCompletions=name_of_station;
            a=a->next;
           
          }
          else{
          while(currCompletions->next!=NULL){
            currCompletions=currCompletions->next;
          }
          currCompletions->next=name_of_station;
          a=a->next;
        }}
        else{
          a=a->next;
        }
      }
      for(int i=0;i<NUM_CHARS;i++){
        if(node->branch[i]!=NULL){
        addCompletions(node->branch[i],currCompletions);}
      }
    }
    else{
      for(int i=0;i<NUM_CHARS;i++){
        if(node->branch[i]!=NULL){
        addCompletions(node->branch[i],currCompletions);}
      }
    
  }
  // Insert your code here
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


#endif
