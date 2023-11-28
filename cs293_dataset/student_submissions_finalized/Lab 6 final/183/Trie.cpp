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
listOfObjects<string> *x=nullptr;

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
  for(int i=0;i<len;i++){
    int index = toupper(wordInName.at(i)) - 'A';
    if(!currNode->branch[index]){
      currNode->branch[index]=new TrieNode();               
      (currNode->branch[index])->parent=currNode;    //inserting letters in wordInName if not present
      currNode->numNonNullBranches++;
    }
    currNode=currNode->branch[index];               //if letter is present then check next letter
  }
  currNode->isWord=true;                   //at end of wordInName updating isWord=true (useless if already true)
  if(!currNode->indices){
      currNode->indices=new listOfObjects<int>(indexOfName);     //if no linked list then create new list and insert new index at head
  }
  else{
    listOfObjects<int>*temp=currNode->indices;               //if there is linked list then find tail and point new index to tail and 
    while(temp->next) {
      if(temp->object==indexOfName){return false;}           //update tail NOTE:if index is already present in linked list then return false
      temp=temp->next;
    }
    if(temp->object==indexOfName){return false;}
    temp->next=new listOfObjects<int>(indexOfName);
  }
  return true;
}
// Insert your code here


bool Trie::del(string wordInName, string name) {
  TrieNode *currNode = root;
  TrieNode *lastBranchNode = root;   //this is last node where it has either two children or any linked list is present
  int lastBranchChar = -1;           //this is index of branch of next letter to lastbranchNode
  int h=0;
  int len = wordInName.length();
  if(!root)
        return false;                 //if trie is empty return false
  if(!isPresent(wordInName))
          return false;               //if wordInName is not present in trie then return false
  for(int i=0;i<len;i++){
        int index = toupper(wordInName.at(i)) - 'A';
        if(i==len-1){
          h++;                                 //finding last letter in wordInName
        }
        if((currNode->isWord==true)||(currNode==root)||(currNode->numNonNullBranches>1)){
          lastBranchNode=currNode;                        //updating lastBranchNode and lastBranchChar
          lastBranchChar=index;
        }
        currNode=currNode->branch[index];           
  }
  if(h==1){
    if(currNode->isWord==false) return false;          //if there is no linked list at end of wordInName then return false
    listOfObjects<int>*prev=nullptr;                   //prev of currnode in linked list
    listOfObjects<int>*temp=currNode->indices;         //currnode in linkes list
    int i=temp->object;
    string s=nameDict->getKeyAtIndex(i);               //word at head of linked list
    if(s==name){                                      
      currNode->indices=currNode->indices->next;       //if word at head is to be deleted then update currNode indices to next to head
      if(currNode->indices){return true;}              //now after dleting if linked list is not empty then return true
      else{currNode->isWord=false;}                    //if empty then update isWord to false
    }
    if(!currNode->indices){                               //if linked list is empty
      if(currNode->numNonNullBranches>0){return true;}    // and no.of children for last letter of wordInName is>o simply return true
      lastBranchNode->branch[lastBranchChar]=nullptr;     //if no children then find  lastBranchNode and update its branch[latbranchChar] to null
      lastBranchNode->numNonNullBranches--;               //decrease no.of children of lastBranchNode by 1
      return true;
    }
    else{
      while(temp->next){            
      prev=temp;                                     //if linked list is not empty and word is not at head of linked list
      temp=temp->next;                               //find word in linked list then update pointer of currnode prev to currnode next
      int i=temp->object;                            
      string s=nameDict->getKeyAtIndex(i);
      if(s==name){
        prev->next=temp->next;
        temp=nullptr;
        return true;}
      }
      return false;
    }
  }
  return true;
}
  // Insert your code here

listOfObjects<string> * Trie::completions(string prefix) {
  TrieNode *currNode = root;
  int len = prefix.length();
  listOfObjects<string> *currCompletions = nullptr;
  for(int i=0;i<len;i++){
        int index = toupper(prefix.at(i)) - 'A';           //finding node at last letter of prefix
        currNode=currNode->branch[index];
  }
  recursiveAddCompletions(currNode,x);                    //calling recursiveAddCompletions(currNode,x) to update x where x is global to store completions
  currCompletions=x;                                              
  return currCompletions;                                 //returning global completions
}

bool Trie::recursiveAddCompletions(TrieNode *node, listOfObjects<string> *currCompletions) {
  if (node->isWord) {
    if (!addCompletions(node,x)) {
      return false;
    }
  }
  
  TrieNode *currNode = node;
  for (int i = 0; i < NUM_CHARS; i++) {
    if (currNode->branch[i] != nullptr) {
      if (!recursiveAddCompletions(currNode->branch[i], x)) {
	      return false;
      }
    }
  }
  currCompletions=x;
  return true;
}

bool Trie::addCompletions(TrieNode *node, listOfObjects<string> *currCompletions) {

  // Insert your code here 
  if(node->isWord==true){             //if linked list is not empty 
    while(node->indices){            //traverse through linked list of last letter
      string s=nameDict->getKeyAtIndex(node->indices->object); //word at node at linked list
      if(!currCompletions){
          currCompletions=new listOfObjects<string>(s);      //if completions is null then create new list whose head is word at node at linked list
      }
      else{
          listOfObjects<string>*temp=currCompletions;      //if completion is not empty 
          int r=0;                                         //finding if word is already present in linked list of completion
          if(temp->object==s){r++;}                        //if prrsent then update r
          while(temp->next) {                             
            temp=temp->next;                              //updating node in linked list of currcompletions until nullptr is found
            if(temp->object==s) r++;
          }
          if(r==0){
          temp->next=new listOfObjects<string>(s);}      //if already present in currcompletions then don't insert else insert
      }
      node->indices=node->indices->next;              //traverse through linked list of last letter
    }
    x=currCompletions;                  //updating global completions
    return true;
  }
  else{
    return false;
  }
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
