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
  int numIndices; //Number of indices at the leaf Node
  int pos; // The ascii value of char stored here minus that of 'A'
  int numNonNullBranches; 
  TrieNode *branch[NUM_CHARS];
  TrieNode* parent; //Parent of the the trie Node

  // Constructor
  TrieNode() {
    isWord = false;
    indices = nullptr;
    numIndices = 0;
    pos = -1;
    parent = nullptr;
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

  //Appending completions from the leaf node into 
  //the currCompletiosn list Of string objects
  bool addCompletions(TrieNode *node, listOfObjects<string> *currCompletions);

 public:
  // Constructor
  Trie(Dictionary<int> *nameToIndex);
  // Destructor
  ~Trie();
  
  // Inserts the wordInName contained in Name into the trie
  bool insert(string wordInName, int indexOfName);

  // Deletes the wordInName contained in name from the trie
  bool del(string wordInName, string name);

  // Returns a list of Object containing a linked list of strings 
  // which are matches of prefix in the trie
  listOfObjects<string> *completions(string prefix);
  bool isPresent(string wordInName);

  // Deletes recursively from the node till the root node
  // This is different from the recursiveDelete defined earlier
  // Here the deletion, is the removal is of a particular word 
  // from the trie
  void recursiveDel(TrieNode* node);

  //Prints the Trie
  void printTrie();
  void recursivePrintTrie(TrieNode *node, const string& prefix, int branchId, bool siblingsToRight);
};

#endif
