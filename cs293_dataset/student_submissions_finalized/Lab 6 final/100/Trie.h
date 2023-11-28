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
  listOfObjects<int> *indices; // Indices in stnNameToIndex dictionary;
                              // non-null only if isLeaf is true
  int numNonNullBranches; 
  TrieNode *parent;             //parent of node
  int pos;                      //position of node in parent node
  TrieNode *branch[NUM_CHARS];

  // Constructor
  TrieNode() {
    isWord = false;
    indices = nullptr;
    parent=nullptr;
    pos=0;
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
  void recursiveDelete(TrieNode *node);
  bool isPresentInCompletions(listOfObjects<string> *completions, string name);
  void freeCompletionList(listOfObjects<string> *completions);
  bool recursiveAddCompletions(TrieNode *node, listOfObjects<string> *currCompletions);
  bool addCompletions(TrieNode *node, listOfObjects<string> *currCompletions);
  //deletes empty nodes after deleting a station index
  bool deleteemptynodes(TrieNode* node);
 public:
  // Constructor
  Trie(Dictionary<int> *nameToIndex);
  // Destructor
  ~Trie();
  
  bool insert(string wordInName, int indexOfName);
  bool del(string wordInName, string name);
  listOfObjects<string> *completions(string prefix);
  bool isPresent(string wordInName);
  void printTrie();
  void recursivePrintTrie(TrieNode *node, const string& prefix, int branchId, bool siblingsToRight);
};

#endif
