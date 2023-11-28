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
  listOfObjects<int> *indices; // Indices in stnNameToIndex (also referred
                               // to as nameDict in the Trie class) dictionary;
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
  // to delete recursively all the children and the given node
  void recursiveDelete(TrieNode *node);

  // To check if the given string is present in the list or not
  bool isPresentInCompletions(listOfObjects<string> *&completions, string name);

  // Used to empty the completion list
  void freeCompletionList(listOfObjects<string> *&completions);

  // To recursively update the list containg the station names having a word with given prefix
  bool recursiveAddCompletions(TrieNode *node, listOfObjects<string> *&currCompletions);

  // A function to add all the station names of the given node to list
  bool addCompletions(TrieNode *node, listOfObjects<string> *&currCompletions);

public:
  // Constructor
  Trie(Dictionary<int> *nameToIndex);
  // Destructor
  ~Trie();

  // Function to insert the node in trie
  bool insert(string wordInName, int indexOfName);

  // Function to delete the given station name from the node of the given word
  bool del(string wordInName, string name);

  // Function to make a list of station names haviing a word with given prefix
  listOfObjects<string> *completions(string prefix);

  // Function to check if given word exits in trie or not
  bool isPresent(string wordInName);

  // Function to print the trie
  void printTrie();

  // Helper function of the printTrie
  void recursivePrintTrie(TrieNode *node, const string &prefix, int branchId, bool siblingsToRight);

  // Function made to assist the del function
  void delete_intermediate(TrieNode *ptr, int index, string wordInName);
};

#endif
