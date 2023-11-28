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

// Function to add station to Trie
bool Trie::insert(string wordInName, int indexOfName) {
  TrieNode *currNode = root; // Set currNode to root
  int len = wordInName.length(); // Length of wordInName

  // Insert your code here
  for(int idx = 0; idx < len; idx++){
    int letter = toupper(wordInName.at(idx)) - 'A'; // Compute next branch
    if(currNode->branch[letter] == nullptr){
      currNode->branch[letter] = new TrieNode(); // Create new TrieNode if it doesn't already exist
      currNode->numNonNullBranches++;
    }
    currNode = currNode->branch[letter]; // Keep moving till you reach end of word
  }

  currNode->isWord = true; //Set isWord to true
  listOfObjects<int>* newObject = new listOfObjects<int>(indexOfName);
  newObject->next = currNode->indices;
  currNode->indices = newObject; // insert indexOfName to index list at currNode

  return true;
}

// Function to delete station from Trie
bool Trie::del(string wordInName, string name) {
  TrieNode *currNode = root; // Set currNode to root
  TrieNode *lastBranchNode = nullptr; // The last node it branched from; nullptr for root
  int lastBranchChar = -1; // The branch taken to reach this node; -1 for root
  int len = wordInName.length(); // Length of wordInName

  return delHelper(wordInName, name, lastBranchNode, lastBranchChar, currNode, 0); // Call helper function
}

// Helper function for del
bool Trie::delHelper(string wordInName, string name, TrieNode* lastBranchNode, int lastBranchChar, TrieNode* currNode, int idx){
  int len = wordInName.length(); // Length of wordInName
  if(idx == len){ // If at word end
    //Remove from list
    if(!currNode->isWord)
      return false; // Set isWord to false
    
    // Remove the required index from index list
    if(nameDict->getKeyAtIndex(currNode->indices->object) == name){
      currNode->indices = currNode->indices->next;
      delete currNode->indices;
    } else{
      bool found = false;

      listOfObjects<int>* prev = currNode->indices;
      listOfObjects<int>* curr = currNode->indices->next;
      while(curr != nullptr){
        if(nameDict->getKeyAtIndex(curr->object) == name){
          found = true;
          prev->next = curr->next;
          delete curr;
          break;
        }
        prev = curr;
        curr = curr->next;
      }

      if(!found)
        return false; // Return false as deletion unsuccessfull
    }

    if(currNode->indices == nullptr){ // If no indices in index list
      currNode->isWord = false; // Set isWord to false

      if(currNode->numNonNullBranches > 0) // If other branches left
        return true; // Return

      // If no branches left from trie
      lastBranchNode->branch[lastBranchChar] = nullptr; // Delte this node's existence from parent's children
      lastBranchNode->numNonNullBranches--; // Decrease parent's numNonNullBranches
      delete currNode; // Free currNode from heap
    }

    return true;
  } else{ // If not at word end
    int letter = toupper(wordInName.at(idx)) - 'A';
    if(currNode->branch[letter] == nullptr) // If no branch with letter
      return false; // Deletion unsuccessful
    if(delHelper(wordInName, name, currNode, letter, currNode->branch[letter], idx+1) == false) // Call delHelper to respective child
      return false; // Return deletion unsuccessfull

    // If node is being deleted, do the necessary cleanup up the whole Trie
    if(!currNode->isWord){
      if(currNode->numNonNullBranches > 0)
        return true;
      lastBranchNode->branch[lastBranchChar] = nullptr;
      lastBranchNode->numNonNullBranches--;
      delete currNode;
    }

    return true;
  }
}

// Function to return completions with prefix prefix
listOfObjects<string> * Trie::completions(string prefix) {
  TrieNode *currNode = root; // Set currNode to root
  int len = prefix.length(); // Length of wordInName
  listOfObjects<string> *currCompletions = nullptr; // Initialise currCompleteions to nullptr

  // Insert your code here
  for(int idx = 0; idx < len; idx++){ // Traverse down the trie till prefix matches
    int letter = toupper(prefix.at(idx)) - 'A';
    if(currNode->branch[letter] == nullptr){ // If traversal stops
      return nullptr; // No completions possible
    }
    currNode = currNode->branch[letter];
  }

  recursiveAddCompletions(currNode, currCompletions); // Add the completions from currNode recursively

  return currCompletions;
  
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

// Function to add completions generated from node
bool Trie::addCompletions(TrieNode *node, listOfObjects<string>* &currCompletions) {

  // Insert your code here
  listOfObjects<int>* currObject = node->indices; // Index list at currNode
  while(currObject != nullptr){ // While not at end of index list
    int index = currObject->object; // Retrieve the indes
    string stationName = nameDict->getKeyAtIndex(index); // Retrieve the station name at the index

    // Add to currCompletions
    listOfObjects<string>* newObject = new listOfObjects<string>(stationName);
    newObject->next = currCompletions;
    currCompletions = newObject;

    currObject = currObject->next;
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
