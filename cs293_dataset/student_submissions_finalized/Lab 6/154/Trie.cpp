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

template<typename T>
bool listinsert(const T &o, listOfObjects<T> *l){
  // tempelate function to insert an object to the linked list l
  // inserts only if that object is not present
  listOfObjects<T> *curr = l;
  while(curr->next != nullptr){
    if(curr->object == o){
      return true;
    }
    curr = curr->next;
  }
  curr->next = new listOfObjects<T>(o);
  return true;
}

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
  // insert a (string,index) to trie
  TrieNode *currNode = root;
  int len = wordInName.length();
  int idx; 
  for(int i=0; i<len; i++){
    idx = tolower(wordInName[i])-'a'; // convert char to corresponding index
    if (currNode->branch[idx] == nullptr){
      currNode->branch[idx] = new TrieNode();
      currNode->numNonNullBranches++;
    }
    currNode = currNode->branch[idx];
  }
  if(currNode->isWord){ // insert to linked list
    return listinsert<int>(indexOfName, currNode->indices);
  }
  currNode->isWord = true;
  currNode->indices = new listOfObjects<int>(indexOfName);
  return true;
}

bool Trie::del(string wordInName, string name) {
  // delete (wordInName,index(name)) from trie
  TrieNode *currNode = root;
  TrieNode *lastBranchNode = root; // stores last branching node
  int lastBranchChar = toupper(wordInName.at(0)) - 'A'; // last branch index
  int len = wordInName.length();

  // find that node
  for (int i = 0; i < len; i++) {
    int letter = toupper(wordInName.at(i)) - 'A';
    if (currNode->branch[letter] == nullptr) {
      return true; // not present
    }
    if(currNode->numNonNullBranches > 1){
      lastBranchNode = currNode;
      lastBranchChar = letter;
    }
    currNode = currNode->branch[letter];
  }
  if (!currNode->isWord)
    return true; // not present

  
  listOfObjects<int> *curridx = currNode->indices;
  if(nameDict->getKeyAtIndex(curridx->object)==name){ // base case
    currNode->indices = curridx->next;
    delete curridx;
    if(currNode->indices==nullptr){ // handle indices getting empty
      currNode->isWord=false;
      if(currNode->numNonNullBranches == 0){ // handle the entire branch becoming redundant
        recursiveDelete(lastBranchNode->branch[lastBranchChar]);
        lastBranchNode->branch[lastBranchChar] = nullptr;
        lastBranchNode->numNonNullBranches--;
      }
    }
    return true;
  }
  // now iterate on curridx->next
  while(curridx->next!=nullptr){
    if(nameDict->getKeyAtIndex(curridx->next->object)==name){
      listOfObjects<int> *temp = curridx->next;
      curridx->next = temp->next;
      delete temp;
      return true;
    }
    curridx = curridx->next;
  }
  return true; //not present
}

listOfObjects<string> * Trie::completions(string prefix) {
  // return list of completeions(full station name)
  TrieNode *currNode = root;
  int len = prefix.length();
  int idx;
  // find that node
  for(int i=0; i<len; i++){
    idx = tolower(prefix[i])-'a'; // convert char to corresponding index
    if (currNode->branch[idx] == nullptr){
      return nullptr; // since not found
    }
    currNode = currNode->branch[idx];
  }
  
  // create new linked list with garbage value to avoid base case
  listOfObjects<string> *currCompletions = new listOfObjects<string>("Start"); 
  recursiveAddCompletions(currNode, currCompletions);
  listOfObjects<string> *to_return = currCompletions->next; // separate garbage
  delete currCompletions; // delete garbage node
  return to_return;  
}

bool Trie::recursiveAddCompletions(TrieNode *node, listOfObjects<string> *currCompletions) {
  // recursively add completions of curr node and it's branches to linked list currCompletions

  if (node->isWord) { // only add if it's a word
    if (!addCompletions(node, currCompletions)) {
      return false;
    }
  }

  TrieNode *currNode = node;
  // add branches also
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
  // add all objects in curr node to curr completions 
  listOfObjects<int> *curridx = node->indices;
  if(curridx == nullptr){
    return false;
  }
  while(curridx != nullptr){
    if(!listinsert<string>(nameDict->getKeyAtIndex(curridx->object), currCompletions)){
      return false;
    }
    curridx = curridx->next;
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
