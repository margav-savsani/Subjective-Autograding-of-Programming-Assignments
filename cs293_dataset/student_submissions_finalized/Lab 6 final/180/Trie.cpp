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

bool Trie::insert(string wordInName, int indexOfName) {      //insert the word at the given index
  TrieNode *currNode = root;
  int len = wordInName.length();
  bool entered_if = false;

  for (int i = 0; i < len; i++) {
    int letter = toupper(wordInName.at(i)) - 'A';            //convert in uppercase

    if (currNode->branch[letter] == nullptr) {
      entered_if = true;
      TrieNode* a = new TrieNode();
      currNode->branch[letter] = a;
      currNode->numNonNullBranches++;
    }
    currNode = currNode->branch[letter];
  }

  if(currNode->isWord != true){                       //if there are already words then add to it
    currNode->isWord = true;
    listOfObjects<int> *a = new listOfObjects<int>(indexOfName);
    currNode->indices = a;
    return true;
  }
  else{
    listOfObjects<int> *a = new listOfObjects<int>(indexOfName);
    listOfObjects<int> *ins = currNode->indices;
    while(ins->next != NULL){
      ins = ins->next;
    }
    ins->next = a;
    return true;
  }

  return false;
}

bool Trie::del(string wordInName, string name) {                 //function to delete
  TrieNode *currNode = root;
  TrieNode *lastBranchNode = root;
  int lastBranchChar = -1;
  int len = wordInName.length();
  int letter1 = toupper(wordInName.at(0)) - 'A';
  lastBranchChar = letter1;

  for(int i = 0; i < len ;i++){                                    //find the last word which should never be deleted bcoz it will have branch or word 
    int letter = toupper(wordInName.at(i)) - 'A';

    if(currNode->numNonNullBranches > 1 || currNode->indices != NULL){
      lastBranchNode = currNode;
      lastBranchChar = letter;
    }
    if (currNode->branch[letter] == nullptr) {
      return false;
    }
    currNode = currNode->branch[letter];
    
  }
  if(currNode->numNonNullBranches > 0){                            //if last letter have branch or more than one word then recursive delete no required
    string s = nameDict->getKeyAtIndex(currNode->indices->object);
    if(s==name) {                                                  //if first match and there is no other word then we are done
      if(currNode->indices->next ==NULL){
        delete(currNode->indices);
        currNode->indices = NULL;
        currNode->isWord = false;
        return true;
      }
      else{
        listOfObjects<int>* temp = currNode->indices->next;         //if not then traverse through the list
        delete(currNode->indices);
        currNode->indices = temp;
        return true;
      }
    }
    else{
      listOfObjects<int>* prev = currNode->indices;
      listOfObjects<int> *curr = currNode->indices->next;           //else recursively traverse till end
      while(curr != NULL){
        string s = nameDict->getKeyAtIndex(curr->object);
        if(s == name){
          prev->next = curr->next;
          delete(curr);
          return true;
        }
        curr = curr->next;
        prev = prev->next; 
      }
    }
  }

  else{
    string s = nameDict->getKeyAtIndex(currNode->indices->object);       //string to find
    if(s==name) {
      if(currNode->indices->next ==NULL){
        lastBranchNode->numNonNullBranches --;                            //reduce number of branches
        recursiveDelete(lastBranchNode->branch[lastBranchChar]);           //recursively deleted
        lastBranchNode->branch[lastBranchChar] = NULL;
        
        return true;
      }
      else{
        listOfObjects<int>* temp = currNode->indices->next;
        delete(currNode->indices);
        currNode->indices = temp;
        return true;
      }
    }
    else{                                                               //traverse through list and delete
      listOfObjects<int>* prev = currNode->indices;
      listOfObjects<int> *curr = currNode->indices->next;
      while(curr != NULL){
        string s = nameDict->getKeyAtIndex(curr->object);
        if(s == name){
          prev->next = curr->next;
          delete(curr);
          return true;
        }
        curr = curr->next;
        prev = prev->next; 
      }

    }
  }

  // Insert your code here
  return false;
}

listOfObjects<string> * Trie::completions(string prefix) {       //go to last letter and then perform addcompletions
  TrieNode *currNode = root;
  int len = prefix.length();
  listOfObjects<string> *currCompletions = nullptr;
  for (int i = 0; i < len; i++) {
    int letter = toupper(prefix.at(i)) - 'A';

    if (currNode->branch[letter] == nullptr) {
      return currCompletions;
    }
    currNode = currNode->branch[letter];
  }
  //add completion invoked 
  addCompletions(currNode,currCompletions);
  
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

bool Trie::addCompletions(TrieNode *node, listOfObjects<string>* &currCompletions) {

  // Insert your code here
  // if node has word then add all of them
  if(node->isWord == true){
    listOfObjects<int> *ins = node->indices;
    string s = nameDict->getKeyAtIndex(ins->object);
    if(currCompletions == NULL){
      currCompletions = new listOfObjects<string>(s);
    }
    else{
      listOfObjects<string> * str = new listOfObjects<string>(s);
      listOfObjects<string>* temp = currCompletions;
      while(temp->next != NULL){
        temp=temp->next;
      }
      temp->next =str; 
    }
    //traverse through all indices and add all the strings associated
    while(ins->next != NULL){
      ins = ins->next;
      string s = nameDict->getKeyAtIndex(ins->object);
      if(currCompletions == NULL){
        currCompletions = new listOfObjects<string>(s);
      }
      else{
        listOfObjects<string> * str = new listOfObjects<string>(s);
        listOfObjects<string>* temp = currCompletions;
        while(temp->next != NULL){
          temp=temp->next;
        }
        temp->next = str;
      }
    } 
  }
  //apply function recursively to all branches
  for(int i = 0 ; i < NUM_CHARS ;i++){
    if(node->branch[i] != nullptr){
      addCompletions(node->branch[i],currCompletions);
    }
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
