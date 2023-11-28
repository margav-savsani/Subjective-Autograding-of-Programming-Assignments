#ifndef TRIE_H
#define TRIE_H

#include "dictionary.h"
using namespace std;

#define NUM_CHARS 26

class TrieNode {
 public:
  bool isWord;
  listOfObjects<int> *indices; // linked list of Indices in stnNameToIndex dictionary;
                              // non-null only if isLeaf is true
  int numNonNullBranches;
  TrieNode *branch[NUM_CHARS]; // i = 5 means branch[5] stores the character 'f'. i = 0 is 'a', and i = 25 is 'z'.

  // Constructor
  TrieNode(): isWord(false), indices(nullptr), numNonNullBranches(0){
    for (int i = 0; i < NUM_CHARS; i++) {
      branch[i] = nullptr;
    }
  }

  // Destructor
  ~TrieNode() {
    delete indices;
    // listOfObjects<int> *currIndex = indices;
    // while (currIndex != nullptr) {
    //   listOfObjects<int> *toDeleteIndex = currIndex;
    //   currIndex = currIndex->next;
    //   delete toDeleteIndex;
    // }
  }
};

class Trie {
 private:
  Dictionary<int> *nameDict;
  TrieNode *root;
  void recursiveDelete(TrieNode *node);
  bool isPresentInCompletions(listOfObjects<string> *completions, const string &name);
  void freeCompletionList(listOfObjects<string> *completions);
  bool recursiveAddCompletions(TrieNode *node, listOfObjects<string> *currCompletions);
  bool addCompletions(TrieNode *node, listOfObjects<string> *currCompletions);
  
 public:
  // Constructor
  Trie(Dictionary<int> *nameToIndex);
  // Destructor
  ~Trie();
  
  bool insert(const string &wordInName, int indexOfName);
  bool del(const string &wordInName, const string &name);
  listOfObjects<string> *completions(const string &prefix);
  bool isPresent(const string &wordInName);
};

#endif
