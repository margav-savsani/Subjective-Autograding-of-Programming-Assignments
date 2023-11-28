#ifndef TRIE_H
#define TRIE_H

#ifndef DICTONARY_H
#include "dictionary.h"
#endif

using namespace std;

#define NUM_CHARS 26

class TrieNode {
 public:
  bool isWord;
  listOfObjects<int> *indices; // Indices in stnNameToIndex (also referred
                               // to as nameDict in the Trie class) dictionary;
                               // non-null only if isWord is true
  int numNonNullBranches;      // Number of Non Null Branches of a Node
  TrieNode *branch[NUM_CHARS]; // All the Branches originating from a Node

  // Constructor
  TrieNode() {
    isWord = false;
    indices = nullptr;
    numNonNullBranches = 0;
    for (int i = 0; i < NUM_CHARS; i++) {
      branch[i] = nullptr;
    }
  }

  // Destructor
  ~TrieNode() {
    listOfObjects<int> *currIndex = indices;
    while (currIndex != nullptr) {
      listOfObjects<int> *toDeleteIndex = currIndex;
      currIndex = currIndex->next;
      delete toDeleteIndex;
    }
  }
};

class Trie {
 private:
  Dictionary<int> *nameDict;
  TrieNode *root;
  void recursiveDelete(TrieNode *node);      // Recursively Delete everything from a given Node
  bool isPresentInCompletions(listOfObjects<string> *completions, string name);
  void freeCompletionList(listOfObjects<string> *completions);
  bool recursiveAddCompletions(TrieNode *node, listOfObjects<string> *currCompletions);
  bool addCompletions(TrieNode *node, listOfObjects<string> *currCompletions);  
  
 public:
  // Constructor
  Trie(Dictionary<int> *nameToIndex);
  // Destructor
  ~Trie();
  
  bool insert(string wordInName, int indexOfName);      // Insert a new Station Name into Trie with a particlar Index
  bool del(string wordInName, string name);             // Function to Delete a particular word from Trie
  listOfObjects<string> *completions(string prefix);    // Linked List to store completions of a given prefix
  bool isPresent(string wordInName);                    // To check if a string is present in the Trie
  void printTrie();                                     // To Print Trie
  void recursivePrintTrie(TrieNode *node, const string& prefix, int branchId, bool siblingsToRight); // To Print Recursively

};

#endif
