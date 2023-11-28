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
int Trie::index(char c){
  if ( c < 91 ){
    return c-'A';
  }
  else {
    return c-'a';
  }
}

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

//Function to insert words in trie
bool Trie::insert(string wordInName, int indexOfName) {
  
  //Inserts the words into the tries
  TrieNode *currNode = root;
  int len = wordInName.length();
  for (int i = 0 ; i < len ; i++ ){
    char c = wordInName[i];
    int ind = index(c);
    if ( currNode->branch[ind] == nullptr ){
      currNode->branch[ind] = new TrieNode();
    }
    currNode = currNode->branch[ind];
  }
  currNode->isWord = true;
  
  //Adds index of name at the end of tries in a linked list
  if ( currNode->indices == nullptr ){
    currNode->indices = new listOfObjects<int>(indexOfName);
  }
  else {
    listOfObjects<int> *currObject = currNode->indices;
    while ( currObject->next != nullptr ){
      currObject = currObject->next;
    }
    currObject->next = new listOfObjects<int> (indexOfName);
  }
  return true;
}

bool Trie::del(string wordInName, string name) {
  
  //find the node, return false if not found
  TrieNode *currFind = root;
  int len = wordInName.length();
  for ( int i = 0 ; i < wordInName.length() ; i++ ){
    char c = wordInName[i];
    int ind = index(c) ;
    if ( currFind->branch[ind] == nullptr ){
      return false;
    }
    else {
      currFind = currFind->branch[ind];
    }
  }
  if (currFind->isWord == false ){
    return false;
  }
  listOfObjects<int> *FH = currFind->indices;
  listOfObjects<int> *FC = currFind->indices;
  bool is_found = false;
  while ( FC != nullptr ){
    if ( name == nameDict->getKeyAtIndex(FC->object) ){
      is_found = true;
      break;
    }
    FC=FC->next;
  }
  if (is_found == false ){
    return false;
  }
  
  // now if the element is not present we have ensured, our function will return false
  //from now on we can assume word is present in trie
  TrieNode *currNode = root;
  TrieNode *lastBranchNode = nullptr;
  int lastBranchChar = -1;
  for (int i = 0 ; i < wordInName.length() ; i++){
    char c = wordInName[i];
    int ind = index(c);
    currNode = currNode->branch[ind];
  }
  listOfObjects<int> *head = currNode->indices;
  listOfObjects<int> *currObject = head;
  //case 1 - only 1 element in the list
  //case 2 - more than 1 element in the list
  if ( head->next == nullptr ){
    //case 1 if its a prefix
    //case 2 if its not a prefix
    bool is_prefix = true;
    for ( int k = 0 ; k < 26 ; k++ ){
      if (currNode->branch[k] != nullptr ){
        is_prefix = false;
      }
    }
    if ( !is_prefix ){
      currNode->indices = nullptr;
      currNode->isWord = false;
    }
    else{
      TrieNode *temp = root;
      char branch = wordInName[0];
      TrieNode *FP = root;
      for ( int i = 0 ; i < len - 1 ; i++ ){
        char c = wordInName[i];
        int n_b = 0;
        for (int js = 0 ; js < 26 ; js++ ){
          if (FP->branch[js]!=nullptr){
            n_b++;
          }
        }
        if ( FP->isWord || n_b>1 ){
          temp = FP;
          branch = c;
        }
        FP = FP->branch[index(c)];
      }
      temp->branch[index(branch)] = nullptr;
    }
  }
  else{
    //delete element from list starting with head
    if ( nameDict->getKeyAtIndex(currNode->indices->object) == name ){
      currNode->indices = currNode->indices->next;
    }
    else {
      while( nameDict->getKeyAtIndex(currObject->next->object) != name ){
        currObject = currObject->next;
      }
      currObject->next = currObject->next->next;
    }
  }
  return true;
}

listOfObjects<string> * Trie::completions(string prefix) {
  TrieNode *currNode = root;
  int len = prefix.length();
  listOfObjects<string> *currCompletions = nullptr;
  //Go to the node where the prefix ends
  for ( int i = 0 ; i < len ; i++ ){
    char c = prefix[i];
    int ind = index(c) ;
    currNode = currNode->branch[ind];
  }
  recursiveAddCompletions(currNode, currCompletions);
  return currCompletions;
  
}

bool Trie::recursiveAddCompletions(TrieNode *node, listOfObjects<string> *&currCompletions) {
  if (node->isWord) {
    if (!addCompletions(node, currCompletions)) {
      listOfObjects<string> *s = new listOfObjects<string> ("Hello");
      currCompletions = s;
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

bool Trie::addCompletions(TrieNode *node, listOfObjects<string> *&currCompletions) {
  //Exceptional case when currCompletionos is empty
  if ( currCompletions == nullptr ){
    string s = nameDict->getKeyAtIndex(node->indices->object);
    currCompletions = new listOfObjects<string> (s);
    listOfObjects<string> *lastFilled = currCompletions;
    listOfObjects<int> *fil = node->indices->next;
    while(fil!=nullptr){
      int val = fil->object;
      lastFilled->next = new listOfObjects<string> ( nameDict->getKeyAtIndex(val)  );
      lastFilled = lastFilled->next;
      fil = fil->next;
    }
  }
  //last filled element in currCompletions
  //first element to start filling in indices list
  //a loop which takes element from indices list and puts it into currCompletions
  else{
    listOfObjects<string> *lastFilled = currCompletions;
    while(lastFilled->next != nullptr ){
      lastFilled = lastFilled->next;
    }
    listOfObjects<int> *fil = node->indices;
    while(fil!=nullptr){
      int val = fil->object;
      lastFilled->next = new listOfObjects<string> ( nameDict->getKeyAtIndex(val)  );
      lastFilled = lastFilled->next;
      fil = fil->next;
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
