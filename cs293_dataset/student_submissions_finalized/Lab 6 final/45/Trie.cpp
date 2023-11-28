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

int pos(char c){
  return toupper(c)-'A';
}

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

  // Insert your code here
  int i=0;
  while(true){
    // if a branch is nullptr,then create a new node there
    int index=pos(wordInName[i]);
    if(currNode->branch[index]==nullptr){
      currNode->branch[index]=new TrieNode();
      currNode->numNonNullBranches++;
    }
    currNode=currNode->branch[index];
    // Now create a linked list with indexes of all names associated with 'wordInName'
    if(i==len-1){
      currNode->isWord=true;
      listOfObjects<int>* ptr = currNode->indices;
      currNode->indices=new listOfObjects<int>(indexOfName);
      currNode->indices->next=ptr;
      return true;
    }
    i++;
  }
  return false;
}

bool Trie::del(string wordInName, string name) {
  TrieNode *currNode = root;
  TrieNode *lastBranchNode = root;
  int lastBranchChar = pos(wordInName[0]);
  int len = wordInName.length();

  // Insert your code here
  int i=0;
  while(i<len){

    int index=pos(wordInName[i]);
    currNode=currNode->branch[index];

    // assigning nearest branch to leaf.branch is taken when that root of branch(say r)
    //then r->numNonNullBranches>1 or r->isword==true
    if((currNode->numNonNullBranches>1 or currNode->isWord==true) and i<len-1 )
    {
      lastBranchNode=currNode;
      lastBranchChar=pos(wordInName[i+1]);
    }
    
    if(i==len-1){

      listOfObjects<int>* ptr=currNode->indices;
      listOfObjects<int>* ptr2;
      ptr2=ptr;
      // deleting station name in indices
      if(currNode->indices->object==nameDict->get(name)->value){currNode->indices=currNode->indices->next;}
      else{
        while(true){
          if(ptr->next->object==nameDict->get(name)->value){
            listOfObjects<int>* ptr3=ptr->next->next;
            ptr->next=ptr3;
            break;
          }
          ptr=ptr->next;
        }
        currNode->indices=ptr2;
      }

      // doing a recursive deletion of that branch.
      if(currNode->indices==nullptr){
        if(currNode->numNonNullBranches==0){
          recursiveDelete(lastBranchNode->branch[lastBranchChar]);
          lastBranchNode->branch[lastBranchChar]=nullptr;
          lastBranchNode->numNonNullBranches--;
        }
        else{
          currNode->isWord=false;
        }
      }

      return true;

    }

    i++;
  }
  return false;
}

listOfObjects<string> * Trie::completions(string prefix) {
  TrieNode *currNode = root;
  int len = prefix.length();
  listOfObjects<string> *currCompletions=nullptr;

  for(int i=0;i<len;i++){// traversing to end of prefix in the trie
    int index=pos(prefix[i]);
    if(currNode->branch[index]!=nullptr){
      currNode=currNode->branch[index];
    }
    else{//in case prefix is not present in any word
      return nullptr;
    }
  }
  currCompletions=new listOfObjects<string>("$");
  recursiveAddCompletions(currNode,currCompletions);
  return currCompletions->next;
  
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

  // Insert your code here
  listOfObjects<int>* a;
  a=node->indices;
  listOfObjects<string>* b;
  listOfObjects<string>* p;
  b=new listOfObjects<string>(nameDict->getKeyAtIndex(a->object));
  p=b;//storing current address of b in a ptr p
  while(a->next!=nullptr){//traverse through a and add appropriate strings to b.
    a=a->next;
    b->next=new listOfObjects<string>(nameDict->getKeyAtIndex(a->object));
    b=b->next;  
  }
  b->next=currCompletions->next;// add currcompletions to now found linked list
  currCompletions->next=p;//store p in currCompletions->next
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
