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

bool Trie::insert(string wordInName, int indexOfName) {

  TrieNode *currNode = root;
  int len = wordInName.length();

  int i=0;

  while(i<len){

    int z = int(wordInName[i]);
    
    if(z>=97 && z<=122){
      //need to create a new node only if alreaddy not present else skip to the next i
      if(currNode->branch[z-97] == nullptr){
        currNode->branch[z-97] = new TrieNode;
        if(currNode->branch[z-97]==nullptr){
          return false;
        }
        currNode->numNonNullBranches++;
      }
      currNode = currNode->branch[z-97];
    }
    
    else if(z>=65 && z<=90){
      if(currNode->branch[z-65] == nullptr){
        currNode->branch[z-65] = new TrieNode;
        if(currNode->branch[z-65]==nullptr){
          return false;
        }
        currNode->numNonNullBranches++;
      }
      currNode = currNode->branch[z-65];
    }
    
    i++;
  }
  
  //for the last node this should be set to true if not already
  if(currNode->isWord==false){
    currNode->isWord = true;
    currNode->indices = new listOfObjects<int>(indexOfName);
    if(currNode->indices == nullptr){//memory allocation failure
      return false;
    }
  }

  else{
    listOfObjects<int> *l = currNode->indices;
    //going to the first unoccupied pointer in the list 
    while(l->next != nullptr){
      l = l->next;
    }
    l->next = new listOfObjects<int>(indexOfName);
    if(l->next == nullptr){
      return false;
    }
  }
  
  return true;

}

bool Trie::del(string wordInName, string name) {
  TrieNode *currNode = root;
  TrieNode *lastBranchNode = nullptr;
  int lastBranchChar = -1;
  int len = wordInName.length();

  //checking if the word is actually present in the trie , if not then it would return false
  if(!isPresent(wordInName)){
    return false;
  }

  int i = 0;
  
  //matching the wordInName and currNode reaches the last matching character
  while(i<len){
    int z = int(wordInName[i]);

    if(z>=97 && z<=122){
      currNode=currNode->branch[z-97];
    }
    else if(z>=65 && z<=90){
      currNode=currNode->branch[z-65];
    }

    //make sure to do this!!!
    i++;
  }

  //if currNode isWord only then it makes sense to delete it ,as the listofindices is non-null only
  //if isWord is set to true
  if(currNode->isWord){
    listOfObjects<int> *l = currNode->indices;
    //storing prev pointer so that we can change its next
    listOfObjects<int> *prev = currNode->indices;
    listOfObjects<int> *t = currNode->indices;
    int num=0;

    while(t!=nullptr){
      //checking the number of indices stored in the linked list
      num++;
      t = t->next;
    }

    while(l!=nullptr){
      string x = nameDict->getKeyAtIndex(l->object);
      if(x==name){
        //if the linkedlist has only one node and it is the matching one
        if(l==currNode->indices && num==1){
          //only node removed so no more completions possible
          currNode->isWord = false;
          currNode->indices = nullptr;
          delete l;
          break;
        }
        else if(currNode->indices==l){
          currNode->indices = currNode->indices->next;
          delete l;
          //make sure to break as else we would loop with the l that we deletedand hence generating segfaults
          break;
        }
        else{
          prev->next = l->next;
          delete l;
          break;
        }
      }
      else{
        prev = l;
        l = l->next;
      }
    }
  }
  
  return true;
}

listOfObjects<string> * Trie::completions(string prefix) {

  TrieNode *currNode = root;
  int len = prefix.length();
  listOfObjects<string> *currCompletions = nullptr;

  int i=0;

  while(i<len){

    //ascii code of the character
    int z = int(prefix[i]);
    
    //small alphabets
    if(z>=97 && z<=122){
      if(currNode->branch[z-97]==nullptr){
        //no match found so return nullptr
        return currCompletions;
      }
      else{
        currNode=currNode->branch[z-97];
      }
    }
    
    //capital alphabets
    else if(z>=65 && z<=90){
      if(currNode->branch[z-65]==nullptr){
        return currCompletions;
      }
      else{
        currNode=currNode->branch[z-65];
      }
    }
  
    i++;
  }

  //give a value to currCompletions so as if we don't then we would have to initialize the pointer
  //in addCompletions function and since it is not passed by reference , the changes made there 
  //wouldn't be reflected here and hence we would always have been returning an nullptr here 
  currCompletions = new listOfObjects<string>("KABHI NAHI AYEGA");
  recursiveAddCompletions(currNode,currCompletions);
  //To not consider the default instance we had created
  currCompletions = currCompletions->next;

  return currCompletions;
}

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

bool Trie::addCompletions(TrieNode *node, listOfObjects<string> *currCompletions) {

  // only called when isWord is true so now add all elements from indices of that node
  // to the currCompletions string  
  // get the indexes and then use getkeyatindex function from dictionaries on the nameDict
  // to get the station names and add them to the currCompletions  

  listOfObjects<int> *l = node->indices;
  //after deletions maybe
  if(l==nullptr){
    return true;
  }
  listOfObjects<string> *z = currCompletions;

  //for the cases like mum is searched and we have both mumbai and mumbra , so then 
  //first completions for mumbai are added and then this function would be called for mumbra 
  //so we need to move to the last filled value so as to prevent overwriting of station names 
  while(z->next!=nullptr){
    z=z->next;
  }

  //loop until the list of indices ends
  while(l!=nullptr){
    //name of the station stored at the index given
    string x = nameDict->getKeyAtIndex(l->object);
    //if present then no need to add again in currCompletions
    if(!isPresentInCompletions(currCompletions,x)){
      z->next = new listOfObjects<string>(x);
      z = z->next;
    }
    l=l->next;
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
	if (node->branch[j] !=
   nullptr) {
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
