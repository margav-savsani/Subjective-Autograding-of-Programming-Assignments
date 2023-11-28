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

bool Trie::insert(string wordInName, int indexOfName) {// branch[number n]  indicates the letter with ascii code 97 + n
  TrieNode *currNode = root;
  int len = wordInName.length();
  for(int i = 0; i < len; i++){// go down till last branch and if a branch is null, create it while going down
    
    if(currNode->branch[tolower(wordInName[i])-97] == nullptr){ 
      currNode->branch[tolower(wordInName[i])-97] = new TrieNode();
      currNode->numNonNullBranches++;  
    }
    currNode = currNode->branch[tolower(wordInName[i])-97];
  }
  currNode->isWord = true;// set isWord to true as now a word ends here
  if(currNode->indices == NULL){//linked list
    currNode->indices = new listOfObjects<int>(indexOfName);
  }
  else{
    listOfObjects<int>* insert = currNode->indices;// linked list, storing the indices
    while(insert->next!= nullptr) insert = insert->next;// stores indices recursively
    insert->next = new listOfObjects<int>(indexOfName);// store new index
  }
  return true;
}

bool Trie::del(string wordInName, string name) {// Karna baaki hai
  TrieNode *currNode = root;
  TrieNode *lastBranchNode = root;// parent of node on which recur delete is to be called if something to be deleted
  TrieNode *branchToBeDeleted = nullptr;
  int lastBranchChar = tolower(wordInName[0])-97;// index of child of lastBranchNode to be deleted
  for(int i = 0; i < wordInName.length(); i++){
    if(currNode->branch[tolower(wordInName[i])-97] == nullptr) return false;//wordInName not present
    if(currNode->isWord == true or currNode->numNonNullBranches > 1){// call recur delete if needed
      lastBranchNode = currNode;
      lastBranchChar = tolower(wordInName[i])-97;
    }
    currNode = currNode->branch[tolower(wordInName[i])-97];
  }
  if(currNode->isWord == 0) return false;
  listOfObjects<int> *list = currNode->indices, *prev = NULL;

  while(true){
    //check list ka object apna name hai ki nai, if yes, delete otherwise list = list->next
    if(nameDict->getKeyAtIndex(list->object) == name) break;
    prev = list;
    list = list->next;
    if(list == NULL) return false;
  }
  if(prev == NULL) currNode->indices = list->next;// first obj hi apna hai
  else prev->next = list->next;// koi aur hai
  delete(list);
  if(currNode->indices == NULL){//check karo apna node word hai ki nai
    currNode->isWord = false;
  }
  if(currNode->isWord == false && currNode->numNonNullBranches == 0){// koi node delete karna hai ki nai
    recursiveDelete(lastBranchNode->branch[lastBranchChar]);
    lastBranchNode->numNonNullBranches--;
    lastBranchNode->branch[lastBranchChar] = NULL;
  }
  return true;
}

listOfObjects<string>* Trie::completions(string prefix) {// main func
  TrieNode *currNode = root;
  int len = prefix.length();
  listOfObjects<string>* head = new listOfObjects<string>("NotAString");
  listOfObjects<string>* tail = head;
  if(currNode == nullptr) return nullptr;
  for(int i = 0; i < len; i++){
    if(currNode->branch[tolower(prefix[i])-97] == nullptr) return nullptr;
    currNode = currNode->branch[tolower(prefix[i])-97];// reach node from which we need completions
  }
  recursiveAddCompletions(currNode, head, tail);
  return head;  
}

bool Trie::recursiveAddCompletions(TrieNode* node, listOfObjects<string>* head, listOfObjects<string>* tail) {
  if (node->isWord) {
    if (!addCompletions(node, head, tail)) {
      return false;
    }
  }

  TrieNode *currNode = node;
  for (int i = 0; i < NUM_CHARS; i++) {
    if (currNode->branch[i] != nullptr) {
      if (!recursiveAddCompletions(currNode->branch[i], head, tail)) {// all children
	      return false;
      }
    }
  }

  return true;
}

bool Trie::addCompletions(TrieNode* node, listOfObjects<string>* head, listOfObjects<string>* tail) {// add completions of a node if isword is true
  
  listOfObjects<int>* values = node->indices;

  while(true){// ek linked list of node se values leke apni linked list mai daalna hai
    if (values == nullptr) return true;
    if(isPresentInCompletions(head, nameDict->getKeyAtIndex(values->object))){
      values = values->next;
      continue;
    }
    if(tail->object == "NotAString"){// placeholder
      tail->object= nameDict->getKeyAtIndex(values->object);
      values = values->next;
    }
    else{
      tail->next = new listOfObjects<string>(nameDict->getKeyAtIndex(values->object));
      tail = tail->next;
      values = values->next;
    }
  }

  // Insert your code here
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
