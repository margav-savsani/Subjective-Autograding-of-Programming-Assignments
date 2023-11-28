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

  // Insert your code here
  int i;
  for(i=0;i<len;i++){
    if (currNode->branch[wordInName[i]-'A']==nullptr)
    {
      currNode->branch[wordInName[i]-'A'] = new TrieNode();
    }
      currNode=currNode->branch[wordInName[i]-'A'];
  }

  listOfObjects<int>* t = currNode->indices;
  listOfObjects<int>* p = currNode->indices;
    while(t!=nullptr)
    {
      if(t->object==indexOfName) return false;  //checks if that index is already inserted
      else {
        p = t;
        t=t->next;

      }
    }
    
    if (p == nullptr) {
      currNode->indices = new listOfObjects<int>(indexOfName);
    }
    else {
      p->next =new listOfObjects<int>(indexOfName);
    }
    currNode->numNonNullBranches+=1;
    currNode->isWord=true;
  return true;
}

bool Trie::del(string wordInName, string name) {
  TrieNode *currNode = root;
  TrieNode *lastBranchNode = nullptr;
  int lastBranchChar = -1;
  int len = wordInName.length();
  
  // Insert your code here
  TrieNode *r = root;
  int i;
  for ( i = 0; i < wordInName.length(); i++)
  {
    if (currNode->branch[wordInName[i]-'A']==nullptr)
    {
      break;
    }
      currNode=currNode->branch[wordInName[i]-'A']; 
  }
  if(i!=wordInName.length()-1) return true;
  else{
    while(currNode->indices!=nullptr){  
      if(nameDict->getKeyAtIndex(currNode->indices->object)==name){
        if(currNode->indices->next!=nullptr){
          while(currNode->indices->next!=nullptr){
            currNode->indices->next=currNode->indices;
            currNode->indices=currNode->indices->next;
          }
          currNode->indices=nullptr;
        }
      }
      else currNode->indices=currNode->indices->next;
    }
  }
  
  return true;
}

listOfObjects<string> * Trie::completions(string prefix) {
  TrieNode *currNode = root;
  int len = prefix.length();
  for(int q=0;q<len;q++){
    prefix[q]=toupper(prefix.at(q));  //used this to make it case insensitive
  }
  listOfObjects<string> *currCompletions = nullptr;
  currCompletions=new listOfObjects<string>("d");
  int i;
  for( i=0;i<len;i++){
    if (currNode->branch[prefix[i]-'A']!=nullptr)
    {
      currNode=currNode->branch[prefix[i]-'A'];
    }
    else break;
  }
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
  listOfObjects<int> *q = node->indices;
  listOfObjects<string> *d = currCompletions;
  while (q!=nullptr)
  {
    while(d->next!=nullptr) d=d->next;
    d->next = new listOfObjects<string>(nameDict->getKeyAtIndex(q->object));
    d=d->next;
    q=q->next;
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
