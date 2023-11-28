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
  listOfObjects<string>* autocomp(TrieNode* curr, listOfObjects<string>* end){
  if(curr == nullptr){
    return end;
  }
  if(curr->isWord){
    listOfObjects<int>* a = curr->indices;
    while(a != nullptr){
      end->next = new listOfObjects<string> (nameDict->getKeyAtIndex(a->object));
      end = end->next;
      a = a->next;
    }
  }
  if(curr->numNonNullBranches == 0){
    return end;
  }
  for (int i=0; i < 26; i++){
    end = autocomp(curr->branch[i], end);
  }
  return end;
}
  bool isPresent(string wordInName);
  bool isEmpty(TrieNode* root)
{
    for (int i = 0; i < 26; i++)
        if (root->branch[i])
            return false;
    return true;
}
  void printTrie();
  void recursivePrintTrie(TrieNode *node, const string& prefix, int branchId, bool siblingsToRight);
};

#endif
