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
  int numNonNullBranches;
  TrieNode *branch[NUM_CHARS];

  // Constructor
  TrieNode() {
    isWord = false;  // True when the node represents end of word
    indices = nullptr;  // Stores the all possible indices of statin in which the word can be present.
    numNonNullBranches = 0;  // what does this do
    for (int i = 0; i < NUM_CHARS; i++) {
      branch[i] = nullptr;  // children
    }
  }
    bool isEmpty(){
        for(int i = 0; i<NUM_CHARS; i++){
            if(branch[i]){
                return false;
            }
        }
        return true;
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
  Dictionary<int> *nameDict;  // what does this do
  TrieNode *root;
  void recursiveDelete(TrieNode *node);
  bool isPresentInCompletions(listOfObjects<string> *completions, string name);
  void freeCompletionList(listOfObjects<string> *completions);
  bool recursiveAddCompletions(TrieNode *node, listOfObjects<string> *currCompletions);
  bool addCompletions(TrieNode *node, listOfObjects<string> *currCompletions);
  
 public:
  // Constructor
  Trie(Dictionary<int> *nameToIndex);
  // Destructor
  ~Trie();
  
  bool insert(string wordInName, int indexOfName);
  bool del(string wordInName, string name);
  listOfObjects<string> *completions(string prefix);
  bool isPresent(string wordInName);
};

#endif
