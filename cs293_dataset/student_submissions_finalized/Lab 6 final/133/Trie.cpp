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
  if(len == 0) return false;

  for (int i = 0; i < len; i++){    
    int letter = toupper(wordInName.at(i)) - 'A';    
    if(currNode->branch[letter] == NULL){
      currNode->numNonNullBranches++;
      currNode->branch[letter] = new TrieNode(); 
      if(currNode->branch[letter] == NULL) return false;
    } 
    currNode = currNode->branch[letter];               
  }
  currNode->isWord = true;
  if(currNode->indices == NULL){
    currNode->indices = new listOfObjects(indexOfName);        
  }
  else{    
    listOfObjects<int>* finder=currNode->indices;
    while(true){
      if(finder->next == NULL) break;      
      finder = finder->next;
    }
    finder->next = new listOfObjects(indexOfName);
  }
  // Insert your code here
  return true;
}

bool Trie::del(string wordInName, string name) {
  TrieNode *currNode = root;   
  int len = wordInName.length();
  for(int i=0;i<len;i++){     
    int index = toupper(wordInName.at(i))-'A';
    if(currNode->branch[index] == NULL) return false;
    currNode = currNode->branch[index];  
  }  
  if(currNode->indices->next != NULL || currNode->numNonNullBranches >0){
    if(nameDict->getKeyAtIndex(currNode->indices->object) == name){
      currNode->indices = currNode->indices->next;
    }
    else{
      listOfObjects<int>* indices = currNode->indices;         
      while(indices->next != NULL){        
        if(nameDict->getKeyAtIndex(indices->next->object) == name) break;
        indices = indices->next;      
      }
      listOfObjects<int>* temp = indices->next->next;
      delete indices->next;
      indices->next = temp;
    }
    if(currNode->indices == NULL) currNode->isWord = false;
  }
  else{
    TrieNode* node1 = root;
    TrieNode* node2 = node1->branch[toupper(wordInName.at(0))-'A'];
    int i=1;
    int j=toupper(wordInName.at(0))-'A';
    while(node2 != currNode){     
      if(node2->numNonNullBranches != 1 || node2->isWord){j=toupper(wordInName.at(i))-'A'; node1 = node2;}
      node2 = node2->branch[toupper(wordInName.at(i))-'A'];
      i++;
    }            
    node1->numNonNullBranches--;      
    recursiveDelete(node1->branch[j]);
    node1->branch[j] = NULL;
  }
  // Insert your code here
  return true;
}

listOfObjects<string> * Trie::completions(string prefix) {
  TrieNode *currNode = root;
  int len = prefix.length();
  listOfObjects<string> *currCompletions = NULL;
  for(int i=0;i<len;i++){
    int index=toupper(prefix[i])-'A';
    if(currNode->branch[index] == NULL){return NULL;}    
    currNode = currNode->branch[index];
  }
  if(recursiveAddCompletions(currNode,currCompletions))  return currCompletions;

  // Insert your code here
  else return nullptr;    
}
  
bool Trie::recursiveAddCompletions(TrieNode *node, listOfObjects<string>* &currCompletions) {
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

bool Trie::addCompletions(TrieNode *node, listOfObjects<string>* &currCompletions) {   
  if(node->indices == NULL) return false; 
  if(currCompletions == NULL){
    listOfObjects<int> *indices= node->indices;    
    currCompletions = new listOfObjects<string>(nameDict->getKeyAtIndex(indices->object));        
    listOfObjects<string> *tail =  currCompletions;
    indices = indices->next;    
    while(indices != NULL){
      string name = nameDict->getKeyAtIndex(indices->object);
      if(!isPresentInCompletions(currCompletions,name)) {
        tail->next = new listOfObjects<string>(name);
        tail = tail->next;
      }
      indices = indices->next;      
    }
  }
  else{
    listOfObjects<string> *tail = currCompletions;
    while(true){
      if(tail->next == NULL) break;
      tail = tail->next;
    }
    listOfObjects<int> *indices= node->indices;
    while(indices != NULL){
      string name = nameDict->getKeyAtIndex(indices->object);
      if(!isPresentInCompletions(currCompletions,name)) {
        tail->next = new listOfObjects<string>(name); 
        tail = tail->next;
      }          
      indices = indices->next;     
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
