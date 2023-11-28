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

// Constructor 
Trie::Trie(Dictionary<int> *nameToIndex) {
  nameDict = nameToIndex;
  root = new TrieNode();
  if (root == nullptr) {
    cout << "Memory allocation failure." << endl;
    exit(-1);
  }
}

// Destructor
Trie::~Trie() {
  recursiveDelete(root);
}

// Function to Recursively Delete everything from a given Node
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

// Insert a new Station Name into Trie with a particlar Index
bool Trie::insert(string wordInName, int indexOfName) {

  TrieNode *currNode = root;
  int len = wordInName.length();
  int index;

  for(int i = 0; i < len; i++){
    int index = toupper(wordInName.at(i)) - 'A';
    if(currNode->branch[index] == nullptr){
      currNode->branch[index] = new TrieNode();                // Make a new Node at appropriare Branch
      currNode->numNonNullBranches = currNode->numNonNullBranches + 1;  // Increment number of Non Null Branches
    }
    currNode = currNode->branch[index];
  }

  // After the for loop, currNode is now the last character of word
  // So, set isWord to true of current Node
  currNode->isWord = true;

  // Update indices at last character of word
  listOfObjects<int> *newIndex = new listOfObjects<int>(indexOfName);

  if(currNode->indices == nullptr){
    currNode->indices = newIndex;
  }
  else{
    listOfObjects<int> *currIndices = currNode->indices;
    while(currIndices->next != nullptr){
      currIndices = currIndices->next;
    }
    currIndices->next = newIndex;
  }

  return true;

}

// Function to Delete a particular word from Trie
// wordInName is the part of whole word that is to be deleted
// name is the full string of word which is to be deleted
bool Trie::del(string wordInName, string name) {

  TrieNode *currNode = root;
  TrieNode *lastBranchNode = root;      // Last Node from which word has to be erased
  int lastBranchChar = toupper(wordInName.at(0)) - 'A';
  int len = wordInName.length();
  bool erase = false;                   // Bool to check whether word has to be erased or not

  for (int i = 0; i < len; i++) {       // Delete the index of word from indices at its last character
    int letter = toupper(wordInName.at(i)) - 'A';
    currNode = currNode->branch[letter];
  }
  listOfObjects<int> *currIndices = currNode->indices;

  if(currIndices->next == nullptr){     // If only 1 index is present
    currNode->indices = nullptr;        // Delete it and erase the word from Trie if it is not a prefix of another word
    if(currNode->numNonNullBranches != 0) erase = false;
    else erase = true;
    currNode->isWord = false;
  }
  else{        // else delete the Index but do not erase the string from Trie
    if(currIndices->object == nameDict->get(name)->value){      // If first index is to be deleted
      currNode->indices = currIndices->next;    // Set first pointer to second index
    }
    else{      // else iterate to find the index to be deleted and delete it
      while(currIndices->next->object != nameDict->get(name)->value){
        currIndices = currIndices->next;
      }
      currIndices->next = currIndices->next->next;
    }
  }

  if(erase){                  // Erase the string from Trie if erase is true
    currNode = root;
    for (int i = 0; i < len; i++) {
      int letter = toupper(wordInName.at(i)) - 'A';
      if(currNode->numNonNullBranches > 1 || (currNode->isWord)){     // Find last Node at which Non Null Branches are greater than 1 
        lastBranchNode = currNode;                                    // or which is at last of a word
        lastBranchChar = letter;                                      // And Delete the part of string from this Node
      } 
      currNode = currNode->branch[letter];
    }
    //cout << "LAST BRANCH CHAR : " << lastBranchChar << endl;
    lastBranchNode->branch[lastBranchChar] = nullptr;
    //recursiveDelete(lastBranchNode->branch[lastBranchChar]);
    lastBranchNode->numNonNullBranches--;
  }
  
  return true;

}

// Get Completions of word from a given prefix
listOfObjects<string> * Trie::completions(string prefix) {

  TrieNode *currNode = root;
  int len = prefix.length();
  listOfObjects<string> *currCompletions = new listOfObjects<string>("__INIT__");     // Linked List of completions

  for (int i = 0; i < len; i++) {   // Check if the prefix is present in Trie
    int letter = toupper(prefix.at(i)) - 'A';
    if (currNode->branch[letter] == nullptr) {
      return nullptr;               // return null if prefix is not present
    }
    currNode = currNode->branch[letter];
  }

  recursiveAddCompletions(currNode,currCompletions);    // Resursively add Completions into completions list

  return currCompletions;

}

// Recursively add completions from all the branches possible of a node
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

// Add Completion of a particular word into Linked List of Completions
bool Trie::addCompletions(TrieNode *node, listOfObjects<string> *currCompletions) {

  listOfObjects<int> *currIndices = node->indices;

  while (currIndices != nullptr) {         // Add all the indeices stored in a last node of a word

	  listOfObjects<string> *newCompletion = new listOfObjects<string>(nameDict->getKeyAtIndex(currIndices->object));

    if(currCompletions->object == "__INIT__"){         // Store at first index if it was empty
      currCompletions->object = nameDict->getKeyAtIndex(currIndices->object); 
    }
    else{                  // else traverse through Linked List and store at appropriate position
      listOfObjects<string> *tempCompletion = currCompletions;
      while(tempCompletion->next != nullptr){
        tempCompletion = tempCompletion->next;
      }
      tempCompletion->next = newCompletion;
    }
	  currIndices = currIndices->next;
  }

  return true;

}

// Check for a name being present in Linked list of completions
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

// Free or Delete the Completions Linked list
void Trie::freeCompletionList(listOfObjects<string> *completions) {
  listOfObjects<string> *currCompl = completions;
  while (currCompl != nullptr) {
    listOfObjects<string> *toDeleteCompl = currCompl;
    currCompl = currCompl->next;
    delete toDeleteCompl;
  }
  return;
}

// To check if a string is present in the Trie
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
