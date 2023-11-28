#ifndef TRIE_H
#define TRIE_H

#include "dictionary.h"
using namespace std;

#define NUM_CHARS 26

class TrieNode {
 public:
  bool isWord; // the square node in the lectures. Demarcates the end of a word. Required since one word could be the prefix of another.
  listOfObjects<int> *indices = nullptr; // linked list of Indices in stnNameToIndex dictionary; non-null iff isWord is true. (for <=, note that since the word is a valid word, it is part of some station and hence indices is non-null)
  int numNonNullBranches;
  TrieNode *branch[NUM_CHARS]; /* i = 5 means branch[5] stores the character 'f' */ // Similarly, i = 0 is 'a', and i = 25 is 'z'.

  // Constructor
  TrieNode(): isWord(false), indices(nullptr), numNonNullBranches(0){
    for (int i = 0; i < NUM_CHARS; i++) {
      branch[i] = nullptr;
    }
  }

  // Destructor
  // ~TrieNode() {
  //   ll *currIndex = indices;
  //   while (currIndex != nullptr) {
  //     ll *toDeleteIndex = currIndex;
  //     currIndex = currIndex->next;
  //     delete toDeleteIndex;
  //   }
  // }
  ~TrieNode(){} // this is enough since in the trie we use a recursive delete procedure. Had trie's destructor just been `delete root` then yep, this would work. EIther way, simpler to have trie do the deletion and not worry about one node deleting another, esp. when nodes are to be deleted in the trie.
};

class Trie {
  typedef TrieNode * ptr_type;
 private:
  Dictionary<int> *nameDict; // stores all the station names as a dictionary. Note that a `name` is a station name and can correspond to more than one word in the trie.
  TrieNode *root; // root of the trie

  void recursiveDelete(TrieNode *node); // for destructor. Need this since 
  bool isPresentInCompletions(listOfObjects<string> *completions, const string &name);
  void freeCompletionList(listOfObjects<string> *completions);
  bool recursiveCompletions(TrieNode *node, listOfObjects<string> **currCompletions);
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

  void printTrie();
  void recursivePrintTrie(TrieNode *node, const string& prefix, int branchId, bool siblingsToRight);
};

#endif
