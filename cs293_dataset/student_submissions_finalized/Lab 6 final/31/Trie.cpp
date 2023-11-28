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
     int letter = toupper(wordInName.at(i)) - 'A';
     if(currNode->branch[letter] == NULL){
      currNode->numNonNullBranches++;
      currNode->branch[letter] = new TrieNode();
     }
     currNode = currNode->branch[letter];
    if(i==len-1){
      currNode->isWord = true;
      // add the given index to listofindices present there
      listOfObjects<int>* list = currNode->indices;
      if(list==NULL){
        // if there are no indices present, create one
        currNode->indices = new listOfObjects<int> (indexOfName);
      } 
      // else just add the given index to the linked list of indices
      else{
        while(list->next!=NULL){
          list=list->next;
        }
        list->next = new listOfObjects<int> (indexOfName);
      }
    }
  }

  return true;
}

bool Trie::del(string wordInName, string name) {
  TrieNode *currNode = root;
  //TrieNode *lastBranchNode = nullptr;
  //int lastBranchChar = -1;
  int len = wordInName.length();

  // Insert your code here

  // find the foot of the wordInName in the trie 
  for(int i=0; i<len; i++){
    int letter = toupper(wordInName.at(i)) - 'A';
    if(currNode->branch[letter] == NULL){
      return false;
    }
    currNode = currNode->branch[letter]; 
  }

  // delete the index corresponding to name if any from the indices present at currNode
  if(currNode->isWord){
    listOfObjects<int>* parent = NULL;
    listOfObjects<int>* child = currNode->indices;
    while(child!=NULL){
      if(nameDict->getKeyAtIndex(child->object)==name){
        // make parent's next point to child's next, then delete child
         if(parent!=NULL){
            parent->next = child->next;
            delete child; 
         }
         else currNode->indices=child->next;
         return true;
      }
      parent = child;
      child = child->next;
    }
  }

  // If there are no indices left after deleting, make isWord false
  if(currNode->indices == NULL){
      currNode->isWord = false;
  }

  return false;
}

listOfObjects<string>* Trie::completions(string prefix) {
  TrieNode *currNode = root;
  int len = prefix.length();
  listOfObjects<string> *currCompletions = new listOfObjects<string> ("");

  // find the foot node of the given prefix
  for(int i=0; i<len; i++){
    int letter = toupper(prefix.at(i)) - 'A';
    if(currNode->branch[letter] == NULL){
      return NULL;
    }
    currNode = currNode->branch[letter]; 
  }

  // recursively add the strings starting at currNode
  recursiveAddCompletions(currNode, currCompletions);

  return currCompletions->next;
  
}

bool Trie::recursiveAddCompletions(TrieNode *node, listOfObjects<string> *currCompletions) {
  // recursively traverse the trie and add the strings at every isWord node to the linkedlist of strings 'currCompletions'
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
  if(node->isWord){
    // add all the strings corresponding to indices at node into the linkedlist currCompletions
    listOfObjects<string>* list = currCompletions;
    if(list!=NULL){
      while(list->next!=NULL){
        list = list->next;
      }
    }
    listOfObjects<int>* ind = node->indices;
    while(ind!=NULL){
        list->next = new listOfObjects<string> (nameDict->getKeyAtIndex(ind->object));
        list = list->next;
        ind = ind->next;
    }
    return true;
  }

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
