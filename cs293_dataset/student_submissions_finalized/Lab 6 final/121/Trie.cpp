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
  for(int i=0; i<len; i++){  //inserting every character of wordInName in trie
    //calculating index value of branch array
    int a = toupper(wordInName[i]) - 'A';
    
    //first we reach the last node for the wordInName in our trie, if some suffix of wordInName is not present
    //we create the nodes and then reach the last node
    //if branch is null
    if (currNode->branch[a]==nullptr){
      currNode->branch[a] = new TrieNode();
      currNode->numNonNullBranches++;
      currNode = currNode->branch[a];
    }
    //if the branch exists
    else{
      currNode = currNode->branch[a];
    }

    //now we are on the last node that is, our word ends on this node, so first we correct index
    if(i == len-1){      
      if(!currNode->isWord){
        currNode->indices = new listOfObjects<int>(indexOfName);
      }
      else{
        listOfObjects<int> *currind = currNode->indices;
        //finally currind should either be last link in linked list of indices 
        //or it should have same value as indexOfName
        while(currind->next!=nullptr && currind->object!=indexOfName){ 
          currind=currind->next;
        }
        if(currind->object==indexOfName){ //currind has value same as what was to be inserted 
          return false; //object wasn't inserted since it already exists
        }
        else{ //this means we are on last link of list whose value isn't indexOfName
          currind->next = new listOfObjects<int>(indexOfName);
        }
      }
      //lastly, updating the value of isWord
      currNode->isWord=true; //if it is already true, doesn't matter
    }
  }
  return true;
}

bool Trie::del(string wordInName, string name) {
  TrieNode *currNode = root;
  TrieNode *lastBranchNode = root;
  int lastBranchChar = toupper(wordInName[0]) -'A';
  int len = wordInName.length();
  //assumption : wordInName and name are present in tree and dictionary respectively
  // Insert your code here
  for (int i=0; i<len; i++){
    int a = toupper(wordInName[i]) - 'A';
    if(currNode->numNonNullBranches>1 || currNode->isWord){
      
        lastBranchNode = currNode;  
        lastBranchChar = a;
      
      // else lastBranchChar = -1;
    }
    currNode = currNode->branch[a];
  }

  //now we are at the last node for word and we can execute deletion with values of lastBranchNode and lastBranchChar in hand
  //deleting the index of station 'name' here
  if(currNode->indices != nullptr){
    //find the entry in indices which corresponds to station name
    listOfObjects<int> *currind = currNode->indices;
    listOfObjects<int> *prevind = nullptr;
    while(currind!=nullptr){
      if(name == nameDict->getKeyAtIndex(currind->object)){
        //deleting current node from linked list
        if(prevind==nullptr){
          currNode->indices = currind->next;
        }
        else{
          prevind->next = currind->next;
        }
        //we can break out of while loop now
        break;
      }
      //updating the iterative variables
      prevind = currind;
      currind = currind->next;
    }
  }
  //deleting the whole branch if there is no other word here
  
  // if (!(currNode->isWord || currNode->numNonNullBranches>0)) {
  //   currNode->isWord = false;
  //   lastBranchNode->branch[lastBranchChar] = nullptr;
  // }
  if(currNode->indices==nullptr){
    if(currNode->numNonNullBranches==0){
      lastBranchNode->branch[lastBranchChar] = nullptr;
      currNode->isWord=false;
    }
    else{
      currNode->isWord=false;
    }
  }
  
  return true;
}

listOfObjects<string> * Trie::completions(string prefix) {
  TrieNode *currNode = root;
  int len = prefix.length();
  listOfObjects<string> *currCompletions = new listOfObjects<string>("");

  // Insert your code here
  //reaching the node where prefix ends
  for (int i =0; i<len; i++){
    int a = toupper(prefix[i]) - 'A';
    if (currNode->branch[a]==nullptr) return nullptr; //since there are no words with this prefix
    currNode = currNode->branch[a];
  }
  //calling add completions from this point
  recursiveAddCompletions(currNode, currCompletions);
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

  // Insert your code here
  //adds all the words that are completed on node in the currCompletions array
  if(node->isWord){ //if node is a word
    listOfObjects<int> *currind = node->indices;   //going through the indices
    while(currind!=nullptr){   //until currind becomes nullptr
      if(!isPresentInCompletions(currCompletions,nameDict->getKeyAtIndex(currind->object))){ //if station name is already present in currCompletion
        listOfObjects<string> *currentry=currCompletions;  //going through currCompletions to insert station name
        if (currentry->object==""){
          currentry->object = nameDict->getKeyAtIndex(currind->object);
        }
        else{
          while(currentry->next!=nullptr){  //last element of currCompletions
            currentry=currentry->next;
          }
          currentry->next= new listOfObjects<string> (nameDict->getKeyAtIndex(currind->object)); //assigning value to last element
        }
      }
      currind = currind->next;
    }
  }
  return true; //successfully added all the words of this node to currCompletions
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
