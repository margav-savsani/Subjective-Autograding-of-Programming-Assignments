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

using namespace std;
//Constructor
Trie::Trie(Dictionary<int> *nameToIndex) {
  nameDict = nameToIndex;
  root = new TrieNode();
  if (root == nullptr) {
    cout << "Memory allocation failure." << endl;
    exit(-1);
  }
}
//Destructor
Trie::~Trie() {
  recursiveDelete(root);
}
//Recursively Deletes the entire Trie starting at node
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
//inserts a given station name in the trie 
//along with its occurence index in dictionary
bool Trie::insert(string wordInName, int indexOfName) {
  TrieNode *currNode = root;
  //length of station name
  int len = wordInName.length();
  //stores capitalized station name
  char Word[len];
  for (int i=0;i<len;i++){
    Word[i]=(char)toupper(wordInName[i]);
  }
  //Executing the loop for each char in station name
  for (int i=0;i<len;i++){
    int index=(int(Word[i])-65);
    if (currNode->branch[index]==nullptr){
      TrieNode * newnode=new TrieNode();
      currNode->branch[index]=newnode;
      currNode->numNonNullBranches++;
    }
    currNode=currNode->branch[index];
  }
  //Storing the index in the linked list
  currNode->isWord=true;
  if(currNode->indices!=nullptr){
    listOfObjects<int> *curr;
    curr=currNode->indices;
    while(curr->next!=nullptr){
      curr=curr->next;
    }
    curr->next=new listOfObjects(indexOfName);
  }
  else{
    currNode->indices=new listOfObjects(indexOfName);
  }
  // Insert your code here
  //Returns true after successful insertion
  return true;
}
//Deletes a given station name from the trie
bool Trie::del(string wordInName, string name) {
  //Stores the current node
  TrieNode *currNode = root;
  //Stores the last node which has either two children or is the ending of a word
  TrieNode *lastBranchNode = nullptr;
  //Index of next attached branch to the lastBranchNode 
  int lastBranchChar = -1;
  //Length of station prefix
  int len = wordInName.length();
  //Capitalizing it
  char Word[len];
  for (int i=0;i<len;i++){
    Word[i]=(char)toupper(wordInName[i]);
  }
  //Matching all characters of station name 
  int i=0;
  int index=(int(Word[i]-65));
  while (currNode->branch[index]!=nullptr && i<len){
    //Updating lastBranchNode and lastBranchChar
    if(currNode->numNonNullBranches>1 || currNode->isWord){
      lastBranchNode=currNode;
      lastBranchChar=index;
    }
    //Going down one level
    currNode=currNode->branch[index];
    i++;
    if(i<len){
      index=(int(Word[i])-65);
    }
  }
  //Stores whether the linked list becomes empty or not
  bool noindex=false;
  if(i==len){
    //Deleting according to cases
    if(currNode->indices!=nullptr){
      listOfObjects<int> *curr;
      curr=currNode->indices;
      if(!(name!=nameDict->getKeyAtIndex(curr->object))){
        if(curr->next==nullptr){
          currNode->indices=nullptr;
          //linked list becomes empty
          noindex=true;
        }
        else{
          currNode->indices=curr->next;
          curr=curr->next;
        }
      }
      else{
        while (curr->next!=nullptr && name!=nameDict->getKeyAtIndex(curr->next->object)){
          curr=curr->next;
        }
        if(curr->next!=nullptr){
          if(curr->next->next==nullptr){
            curr->next=nullptr;
          }
          else{
            curr->next=curr->next->next;
          }
        }
      }
    }
  }
  //Pruning the tree from lastBranchNode
  if(noindex){
    TrieNode *currNode = lastBranchNode;
    currNode->branch[lastBranchChar]=nullptr;
  }
  // Insert your code here
  //Returning true after successful deletion
  return true;
}
//Completes the prefix of station name by checking all possible names
listOfObjects<string> * Trie::completions(string prefix) {
  TrieNode *currNode = root;
  //length of prefix
  int len = prefix.length();
  //Capitalizing the prefix
  char Word[len];
  for (int i=0;i<len;i++){
    Word[i]=(char)toupper(prefix[i]);
  }
  //linked list storing all possible completions
  listOfObjects<string> *currCompletions = nullptr;
  int i=0;
  int index=(int(Word[i])-65);
  //Going till the end of prefix
  while(currNode->branch[index]!=nullptr && i<len){
    currNode=currNode->branch[index];
    i++;
    if(i<len){
      index=(int(Word[i])-65);
    }
  }
  //Invoking recursive add completion at that node
  if (i==len){
    recursiveAddCompletions(currNode,currCompletions);
  }


  // Insert your code here
  //Returning the completions
  return currCompletions;
   
}
//Finds all possible completion given a particular node
bool Trie::recursiveAddCompletions(TrieNode *node, listOfObjects<string> *&currCompletions) {
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
  //Returning true
  return true;
}
//Adding all possible names from a given node to currCompletions
bool Trie::addCompletions(TrieNode *node, listOfObjects<string> *&currCompletions) {
  TrieNode *currNode=node;
  //Depending on case
  if (currCompletions==nullptr){
    if(currNode->indices!=nullptr){
      listOfObjects<int> *curr;
      curr=currNode->indices;
      currCompletions=new listOfObjects(nameDict->getKeyAtIndex(curr->object));
      while (curr->next!=nullptr){
        curr=curr->next;
        currCompletions->next=new listOfObjects(nameDict->getKeyAtIndex(curr->object));
        currCompletions=currCompletions->next;
      } 
    }
    //returning true
    return true;
  }
  else{
    if(currNode->indices!=nullptr){
      listOfObjects<int> *curr;
      curr=currNode->indices;
      currCompletions->next=new listOfObjects(nameDict->getKeyAtIndex(curr->object));
      while(curr->next!=nullptr){
        curr=curr->next;
        currCompletions->next=new listOfObjects(nameDict->getKeyAtIndex(curr->object));
        currCompletions=currCompletions->next;
      }
    }
    //returning true
    return true;
  }
  // Insert your code here
  //returning false
  return false;
}
//Checks for presence in completion
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
//Generates list of completion
void Trie::freeCompletionList(listOfObjects<string> *completions) {
  listOfObjects<string> *currCompl = completions;
  while (currCompl != nullptr) {
    listOfObjects<string> *toDeleteCompl = currCompl;
    currCompl = currCompl->next;
    delete toDeleteCompl;
  }
  return;
}
//checks for a particular station name
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
