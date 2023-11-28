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

  // Root CANNOT be NULL -- that is a memory allocation failure. (take care in deletion)

  for(int i = 0; i < len; i++) {
    int index = toupper(wordInName.at(i)) - 'A';
    
    if (currNode->branch[index] == nullptr) {
      
      currNode->branch[index] = new TrieNode();
      currNode->numNonNullBranches++;
      
    }

    // termination condition. 

    if (i == len - 1){
      currNode->branch[index]->isWord = true;

      // add the indexOfName to the list of Objects iteratively. 
      listOfObjects<int> *currObj = currNode->branch[index]->indices;

      // base case. -- no memory for currObj
      if (currObj == nullptr) {
        
        currNode->branch[index]->indices = new listOfObjects<int>(indexOfName);
        return true;
      }

      // duplicate check. 
      if (currObj->object == indexOfName) { return false; }

      while (currObj->next != nullptr) {
        currObj = currObj->next;

        // checking for duplicates. 
        if (currObj->object == indexOfName){ return false; }
      }

      // reached at the end of the listOfObjects. 
      currObj->next = new listOfObjects<int>(indexOfName);
      return true;

    }

    currNode = currNode->branch[index];

  }

  // in case for some reason this happens. 

  return false;
}

bool Trie::del(string wordInName, string name) {

  TrieNode *currNode = root;
  TrieNode *lastBranchNode = nullptr;
  int lastBranchChar = -1;
  int len = wordInName.length();

  // Insert your code here

  /*
  1. Find the last node of what we want i.e. check if present
  2. If we reach end successfully, remove the key from the linked list. 
  3. We will get the key from the hash value of the name.  
  4. Then travel upward and delete the word as much as possible before encountering a sub-word, or a branch point. 
  */

  // unnecessary variable to break outer for loop. 
  bool setbreak = false;

  for (int i = 0; i < len; i++ ) {
    int index = toupper(wordInName.at(i)) - 'A';

    // updating last branch node/last word. 
    if (currNode->numNonNullBranches > 1 || currNode->isWord || currNode == root) {
      lastBranchNode = currNode;
      lastBranchChar = index; 
    }
    
    currNode = currNode->branch[index];

    if (currNode == nullptr) {return false;}
    
    // upon reaching the last node. 
    if (i == len - 1) {

      // index in linear probing. 
      int key = nameDict->get(name)->value;
    
      // removing this hash value
      listOfObjects<int>* currObj = currNode->indices;

      // base case. 
      
      // this should never happen but still. 
      if (currObj == nullptr) {return false; }

      if (currObj->object == key) {
        
        // if the key is same, change the indices of currNode. 
        // currObj->next = nullptr is handled. 

        currNode->indices = currObj->next;
      
        break;
      }      

      while (currObj->next != nullptr) {
        
        if (currObj->next->object == key) {
          currObj->next = currObj->next->next;
          setbreak = true;
          break;
        }
      }
      if (setbreak) break;

      else {
        return false;
      }
    }
  }

  // index is deleted. Now checking if the branch needs some nuking. 

  // if other names are there, we are done. 
  if (currNode->indices != nullptr) {return true;}

  // The harder case. 
  /*
  1. Remove the word till an isWord is found or a branch is found. -- handled by lastbranchnode/char
  2. RecursiveDelete
  */

  // deleting the stuff below last branch node. -- BUT if the "deleted" node has ANY children, just set isWord to false. 
  if (currNode->numNonNullBranches == 0){
    recursiveDelete(lastBranchNode->branch[lastBranchChar]);
    lastBranchNode->branch[lastBranchChar] = nullptr;
    if (lastBranchNode->numNonNullBranches > 1) lastBranchNode->numNonNullBranches--;
  }
  else if (currNode->numNonNullBranches > 0) {
    currNode->isWord = false; 
  }
  return true;
}

listOfObjects<string> * Trie::completions(string prefix) {

  TrieNode *currNode = root;
  int len = prefix.length();
  listOfObjects<string> *currCompletions = nullptr;

  /*
  1. Reach till the node of prefix
  2. Call RecursiveAddCompletions. 
  */

  for (int i = 0; i < len; i++) {

    int index = toupper(prefix.at(i)) - 'A';
    if (currNode->branch[index] == nullptr) {
      return nullptr; 
      cout << "Terminated" << endl;
    }
    currNode = currNode->branch[index];

  }

  recursiveAddCompletions(currNode, currCompletions);
  
  return currCompletions;
  
}

bool Trie::recursiveAddCompletions(TrieNode *node, listOfObjects<string> *&currCompletions) {
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

  /*
  At this point isWord is true. 
  0. Traverse through the linked list at this node for names. 
  1. If the corresponding name is already present, ignore
  2. If the name is not present in currCompletions, add it to the linked list. 
  */

  listOfObjects<int>* currNames = node->indices;
  
  while (currNames != nullptr) {
    bool add = true;
    listOfObjects<string> *currObj = currCompletions; 
    
    // base case
    if (currObj == nullptr) {
      currCompletions = new listOfObjects<string> (nameDict->getKeyAtIndex(currNames->object));
      currNames = currNames->next;
      continue;
    }

    if (currObj->object == nameDict->getKeyAtIndex(currNames->object)) add = false;

    // checking if the name is already present. 
    while (currObj->next != nullptr) {
      if (currObj->object == nameDict->getKeyAtIndex(currNames->object)) {add = false; break;}
      currObj = currObj->next;
    }

    // adding the name to the completions. 
    if (add == true) {
      currObj->next = new listOfObjects<string> (nameDict->getKeyAtIndex(currNames->object));
    }

    currNames = currNames->next;
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
