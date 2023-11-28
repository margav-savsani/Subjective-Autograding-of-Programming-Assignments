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
  void addIndex(int indexOfName){
    //cout<<"Inside insert"<<endl;
    listOfObjects<int> *currNode = indices;
    //cout<<"Is currNode NULL?"<<(currNode==NULL)<<endl;
    if (currNode==NULL){
      listOfObjects<int>* newNode = new listOfObjects<int>(indexOfName);
      indices = newNode;
    }
    else{
      while(currNode->next!=NULL){
        currNode = currNode->next;
      }
      listOfObjects<int>* newNode = new listOfObjects<int>(indexOfName);
      currNode->next = newNode;
    }
  }

  void deleteIndex(string name, Dictionary<int> *nameDict){
    // cout<<"I am here"<<endl;
    listOfObjects<int> *prevNode = indices;
    // cout<<"I prevNode NULL?"<<(prevNode==NULL)<<endl;
    // cout<<"I am here 2"<<endl;
    listOfObjects<int> *currNode = indices->next;
    // cout<<"I currNode NULL?"<<(currNode==NULL)<<endl;

    bool found = false;
    //The case where prevnode(indices) contains the correct name - then reinitialize indices
    if (nameDict->getKeyAtIndex(prevNode->object) == name){
        found = true;
        indices = indices->next;
    }
    else {
      while(currNode->next != NULL){
        if (nameDict->getKeyAtIndex(currNode->object) == name){
          found = true;
          prevNode->next = currNode->next;
        }
        currNode = currNode->next;
        prevNode = prevNode->next;
      }
      // To check the case if the last node has the correct name
      if (nameDict->getKeyAtIndex(currNode->object) == name){
          found = true;
          prevNode->next = NULL;
      }
    }
  }

  // void printIndices(){
  //   listOfObjects<int> *currNode = indices;

  //   if (currNode==NULL){
  //     cout<<"EMPTY LINKED LIST"<<endl;
  //   }
  //   while(currNode->next!=NULL){
  //     cout<<"Printing elements"<<endl;
  //     cout<<currNode->object<<" ";
  //   }
  //   cout<<endl;
  // }

  bool isListEmpty(){
    if (indices == NULL){
      return true;
    }
    else{
      return false;
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
  bool isPresent(string wordInName);
  void recursivePrintTrie(TrieNode *node, const string& prefix, int branchId, bool siblingsToRight);
  void printTrie();
  void addStationName(string Name, listOfObjects<string> *currCompletions);
  bool find(string Name, listOfObjects<string> *currCompletions);
};

#endif
