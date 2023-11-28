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

// This function inserts a given word into the trie.
// It goes down the trie and initialise if any essential childnode is nullptr to a new trienode.
// The last char or a node in the word is set to isWord to true.
// If listOfObjects is nullptr ,a new one is created and index is stored in them,
// else the new listOfObjects is appended to the already present list.

bool Trie::insert(string wordInName, int indexOfName) {
  TrieNode *currNode = root;
  int len = wordInName.length();

  // Insert your code here
  for(int i=0;i<len;i++){
    int letter = toupper(wordInName.at(i)) - 'A';

    if(currNode->branch[letter] == nullptr){
      currNode->branch[letter] =new TrieNode();
      currNode->numNonNullBranches++;
      currNode = currNode->branch[letter];
    }
    else{
      currNode = currNode->branch[letter];
    }
  }

  currNode->isWord = true;
  if(currNode->indices == nullptr){
    currNode->indices = new listOfObjects<int>(indexOfName);
    return true;
  }
  else{
    listOfObjects<int> *tail=currNode->indices;
    while(tail->next!=nullptr){
      tail = tail->next;
    }

    tail->next = new listOfObjects<int>(indexOfName);
    return true;
  }

  return false;
}

// There are actaully 5 cases corresponding to this.
// 1) Simple base case,the word is ascertained to more than 1 listOfObjects,we just have to remove the object corresponding to the name given as parameter.
// 2) The word has only 1 listOfObjects that is to be removed and the last node in the wordInName has more than 1 nonNullBranches.
// 3) Any proper node of wordInName has nonNUllBranches > 1
// 4) Any proper node of wordInName has isWord set to true.
// 5) None of the above satisfies,i.e; our wordInName is a straight set of nodes,no branches.

bool Trie::del(string wordInName, string name) {
  TrieNode *currNode = root;
  TrieNode *lastBranchNode = nullptr;
  int lastBranchChar = -1;
  int len = wordInName.length();

  // Insert your code here

  if(!isPresent(wordInName))return false;

  for(int i=0;i<len;i++){
    int letter = toupper(wordInName.at(i)) - 'A';

    currNode = currNode->branch[letter];
    if((i<len-1) && (currNode->numNonNullBranches > 1 || currNode->isWord == true)){
      lastBranchNode = currNode;
      lastBranchChar = i;
    }
    else if(i==len-1 && currNode->numNonNullBranches > 1){
      lastBranchNode = currNode;
      lastBranchChar = i;
    }

  }

  int count = 1;
  listOfObjects<int> *tail=currNode->indices;
  while(tail->next!=nullptr){
    count++;
    tail = tail->next;
  }

  if(count > 1){
    listOfObjects<int> *tail = currNode->indices;
    for(int i=0;i<count;i++){
      if(i ==0 && nameDict->getKeyAtIndex(tail->object) == name){
        currNode->indices = tail->next;
        return true;
      }

      else if(nameDict->getKeyAtIndex(tail->next->object) == name){
        tail->next = tail->next->next;    
        return true;   
      }

      else tail= tail->next;
    }
  }

  if(count ==1 && lastBranchNode == currNode){
    currNode->isWord = false;
    currNode->indices = nullptr;
    return true;
  }

  if(count ==1){
    if(lastBranchNode == nullptr){
      int letter = toupper(wordInName.at(0)) - 'A';
      recursiveDelete(root->branch[letter]);
      root->branch[letter] = nullptr;
    }

    else{
      int letter = toupper(wordInName.at(lastBranchChar+1)) - 'A';
      recursiveDelete(lastBranchNode->branch[letter]);
      lastBranchNode->branch[letter] = nullptr;
    }
  }

  return true;
}

// We go upto the last node of the given string prefix and exploit the use of recursiveAddCompletions to get 
// all the station names from that node onwards.

listOfObjects<string> * Trie::completions(string prefix) {
  TrieNode *currNode = root;
  int len = prefix.length();
  listOfObjects<string> *currCompletions = nullptr;

  // Insert your code here
  currCompletions = new listOfObjects<string>("dummy");

  for(int i=0;i<len;i++){
    int letter = toupper(prefix.at(i)) - 'A';
    currNode = currNode->branch[letter];
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

// Checks if the given node has isWord true and if so,
// appends the list of listOfObjects to the given currCompletions.

bool Trie::addCompletions(TrieNode *node, listOfObjects<string> *currCompletions) {

  // Insert your code here

  if(node->isWord == true){
    listOfObjects<int> *tail = node->indices;
    while(tail!=nullptr){
      string s = nameDict->getKeyAtIndex(tail->object);

      if(currCompletions == nullptr){
        currCompletions = new listOfObjects<string>(s);
      }

      else{
        while(currCompletions->next!=nullptr){
          currCompletions = currCompletions->next;
        }
        currCompletions->next = new listOfObjects<string>(s);
        currCompletions = currCompletions->next;
      }

      tail = tail->next;
    }

    return true;
  }
  return false;
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
