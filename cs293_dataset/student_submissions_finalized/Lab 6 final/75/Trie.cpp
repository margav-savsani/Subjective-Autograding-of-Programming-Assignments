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
  int index = 0;
  bool newWord = false;

  for(int i = 0; i < len; i++){
    index = wordInName[i] - 'A';
    if (currNode -> branch[index] == NULL){ // the node corresponding to the current alphabet is not present in the trie
      currNode->branch[index] = new TrieNode; // creating a new node at the specific index if not already present
      currNode->numNonNullBranches++;// increment the number of branches from that node
      newWord = true;
    }

    currNode = currNode->branch[index]; // going to the next node
  }
  currNode->isWord = true;// to indicate that the word hasended at this node
  // update the listOfIndices to store the index to the full name of the station in the dictionary

  // Adds a new node containing the index of the word to the starting of the linked list 
  currNode->addIndex(indexOfName);

  // currNode->printIndices();
  return true;
}

bool Trie::del(string wordInName, string name) {
  if (root == NULL){
    return false;
  }
  TrieNode *currNode = root;
  TrieNode *lastBranchNode = root;
  int lastBranchChar = -1;
  int len = wordInName.length();
  int index = 0;
  bool newWord = false;

  // We know that the root is not null 
  for (int i = 0; i<NUM_CHARS; i++){
    if (root->branch[i]!=NULL){
      lastBranchChar = i;
      break;
    }
  }
  if (currNode == NULL){
    return false;
  }

  for (int i = 0; i<len;i++){
    index = wordInName[i] - 'A';
    if (currNode -> branch[index] == NULL){ // the node corresponding to the current alphabet is not present in the trie
      return false; // the word is not present in the trie
    }
    if (currNode->numNonNullBranches>1){
      lastBranchNode = currNode; // to store the node, which has the last branch corresponding to the word to be deleted
      lastBranchChar = index; // to store the last common alphabet that the word to be deleted has i common with the other branches
    }
    if (currNode->isWord==true){
      lastBranchNode = currNode; // to store the node, which has the last branch corresponding to the word to be deleted
      lastBranchChar = index; // to store the last common alphabet that the word to be deleted has i common with the other branches
    }
    currNode = currNode->branch[index]; // going to the next node
  }

  // Two cases are possible - either the word to be delete has a unique branch at the end or it is a prefix to some other branch
  if (currNode->numNonNullBranches==1){ // The given word is prefix to other word
       //delete word indice from the index linked list
       currNode->deleteIndex(name, nameDict);
       // if index linked list is empty, then isWord = false
       if (currNode->isListEmpty()){
        currNode->isWord = false;
       }
       return true;
  }
  else { // The given word has seperate branch corresponding to it at the end
      //delete from the index linked list
      currNode->deleteIndex(name, nameDict);
      if(currNode->isListEmpty()){
        lastBranchNode->branch[lastBranchChar] = NULL;
        lastBranchNode->numNonNullBranches--;
      }
      return true;
  }
  // Update the number of indices stored in that node (or leaf)
}

listOfObjects<string> * Trie::completions(string prefix) {
  TrieNode *currNode = root;
  int len = prefix.length();
  listOfObjects<string> *currCompletions = new listOfObjects<string>("");// sentinel pointer to the linked list of completions

  for(int i=0;i<len;i++)
    {
        if(currNode->branch[prefix[i]-'A']==NULL)
            return NULL;
        currNode=currNode->branch[prefix[i]-'A'];
    }
  
  recursiveAddCompletions(currNode, currCompletions);
  // cout<<"I reached here"<<endl;
  // cout<<"Is currCompletion NULL?"<<(currCompletions==NULL)<<endl;
  return currCompletions;
}

bool Trie::recursiveAddCompletions(TrieNode *node, listOfObjects<string> *currCompletions) {
  if (node->isWord) {
    // cout<<"Calling addcompletions"<<endl;
    if (!addCompletions(node, currCompletions)) {
      return false;
    }
  }
  // cout<<"checkpoint2"<<endl;
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

  if (node->indices == NULL){
    return false;
  }
  else {
    // cout<<"entered the add completions function"<<endl;
    listOfObjects<int> *currNode = node->indices;
    
    // cout<<"Station Name is:"<<nameDict->getKeyAtIndex(currNode->object)<<endl;
    if (!find(nameDict->getKeyAtIndex(currNode->object),currCompletions)){
      addStationName(nameDict->getKeyAtIndex(currNode->object),currCompletions);
    }
    // cout<<"Is currCompletions NULL? (aFTER COMING OUT OF THE addStationName Function)"<<(currCompletions==NULL)<<endl;
    while(currNode->next!=NULL){
      // cout<<"Station Name is:"<<nameDict->getKeyAtIndex(currNode->object)<<endl;
      currNode = currNode->next;
      if (!find(nameDict->getKeyAtIndex(currNode->object),currCompletions)){
        addStationName(nameDict->getKeyAtIndex(currNode->object),currCompletions);
      }
      // cout<<"Is currCompletions NULL?"<<(currCompletions==NULL)<<endl;
      // cout<<"Loop mein atak gaya bc"<<endl;   
    }

    return true;
  }
}

void Trie::addStationName(string Name, listOfObjects<string> *currCompletions){
    //cout<<"Inside insert"<<endl;
    listOfObjects<string> *currNode = currCompletions;
    // cout<<"Is currNode NULL? (inside addStationName)"<<(currNode==NULL)<<endl;
    if (currNode->object==""){
      // listOfObjects<string>* newNode = new listOfObjects<string>(Name);
      // currCompletions->next = newNode;
      currNode->object = Name;
      // cout<<"Is currNode NULL? (inside addStationName AFTER SETTING THE NEW VALUE)"<<(currCompletions==NULL)<<endl;
    }
    else{
      while(currNode->next!=NULL){
        currNode = currNode->next;
      }
      listOfObjects<string>* newNode = new listOfObjects<string>(Name);
      currNode->next = newNode;
    }
}

bool Trie:: find(string Name, listOfObjects<string> *currCompletions){
  listOfObjects<string> *currNode = currCompletions;
  if (currNode->object==""){
    return false;
  }
  else {
    while (currNode->next!=NULL){
      if (currNode->object == Name){
        return true;
      }
      currNode = currNode->next;
    }
    // to check for the last node 
    if (currNode->object == Name){
        return true;
    }
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
