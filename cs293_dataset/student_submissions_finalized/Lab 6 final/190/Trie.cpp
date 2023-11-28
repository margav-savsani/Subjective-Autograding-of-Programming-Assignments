#ifndef TRIE_CPP
#define TRIE_CPP

#ifndef STD_HEADERS
#include "std_headers.h" 
#endif

#ifndef DICTIONARY_H
#include "dictionary.h"
#endif

#ifndef TRIE_H
#include "Trie.h"
#endif


#include <bits/stdc++.h>
using namespace std;

Trie::Trie(Dictionary<int> *nameToIndex) {
  nameDict = nameToIndex;
  root = new TrieNode();
  if (root == nullptr) {
    cout << "Memory allocation failure." << endl;
    exit(-1);
  }
}

Trie::~Trie() {
  recursiveDelete(root);
}

void Trie::recursiveDelete(TrieNode *node) {
  if (node == nullptr) {
    return;
  }
  else {
    for (int i = 0; i < NUM_CHARS; i++) {
      TrieNode *currNode = node->branch[i];
      recursiveDelete(currNode);
      node->branch[i] = nullptr;
    }
    if (node != root) {
      delete node;
    }
    return;
  }
}
 













// IT IS WORKING =================================================================
//==================================================================================
bool Trie::insert(string wordInName, int indexOfName) {
  TrieNode *currNode = root;
  int len = wordInName.length();

  // Insert your code here

  // ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^MAKING THE INSERT FUNCTION^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

  /* wordInName === e.g. Mumbai, Delhi, Central, ...
    Best way is to keep all letters small while inserting and later capitalising them as required.
  */ 


  // Making all letters lowercase in wordInName
  transform(wordInName.begin(), wordInName.end(), wordInName.begin(), ::tolower);

  // cout << "word to insert: " << wordInName << ", "<< indexOfName << endl;

  for(int i=0; i<len; i++){

    char letter = wordInName[i];

    // TrieNode *thisNode = currNode->branch[(int)(letter - 'a')]; // This is just a copy

    // if( currNode->branch[(int)(letter - 'a')] == nullptr){
    //   cout << "right now null pointer" <<endl;
    // }
    if( currNode->branch[(int)(letter - 'a')] == nullptr ){

      // This is the branch point
      //Increasing no of branches by 1
      currNode->numNonNullBranches++;

      TrieNode *newNode = new TrieNode();
      currNode->branch[(int)(letter - 'a')] = newNode;

      // cout << letter << endl;
    }

    // if( currNode->branch[(int)(letter - 'a')] == nullptr){
    //   cout << "still null pointer" <<endl;
    // }



    //At the end 
    currNode = currNode->branch[(int)(letter - 'a')];
  }


  // Now adding the index in the linked list in leaf
  // Please note that currNode is the leaf

  listOfObjects<int> *newlistnode = new listOfObjects<int>(indexOfName);
  // If used for the first time
  if(currNode->indices == nullptr){
    currNode->indices = newlistnode;
    currNode->isWord = true;
  }
  else{
    listOfObjects<int> *firstlistnode = currNode->indices;
    listOfObjects<int> *node_i = firstlistnode;

    while(node_i->next != nullptr){
      node_i = node_i->next;
    }

    //node_i is now the last node
    node_i->next = newlistnode;

  }

  // ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

  return true;
}











// IT IS WORKING YAY=================================================================
//==================================================================================

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
bool Trie::del(string wordInName, string name) {
// bool Trie::del(string wordInName, int index) {

  TrieNode *currNode = root;
  TrieNode *lastBranchNode = nullptr;
  int lastBranchChar = -1;
  int len = wordInName.length();
  
  // Insert your code here


  // ^^^^^^^^^^^^^^^^^^^^^^^CODE HERE^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

  // No use of parameter 'name' ig

  // Making all letters lowercase in wordInName
  transform(wordInName.begin(), wordInName.end(), wordInName.begin(), ::tolower);



  TrieNode *branchPointNode = root;
  char branchPointChar = wordInName[0];

  for(int i=0; i<len; i++){


    char letter = wordInName[i];

    if(currNode->numNonNullBranches > 1){
      branchPointChar = letter;
      branchPointNode = currNode;
    }
    
    currNode = currNode->branch[(int)(letter - 'a')];
    if(currNode == nullptr){
      cout << wordInName <<  " ----> NOT PRESENT IN TRIE" << endl;
      return false;
    }
  }


  lastBranchNode = currNode;

  
  listOfObjects<int> *firstlistnode = lastBranchNode->indices;
  listOfObjects<int> *node_i = firstlistnode;
  // listOfObjects<int> *parent_node_i = firstlistnode;

  // If first listnode is the required itself
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    if (nameDict->getKeyAtIndex(firstlistnode->object) == name){
    // if (firstlistnode->object == index){

      // Have to delete first node
      lastBranchNode->indices = firstlistnode->next;
    }

  // node_i goes from first node to second last node.
  while(node_i->next != nullptr){

    int myindex = node_i->next->object;

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    if (nameDict->getKeyAtIndex(myindex) == name){
    // if (myindex == index){

      // Have to delete listnode 'node_i->next'
      node_i->next = node_i->next->next;
      return true;
    }

    node_i = node_i->next;
  }


  // DOESNT MAKE SENSE IF IT IS NOT PRESENT IN THE LIST!!!
  // ---------DO THIS ONLY IF NAME NOT PRESENT IN LIST -------------
  // Deleting from the branch-point char from branch-point node
  if(firstlistnode == nullptr){
  	branchPointNode->branch[(int)(branchPointChar - 'a')] = nullptr;
  	branchPointNode->numNonNullBranches--;
  }
  // ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
  return true;
}












