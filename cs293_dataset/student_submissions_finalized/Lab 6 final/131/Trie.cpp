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

struct TrieNode* Trie:: newNode(){ //creates a new node for the alphabet to be inserted 
    TrieNode *newnode = new TrieNode;
    newnode->isWord=false;
    for(int i=0;i<NUM_CHARS;i++){ // initialises all the children to be null
      newnode->branch[i]=nullptr;
    }
    return newnode; // returns the newly created node
}

bool Trie::insert(string wordInName, int indexOfName) { // inserts word into the trie
  TrieNode *currNode = root;
  int len = wordInName.length(); // calculate length of the word to be inserted
  if (!isPresent(wordInName)){ // check if word is alredy present in the trie
    for (int i=0;i<len; i++){
      int letter =wordInName[i]-'A'; //add alphabets of the word if not present alredy
      if (!currNode->branch[letter])
        currNode->branch[letter]=newNode();
     currNode=currNode->branch[letter]; 
    }
  }
  else{
    for (int i = 0; i < len; i++) { // when word is alredy present
    int letter = toupper(wordInName.at(i)) - 'A';
    currNode = currNode->branch[letter];// get the location of the last element of the word 
    }
  }
    currNode->isWord=true; // set isWord to true
    
    listOfObjects<int> *tempindex = new listOfObjects<int> (0);// add a element ot the linked list of indices
    tempindex->object = indexOfName;                           // stored at the end of the word 
    tempindex->next = currNode->indices;
    currNode->indices =tempindex;
    
  // Insert your code here

  return true;
  
}

bool Trie::del(string wordInName, string name) {
  TrieNode *currNode = root;
 
  TrieNode *lastBranchNode = nullptr;
  int lastBranchChar = -1;
  int len = wordInName.length();
  
   if (isPresent(wordInName)){// check if word to be deleted is present in the trie
      deleting(root,wordInName,name,0); // call a recursive function
    }

  // Insert your code here
  return true;
}
bool Trie::isEmpty(TrieNode* root) // to check if all the children of a particular trie node are null
{
  for (int i = 0; i < NUM_CHARS; i++)
    if (root->branch[i]) 
      return false;  // if child not a null pointer return false
  return true;
}

struct TrieNode* Trie::deleting(TrieNode * root ,string wordInName,string station,int level=0){
  if (!root)
    return nullptr;
  
  if (level == wordInName.length()) {// this is just for the last letter of the word
    if (root->isWord){
      bool onlyone=true; 
      listOfObjects<int> *index =root->indices;
      listOfObjects<int> *prev =root->indices;
      while(nameDict->getKeyAtIndex(index->object) !=station){ // find the location of the station in the linked lisr=t
          onlyone=false;
          prev=index;
          index=index->next;
      }
      if(onlyone==true && index->next !=nullptr){
        root->indices=index->next; // station is the first element in the linked list of indices associated  with the word
      }
      else if(onlyone==false){prev->next=index->next;index->next=nullptr;} // word occurs in more than one station 
      else {root->isWord = false;} // word occurs in only one station name
    }

    if (isEmpty(root) && root->isWord==false) { // delete the node if all its children are null 
        delete (root);                          // and it does not occur in another station name
        root = nullptr;
    }
 
    return root;
  }
 
  int index = wordInName[level] - 'A'; // for all letters except the last
  root->branch[index] =deleting(root->branch[index], wordInName,station, level + 1); // recurse over all the letters
  if (isEmpty(root) && root->isWord == false) {
    delete (root);  // delete the node if all its children are null
    root = nullptr;  // and it does not occur in another station name
  }
 
  return root;
}

listOfObjects<string> * Trie::completions(string prefix) {
  TrieNode *currNode = root; 
  int len = prefix.length(); 
  listOfObjects<string> *currCompletions=nullptr; // initialise a linked list of stirng type to store stations
 
  for (int i = 0; i < len; i++) {
    int letter = toupper(prefix.at(i)) - 'A';
    if (currNode->branch[letter] == nullptr) {
      return nullptr;
    }
    currNode = currNode->branch[letter];// get the location of the last element of the prefix in the trie
  }
   recursiveAddCompletions(currNode,currCompletions);// passed by reference
  return currCompletions;
  
}

bool Trie::recursiveAddCompletions(TrieNode *node, listOfObjects<string> *&currCompletions) {
  if (node->isWord) {  // a complete word found 
    if (!addCompletions(node, currCompletions)) { 
      return false;
    }
  }

  TrieNode *currNode = node;
  for (int i = 0; i < NUM_CHARS; i++) {
    if (currNode->branch[i] != nullptr) { // recurse over all the children of the susequent nodes
      if (!recursiveAddCompletions(currNode->branch[i], currCompletions)) {
	return false;
      }
    }
  }
  return true;
}

bool Trie::addCompletions(TrieNode *node, listOfObjects<string> *&currCompletions) {
  listOfObjects<int> *currIndex = node->indices; // iterate over all elements of linked list at the end of a complete word
  while (currIndex != nullptr) {//to store the keys of the corresponding indices in currCompletions
    if (!isPresentInCompletions(currCompletions,nameDict->getKeyAtIndex(currIndex->object))){
      listOfObjects<string> *tempWord = new listOfObjects<string> ("");
      tempWord->object = nameDict->getKeyAtIndex(currIndex->object);
      tempWord->next = currCompletions;  // updating linked list of station names with the given preifx
      currCompletions = tempWord;
    
    }
    currIndex=currIndex->next;   
   
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
{ string a="|   ";
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
	recursivePrintTrie(currNode, prefix + ((siblingsToRight) ? a : "    "), i, childrenToRight);
      }
    }
  }
}
// End edit version 1

#endif
