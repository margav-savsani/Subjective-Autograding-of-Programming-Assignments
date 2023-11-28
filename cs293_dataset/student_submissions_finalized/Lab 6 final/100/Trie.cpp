#ifndef TRIE_CPP
#define TRIE_CPP

#ifndef STD_HEADERS
#include "std_headers.h"
#endif
#include<algorithm>
#ifndef DICTIONARY_H
#include "dictionary.h"
#endif

#ifndef TRIE_H
#include "Trie.h"
#endif

using namespace std;

//constructor
Trie::Trie(Dictionary<int> *nameToIndex) {
  nameDict = nameToIndex;
  root = new TrieNode();
  if (root == nullptr) {
    cout << "Memory allocation failure." << endl;
    exit(-1);
  }
}

//destructor
Trie::~Trie() {
  recursiveDelete(root);
}

//deletes all elements in trie
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

//inserts new station in trie
bool Trie::insert(string wordInName, int indexOfName) {
  TrieNode *currNode = root;
  int len = wordInName.length();
  for(int i=0;i<len;i++){
     //to make wordInName uppercase
    transform(wordInName.begin(), wordInName.end(), wordInName.begin(), ::toupper); 

    //finds index of each letter of word
    int ind=(int)wordInName[i]-65;

    //checking the position is null or not if null giving it a memorylocation
    //else moving on next letter
    if(currNode->branch[ind]!=nullptr){
      currNode=currNode->branch[ind];
      continue;
    }
    else{
      currNode->branch[ind]=new TrieNode;
      currNode->numNonNullBranches+=1;
      currNode->branch[ind]->parent=currNode;
      currNode=currNode->branch[ind];
      currNode->pos=ind;
    }
  }
  currNode->isWord=true;          //making last node a leaf as end of word

  //storing index of the station name present in dictionary to the leaf of trie
  if(currNode->indices==nullptr){
    currNode->indices=new listOfObjects<int>(indexOfName);
  }
  else{
    listOfObjects<int>*last=currNode->indices,*prevnode=nullptr;
    while(last!=nullptr){
      if(last->object==indexOfName)return false;
      prevnode=last;
      last=last->next;
    }
    prevnode->next=new listOfObjects<int>(indexOfName);
  }
  return true;
}

//deletes all empty nodes after deleting a station name and index from trie
//this is helper function to del
bool Trie::deleteemptynodes(TrieNode* node){
  if(node==nullptr)return true;
  if(node==root)return true;
  if(node->numNonNullBranches>0 || node->indices!=nullptr)return true;
  TrieNode *newnode=node->parent;
  newnode->branch[node->pos]=nullptr;
  node->parent=nullptr;
  newnode->numNonNullBranches--;
  return deleteemptynodes(newnode);
}

//deletes a station name from trie by deleting each word taken as wordInName
bool Trie::del(string wordInName, string name) {
  TrieNode *currNode = root;
  TrieNode *lastBranchNode = nullptr;
  int lastBranchChar = -1;
  int len = wordInName.length();
  
  //reaching upto last node corresponding to prefix in trie
  for(int i=0;i<len;i++){
    if(currNode==nullptr)return false;
    lastBranchNode=currNode;
    int ind=toupper(wordInName.at(i))-'A';
    currNode=currNode->branch[ind];
  }

  //getting index  of station name
  int ip=nameDict->get(name)->value;
  listOfObjects<int> *indices=currNode->indices,*prev=nullptr;

  //searching for index in listofobjects
  while(indices!=nullptr){
    if(indices->object==ip)break;
    prev=indices;
    indices=indices->next;
  }

  //deleting empty nodes corresponding to station name
  if(indices==nullptr)return false;
  if(prev==nullptr){
    currNode->indices=nullptr;
    return deleteemptynodes(currNode);
  }
  prev->next=indices->next;

  return true;
}

//finds all stations starting with prefix
listOfObjects<string> * Trie::completions(string prefix) {
  TrieNode *currNode = root;
  int len = prefix.length();
  //creating a non empty list of objects
  listOfObjects<string> *currCompletions = new listOfObjects<string>("EMPTY");

  //finding last node in trie corresponding to prefix
  for(int i=0;i<len;i++){
    int ind=toupper(prefix.at(i))-'A';
    currNode=currNode->branch[ind];
    if(currNode==nullptr)return nullptr;
  }
  
  //recursively searches all branches of that last node and onward to find 
  //corresponding leaf nodes
  recursiveAddCompletions(currNode,currCompletions);

  //removes the dummy node from list
  currCompletions=currCompletions->next;
  return currCompletions;
  
}

//recursively  inds all completions adds them
bool Trie::recursiveAddCompletions(TrieNode *node, listOfObjects<string> *currCompletions) {
  if (node->isWord) {
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

//adds all station names corresponding to given leaf node
bool Trie::addCompletions(TrieNode *node, listOfObjects<string> *currCompletions) {

  listOfObjects<string> *tail=currCompletions,*prev=nullptr;

  //finds position in currcompletions to insert a new station name
  while(tail!=nullptr){
    prev=tail;
    tail=tail->next;
  }
  listOfObjects<int>*indices=node->indices;

  //add all station names from node indices to currcompletions list
  while(indices!=nullptr){
    int x=indices->object;
    string name=nameDict->getKeyAtIndex(x);   //gets station name from its index in dictionary
    if(prev==nullptr){
      prev=new listOfObjects<string>(name);
    }
    else{
      prev->next=new listOfObjects<string>(name);
      prev=prev->next;
    }
    indices=indices->next;
  }
  return true;
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
    if (node->isWord) {
      cout << "(isWord)";
      listOfObjects<int> *currIndices = node->indices;
      while (currIndices != nullptr) {
	cout << endl << prefix << "     " << nameDict->getKeyAtIndex(currIndices->object);
	currIndices = currIndices->next;
      }
    }
    else {
      cout << "()";
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