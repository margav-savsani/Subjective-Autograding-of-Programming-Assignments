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
  for(int i=0;i<len;i++){
    int x = int(wordInName[i]);
    x=x-65; //converting alphabets into index of the array
    if(currNode->branch[x] == nullptr){
      TrieNode *temp; //creating a new trienode*
      temp = new TrieNode();
      temp->isWord=false;
      temp->numNonNullBranches=0;
      currNode->branch[x] = temp;
      currNode->numNonNullBranches=currNode->numNonNullBranches+1;
      } // if that letter was not already there,creating a new node
    if(i==len-1){
        currNode->branch[x]->isWord=true;
        if(currNode->branch[x]->indices == nullptr){
          listOfObjects<int> *tem;
          tem = new listOfObjects<int>(indexOfName);
          tem->next = nullptr;
          currNode->branch[x]->indices = tem;
          break;
        }
        else{
          listOfObjects<int> *teme;
          teme = new listOfObjects<int>(indexOfName);
          teme->next=nullptr;
          listOfObjects<int> *xy;
          xy=currNode->branch[x]->indices;
          while(xy->next != nullptr){
            xy=xy->next;
          }
          xy->next=teme;
        }
    } // if the whole string insertion was done,we need to update the indices 
    currNode=currNode->branch[x]; //going onto the next node for the next insertion
  }
  return true;
}

bool Trie::del(string wordInName, string name) {
  TrieNode *currNode = root;
  TrieNode *lastBranchNode = nullptr;
  int lastBranchChar = -1;
  int len = wordInName.length();

  
  return true;
}

listOfObjects<string> * Trie::completions(string prefix) {
  TrieNode *currNode = root;
  int len = prefix.length(); //length of prefix
  listOfObjects<string> *currCompletions = new listOfObjects<string>("fuckyou"); //initialising currCompletions
  for(int i=0;i<len;i++){
    currNode=currNode->branch[int(prefix[i])-65];
  }
  recursiveAddCompletions(currNode,currCompletions);
  
  return currCompletions->next;
  
} //going till the prefix and calling the function recursiveAddCompletions

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
  listOfObjects<string> *zy;
  zy=currCompletions;
  listOfObjects<int> *rey = node->indices;
  listOfObjects<int> *reye = node->indices; // defining new variables so that playing around with them doesn't mess up the original values
  int l=0; //length of the list
  while(rey != nullptr){
    l=l+1;
    rey=rey->next;
  }
  for(int i=0;i<l;i++){
    string ap;
    ap=nameDict->getKeyAtIndex(reye->object);
    reye=reye->next;
    listOfObjects<string> *tmp;
    tmp = new listOfObjects<string>(ap);
    while(zy->next != nullptr){
      zy=zy->next;
    }
    zy->next=tmp;
    zy=zy->next;
  }
  return true;
} // adds new strings into the currCompletions

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
