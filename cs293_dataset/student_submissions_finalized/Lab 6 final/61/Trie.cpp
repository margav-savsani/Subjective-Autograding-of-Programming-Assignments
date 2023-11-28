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
  for (int i = 0; i < len; i++) {
    int letter = toupper(wordInName.at(i)) - 'A';

    if (currNode->branch[letter] == nullptr) {
      currNode->branch[letter] =new TrieNode();
      currNode->numNonNullBranches++;
    }
    currNode = currNode->branch[letter]; 
  }
  listOfObjects<int> *newindex = new listOfObjects<int> (indexOfName);
  newindex->next=currNode->indices;
  currNode->indices=newindex;
  currNode->isWord=true;
  currNode->numNonNullBranches++;
  
 

  return true;

}

bool Trie::del(string wordInName, string name) {
  TrieNode *currNode = root;
  TrieNode *lastBranchNode = nullptr;
  int lastBranchChar = -1;
  int len = wordInName.length();
   if(isPresent(wordInName)){
    for (int i = 0; i < len; i++) {
    int letter = toupper(wordInName.at(i)) - 'A';
    if(currNode->numNonNullBranches>1){
      lastBranchNode=currNode;
      lastBranchChar=letter;
    }
    currNode = currNode->branch[letter];
  }
  int num=0;
  listOfObjects<int> *current=currNode->indices;
  listOfObjects<int> *prev=NULL;
  while(current!=NULL){
    if(nameDict->getKeyAtIndex(current->object)==name){
       if(prev==NULL){
        currNode->indices=currNode->indices->next;
       }
       else{
       prev->next=current->next;
       }
       
    }
    num++;
    prev=current;
    current=current->next;
  }
  if(num==1){
  if(currNode->numNonNullBranches!=1){
    currNode->isWord=false;
    currNode->indices=NULL;
  }
  else{
  lastBranchNode->branch[lastBranchChar]=NULL;
  }
  }
  return true;
  }

  else{
    return false;
  }

}

listOfObjects<string> * Trie::completions(string prefix) {
  TrieNode *currNode = root;
  int len = prefix.length();
  listOfObjects<string> *currCompletions = nullptr;
  for (int i = 0; i < len; i++) {
    int letter = toupper(prefix.at(i)) - 'A';
    if (currNode->branch[letter] == nullptr) {
      currCompletions = nullptr;
      return currCompletions;
    }
    currNode = currNode->branch[letter];
  }
  currCompletions=recursiveAddCompletions(currNode,currCompletions);

  return currCompletions;
  
}

listOfObjects<string> * Trie::recursiveAddCompletions(TrieNode *node, listOfObjects<string> *Completions) {
  if (node->isWord) {
      //cout<<"recaddcom:"<<currCompletions<<endl;
      Completions=addCompletions(node, Completions);
      //cout<<"recaddcom:"<<currCompletions<<endl;
      return Completions;
  }

  TrieNode *currNode = node;
  for (int i = 0; i < NUM_CHARS; i++) {
    if (currNode->branch[i] != nullptr) {
      Completions=recursiveAddCompletions(currNode->branch[i], Completions);
      
    }
  }
return Completions;

}

listOfObjects<string> * Trie::addCompletions(TrieNode *node, listOfObjects<string> *currCompletions) {
  
  listOfObjects<int> *current=node->indices;
  while(current!=NULL){
    listOfObjects<string> *newcom = new listOfObjects<string> ( nameDict->getKeyAtIndex(current->object));
    //cout<<nameDict->getKeyAtIndex(current->object)<<endl;
    newcom->next=currCompletions;
    currCompletions=newcom;
    current=current->next;
  }
  //cout<<"addCom:"<<currCompletions<<endl;
  return currCompletions;
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
