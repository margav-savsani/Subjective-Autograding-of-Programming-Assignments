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
  for (int i = 0; i < len; i++){

    int index = toupper(wordInName.at(i)) - 'A';

    if (!currNode->branch[index]){
      currNode->branch[index] = new TrieNode();
      currNode->numNonNullBranches += 1;
    }

    currNode = currNode->branch[index];
  }
  
  // mark last node as leaf
  currNode->isWord = true;
  listOfObjects<int> *temp = currNode->indices;

  if (temp==NULL){
    currNode->indices = new listOfObjects<int>(indexOfName);
    return true;
  }
  while(temp->next!=NULL){
    temp = temp->next;
  }
  temp->next = new listOfObjects<int>(indexOfName);
  return true;
}

bool Trie::del(string wordInName, string name) {
  TrieNode *currNode = root;
  TrieNode *lastBranchNode = nullptr;
  TrieNode *temp = nullptr;
  int lastBranchChar = -1;
  int len = wordInName.length();

  for (int i=0; i<len; i++){
    int index = toupper(wordInName.at(i)) - 'A';
    if(!currNode->branch[index]){ //if not found return null
      return false;
    }

    if( i<len && ( currNode->numNonNullBranches>1 || currNode->isWord ) ){
      // cout<<" ++numnonnullbrancjes "<<currNode->numNonNullBranches<<endl;
       lastBranchNode = currNode;
       lastBranchChar = index;
      //  cout<<" ++lastbranchNode -> index "<<char( '\0' + lastBranchChar + 'A')<<endl;

    }
    
    currNode = currNode->branch[index];

  }

  if(currNode->isWord){

    //delete the occurrence of the word from indices
    listOfObjects<int> *temp = currNode->indices;
    if(temp->next==NULL){
      //only one indices is there then check for numnonNullbranches
      if(nameDict->getKeyAtIndex(temp->object)==name){

        delete(temp);
        currNode->indices=nullptr;
        currNode->isWord=false;
        
        if(currNode->numNonNullBranches == 0 && lastBranchChar!=-1){
          recursiveDelete(lastBranchNode->branch[lastBranchChar]);
          // cout<<" ++lastbranchNode -> index "<<char( '\0' + lastBranchChar + 'A')<<endl;
          lastBranchNode->numNonNullBranches -= 1;
          // recursiveDelete(lastBranchNode->branch[lastBranchChar]);
          lastBranchNode->branch[lastBranchChar] = NULL;
          // TrieNode* g = lastBranchNode, *h;
          // while( g!=NULL && g->isWord==false ){
          //   h = g
          // }
          // h = g->branch[lastBranchChar]

        }
        else if(currNode->numNonNullBranches == 0 && lastBranchChar==-1){
          // cout<<"inside \n";
          for(int i=0; i<NUM_CHARS; i++){
            if(root->branch[i]!=NULL){
              recursiveDelete(root->branch[i]);
              root->branch[i]=NULL;
              root->numNonNullBranches--;
            }
          }
        }
        
        return true;
      }
    }
    else{
      //many indices are there i have to delete just the given station name
      if(nameDict->getKeyAtIndex(temp->object) == name){
        currNode->indices = temp->next;
        delete(temp);
        return true;
      }
      while( temp->next!=NULL && nameDict->getKeyAtIndex(temp->next->object) != name ){
        temp = temp->next;
      }
      if(nameDict->getKeyAtIndex(temp->next->object) == name){
        listOfObjects<int> *t = temp->next;
        temp->next = temp->next->next;
        delete(temp->next);
        return true;
      }
      return false;//name not found
    }
  }

  return false;
}

listOfObjects<string> * Trie::completions(string prefix) {
  TrieNode *currNode = root;
  int len = prefix.length();
  listOfObjects<string> *currCompletions = nullptr;
  listOfObjects<string> *temp = nullptr;
  // Insert your code here
  for (int i = 0; i < len; i++){

    int index = toupper(prefix.at(i)) - 'A';

    if (!currNode->branch[index]) // if null 
      return currCompletions;
    
    currNode = currNode->branch[index]; 
  }
  recursiveAddCompletions(currNode, *&currCompletions);

  return currCompletions;
  
}

bool Trie::recursiveAddCompletions(TrieNode *node, listOfObjects<string> *&currCompletions) {
  if (node->isWord) {
    if (!addCompletions(node, *&currCompletions)) {
      return false;
    }
  }

  TrieNode *currNode = node;
  for (int i = 0; i < NUM_CHARS; i++) {
    if (currNode->branch[i] != nullptr) {
      if (!recursiveAddCompletions(currNode->branch[i], *&currCompletions)) {
	return false;
      }
    }
  }

  return true;
}

bool Trie::addCompletions(TrieNode *node, listOfObjects<string> *&currCompletions) {

   if(node->isWord){ 

      listOfObjects<int> *t = node->indices;
      listOfObjects<string> *y = currCompletions;
      listOfObjects<string> *temp = new listOfObjects<string>(nameDict->getKeyAtIndex(t->object));

      if (currCompletions==NULL)      
        currCompletions = temp;      
      else{
        while(y->next!=NULL)
          y = y->next;
        y->next = temp;
      }
      
      while(t->next!=NULL){
        t = t->next;
        listOfObjects<string> *node = new listOfObjects<string>(nameDict->getKeyAtIndex(t->object));
        temp->next = node;
        temp = temp->next;   
      }

      return true;
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

