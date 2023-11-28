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
  int i = 0;
  TrieNode*val = root;
  while (len>0){
    if(val->branch[(wordInName[i]-'A')]==nullptr){
      val->branch[wordInName[i]-'A'] = new TrieNode();
      val->numNonNullBranches++ ;
      val = val->branch[wordInName[i]-'A'];
      
      len--;
      i++;
    }
    else{
      val = val->branch[wordInName[i]-'A'];
      i ++;
      len--;
    }
    if(len==0){
      val->isWord = true;
      listOfObjects<int> *v =val->indices;
      listOfObjects<int> *a ;
      
      if (val->indices==nullptr)
      {
        val->indices= new listOfObjects(indexOfName);
      }
      else{
      while(true){
        if(v == nullptr){
          a->next= new listOfObjects(indexOfName);
          break;
        }
        else{ a=v;
          v = v->next;
          continue;
        }
      }}
      
    }
    }
    return true;
    }

 bool Trie::del(string wordInName, string name) {
  TrieNode *currNode = root;
  TrieNode *lastBranchNode ;
  lastBranchNode = root;
  int lastBranchChar = 0;
  int len = wordInName.length();
  int i =0;
  while(len>0){
    if(lastBranchNode->branch[wordInName[i]-'A'] != nullptr){
      lastBranchNode = lastBranchNode->branch[wordInName[i]-'A'];
      len --;
      i++;
    }
    else{
      len --;
    }
  }
  TrieNode * val = new TrieNode();
  val = lastBranchNode;
  
  if(nameDict->getKeyAtIndex(val->indices->object)==name){
     
    if(val->indices->next == nullptr){
      val->isWord = false;
      val->indices=nullptr;
    }
    else{ val->indices=val->indices->next; }
  }
  else{ 
    listOfObjects<int> *x=val->indices;int i=0;
    while(x != nullptr ){
      if(nameDict->getKeyAtIndex(x->object)== name){
         break;
    } 
      i++;
      x = x->next;
    }
    x=val->indices;
    for(int j=0;j<i-1;j++){
      x=x->next;
  }
    x = x->next->next;}
 
 /* while(lastBranchNode->indices != nullptr){
    lastBranchChar ++;
   if( nameDict->lastBranchNode->indices->object == name){ 
   break;
   }
   else{
    lastBranchNode->indices = lastBranchNode->indices->next;
    continue;
   }}
  if(lastBranchChar==1){
    int i =0;
    TrieNode * v = new TrieNode();
    v= currNode->branch[wordInName[1]-'A'];
    while(len>1){
          if(currNode->branch[wordInName[i]-'A']->isWord == true)
      {
        v= currNode->branch[wordInName[i]-'A'];
        currNode = currNode->branch[wordInName[i]-'A'];
        i++;
        len--;
      }
      else{
      len --;
      currNode = currNode->branch[wordInName[i]-'A'];
      i++;
    }
    recursiveDelete(v);
    }
  else{
  if(v == )

  }




  
  else{

  } 
*/

  return true;
} 
 

listOfObjects<string> * Trie::completions(string prefix) {
  TrieNode *currNode = root;
  int len = prefix.length();
  listOfObjects<string> *currCompletions = nullptr;
  int i =0;
  while(len>0){
    if(currNode->branch[prefix[i]-'A'] != nullptr){
      currNode = currNode->branch[prefix[i]-'A'];
      len --;
      i++;
    }
    else
    {
      len--;
    }
  }
  currCompletions = new listOfObjects<string>("rishi");
  recursiveAddCompletions(currNode,currCompletions);
  

 /* listOfObjects<int> *v =currNode->indices;
  currCompletions = new listOfObjects(nameDict->getKeyAtIndex(v->object));
 listOfObjects<string> *x = currCompletions;
  v= v->next;
  while(v != nullptr){
    x->next=new listOfObjects(nameDict->getKeyAtIndex(v->object));
    x = x->next;
    v=v->next; */
  

  // Insert your code here
  return currCompletions->next;
  
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

  listOfObjects<int> *v =node->indices;
 listOfObjects<string> *x = currCompletions;
  while(v != nullptr){
    while(x->next == nullptr){
    listOfObjects<string> *a = new listOfObjects(nameDict->getKeyAtIndex(v->object));
    x->next = a;
    v=v->next;
    // x = x->next;
    // continue;
  }
     x=x->next;}
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
