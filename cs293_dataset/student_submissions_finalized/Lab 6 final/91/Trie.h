#ifndef TRIE_H
#define TRIE_H

#include "dictionary.h"

#define NUM_CHARS 26

class TrieNode {
  public:
    bool isWord;
    listOfObjects<int>* indices; // Indices in stnNameToIndex (also referred
                                 // to as nameDict in the Trie class) dictionary;
                                 // non-null only if isWord is true
    int numNonNullBranches;
    TrieNode* branch[NUM_CHARS];

    // Constructor
    TrieNode();

    // Destructor
    ~TrieNode();
};

class Trie {
  private:
    Dictionary<int>* nameDict;
    TrieNode* root;
    void recursiveDelete(TrieNode* node);
    bool isPresentInCompletions(listOfObjects<std::string>* completions, std::string name);
    void freeCompletionList(listOfObjects<std::string>* completions);
    bool recursiveAddCompletions(TrieNode* node, listOfObjects<std::string>*& currCompletions);
    bool addCompletions(TrieNode* node, listOfObjects<std::string>*& currCompletions);
    
  public:
    // Constructor
    Trie(Dictionary<int>* nameToIndex);
    // Destructor
    ~Trie();
    
    bool insert(string wordInName, int indexOfName);
    bool del(string wordInName, std::string name);
    listOfObjects<std::string>* completions(std::string prefix);
    bool isPresent(string wordInName);

    void printTrie();
    void recursivePrintTrie(TrieNode* node, std::string const& prefix, int branchId, bool siblingsToRight);
};

#endif
