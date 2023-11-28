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

  for(int i=0; i < len; i++){
    int index = tolower(wordInName[i]) - 'a';
    if(currNode->branch[index] == nullptr){
      currNode->numNonNullBranches++;
      currNode->branch[index] = new TrieNode();
    }
    currNode->branch[index]->parent = currNode;
    currNode = currNode->branch[index];
  }
  currNode->isWord = true;

  listOfObjects<int> *store_list;
  store_list = currNode->indices;

  if(currNode->indices != nullptr){
    while(store_list->next != nullptr){
      store_list = store_list->next;
    }
    store_list->next = new listOfObjects(indexOfName);
  }

  else currNode->indices = new listOfObjects(indexOfName);
  return true;
}

bool Trie::del(string wordInName, string name) {
  if(!isPresent(wordInName)) return false;
  TrieNode *store_root = root;
  TrieNode *currNode = root;
  TrieNode *lastBranchNode = nullptr;
  int lastBranchChar = -1;
  int len = wordInName.length();

  // Insert your code here

  for(int i=0; i < len; i++){
    int index = tolower(wordInName[i]) - 'a';
    currNode = currNode->branch[index];
  }

  int count = 0;
  listOfObjects<int> *count_num_in_indice_list;
  count_num_in_indice_list = currNode->indices;

  while(count_num_in_indice_list != nullptr){
    count++;
    count_num_in_indice_list = count_num_in_indice_list -> next;
  }


  listOfObjects<int> *store_the_list;
  store_the_list = currNode->indices;

  listOfObjects<int> *store_pointer;

  if(count == 1 && (nameDict->getKeyAtIndex(currNode -> indices -> object) == name)){
    delete currNode->indices;
    currNode->isWord = false;
    while(!(currNode -> parent -> numNonNullBranches > 1)){
      // TrieNode *store = currNode->parent;
      for (int i = 0; i < NUM_CHARS; i++) {
        if(currNode->parent->branch[i] != nullptr){
          // delete currNode;
          currNode = currNode->parent;
          currNode->branch[i] = nullptr;
          break;
        }
      }
      
    }
    
    TrieNode *store_curr = currNode;
    for (int i = 0; i < NUM_CHARS; i++) {
        if(currNode->parent == store_root){
          if(store_root->branch[i] == store_curr){
            // delete currNode;
            currNode = store_root;
            currNode->branch[i] = nullptr;
            break;
          }
        }
        else{
          if(currNode->parent->branch[i] == store_curr){
            // delete currNode;
            currNode = currNode->parent;
            currNode->branch[i] = nullptr;
            break;
          }
        }
      
      }

    return true;
  }

  if(count != 1 && (nameDict->getKeyAtIndex(currNode -> indices -> object) == name)){
    store_the_list = store_the_list -> next;
  }
  
  while(store_the_list != nullptr){
    if(nameDict->getKeyAtIndex(store_the_list -> object) == name){
      // store_pointer = store_the_list -> next;
      delete store_the_list;
      store_the_list= store_pointer;
      return true;
    }
    store_the_list = store_the_list -> next;
  }

}

listOfObjects<string> * Trie::completions(string prefix) {
  TrieNode *currNode = root;
  int len = prefix.length();
  listOfObjects<string> *currCompletions = nullptr;

  // Insert your code here

  for(int i=0; i < len; i++)
  {
    int index = tolower(prefix[i]) - 'a';
    currNode = currNode->branch[index];
    if (currNode == nullptr) return nullptr;
  }
  recursiveAddCompletions(currNode, currCompletions);
  return currCompletions;
}

bool Trie::recursiveAddCompletions(TrieNode *node, listOfObjects<string>* &currCompletions) {
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
  listOfObjects<int> *append_list;
  append_list = node->indices;

  // listOfObjects<string> *store_curr_completions = currCompletions;
  // listOfObjects<string> *store_append_list = append_list;

  // while(store_append_list != nullptr){
  //   while(store_curr_completions != nullptr){
  //     if(nameDict->getKeyAtIndex(append_list -> object) == store_curr_completions)
  //       return false;
  //     store_curr_completions = store_curr_completions -> next;
  //   }
  //   store_append_list = store_append_list -> next;
  // }

  while(append_list != nullptr){
    listOfObjects<string> *store_new;
    store_new = new listOfObjects<string>(nameDict->getKeyAtIndex(append_list -> object));

    listOfObjects<string> *store_curr_Compl;
    store_curr_Compl = currCompletions;

    currCompletions = store_new;
    store_new->next = store_curr_Compl;

    append_list = append_list->next;
  }

  // while(currCompletions != nullptr){
  //   currCompletions = currCompletions -> next;
  // }

  // while(append_list != nullptr){
  //   currCompletions = new listOfObjects<string> (nameDict->getKeyAtIndex(append_list -> object));
  //   append_list = append_list -> next;
  //   // node->next = currCompletions
  //   currCompletions = currCompletions -> next;
  // }

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
