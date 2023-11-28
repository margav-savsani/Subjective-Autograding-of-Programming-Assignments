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
  for (int i = 0; i < len; i++)
    {
        int index = toupper(wordInName[i]) - 'A';
        if (!currNode->branch[index]){
            currNode->branch[index] = new TrieNode();
            currNode->numNonNullBranches++;
        }
        currNode = currNode->branch[index];
    }
  
    // mark last node as leaf
    currNode->isWord = true;
    listOfObjects<int> *Indice = currNode->indices;
    while (Indice != nullptr){
      if(Indice->object == indexOfName){
        return true;
      }
      else{
        Indice = Indice->next;
      }
    } 
    listOfObjects<int> *ins = new listOfObjects<int>(indexOfName);
    if(ins == nullptr){
      return false;
    }
    else{
      ins->next = currNode->indices;
      currNode->indices = ins;
      return true;
    }
}

bool Trie::del(string wordInName, string name) {
  TrieNode *currNode = root;
  TrieNode *lastBranchNode = nullptr;
  int lastBranchChar = -1;
  int len = wordInName.length();

  // Insert your code here
  for ( int i = 0;i< len; i++){
    int index = toupper(wordInName[i]) - 'A';
    if (currNode->branch[index] == nullptr){
      cout<<"not found"<<endl;
      return false;
    }
    
    if (currNode -> numNonNullBranches > 1 ){
      lastBranchNode = currNode;
      lastBranchChar = i;
    }
    currNode = currNode->branch[index];
  }
  if(!currNode->isWord){
    cout<<"not found"<<endl;
    return false;
  }
  listOfObjects<int> *currindice = currNode->indices;
  listOfObjects<int> *x = nullptr;
  while ( currindice != nullptr){
      if (currNode->indices != nullptr){
        return true;
      }
      else{
        currNode->isWord = false;
        if(currNode->numNonNullBranches > 0){
          return true;
        }
        
        TrieNode *y;
        for (int i = lastBranchChar;i<len;i++){
          int in = toupper(wordInName[i])-'A';
          y = currNode;
          currNode = currNode->branch[in];
          delete y;
        } 
        return true;
      }

    }
    else{
      x = currindice;
      currindice = currindice->next;
    }
  }
  return false;
}

listOfObjects<string> * Trie::completions(string prefix) {
  TrieNode *currNode = root;
  int len = prefix.length();
  listOfObjects<string> *currCompletions = nullptr;
  bool a=recursiveAddCompletions(currNode,currCompletions);
  for ( int i=0; i<len;i++){
    int index = toupper(prefix[i]) - 'A';
    if(currNode->branch[index]==nullptr){
      delete currCompletions;
      return nullptr;
    }
    currNode = currNode->branch[index];
  }
  if (a){
    return currCompletions;
  }
  else{
    freeCompletionList(currCompletions);
    return 0;
  }
  // Insert your code her
  
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
  listOfObjects<int> *list1=node->indices;
  listOfObjects<string> *curr=currCompletions,*prev=nullptr;
  while(curr!=nullptr){
    prev=curr;
    curr=curr->next;
  }
  while(list1!=nullptr){
    if(prev==nullptr){
      currCompletions=new listOfObjects<string>(nameDict->getKeyAtIndex(list1->object));
      list1=list1->next;
      prev=currCompletions;
    }
    else{
      prev->next=new listOfObjects<string>(nameDict->getKeyAtIndex(list1->object));
      prev=prev->next;
      list1=list1->next;
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
// End edit version 1

#endif
