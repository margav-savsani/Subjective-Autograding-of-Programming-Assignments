#ifndef TRIE_H
#define TRIE_H

#ifndef DICTONARY_H
#include "dictionary.h"
#endif

using namespace std;

#define NUM_CHARS 26

class TrieNode 
{
    public:
        bool isWord;
        listOfObjects<int> *indices; // Indices in stnNameToIndex (alse referred
                                     // to as nameDict in Trie class) dictionary;
                                     // non-null only if isWord is true
        int numNonNullBranches;
        TrieNode *branch[NUM_CHARS];

        // Constructor
        TrieNode() 
        {
            isWord = false;
            indices = nullptr;
            numNonNullBranches = 0;
            for (int i = 0; i < NUM_CHARS; i++) 
            {
                branch[i] = nullptr;
            }
        }

        // Destructor
        ~TrieNode() 
        {
            listOfObjects<int> *currIndex = indices;
            while (currIndex != nullptr) 
            {
                listOfObjects<int> *toDeleteIndex = currIndex;
                currIndex = currIndex->next;
                delete toDeleteIndex;
            }
        }
};

class Trie 
{
    private:
        Dictionary<int> *nameDict;
        TrieNode *root;
        void recursiveDelete(TrieNode *node); // IMPLEMENTED
        bool isPresentInCompletions(listOfObjects<string> *completions, string name); // IMPLEMENTED
        void freeCompletionList(listOfObjects<string> *completions); // IMPLEMENTED
        bool recursiveAddCompletions(TrieNode *node, listOfObjects<string> * &currCompletions); // IMPLEMENTED
        bool addCompletions(TrieNode *node, listOfObjects<string> * &currCompletions);
        
    public:
        // Constructor
        Trie(Dictionary<int> *nameToIndex); // IMPLEMENTED
        // Destructor
        ~Trie(); // IMPLEMENTED  
        bool insert(string wordInName, int indexOfName); // DONE
        bool del(string wordInName, string name); // DONE
        listOfObjects<string> *completions(string prefix);
        bool isPresent(string wordInName); // IMPLEMENTED ==> Complete word
        void printTrie();
        void recursivePrintTrie(TrieNode *node, const string& prefix, int branchId, bool siblingsToRight); // IMPLEMENTED
};

#endif
