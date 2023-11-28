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

//constructor
Trie::Trie(Dictionary<int> *nameToIndex) {
  nameDict = nameToIndex;
  root = new TrieNode();
  if (root == nullptr) {
    cout << "Memory allocation failure." << endl;
    exit(-1);
  }
}
//destructors
Trie::~Trie() {
  recursiveDelete(root);
}
//recursively deletes the trie below the provided node
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
//inserts a word inside the trie
bool Trie::insert(string wordInName, int indexOfName) {
  TrieNode *currNode = root;
  int len = wordInName.length();
  for(int i = 0; i < len; i++){
    if(currNode->branch[wordInName[i] - 'A'] == nullptr){
      currNode->branch[wordInName[i] - 'A'] = new TrieNode;
      currNode->numNonNullBranches++;
    }
    currNode = currNode->branch[wordInName[i] - 'A'];
  }
  currNode->isWord = true;
  //adds indexOfName to the list of indices
  if(currNode->indices == nullptr)
    currNode->indices = new listOfObjects<int>(indexOfName);
  else{
    listOfObjects<int> *temp = currNode->indices;
    while(temp != nullptr){
      if(temp->object == indexOfName)
        return true;
      else if(temp->next == nullptr){
        temp->next = new listOfObjects<int>(indexOfName);
        break;
      }
      temp = temp->next;
    }
  }
  // Insert your code here
  return true;
}
//Deletes a word from the trie. Returns true if success, else returns false
bool Trie::del(string wordInName, string name) {
  TrieNode *currNode = root;
  TrieNode *lastBranchNode = nullptr;
  int lastBranchChar = -1;
  int len = wordInName.length();

  // Find the word in the trie
  for(int i = 0; i < len; i++){
    //If word not found, return false
    if(currNode->branch[wordInName[i] - 'A'] == nullptr)
      return false;
    else if(currNode->numNonNullBranches > 1){
      lastBranchNode = currNode;
      lastBranchChar = wordInName[i] - 'A'; 
    }
    currNode = currNode->branch[wordInName[i] - 'A'];
  }
  if(!currNode->isWord)
    //If word not found, return false
    return false;
  else{
    //if only one name has this word, then we need to delete the trieNodes
    if(currNode->indices->next == nullptr){
      if(strcmp(nameDict->getKeyAtIndex(currNode->indices->object).c_str(), name.c_str()) == 0){
        if(lastBranchNode != nullptr){
          // recursiveDelete(lastBranchNode);
          recursiveDelete(lastBranchNode->branch[lastBranchChar]);
          lastBranchNode->branch[lastBranchChar] = nullptr;
          lastBranchNode->numNonNullBranches--;
        }
        else{
          recursiveDelete(root->branch[wordInName[0] - 'A']);
          root->branch[wordInName[0] - 'A'] = nullptr;
          root->numNonNullBranches--;
        }
        return true;
      }
      else
        //If word not found, return false
        return false;
    }
    else{
      //if multiple names have this word, then we only need to delete the object 
      //(from listOfObjects) corresponding to it
      listOfObjects<int> *prev = nullptr;
      listOfObjects<int> *curr = currNode->indices;
      while(curr != nullptr){
        if(strcmp(nameDict->getKeyAtIndex(curr->object).c_str(), name.c_str()) == 0){
          if(prev == nullptr){
            //what to do if the index to be deleted is the first thing in the list
            currNode->indices = curr->next;
            delete curr;
          }
          else{
            prev->next = curr->next;
            delete curr;
          }
          break;
        }
        //update the pointers
        prev = curr;
        curr = curr->next;
      }
    }
    return true;
  }
}
//find the completions of a prefix, searches the trie and returns a list of all possible names
listOfObjects<string> * Trie::completions(string prefix) {
  TrieNode *currNode = root;
  int len = prefix.length();
  listOfObjects<string> *currCompletions = nullptr;
  
  for(int i = 0; i < len; i++){
    if(currNode == nullptr)
      return currCompletions;
    currNode = currNode->branch[prefix[i] - 'A'];
  }
  vector<int> idx;
  listOfObjects<string> *Completions = currCompletions;
  findIndexes(currNode, idx);
  for(auto & index : idx){
    // cout << nameDict->getKeyAtIndex(index) << endl;
    if(Completions == nullptr){
      Completions = new listOfObjects<string>(nameDict->getKeyAtIndex(index));
      currCompletions = Completions;
    }
    else{
      Completions->next = new listOfObjects<string>(nameDict->getKeyAtIndex(index));
      Completions = Completions->next;
    }
  }
  // eturns list
  return currCompletions;
  
}
//finds indexes of all words containing currNode, and returns a vector of indices of names
void Trie::findIndexes(TrieNode *currNode, vector<int> &idx){
  if(currNode == nullptr)
    return;
  else if(currNode->isWord){
    listOfObjects<int>* temp = currNode->indices;
    while(temp != nullptr){
      idx.push_back(temp->object);
      temp = temp->next;
    }
    return;
  }
  else{
    for(int i = 0; i < NUM_CHARS; i++)
      findIndexes(currNode->branch[i], idx);
  }
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
