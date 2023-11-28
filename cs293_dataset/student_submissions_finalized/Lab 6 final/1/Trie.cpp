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
  for(int i = 0; i < len; i++){
    int c = toupper(wordInName[i]) - 'A';
    //cout << c << endl;
    if(currNode->branch[c] == nullptr){
      //inserting a new trie node for char c
      currNode->branch[c] = new TrieNode;
      currNode->numNonNullBranches++;
    }
    //node already exists
    currNode = currNode->branch[c];
  }
  //now currNode points to the TrieNode with the last letter of the word.
  //isWord at the last node
  currNode->isWord = true;
  //adding index of the station to the node's previously empty list of indices
  if(currNode->indices == nullptr){
    currNode->indices = new listOfObjects<int>(indexOfName);
    return true;
  }
  else{
    listOfObjects<int> * curr = currNode->indices;
    while(curr->next != nullptr){
      //check if the station name has already been stored in the last node
      if(curr->object == indexOfName){
        cout << "Station already exists" << endl;
        return true;
      }
      curr = curr->next;
    }
    //if not, link a new int index to the indices
    curr->next = new listOfObjects<int>(indexOfName);
    return true;
  }
}

bool Trie::del(string wordInName, string name) {
  TrieNode *currNode = root;
  TrieNode *lastBranchNode = nullptr;
  int lastBranchChar = -1;
  int len = wordInName.length();

  // Insert your code here
  for(int i = 0; i < len; i++){
    int c = toupper(wordInName[i]) - 'A';
    //cout << c << endl;
    //the path of the word doesn't exist.
    if(currNode->branch[c] == nullptr){
      cout << "No station with the word " << wordInName << endl;
      return false;
    }
    //lastBranchNode points to the last node which is a word itself/prefix of some other word.
    else{
      if(currNode->isWord || currNode->numNonNullBranches > 1){
        lastBranchNode = currNode;
        lastBranchChar = c;
      }
      currNode = currNode->branch[c];
    }
  }
  //currNode now points to the last node in the word's path
  if(!currNode->isWord){
    cout << "No station with the word " << wordInName << endl;
    return false;
  }
  bool isPrefix = currNode->numNonNullBranches > 0, deleted = false;
  listOfObjects<int> *prev = nullptr;
  listOfObjects<int> *curr = currNode->indices;
  //move in the list of indices until the station name found.
  //while storing the previous linked-list node
  while(curr != nullptr){
    if(nameDict->getKeyAtIndex(curr->object) == name){
      //cout << "found name" << endl;
      if(prev == nullptr){
        if(curr->next == nullptr){
          //it was the only station name with the word.
          currNode->isWord = false;
          currNode->indices = nullptr;
        }
        else{
          currNode->indices = curr->next;
        }
        delete curr;
        deleted = true;
        break;
      }
      else{
        prev->next = curr->next;
        delete curr;
        deleted = true;
        break;
      }
    }
    prev = curr;
    curr = curr->next;
  }
  if(!deleted){cout << "Station not found" << endl; return false;}
  //need to delete trie nodes if the word deleted occurred only in the one station name
  //or was a prefix to some other word.
  if(!currNode->isWord && !isPrefix){
    if(lastBranchNode == nullptr){
      recursiveDelete(root);
    }
    else{
      //delete everything in the sub-tree of the lastBranchNode corresponding to lastBranchChar
      recursiveDelete(lastBranchNode->branch[lastBranchChar]);
      lastBranchNode->branch[lastBranchChar] = nullptr;
      lastBranchNode->numNonNullBranches--;
    }
  }
  return true;  
}

listOfObjects<string> * Trie::completions(string prefix) {
  TrieNode *currNode = root;
  int len = prefix.length();
  listOfObjects<string> *currCompletions = new listOfObjects<string>("$$");
  //dummy string added to make it non NULL
  // Insert your code here
  for(int i = 0; i < len; i++){
    //compare characters in uppercase
    int c = toupper(prefix[i]) - 'A';
    //cout << c << endl;
    //prefix doesn't exist in the trie.
    if(currNode->branch[c] == nullptr){
      return nullptr;
    }
    currNode = currNode->branch[c];
  }
  //call recursive add
  if(!recursiveAddCompletions(currNode, currCompletions)) return nullptr;
  //delete the dummy string node at the head.
  listOfObjects<string> *temp = currCompletions->next;
  delete currCompletions;
  currCompletions = temp;
  return currCompletions;
}

bool Trie::recursiveAddCompletions(TrieNode *node, listOfObjects<string> *currCompletions) {
  //if is a word call add completions on the node
  if (node->isWord) {
    if (!addCompletions(node, currCompletions)) {
      return false;
    }
  }
  //then call recursive add on all the non-NULL children nodes.
  TrieNode *currNode = node;
  for (int i = 0; i < NUM_CHARS; i++) {
    if (currNode->branch[i] != nullptr) {
      //cout << char(i + 'A') << endl;
      if (!recursiveAddCompletions(currNode->branch[i], currCompletions)) {
	      return false;
      }
    }
  }

  return true;
}

bool Trie::addCompletions(TrieNode *node, listOfObjects<string> *currCompletions) {
  // Insert your code here
  listOfObjects<string> *to_add_at = currCompletions;
  if(currCompletions != nullptr){ //just a safety check, it should be non-NULL
    while(to_add_at->next != nullptr){
      to_add_at = to_add_at->next;
    }
  }
  if(node->isWord){
    //need to go over the indices/station names stored in the word node.
    listOfObjects<int> *curr = node->indices;
    while(curr != nullptr){
      string name = nameDict->getKeyAtIndex(curr->object);
      listOfObjects<string> *temp = currCompletions;
      bool repeat = false;
      //check if station name already a valid completion
      while(temp != nullptr){
        if(temp->object == name){
          repeat = true;
          break;
        }
        temp = temp->next;
      }
      if(!repeat){
        //if not repeated add to the completions' linked list
        to_add_at->next = new listOfObjects<string>(nameDict->getKeyAtIndex(curr->object));
        to_add_at = to_add_at->next;
      }
      //move to the next station name / index
      curr = curr->next;
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

void Trie::printTrie()
{
  recursivePrintTrie(root, "", -1, false);
}

// End edit version 1

#endif
