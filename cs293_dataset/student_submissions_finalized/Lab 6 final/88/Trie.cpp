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
  for(int i=0; i<len; i++){
    //converting to lowercase
    char c;
    if(wordInName[i]>='a' && wordInName[i]<='z'){
      c=wordInName[i]-'a'+'A';
    }
    else{
      c=wordInName[i];
    }
    if (currNode->branch[c-'A'] == nullptr){
      currNode->branch[c-'A'] = new TrieNode(); // creating a new node, if it doesnt exist
      (currNode->numNonNullBranches)++;
    }
    currNode = currNode->branch[c-'A'];
  }
  if(currNode->isWord==false){
    currNode->isWord=true;
    currNode->indices=new listOfObjects<int>(indexOfName); //creating a linked list of words if it doesnt exist
  }
  else{
    listOfObjects<int> *currindex=currNode->indices; //inserting to beginning of linked list
    currNode->indices=new listOfObjects<int>(indexOfName);
    currNode->indices->next=currindex;
  }
  return true; //successfully deleted
}

bool Trie::del(string wordInName, string name) {
  TrieNode *currNode = root;
  TrieNode *lastBranchNode = root;

  char c; // converting to lowercase
  if(wordInName[0]>='a' && wordInName[0]<='z'){
    c=wordInName[0]-'a'+'A';
  }
  else{
    c=wordInName[0];
  }
  char lastBranchChar = c; // default value

  int len = wordInName.length();
  // Insert your code here
  for(int i=0; i<len; i++){
    // converting to lowercase
    char c;
    if(wordInName[i]>='a' && wordInName[i]<='z'){
      c=wordInName[i]-'a'+'A';
    }
    else{
      c=wordInName[i];
    }
    if (currNode->branch[c-'A'] == nullptr){
      return false; // does not exist
    }
    if(currNode->numNonNullBranches>1 || currNode->isWord){
      lastBranchNode=currNode;
      lastBranchChar=c; // storing node of last branch
    }
    currNode = currNode->branch[c-'A'];
  }
  if(currNode->isWord==false){
    return false; // word does not exist
  }
  else{
    // deleting from linked list
    listOfObjects<int> *currindex=currNode->indices;
    listOfObjects<int> *previndex=nullptr;
    while(currindex != nullptr){
      string word=nameDict->getKeyAtIndex(currindex->object);
      if(word==name){
        if(previndex==nullptr){
          currNode->indices=currindex->next;
        }
        else{
          previndex->next=currindex->next;
        }
        delete currindex;
        break;
      }
      previndex=currindex;
      currindex=currindex->next;
    }

    currindex=currNode->indices;
    int count=0;
    while(currindex != nullptr){
      currindex=currindex->next;
      count++;
    }

    // updating trie nodes
    if(count==0) currNode->isWord=false;
    if(!(currNode->isWord) && currNode->numNonNullBranches==0){
      recursiveDelete(lastBranchNode->branch[lastBranchChar-'A']);
      lastBranchNode->branch[lastBranchChar-'A']=nullptr;
      (lastBranchNode->numNonNullBranches)--;
    }
  }
  return true;
}

listOfObjects<string> * Trie::completions(string prefix) {
  TrieNode *currNode = root;
  int len = prefix.length();
  listOfObjects<string> *currCompletions = nullptr;

  // Insert your code here
  bool isPresent=true;
  for(int i=0; i<len; i++){
    // converting to lowercase
    char c;
    if(prefix[i]>='a' && prefix[i]<='z'){
      c=prefix[i]-'a'+'A';
    }
    else{
      c=prefix[i];
    }
    if(currNode->branch[c-'A']!=nullptr){
      currNode=currNode->branch[c-'A'];
    }
    else{
      isPresent=false;
      break;
    }
  }
  if(isPresent){
    recursiveAddCompletions(currNode,currCompletions); // recirsively add completions from given node
  }
  return currCompletions; // nullptr if doesnt exist
  
}

bool Trie::recursiveAddCompletions(TrieNode *node, listOfObjects<string> * &currCompletions) {
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

bool Trie::addCompletions(TrieNode *node, listOfObjects<string> * &currCompletions) {

  // Insert your code here
  if(currCompletions==nullptr){ // create new linked list and insert into it
    listOfObjects<int> *currNode=node->indices;
    string word=nameDict->getKeyAtIndex(currNode->object);
    currCompletions=new listOfObjects<string>(word);
    listOfObjects<string> *curent_node_of_currCompletions=currCompletions;
    while(currNode->next != nullptr){
      word=nameDict->getKeyAtIndex(currNode->next->object);
      curent_node_of_currCompletions->next=new listOfObjects<string>(word);
      curent_node_of_currCompletions=curent_node_of_currCompletions->next;
      currNode=currNode->next;
    }
  }
  else{ // insert into existing list
    listOfObjects<int> *currNode=node->indices;
    listOfObjects<string> *curent_node_of_currCompletions=currCompletions;
    while(curent_node_of_currCompletions->next != nullptr) curent_node_of_currCompletions=curent_node_of_currCompletions->next;
    while(currNode != nullptr){
      string word=nameDict->getKeyAtIndex(currNode->object);
      curent_node_of_currCompletions->next=new listOfObjects<string>(word);
      curent_node_of_currCompletions=curent_node_of_currCompletions->next;
      currNode=currNode->next;
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
