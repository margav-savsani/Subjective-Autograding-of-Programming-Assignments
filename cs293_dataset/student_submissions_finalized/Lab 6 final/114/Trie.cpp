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

  // Inserts all the letters
  for (int i = 0; i < len; i++){
    int letter = toupper(wordInName.at(i)) - 'A';
    if (currNode->branch[letter] == nullptr){
      currNode->branch[letter] = new TrieNode();
      currNode->numNonNullBranches += 1;
    }
    currNode = currNode->branch[letter];
  }

  // Tells that it is end of word
  currNode->isWord = true;

  listOfObjects<int>* temp = currNode->indices;
  listOfObjects<int>* temp_parent = currNode->indices;

  // Finds free position in the linked list
  while(temp != nullptr){
    temp_parent = temp;
    temp = temp->next;
  }

  // If the linkedlist is empty
  if (temp_parent == temp){
    currNode->indices = new listOfObjects<int>(indexOfName);
  } else {
    // If we have to append to the linked list, we have make it as next to its parent node
    temp_parent->next = new listOfObjects<int>(indexOfName);
  }

  return true;
}

TrieNode* delete_recursive(TrieNode* root, string word, Dictionary<int>* nameDict, string name, int depth = 0){
  if (root == nullptr){
    return NULL;
  }

  // If we have reached the end of the word
  if (depth == word.length()){
    if (root->isWord){

      // Counts no of words other than the one we are going to delete
      int count = 0;

      listOfObjects<int>* temp = root->indices;         // Current Node
      listOfObjects<int>* temp_parent = root->indices;  // Parent of Current Node
      
      while (temp != nullptr) {
        if (nameDict->getKeyAtIndex(temp->object) == name){
          // If linkedlist has only one element
          if (temp == root->indices && temp->next == nullptr){
            root->indices = nullptr;
          // If the index is stored at first element of linkedlist and there are other indexes attached to this node
          } else if (temp == root->indices && temp->next != nullptr){
            root->indices = temp->next;
          // If index is not stored at first node of linked list
          } else {
            temp_parent->next = temp->next;
          }
        } else {
          count++;
        }

        temp_parent = temp;
        temp = temp->next;
      }

      if (count == 0){
        root->isWord = false; // If the word doesnt have any other indexes attached to it, we have to make isword to false
      }

    }

    // We are deleting the node if it doesnt have any branches
    if(root->numNonNullBranches == 0 && !root->isWord){
      delete root;
      root = NULL;
    }

    return root;
  }

  int index = toupper(word[depth]) - 'A';

  // Recursively delete the node
  root->branch[index] = delete_recursive(root->branch[index], word, nameDict, name, depth + 1);

  // If the node has been deleted, we have to reduce count of no of filled branches
  if (root->branch[index] == NULL){
    root->numNonNullBranches -= 1;
  }

  // We dont need delete the actual root
  if (depth > 0){
    if (root->numNonNullBranches == 0 && root->isWord == false){
      delete root;
      root = nullptr;
    }
  }

  return root;
}

bool Trie::del(string wordInName, string name) {
  TrieNode *currNode = root;

  root = delete_recursive(currNode, wordInName, nameDict, name);

  return true;
}

listOfObjects<string> * Trie::completions(string prefix) {
  TrieNode *currNode = root;
  int len = prefix.length();
  listOfObjects<string> *currCompletions = nullptr;

  // Insert your code here

  // Goes to end of word
  for (int i = 0; i < len; i++){
    int letter = toupper(prefix.at(i)) - 'A';
    if (currNode->branch[letter] == nullptr){
      break;
    }
    currNode = currNode->branch[letter];
  }

  // If the word is present in the trie
  if (currNode != nullptr) {
    recursiveAddCompletions(currNode, currCompletions);
  }

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

bool Trie::addCompletions(TrieNode *node, listOfObjects<string>* &currCompletions) {

  // Insert your code here

  listOfObjects<int>* temp = node->indices;
  while (temp != nullptr) {
    bool found = false;
    string name = nameDict->getKeyAtIndex(temp->object);
    
    // If we havent initialized the linkedlist
    if (currCompletions == nullptr){
      currCompletions = new listOfObjects<string>(name);
    } else {

      listOfObjects<string>* temp2 = currCompletions;
      // We are going to end of linkedlist to add new words
      while (temp2->next != nullptr){
        temp2 = temp2->next;
      }
      
      temp2->next = new listOfObjects<string>(name);
    }

    temp = temp->next;
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
