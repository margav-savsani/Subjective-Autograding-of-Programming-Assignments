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

bool Trie::insert(string wordInName, int indexOfName) { // inserts a new word into the trie
  TrieNode *currNode = root;
  
  int n=wordInName.length(),i=0;
  while(i<n){       //going through the trie
    int j;   //integer corresponding to the char(a-z or A-Z) . 
    if (wordInName[i] < 'a'){
      j=int(wordInName[i]-'A');
    }
    else j=int(wordInName[i]-'a');
    if(currNode->branch[j] != nullptr){    //if branch corresponding to the required char is already initialised traverse through that branch
      currNode=currNode->branch[j];
      i++;
      continue;
    }
    else{
      currNode->branch[j]=new TrieNode; //if its not initialised ,initialising it and then traversing
      currNode->numNonNullBranches++;
      currNode=currNode->branch[j];
      i++;    
    }
  }
  currNode->isWord=true; //After traversing through the chars corresponding to the chars in the string.The last branch should point to the complete word

  listOfObjects<int> * newword= new listOfObjects<int>(indexOfName),*currword = currNode->indices,*prevword;
  if(newword==nullptr) return false;
  if(currword ==nullptr){
    currNode->indices=newword;
    return true;
  }
  while (currword !=nullptr) {  //Adding the index corresponding to the complete word to the linked list
    prevword=currword;
    if(currword->object==indexOfName) break;
    currword=currword->next;
  }
  
  prevword->next=newword;

  return true;
}

bool Trie::del(string wordInName, string name) { //deletes a word from the trie
  TrieNode *currNode = root;
  TrieNode *lastBranchNode = nullptr; //the last  node with more than one  branches ,all branches below this must be deleted
  int lastBranchChar = -1;
  int len=wordInName.length(),i=0;
  while (i<len)
  {
    int j;
    if (wordInName[i] < 'a'){
      j=int(wordInName[i]-'A');
    }
    else j=int(wordInName[i]-'a');
    if(currNode->branch[j] != nullptr){
      
      if(currNode->numNonNullBranches >1){   //when a node has more the one branches it can be considered a lastBranchNode. 
        lastBranchNode=currNode; 
        lastBranchChar=j;
      }
      i++;
      currNode=currNode->branch[j];
      continue;
    }
    else{
      return false;
    }
  }
  if(!currNode->isWord) return false;

  listOfObjects<int> * currword=currNode->indices;
  listOfObjects<int> * prevword=nullptr;
  while(nameDict->getKeyAtIndex(currword->object) != name ){ 
    prevword=currword;
    currword=currword->next;
    if(currword == nullptr) return true;

  }
  if(prevword==nullptr && currword->next==nullptr ){  //If there is only one element in the indices
    recursiveDelete(lastBranchNode->branch[lastBranchChar]); //The  nodes upto the lastbranch must be deleted
    lastBranchNode->branch[lastBranchChar]=nullptr;
    return true;
  }

  prevword->next=currword->next;   //if there are more than one elements in the indices only the required element in indices must be deleted.
  delete currword; 
 
  return true;
}

listOfObjects<string> * Trie::completions(string prefix) {
  TrieNode *currNode = root;
  int len = prefix.length(),i=0;
  listOfObjects<string> *currCompletions = nullptr;
  bool found=true;

  while(i<len){    //traversing the trie following the prefix
 
    
    int j;
    if (prefix[i] < 'a'){
      j=int(prefix[i]-'A');
    }
    else j=int(prefix[i]-'a');
    if(currNode->branch[j] != nullptr){  
      
      
      i++;
      currNode=currNode->branch[j];
      continue;
    }
    else{
      found= false;  //if the prefix is not there is the trie 'found' becomes false
      break;
    }  
  }       
  
  if(found){
    recursiveAddCompletions(currNode,currCompletions); //when prefix is present in the trie doing recursiveAddCompletions from the node corresponding to last char in the prefix
  }

  return currCompletions;
  
}

bool Trie::recursiveAddCompletions(TrieNode *node, listOfObjects<string> * &currCompletions) {
  if (node->isWord) {       //A string can be added to completions only when the node has a word.
    if (!addCompletions(node, currCompletions)) {  
      return false;
    }
  }

  TrieNode *currNode = node;
  for (int i = 0; i < NUM_CHARS; i++) {
    if (currNode->branch[i] != nullptr) { //recursivly adding completions for each branch of a node.
      if (!recursiveAddCompletions(currNode->branch[i], currCompletions)) {
	return false;
      }
    }
  }

  return true;
}

bool Trie::addCompletions(TrieNode *node, listOfObjects<string> *&currCompletions) {
  if(!node->isWord) return false;

  listOfObjects<int>* currword=node->indices;
  while(currword != nullptr){ //iterating throught the linked list
    string temp = nameDict->getKeyAtIndex(currword->object);  //String corresponding to an index in the linked list

    listOfObjects<string> * currstr;
    if (currCompletions==nullptr){
      currCompletions=new listOfObjects<string>(temp);

    }
    else{
      bool found=isPresentInCompletions(currCompletions,temp); //checking if the string is already present in collections
      if(!found){
 
        currstr=new listOfObjects<string>(temp);  //if its not present adding it  at the front of the linked list
        currstr->next=currCompletions;
        currCompletions=currstr;
      }
    }
    currword=currword->next;
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
