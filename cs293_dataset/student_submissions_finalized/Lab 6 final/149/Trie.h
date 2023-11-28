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
  void recursiveDelete(TrieNode *node);
  bool isPresentInCompletions(listOfObjects<string> *completions, string name);
  void freeCompletionList(listOfObjects<string> *completions);
  bool recursiveAddCompletions(TrieNode *node, listOfObjects<string> *&currCompletions);
  bool addCompletions(TrieNode *node, listOfObjects<string> *&currCompletions);
  // listOfObjects<string> *prefixCompletor(TrieNode *node, string prefix)
  // {
  //   listOfObjects<string> *a;
  //   for (int i = 0; i < NUM_CHARS; i++)
  //   {
  //     if (node->branch[i] != nullptr)
  //     {
  //       if (node->branch[i]->isWord)
  //       {
  //         listOfObjects<string> *b = a;
  //         char x = i + 65;
  //         string s(1, x);
  //         prefix = prefix + s;
  //         a = new listOfObjects<string>(prefix);
  //         a->next = b;
  //       }
  //       listOfObjects<string> *b = a;
  //       char x = i + 65;
  //       string s(1, x);
  //       prefix = prefix + s;
  //       a = prefixCompletor(node->branch[i], prefix);
  //       a->next = b;
  //     }
  //   }
  // };

public:
  // Constructor
  Trie(Dictionary<int> *nameToIndex);
  // Destructor
  ~Trie();

  bool insert(string wordInName, int indexOfName);
  bool del(string wordInName, string name);
  listOfObjects<string> *completions(string prefix);
  bool isPresent(string wordInName);
  void delet(TrieNode *node, string word, int count);
  void printTrie();
  void recursivePrintTrie(TrieNode *node, const string &prefix, int branchId, bool siblingsToRight);
};

#endif
