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
  //cout << wordInName << endl;
  //cout << indexOfName << endl;
  for (int i = 0; i<len; i++){
    //cout << wordInName[i] << endl;
    //cout << (int)wordInName[i] -97 << endl;
    int curr_index = (int)wordInName[i] -65;
    if(currNode->branch[curr_index]!=nullptr){
      currNode = currNode->branch[curr_index];
      //cout << "used same node " << wordInName[i] << endl; 
    }
    else{
      currNode->branch[curr_index] = new TrieNode();
      currNode->numNonNullBranches+=1;
      //cout << "created new node " << wordInName[i] << endl;
      currNode = currNode->branch[curr_index];
      //cout << "is current node a word?" << currNode->isWord << endl;
    }

    if(i == len-1){
      if(currNode->isWord){
        listOfObjects<int> * list_to_insert_index = currNode->indices;

        while(list_to_insert_index->next!= nullptr){
          if(list_to_insert_index->object==indexOfName){
            return false;
          }
          //cout << "already found index " << list_to_insert_index->object << endl;
          list_to_insert_index = list_to_insert_index->next;
        }

        if(list_to_insert_index->object==indexOfName){
          return false;
        }
        //cout << "already found index " << list_to_insert_index->object << endl;
        if(list_to_insert_index->object==indexOfName){
          return false;
        }
        //cout << "indexofname: " << indexOfName << endl;
        listOfObjects<int> *list_obj = new listOfObjects<int>(indexOfName);
        list_to_insert_index->next = list_obj;
        //cout << "inserted new object in list with index number: " << list_to_insert_index->next->object << endl;

      }
      else{
        currNode->isWord = true;
        listOfObjects<int> *list = new listOfObjects<int>(indexOfName);
        currNode->indices = list;
        //cout << "created new list with index number: " <<currNode->indices->object << endl;
      }
    }
  }
  // Insert your code here

  return true;
}

bool Trie::del(string wordInName, string name) {
  TrieNode *currNode = root;
  TrieNode *lastBranchNode = root;
  int lastBranchChar = wordInName[0]-65;
  int len = wordInName.length();
  for (int i = 0; i<len; i++){
    int curr_index = (int)wordInName[i] -65;
    if(currNode->numNonNullBranches>1 || currNode->isWord){
      lastBranchNode=currNode;
      lastBranchChar=curr_index;
    }
    if(currNode->branch[curr_index]==nullptr){
      return false;
    }
    else{
      currNode=currNode->branch[curr_index];
    }
  }
  if(!(currNode->isWord)){
    return false;
  }
  listOfObjects<int> *list_obj = currNode->indices;

  if(list_obj->next==nullptr){
    if(nameDict->getKeyAtIndex(list_obj->object)!=name){
      return false;
    }
    lastBranchNode->branch[lastBranchChar]=nullptr;
    lastBranchNode->numNonNullBranches-=1;
    return true;
    
  }

  if(nameDict->getKeyAtIndex(list_obj->object)==name){
    currNode->indices = list_obj->next;
    return true;
  }

  listOfObjects<int> *next_obj = list_obj->next;
  while(next_obj!=nullptr){
    if(nameDict->getKeyAtIndex(next_obj->object)==name){
      list_obj->next = next_obj->next;
      return true;
    }
  }
  // Insert your code here
  return true;
}

void Trie::make_unique(listOfObjects<string> *start){
    listOfObjects<string> *ptr1, *ptr2, *dup;
    ptr1 = start;
 
    while (ptr1 != NULL && ptr1->next != NULL) {
        ptr2 = ptr1;
 
        while (ptr2->next != NULL) {

            if (ptr1->object == ptr2->next->object) {

                dup = ptr2->next;
                ptr2->next = ptr2->next->next;
                delete (dup);
            }
            else{
                ptr2 = ptr2->next;
            }
        }
        ptr1 = ptr1->next;
    }
}




listOfObjects<string> * Trie::completions(string prefix) {
  TrieNode *currNode = root;
  int len = prefix.length();
  listOfObjects<string> *currCompletions = new listOfObjects<string> ("first");
  for (int i = 0; i<len; i++){
    int curr_index = (int)prefix[i] -65;
    if(currNode->branch[curr_index]==nullptr){
      return nullptr;
    }
    currNode=currNode->branch[curr_index];
  }

  recursiveAddCompletions(currNode, currCompletions);
  make_unique(currCompletions);

  // Insert your code here

  return currCompletions->next;
  
}

bool Trie::recursiveAddCompletions(TrieNode *node, listOfObjects<string> *currCompletions) {
  //cout << "planning to recursively add from node: " << node->numNonNullBranches << " non null branches" << endl;
  if (node->isWord) {
    if (!addCompletions(node, currCompletions)) {
      return false;
    }
    while (currCompletions->next!=nullptr){
      currCompletions = currCompletions->next;
    }
    
  }

  TrieNode *currNode = node;
  for (int i = 0; i < NUM_CHARS; i++) {
    if (currNode->branch[i] != nullptr) {
      if (!recursiveAddCompletions(currNode->branch[i], currCompletions)) {
	return false;
      }
      if(currCompletions->next!=nullptr){
        currCompletions = currCompletions->next;
      }
    }
  }

  return true;
}

bool Trie::addCompletions(TrieNode *node, listOfObjects<string> *currCompletions) {

  if(node->isWord){
    listOfObjects<int> * list_obj = node->indices;
    listOfObjects<string> *station_name = new listOfObjects<string>(nameDict->getKeyAtIndex(list_obj->object));
    //if(currCompletions==nullptr){
      //currCompletions=station_name;
    //}
    //else{
    currCompletions->next = station_name;
    currCompletions = currCompletions->next;
    //}
    while(list_obj->next!=nullptr){
      list_obj = list_obj->next;
      listOfObjects<string> *station_name = new listOfObjects<string>(nameDict->getKeyAtIndex(list_obj->object));
      currCompletions->next = station_name;
      currCompletions = currCompletions->next;
    }
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
