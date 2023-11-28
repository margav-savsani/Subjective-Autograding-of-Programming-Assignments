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
  for(int i=0;i<len;i++){
    int c=tolower(wordInName[i])-'a';
    if(currNode->branch[c]==nullptr){
      currNode->branch[c]=new TrieNode;
      currNode->numNonNullBranches+=1;
    }
    currNode=currNode->branch[c];
    // //Edit
    // cout<<"Inserted: "<<wordInName[i]<<endl;
    // //End Edit
    if(i==len-1){
      currNode->isWord=true;

      if(currNode->indices==nullptr) {
        currNode->indices=new listOfObjects<int>(indexOfName);
      }
      else{
        listOfObjects<int> *emptyindex=currNode->indices;
        while(emptyindex->next!=nullptr){
          emptyindex=emptyindex->next;
        }
        emptyindex->next=new listOfObjects<int>(indexOfName);
        // currNode->indices=emptyindex;
      }

      // //Edit
      // // cout<<"Index value stored: "<<emptyindex->object<<endl;
      // if(currNode->indices==nullptr) cout<<"Error Caught\n";
      // //Edit End
    }
  }
  return true;
}

bool Trie::del(string wordInName, string name) {
  TrieNode *currNode = root;
  TrieNode *lastBranchNode = nullptr;
  int lastBranchChar = tolower(wordInName[0])-'a';
  int len = wordInName.length();
  int indexOfName=nameDict->get(name)->value;

  // Insert your code here
  lastBranchNode=root;

  for(int i=0;i<len;i++){
    int c=tolower(wordInName[i])-'a';
    lastBranchNode=lastBranchNode->branch[c];
  }

  listOfObjects<int> *index=lastBranchNode->indices;
  int numOfIndices=1;
  while(index->next!=nullptr){
    index=index->next;
    numOfIndices+=1;
  }
  // //EDIT
  // cout<<numOfIndices<<endl;
  // //END EDIT
  index=lastBranchNode->indices;
  if(numOfIndices>1){
    listOfObjects<int> *prev=nullptr;
    while(index->object!=indexOfName){
      prev=index;
      index=index->next;
    }
    if(prev==nullptr){
      lastBranchNode->indices=index->next;
      // delete index;
      return true;
    }
    else{
      prev->next=index->next;
      // delete index;
      return true;
    }
  }
  else{
    TrieNode *checkpoint=root;
    for(int i=0;i<len;i++){
    int c=tolower(wordInName[i])-'a';
    if(currNode->numNonNullBranches>1 || currNode->isWord==true){
      checkpoint=currNode;
      lastBranchChar=tolower(wordInName[i])-'a';
    }
    currNode=currNode->branch[c];
    }
    recursiveDelete(checkpoint->branch[lastBranchChar]);
    checkpoint->numNonNullBranches--;
    checkpoint->branch[lastBranchChar]=NULL;
    return true;
  }

  return false;
}

listOfObjects<string> * Trie::completions(string prefix) {
  TrieNode *currNode = root;
  int len = prefix.length();
  listOfObjects<string> *currCompletions = nullptr;

  // Insert your code here


  for(int i=0;i<len;i++){
    int c=tolower(prefix[i])-'a';
    // //EDIT
    // cout<<"prefix[i]: "<<prefix[i]<<" ,c: "<<c<<endl;
    // //END EDIT
    currNode=currNode->branch[c];
  }
  

  recursiveAddCompletions(currNode,currCompletions);

  // //EDIT
  // if(currCompletions==nullptr){cout<<"currCompletions is null\n";}
  // //END EDIT
  return currCompletions;
  
}

bool Trie::recursiveAddCompletions(TrieNode *node, listOfObjects<string> *&currCompletions) {
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

bool Trie::addCompletions(TrieNode *node, listOfObjects<string> *&currCompletions) {

  // Insert your code here
  listOfObjects<string> *temp=currCompletions;
  listOfObjects<int> *index=node->indices;
  // //Edit
  //   if(node->indices==nullptr){cout<<"Null Indices\n";}
  // //Edit End
  while(index!=nullptr){
    int iValue=index->object;
    if(currCompletions==nullptr){
      currCompletions=new listOfObjects<string>(nameDict->getKeyAtIndex(iValue));
      // //EDIT
      // cout<<"key at index: "<<nameDict->getKeyAtIndex(iValue)<<endl;
      // //END EDIT
      temp=currCompletions;
    }
    else{
      while(temp->next!=nullptr){temp=temp->next;}
      temp->next = new listOfObjects<string>(nameDict->getKeyAtIndex(iValue));
      // //EDIT
      // cout<<"key at index: "<<nameDict->getKeyAtIndex(iValue)<<endl;
      // //END EDIT
    }
    index=index->next;
  }
  // //Edit
  // if(currCompletions==nullptr){cout<<"currCompletions is still null\n";}
  // //End Edit

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
