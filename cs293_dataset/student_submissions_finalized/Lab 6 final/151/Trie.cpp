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

  for(int i = 0; i < len ; i++){
    
    
      // when the character is any alphabet

      int index = tolower(wordInName[i]) - 'a';
      // increase numNonNullBranches and update
      // the array of branches with the new alphabet
      if(currNode->branch[index] == nullptr){
        currNode->numNonNullBranches++;
        currNode->branch[index] = new TrieNode();
      }

      currNode = currNode->branch[index];
  }

  currNode->isWord = true;

      listOfObjects<int>* currObj = currNode->indices;
      
      if(currNode->indices == nullptr){
        currNode->indices = new listOfObjects<int>(indexOfName);
        return true;
      }

      while(currObj->next != nullptr){
        currObj = currObj->next;
      }
      currObj->next = new listOfObjects<int>(indexOfName);


  return true;
}

bool Trie::del(string wordInName, string name) {
  TrieNode *currNode = root;
  TrieNode *lastBranchNode = nullptr;
  int lastBranchChar = -1;
  int len = wordInName.length();
  bool isOnlyWord;

  for(int i = 0; i < len; i++){
    int index = tolower(wordInName[i]) - 'a';

    if(currNode->branch[index] == nullptr){
      return false;
    }
    if(currNode->numNonNullBranches > 1 || currNode->isWord){
      lastBranchNode = currNode;
      lastBranchChar = index;
    }
    currNode = currNode->branch[index];
  }

  if(currNode->isWord){
    listOfObjects<int>* currObj = currNode->indices;
    listOfObjects<int>* prevObj = nullptr;


    if(currNode->numNonNullBranches >= 1){

      if(currObj != nullptr && currObj->next == nullptr)
        isOnlyWord = true;
      else
        isOnlyWord = false;


      if(isOnlyWord){
        currNode->indices = nullptr;
        currNode->isWord = false;
        return true;
      }


      while(currObj != nullptr){
      if(nameDict->getKeyAtIndex(currObj->object) == name){
        prevObj->next = currObj->next;
        delete currObj;
      }
      prevObj = currObj;
      currObj = currObj->next;
      }

      return true;
    }


    if(lastBranchNode == nullptr){
      root = new TrieNode();
      return true;
    }

    if(currObj != nullptr && currObj->next == nullptr)
      isOnlyWord = true;
    else
      isOnlyWord = false;

    cout << isOnlyWord;
    cout << lastBranchChar;

    if(isOnlyWord){
      lastBranchNode->branch[lastBranchChar] = nullptr;
      lastBranchNode->numNonNullBranches--;
      return true;
    }


    while(currObj != nullptr){
      if(nameDict->getKeyAtIndex(currObj->object) == name){
        prevObj->next = currObj->next;
        delete currObj;
      }
      prevObj = currObj;
      currObj = currObj->next;
    }
    return true;
  }


  return false;
}

listOfObjects<string> * Trie::completions(string prefix) {
  TrieNode *currNode = root;
  int len = prefix.length();
  listOfObjects<string> *currCompletions = new listOfObjects<string>("test");

  // Insert your code here

  for(int i = 0; i < len; i++){
    int index = tolower(prefix[i]) - 'a';

    if(currNode->branch[index] == nullptr) return currCompletions;
    currNode = currNode->branch[index];
  }

  recursiveAddCompletions(currNode, currCompletions);

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
  listOfObjects<int>* currObj = node->indices;
  listOfObjects<string>* currString;
  if(currCompletions == nullptr){
    currCompletions = new listOfObjects<string>(nameDict->getKeyAtIndex(currObj->object));
    currObj = currObj->next;
    currString = currCompletions;
  } else {
    currString = currCompletions;
    while(currString->next != nullptr){
      currString = currString->next;
    }
  }

  while(currObj != nullptr){
    currString->next = new listOfObjects<string>(nameDict->getKeyAtIndex(currObj->object));
    currObj = currObj->next;
    currString = currString->next;
  }

  // Insert your code here

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

  return true;
  
}


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

#endif