listOfObjects<string> * Trie::completions(string prefix) {
  TrieNode *currNode = root;
  int len = prefix.length();
  listOfObjects<string> *currCompletions = nullptr;

  // Making all letters lowercase in wordInName
  transform(prefix.begin(), prefix.end(), prefix.begin(), ::tolower);

  // Insert your code here

  // ^^^^^^^^^^^^^^^^^^^^^^^WRITING CODE HERE^^^^^^^^^^^^^^^^^^^^^^^^

  for(int i=0; i<len; i++){
    currNode = currNode->branch[(int)(prefix[i] - 'a')];
  }

  recursiveAddCompletions(currNode, currCompletions);

  // ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
  return currCompletions;
  
}











bool Trie::recursiveAddCompletions(TrieNode *node, listOfObjects<string>*& currCompletions) {
  if (node->numNonNullBranches == 0) {
    if (!addCompletions(node, currCompletions)) {
      return false;
    }
  }

  TrieNode *currNode = node;
  for (int i = 0; i < NUM_CHARS; i++) {
    if (currNode->branch[i] != nullptr) {
      if (!recursiveAddCompletions(currNode->branch[i], currCompletions)) {
        return false;
      }
    }
  }

  return true;
}









bool Trie::addCompletions(TrieNode *node, listOfObjects<string>*& currCompletions) {

  // Insert your code here

  //^^^^^^^^^^^^^^^^Just have to add the completions in the list^^^^^^^^^^^^^^^^^^

  //Getting last element of currCompletions list
  listOfObjects<string> *firststring = currCompletions;
  listOfObjects<string> *ithstring = firststring;

  if(currCompletions != nullptr){
    while(ithstring->next != nullptr) ithstring = ithstring->next;
  }

  listOfObjects<string> *laststring = ithstring;


  // Iterating through index list
  listOfObjects<int> *firstlistnode = node->indices;
  listOfObjects<int> *node_i = firstlistnode;
  while(node_i != nullptr){
    string str = nameDict->getKeyAtIndex(node_i->object);
    listOfObjects<string> *newstring = new listOfObjects<string>(str);

    if(laststring != nullptr){
      laststring->next = newstring;
      laststring = laststring->next;
    }
    else{
      currCompletions = newstring;
      laststring = currCompletions;
    }
    

    node_i = node_i->next;
  }

  return true;
  // ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
}















bool Trie::isPresentInCompletions(listOfObjects<string> *completions, string name) {
  listOfObjects<string> *currCompletion = completions;
  bool isPresent = false;
  while (currCompletion != nullptr) {
    if (currCompletion->object == name) {
      isPresent = true;
      break;
    }
    currCompletion = currCompletion->next;
  }
  return isPresent;
}

void Trie::freeCompletionList(listOfObjects<string> *completions) {
  listOfObjects<string> *currCompl = completions;
  while (currCompl != nullptr) {
    listOfObjects<string> *toDeleteCompl = currCompl;
    currCompl = currCompl->next;
    delete toDeleteCompl;
  }
  return;
}

bool Trie::isPresent(string wordInName) {
  TrieNode *currNode = root;
  int len = wordInName.length();

  for (int i = 0; i < len; i++) {
    int letter = toupper(wordInName.at(i)) - 'A';

    if (currNode->branch[letter] == nullptr) {
      return false;
    }
    currNode = currNode->branch[letter];
  }

  return currNode->isWord;
  
}

// Edit version 1: Added printTrie and recursivePrintTrie functions
// to help in debugging

void Trie::printTrie()
{
  recursivePrintTrie(root, "", -1, false);
}

// Adapted from Adrian Schneider's code on StackOverflow
// Basically a variation of the function we've been using
// print binary search trees in previous labs

void Trie::recursivePrintTrie(TrieNode *node, const string& prefix, int branchId, bool siblingsToRight)
{
  if (node != nullptr) {
    cout << prefix;
    
    cout << ((branchId == 0) ? "|-" : (branchId == -1)? " *":"|_" ) << (char) ((branchId != -1) ? 'A'+branchId: '*');
    cout << ((branchId == 0) ? '-' : (branchId == -1) ? '*':'_');
    
    // If this trie node has isWord set to true, print "(isWord)" and
    // also the list of complete station names (accessed through indices
    // in nameDict) associated with this trie node.






    //***************COMMENTING OUT*****************
    // if (node->isWord) {
    //   cout << "(isWord)";
    //   listOfObjects<int> *currIndices = node->indices;
    //   while (currIndices != nullptr) {
    //     cout << endl << prefix << "     " << nameDict->getKeyAtIndex(currIndices->object);
    //     currIndices = currIndices->next;
    //   }
    // }
    // else {
    //   cout << "()";
    // }
    //***********************************************

    // cout << "(" << node->numNonNullBranches << ")";
    
    // if node is a leaf node, print list
    if(node->numNonNullBranches == 0){
      listOfObjects<int> *firstlistnode = node->indices;
      listOfObjects<int> *node_i = firstlistnode;

      cout << "(";
      while(node_i != nullptr){
        cout << node_i->object << ", ";
        node_i = node_i->next;
      }
      cout << ")";

    }
    cout << endl;



    for (int i = 0; i < NUM_CHARS; i++) {
      TrieNode *currNode = node->branch[i];
      bool childrenToRight = false;
      for (int j = i+1; j < NUM_CHARS; j++) {
        if (node->branch[j] != nullptr) {
          childrenToRight = true;
          break;
        }
      }
      if (currNode != nullptr) {
        recursivePrintTrie(currNode, prefix + ((siblingsToRight) ? "│   " : "    "), i, childrenToRight);
      }
    }
  }
}
// End edit version 1

#endif
