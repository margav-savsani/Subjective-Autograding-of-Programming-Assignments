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

Trie::Trie(Dictionary<int> *nameToIndex){
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

// Inserts the wordInName contained in Name which is
// stored in dictionary at indexOfName
bool Trie::insert(string wordInName, int indexOfName) {
  TrieNode *currNode = root; //
  int len = wordInName.length();

  //Iterating for len times, as we either add all the 
  //letters or go through them if already added
  for (int i = 0; i < len; i++){
    int letter = toupper(wordInName.at(i)) - 'A';//Calculating the pos

    if(currNode->branch[letter] == nullptr){
      // When the letter is not present in the trie
      currNode->branch[letter] = new TrieNode();
      currNode->branch[letter]->pos = letter;
      // Incrementing the number of branches of the currNode
      currNode->numNonNullBranches++;
    }

    //Updating the new node's parent and also moving currNode
    //a step ahead, for the next iteration
    currNode->branch[letter]->parent = currNode;
    currNode = currNode->branch[letter];
  }
  //Indicating the presence of a complete word here
  currNode->isWord = true;  

  /*======Now adding the index to the indices list of objects at the leaf node=======*/

  if(currNode->indices == nullptr){
    //Create a new pointer if it was nullptr
    currNode->indices = new listOfObjects<int>(indexOfName);
  }
  else{
    listOfObjects<int>* currList = currNode->indices;

    //Iterate till you find the position whose next position is empty 
    //We shall put our new index here
    while(currList->next!=nullptr){
      if(currList->object == indexOfName) return false;
      currList = currList->next;
    }
    if(currList->object == indexOfName) return false;
    currList->next = new listOfObjects<int>(indexOfName);
  }
  //Incrementing the number of indices
  currNode->numIndices++;
  return true;
}

// Deletes recursively from the node till the root node
// This is different from the recursiveDelete defined earlier
// Here the deletion, is the removal is of a particular word 
// from the trie
void Trie::recursiveDel(TrieNode* node){

  //When it is the root node
  if(node->pos == -1){
    return;
  }

  if(node->numIndices>0 || node->numNonNullBranches>0){
    //If either the node has non zero branches
    //or non nullptr indices
    //In this case, no deletion shall follow, as there 
    //exists other words requiring these nodes
    return;
  }
  else{
    // When the number of branches is zero and also 
    // the indices is nullptr
    // In this case we remove this node
    node->parent->branch[node->pos] = nullptr;
    node->parent->numNonNullBranches--; //Decrementing the number of branches of its parent node
    //Recursively delete the parent node
    return recursiveDel(node->parent);
  }
}

// Deletes the wordInName contained in name from the trie
bool Trie::del(string wordInName, string name) {
  TrieNode *currNode = root;
  int len = wordInName.length();

  // Iterating all the way till the leaf node
  for (int i = 0; i < len; i++){
    int letter = toupper(wordInName.at(i)) - 'A';
    if (currNode->branch[letter] == nullptr) {
      //Although this is not required
      //But we retain it as a precautionary measure
      //This is the case when the word to be deleted
      //doesn't even exist in the trie
      return false;
    }
    currNode = currNode->branch[letter];
  }

  // If Leaf Node is not a word, then return false
  // This again, isn't required, as other parts of code
  // check the correctness
  if (!currNode->isWord) return false;

  listOfObjects<int>* currList = currNode->indices;
  listOfObjects<int>* prevcurrList = nullptr;
  bool found = false; // to show whether index found or not
  while(currList!=nullptr){
    if(nameDict->getKeyAtIndex(currList->object) == name){
      //Removing the currlist object from the linked list
      if(prevcurrList == nullptr){
        // if prevcurrList is null, then update currList with its next value
        currList = currList->next; 
      }
      else{
        //Else remove the currList by updating next of prevcurrList with
        //the next of currList
        prevcurrList->next = currList->next;
      }
      //Decrementing the numIndices of currNode
      currNode->numIndices--;
      found  = true;
      break;
    }
    prevcurrList = currList;
    currList = currList->next;
  }

  if(!found) return false;
  //Updating the isWord variable depending on numIndices
  if(currNode->numIndices == 0) currNode->isWord = false;
  //Recursively Deleting the word starting from CurrNode
  recursiveDel(currNode);
  return true;

}

// Returns a list of Object containing a linked list of strings 
// which are matches of prefix in the trie
listOfObjects<string> * Trie::completions(string prefix) {
  TrieNode *currNode = root;
  int len = prefix.length();

  // The first object is given name "NULL", this shall be 
  // removed later
  // This is done in order to be able to receive updates to the
  // pointer currCompletions from other functions here!
  listOfObjects<string> *currCompletions = new listOfObjects<string>("NULL");

  //Iterating over the trie for the string prefix
  //till you reach its leaf
  for (int i = 0; i < len; i++){
    int letter = toupper(prefix.at(i)) - 'A';
    if(currNode->branch[letter] == nullptr) return nullptr;
    currNode = currNode->branch[letter];
  }

  //recursively adding completions starting from currNode to currCompletions
  recursiveAddCompletions(currNode, currCompletions);

  //Updating currCompletions with its next, so as to remove the "NULL" named object at start
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


//Appending completions from the leaf node into 
//the currCompletiosn list Of string objects
bool Trie::addCompletions(TrieNode *node, listOfObjects<string> *currCompletions) {

  listOfObjects<int>* currList = node->indices;
  listOfObjects<string> *currStringList = currCompletions,*prevcurrStringList = nullptr;
  //currList is for indices of node
  //currStringList is for currCompletions
  //prevcurrStringList is for the object previous to currStringList

  //Iterating till you reach an object whose next is null
  while(currStringList != nullptr){
    prevcurrStringList = currStringList;
    currStringList = currStringList->next;
  }
  
  //Iterating over the indices of the node and adding them into 
  //currCompletions
  while(currList!=nullptr){
    if(prevcurrStringList == nullptr){
      currCompletions = new listOfObjects<string>(nameDict->getKeyAtIndex(currList->object));
      prevcurrStringList = currCompletions;
    }
    else{
      prevcurrStringList->next = new listOfObjects<string>(nameDict->getKeyAtIndex(currList->object));
      prevcurrStringList = prevcurrStringList->next;
    }
    currList = currList->next;
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
      cout << "(" << node->pos << " " << "Branches: " << node->numNonNullBranches <<  ")";
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
