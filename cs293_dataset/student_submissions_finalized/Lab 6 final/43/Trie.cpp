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
  for(int i = 0; i< len;i++){
    char p = toupper(wordInName.at(i));
    if(currNode->branch[p -'A'] == nullptr){   //If the branch is not present before it creates a new branch.
      currNode->numNonNullBranches++;
      currNode->branch[p -'A'] = new TrieNode();
    }
    currNode = currNode->branch[p-'A'];
    if(i == len-1){   //At the last node adds the indices after adding the node
        currNode->isWord = true;
        listOfObjects<int> *q = currNode->indices;
        if(currNode->indices == nullptr){ //if indices is a nullptr
          currNode->indices = new listOfObjects<int>(indexOfName);
        }
        else{
          while(q->next != nullptr){ //goes to the last of indies list
            q = q->next;
          }
           q->next = new listOfObjects<int>(indexOfName);
        }
    }
  }
  // Insert your code here

  return true;
}

bool Trie::del(string wordInName, string name) {
  TrieNode *currNode = root;
  TrieNode *lastBranchNode = nullptr;
  int lastBranchChar = -1;
  int len = wordInName.length();
  for(int i = 0;i<len;i++){
    char p = toupper(wordInName.at(i));
    if( currNode->branch[p-'A'] == nullptr){
      return false;
    }
    if(currNode->numNonNullBranches > 1){ //stores the last branch to delete the whole branch in case
      lastBranchNode = currNode;
      lastBranchChar = p-'A';
    }
    currNode = currNode->branch[p-'A'];
  }
  listOfObjects<int> *q = currNode->indices;
  if(q->next == nullptr){// this is the case where whole branch is to be deleted.
    TrieNode *z = lastBranchNode->branch[lastBranchChar];
    lastBranchNode->branch[lastBranchChar] = nullptr;
    lastBranchNode->numNonNullBranches = lastBranchNode->numNonNullBranches-1;
    recursiveDelete(z);  
  }
  else{ //this is the case where branch is not needed to be deleted.
    if(nameDict->getKeyAtIndex(q->object) == name){//first element of the list is the searching element
      currNode->indices = q->next;
    }
    else{
      listOfObjects<int> *p = q->next;
      while(nameDict->getKeyAtIndex(p->object) != name){ //if it is not the first element
        p = p->next;
        q = q->next;
      }
    q->next = p->next;
    }
  }
  return true;
}
listOfObjects<string> * Trie::completions(string prefix) {
  TrieNode *currNode = root;
  TrieNode *q;
  int len = prefix.length();
  listOfObjects<string> *currCompletions = new listOfObjects<string>("!!");
  for(int i = 0; i < len;i++){
    char p = toupper(prefix.at(i));
    if(currNode->branch[p - 'A'] == nullptr){
      return nullptr;
    }
    currNode = currNode->branch[p-'A'];
  }
  recursiveAddCompletions(currNode,currCompletions);//recursively add the completions of the before nodes.

  // Insert your code here
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

bool Trie::addCompletions(TrieNode *node, listOfObjects<string> *currCompletions) { // adds the completions of the present node to the currCompletions list
  listOfObjects<int> *q = node->indices;
  listOfObjects<string> *r = currCompletions;
  while(r->next != nullptr){ //going to the last of the list
    r = r->next;
  }
  if(node->isWord){
    while(q != nullptr){ //adding completions
      int p = q->object;
      string s = nameDict->getKeyAtIndex(p);
      r->next =  new listOfObjects<string>(s);
      r = r->next;
      q = q->next;
    }
  // Insert your code here
  
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
