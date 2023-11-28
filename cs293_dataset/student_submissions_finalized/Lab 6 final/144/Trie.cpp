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

  for(int i = 0; i < len; i++){
    char char_to_add = toupper(wordInName[i]);
    //If the node for char is not initialised before, initialise new node.
    if(currNode->branch[(char_to_add - 'A')] == nullptr){
      currNode->branch[(char_to_add - 'A')] = new TrieNode();
      currNode->numNonNullBranches++;
    }
    //Move down the node
    currNode = currNode->branch[(char_to_add - 'A')];
  }

  //Add index to linked list in currNode at end of word
  currNode->isWord = true;
  listOfObjects<int>* pointer_to_node = currNode->indices;

  if(pointer_to_node == nullptr){
    currNode->indices = new listOfObjects<int>(indexOfName);
    currNode = root;
    return true;
  }
  
  while(pointer_to_node->next != nullptr){
    pointer_to_node = pointer_to_node->next;
  }

  pointer_to_node -> next = new listOfObjects<int>(indexOfName);
  currNode = root;
  return true;
}

bool Trie::del(string wordInName, string name) {
  TrieNode *currNode = root;
  TrieNode *lastBranchNode = root; // last node at which branching occurs OR where a word ends in path from root to last character
  int lastBranchChar = 0; // Index to character in wordInName which is child of lastBranchNode
  int len = wordInName.length();


  for(int i = 0; i < len; i++){
    //Go down the path to last character, while updating lastBranchNode
    char char_to_find = toupper(wordInName[i]);
    if(currNode->branch[char_to_find - 'A'] == nullptr){
      return false;
    }
    if(currNode->numNonNullBranches > 1 || currNode->isWord){
      lastBranchNode = currNode;
      lastBranchChar = i;
    }

    currNode = currNode->branch[char_to_find - 'A'];
  }
  //If the string is not a word, return false
  if(!currNode->isWord){
    return false;
  }

  //Iterate through the linked list
  listOfObjects<int>* current_list_node = currNode->indices;
  listOfObjects<int>* next_list_node = current_list_node->next;

  //If only one element in linked list
  if(next_list_node == nullptr){
    //If the name matches
    if(nameDict->getKeyAtIndex(current_list_node->object) == name){
      //Update currNode's indice pointer
      delete current_list_node;
      currNode->indices = nullptr;
      //If no character afterwards, recursively delete the branch from lastBranchNode
      if(currNode->numNonNullBranches == 0){
        recursiveDelete(lastBranchNode->branch[toupper(wordInName[lastBranchChar]) - 'A']);
        lastBranchNode->branch[toupper(wordInName[lastBranchChar]) - 'A'] = nullptr;
        lastBranchNode->numNonNullBranches--;
      }
      //Else change status of node to not a word
      else{
        currNode->isWord = false;
      }

      return true;
    }
    //If not matched, return false
    else{
      return false;
    }
  }

  //If first element in linked list is the word, update the indice pointer in node
  if(nameDict->getKeyAtIndex(current_list_node->object) == name){
    currNode->indices = next_list_node;
    delete current_list_node;
    return true;
  }
  //Find the element in linked list
  while(next_list_node != nullptr){
    //If matched, remove from list
    if(nameDict->getKeyAtIndex(next_list_node->object) == name){
      current_list_node->next = next_list_node->next;
      delete next_list_node;
      return true;
    }

    current_list_node = current_list_node->next;
    next_list_node = next_list_node->next;
  }
  return false;
}

//Reaches the end of prefix, and recursively adds all words using recursiveAddCompletions
listOfObjects<string> * Trie::completions(string prefix) {
  TrieNode *currNode = root;
  int len = prefix.length();
  listOfObjects<string> *currCompletions = nullptr;

  for(int i = 0; i < len; i++){
    char char_to_find = toupper(prefix[i]);
    if(currNode->branch[char_to_find - 'A'] == nullptr){
      return nullptr; //If prefix not in trie
    }

    currNode = currNode->branch[char_to_find - 'A'];
  }
  //Last element of currCompletions will be garbage value, to be removed afterwards
  currCompletions = new listOfObjects<string>(" ");
  //Recursively call the function
  recursiveAddCompletions(currNode, currCompletions);
  // Remove garbage value

  listOfObjects<string>* parentNode = currCompletions;
  listOfObjects<string>* childNode = currCompletions->next;
  //If no element in linked list, return nullptr
  if(childNode == nullptr){
    delete currCompletions;
    return nullptr;
  }

  while(childNode->next != nullptr){
    parentNode = parentNode->next;
    childNode = childNode->next;
  }

  delete childNode;
  parentNode->next = nullptr;
  return currCompletions;
  
}

//Adds the words from currNode and then recursively calls the function on children nodes
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

//Adds all the words of node to currCompletions
bool Trie::addCompletions(TrieNode *node, listOfObjects<string> *currCompletions) {

  listOfObjects<string>* currNode = currCompletions;
  //Finds end of linked list
  while(currNode->next != nullptr){
    currNode = currNode->next;
  }

  listOfObjects<int> *currIndexNode = node->indices;

  //Adds all the words at the end
  while(currIndexNode != nullptr){
    currNode->object = nameDict->getKeyAtIndex(currIndexNode->object);
    currNode->next = new listOfObjects<string>(" ");
    currNode = currNode->next;
    currIndexNode = currIndexNode->next;
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
