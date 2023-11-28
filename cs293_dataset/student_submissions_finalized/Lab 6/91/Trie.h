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
    listOfObjects<int>* indices; // Indices in stnNameToIndex dictionary;
                                 // non-null only if isWord is true
    int numNonNullBranches;
    TrieNode* branch[NUM_CHARS];

    // Constructor
    TrieNode()
    {
        isWord = false;
        indices = nullptr;
        numNonNullBranches = 0;
        for (int i = 0; i < NUM_CHARS; i++) {
            branch[i] = nullptr;
        }
    }

    // Destructor
    ~TrieNode()
    {
        listOfObjects<int>* currIndex = indices;
        while (currIndex != nullptr) {
            listOfObjects<int>* toDeleteIndex = currIndex;
            currIndex = currIndex->next;
            delete toDeleteIndex;
        }
    }
};

class Trie {
  private:
    Dictionary<int>* nameDict;
    TrieNode* root;
    void recursiveDelete(TrieNode* node);
    bool isPresentInCompletions(listOfObjects<std::string>* completions, std::string name);
    void freeCompletionList(listOfObjects<std::string>* completions);
    bool recursiveAddCompletions(TrieNode* node, listOfObjects<std::string>* currCompletions);
    bool addCompletions(TrieNode* node, listOfObjects<std::string>* currCompletions);
    
  public:
    // Constructor
    Trie(Dictionary<int>* nameToIndex);
    // Destructor
    ~Trie();
    
    bool insert(string wordInName, int indexOfName);
    bool del(string wordInName, std::string name);
    listOfObjects<std::string>* completions(string prefix);
    bool isPresent(string wordInName);
};

#endif
