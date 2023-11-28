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
    int alphabet = toupper(wordInName.at(i)) - 'A';   //alphabet gives the position of the characeter according to its position in english alphabet (-1)
    if(currNode->branch[alphabet] == nullptr){
      currNode->branch[alphabet] = new TrieNode();    //creating a new trie node at the appropriate position in the branch of the current node only if it hasn't been created before
      currNode->numNonNullBranches += 1;              //updating the number of non null branches of current node
    }
    
    currNode = currNode->branch[alphabet];            //traversing the trie
    if(i == len - 1){     //add the station name at the leaf of the traversed path of the trie
      if(currNode->isWord){     //if there is an index of a word present already
        listOfObjects<int>  *tempIn = currNode->indices;
        while(tempIn->next!=nullptr){     //traverse the linked list of objects of type int
          tempIn = tempIn->next;
        }
        currNode->isWord = true;
        tempIn->next = new listOfObjects<int> (indexOfName);    //append in the linked list
      }
      else{   //if no word is present already
        currNode->isWord = true;  //setting the isWord to true
        currNode->indices = new listOfObjects<int> (indexOfName);   //create a new element at the start of the linked list
      }
      return true;
    }
  }

  return false;
}

bool Trie::del(string wordInName, string name) {
  TrieNode *currNode = root;
  TrieNode *lastBranchNode = nullptr;
  int lastBranchChar = -1;
  int len = wordInName.length();
  int indexOfName = nameDict->get(name)->value;   //index of name in the nameDict

  // Insert your code here
  for(int i = 0; i < len; i++){   //traversing the trie for wordInName
    int alphabet = toupper(wordInName.at(i)) - 'A';
    if(currNode->branch[alphabet] == nullptr){
      break;
    }
    if(currNode->numNonNullBranches > 1){   //saving the last branch node and last branch character in case we have to delete the whole branch
      lastBranchNode = currNode;
      lastBranchChar = alphabet;
    }
    currNode = currNode->branch[alphabet];
    if(i == len - 1){
      if(!currNode->isWord){
        return false;
      }
      else{
        listOfObjects<int>  *tempIn = currNode->indices;
        listOfObjects<int>  *tempIn2 = nullptr;
        while(tempIn->object != indexOfName){
          tempIn2 = tempIn;
          tempIn = tempIn->next;
        }
        if(tempIn2 == nullptr){
          currNode->indices = tempIn->next;
        }
        else{
          tempIn2->next = tempIn->next;
        }
        if(currNode->indices == nullptr){   //the whole branch since last branching needs to be deleted
          if(lastBranchNode != nullptr){    //normal case
            lastBranchNode->branch[lastBranchChar] = nullptr;
            lastBranchNode->numNonNullBranches -= 1;
          }
          else{   //case in which there is no branching till the end of the wordInName
            if(lastBranchChar == -1){
              lastBranchChar = toupper(wordInName.at(0)) - 'A';
            }
            root->branch[lastBranchChar] = nullptr;
            root->numNonNullBranches -= 1;
          }
        }
      }
      return true;
    }
  }
  return false;
}

listOfObjects<string> * Trie::completions(string prefix) {
  TrieNode *currNode = root;
  int len = prefix.length();
  listOfObjects<string> *currCompletions = new listOfObjects<string> ("");

  // Insert your code here
  for(int i = 0; i < len; i++){   //traversing the trie
    int alphabet = toupper(prefix.at(i)) - 'A';
    if(currNode->branch[alphabet] == nullptr){  //exit the loop and return null pointer if prefix not found
      break;
    }
    currNode = currNode->branch[alphabet];
    if(i == len - 1){
      recursiveAddCompletions(currNode, currCompletions); //call for recursively adding completions in the currCompletions linked list
    }
  }

  return currCompletions->next;   //since the first element is an empty string
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
  listOfObjects<string>  *newCompletionSet = currCompletions;
  while(newCompletionSet->next != nullptr){
    newCompletionSet = newCompletionSet->next;
  }   //now newCompletionSet if the last non null pointer element of the currCompletion linked list
  listOfObjects<int>  *tempIn = node->indices;
  while(tempIn != nullptr){   //adding the element from indices of node to currCompletions side by side
    string CompletionToInsert = nameDict->getKeyAtIndex(tempIn->object);
    newCompletionSet->next = new listOfObjects<string> (CompletionToInsert);
    newCompletionSet = newCompletionSet->next;
    tempIn = tempIn->next;
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
