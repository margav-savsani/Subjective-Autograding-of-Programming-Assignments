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

// Inserts given word into trie along with index at end
bool Trie::insert(string wordInName, int indexOfName) {
  TrieNode *currNode = root;
  int len = wordInName.length();

  // Add word in Trie
  for (int i = 0; i < len; i++){
    int letter = toupper(wordInName.at(i)) - 'A';
    if (currNode->branch[letter] == nullptr) {
      TrieNode* newNode = new TrieNode(wordInName[i]);
      currNode->branch[letter] = newNode;
      currNode->numNonNullBranches++;
    }
    currNode = currNode->branch[letter];
  }

  // Add indices linked list at end
  if(currNode->isWord == false){
    currNode->isWord = true;
    currNode->indices = new listOfObjects<int>(indexOfName);
  }
  else{
    listOfObjects<int>* p = currNode->indices;

    // check if already present
    bool indexPresent = false;
    while(p->next != nullptr){
      if(p->object == indexOfName){
        indexPresent = true;
        break;
      }
      p = p->next;
    }

    if(indexPresent == false){
      p->next = new listOfObjects<int>(indexOfName);
    }
  }


  return true;
}

// Deletes given word in trie
bool Trie::del(string wordInName, string name) {
  if(wordInName == "" || name == "") return false;

  TrieNode *currNode = root;
  TrieNode *lastBranchNode = root;
  int lastBranchChar = toupper(wordInName.at(0)) - 'A';
  int len = wordInName.length();

  // Go till last letter of word and also compute last node which cannot be deleted
  for (int i = 0; i < len; i++) {
    int letter = toupper(wordInName.at(i)) - 'A';

    if (currNode->branch[letter] == nullptr) {
      return false;
    }
    currNode = currNode->branch[letter];

    // If currNode has more than 1 child or a word ends there then it cannot be deleted
    if(i != len-1 && (currNode->numNonNullBranches>1 || currNode->isWord) ){
      lastBranchNode = currNode;
      lastBranchChar = toupper(wordInName.at(i+1)) - 'A';
    }
  }

  if(currNode->isWord == false) return false;

  if(currNode->indices->next == nullptr){
  // If single node in indices
    if(currNode->indices->object != nameDict->get(name)->value) return false;

    if(currNode->numNonNullBranches > 0){
    // If currNode has some child then it cannot be deleted just isWord becomes false
      delete currNode->indices;
      currNode->indices = nullptr;
      currNode->isWord = false;
    }
    else{
    // else delete all node from lastBranchNode till currNode using recursive delete
      recursiveDelete(lastBranchNode->branch[lastBranchChar]);
      lastBranchNode->branch[lastBranchChar] = nullptr;
      lastBranchNode->numNonNullBranches--;
    }
  }
  else{
  // If multiple nodes in indices then just remove required index node from indices linked list
    listOfObjects<int>* i= currNode->indices;
    int index = nameDict->get(name)->value;

    if(i->object == index){
      listOfObjects<int>* temp = i->next;
      delete i;
      currNode->indices = temp;
    }
    else{
      while(i->next != nullptr && i->next->object != index){
        i = i->next;
      }
      if(i->next == nullptr) return false;
      
      listOfObjects<int>* temp = i->next->next;
      delete i->next;
      i->next = temp;
    }
  }

  return true;
}

// Returns linked list of all completions possible for given prefix
listOfObjects<string> * Trie::completions(string prefix) {
  TrieNode *currNode = root;
  int len = prefix.length();
  listOfObjects<string> *currCompletions = nullptr;

  // Go till last letter of prefix
  for (int i = 0; i < len; i++) {
    int letter = toupper(prefix.at(i)) - 'A';

    if (currNode->branch[letter] == nullptr) {
      return nullptr;
    }
    currNode = currNode->branch[letter];
  }
  
  // Find all completions from there
  recursiveAddCompletions(currNode, currCompletions);
  
  return currCompletions;
  
}

// Recursively Adds all possible completions from given node to given linked list
bool Trie::recursiveAddCompletions(TrieNode *node, listOfObjects<string> *& currCompletions) {
  // If a word ends at node then add completions
  if (node->isWord) {
    if (!addCompletions(node, currCompletions)) {
      return false;
    }
  }

  // recursively add completions for all its child
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

// Adds Completions only from given node to given linked list
bool Trie::addCompletions(TrieNode *node, listOfObjects<string> *& currCompletions) {
  listOfObjects<string>* currNode = currCompletions;
  if(currCompletions != nullptr){
    while(currNode->next != nullptr){
      currNode = currNode->next;
    }
  }

  listOfObjects<int>* i = node->indices;
  while(i != nullptr){
    string fullName = nameDict->getKeyAtIndex(i->object);
    if(!isPresentInCompletions(currCompletions, fullName)){
      if(currCompletions == nullptr){
        currCompletions = new listOfObjects<string>(fullName);
        currNode = currCompletions;
      }
      else{
        currNode->next = new listOfObjects<string>(fullName);
        currNode = currNode->next;
      }
    }
    i = i->next;
  }

  return true;
}

// Checks if given string is already present in completions linked list
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

// Frees memory of completions linked list
void Trie::freeCompletionList(listOfObjects<string> *completions) {
  listOfObjects<string> *currCompl = completions;
  while (currCompl != nullptr) {
    listOfObjects<string> *toDeleteCompl = currCompl;
    currCompl = currCompl->next;
    delete toDeleteCompl;
  }
  return;
}

// Checks if word is present in trie
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
