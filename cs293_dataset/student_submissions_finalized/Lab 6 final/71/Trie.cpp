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

  for (int i = 0; i < len; i++) {
    int letter = toupper(wordInName.at(i)) - 'A';
    if(currNode->branch[letter]==nullptr){
      TrieNode *temp=new TrieNode;
      currNode->branch[letter]=temp;
      currNode->numNonNullBranches+=1;
    }
    currNode=currNode->branch[letter];
  }
  if(currNode->indices==nullptr){
    currNode->isWord=true;
    listOfObjects<int> *n=new listOfObjects<int>(indexOfName);
    currNode->indices=n;
  }
  else{
    listOfObjects<int> *n=new listOfObjects<int>(indexOfName);
    n->next=currNode->indices;
    currNode->indices=n;
  }
  return true;
}

bool Trie::del(string wordInName, string name) {
  TrieNode *currNode = root;
  TrieNode *lastBranchNode = root;
  int lastBranchChar = toupper(wordInName.at(0)) - 'A';
  int len = wordInName.length();

  // Insert your code here
  if(!isPresent(wordInName)) return false;
  int indexOfName=nameDict->get(name)->value;
  for (int i = 0; i < len; i++) {
    int letter = toupper(wordInName.at(i)) - 'A';
    if(currNode->numNonNullBranches>1){
      lastBranchNode=currNode;
      lastBranchChar=letter;
    }
    else{
      if(currNode->isWord && i!=len-1){
        lastBranchNode=currNode;
        lastBranchChar=letter;
      }
    }
    currNode = currNode->branch[letter];
  }

  listOfObjects<int> *cur_i=currNode->indices;

  if(cur_i->next==nullptr){
    if(currNode->numNonNullBranches==0) {
      recursiveDelete(lastBranchNode->branch[lastBranchChar]);
      lastBranchNode->branch[lastBranchChar]=nullptr;
    }
    else currNode->isWord=false;
  }
  else{
    if(cur_i->object==indexOfName){
      currNode->indices=cur_i->next;
      delete cur_i;
    }
    else{
      listOfObjects<int> *prev_i=cur_i;
      cur_i=cur_i->next;
      while(cur_i!=nullptr){
        if(cur_i->object==indexOfName){
          prev_i->next=cur_i->next;
          delete cur_i;
          break;
        }
        prev_i=cur_i;
        cur_i=cur_i->next;
      } 
    }
  }
  return true;
}

listOfObjects<string> * Trie::completions(string prefix) {
  TrieNode *currNode = root;
  int len = prefix.length();
  listOfObjects<string> currCompletions("");

  // Insert your code here
  for (int i = 0; i < len; i++) {
    int letter = toupper(prefix.at(i)) - 'A';
    currNode = currNode->branch[letter];
  }
  recursiveAddCompletions(currNode, currCompletions);
  
  return currCompletions.next;
  
}

void Trie::recursiveAddCompletions(TrieNode *node, listOfObjects<string> &currCompletions) {
  if (node->isWord) {
    addCompletions(node,currCompletions);
    return;
  }

  TrieNode *currNode = node;
  for (int i = 0; i < NUM_CHARS; i++) {
    if (currNode->branch[i] != nullptr) {
    recursiveAddCompletions(currNode->branch[i], currCompletions);
    }
  }

}

void Trie::addCompletions(TrieNode *node, listOfObjects<string> &currCompletions) {

  // Insert your code here
  listOfObjects<int> *curr_i=node->indices;
  if(curr_i==nullptr) return ;

  string s=nameDict->getKeyAtIndex(curr_i->object);
  listOfObjects<string> *curr_lob= new listOfObjects<string> (s);

  listOfObjects<string> *prev= &currCompletions;
  while(prev->next!=nullptr){
    prev=prev->next;
  }
  prev->next=curr_lob;

  curr_i=curr_i->next;

  while(curr_i!=nullptr){
    string s=nameDict->getKeyAtIndex(curr_i->object);
    listOfObjects<string> *temp_lob= new listOfObjects<string> (s);
    curr_lob->next=temp_lob;
    curr_lob=curr_lob->next;
    curr_i=curr_i->next;  
  }

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
