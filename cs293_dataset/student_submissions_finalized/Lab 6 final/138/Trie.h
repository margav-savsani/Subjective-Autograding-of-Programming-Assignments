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
  void recursiveDelete(TrieNode *node); // deletes all nodes below and incuding the passed node
  bool isPresentInCompletions(listOfObjects<string> *completions, string name); // tells if a string already exists in the list fo possible completions
  void freeCompletionList(listOfObjects<string> *completions);//  given function
  bool recursiveAddCompletions(TrieNode *node, listOfObjects<string>* &currCompletions);// recusrively adds teh completions
  bool addCompletions(TrieNode *node, listOfObjects<string>* &currCompletions);// adds the possible completions
  
 public:
  // Constructor
  Trie(Dictionary<int> *nameToIndex);
  // Destructor
  ~Trie();
  
  bool insert(string wordInName, int indexOfName); // inserts a stationin the ttrie
  bool del(string wordInName, string name); // deleted a station name from word in name 
  listOfObjects<string> *completions(string prefix); // gives the list of all possible completions
  bool isPresent(string wordInName); // tells if a words exists in the trie or not
  void printTrie();// prints the trie
  void recursivePrintTrie(TrieNode *node, const string& prefix, int branchId, bool siblingsToRight);// prints the trie
  void DeleteFurther(TrieNode *node, string str); // deletes all the nodes with a given substring
};

#endif
