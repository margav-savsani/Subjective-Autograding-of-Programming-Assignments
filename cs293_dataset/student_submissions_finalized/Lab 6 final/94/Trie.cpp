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
    int len = wordInName.length(); //length of input element

    for(int i=0;i<len;i++){
      int k= toupper(wordInName.at(i)) - 'A'; //chnaging into uppercase and getting its value in 1 to 26
      if (currNode->branch[k]==NULL){
        currNode->branch[k]=new TrieNode(); //creating new trienode
        currNode->numNonNullBranches+=1;
      }
      currNode=currNode->branch[k];
    }
    currNode->isWord=true;
    // adding new indexofname to start of list
    listOfObjects<int>*n=new listOfObjects(indexOfName);
    n->next=currNode->indices;
    currNode->indices=n;
 
  return true;
  
}

bool Trie::del(string wordInName, string name) {
  TrieNode *currNode = root;
  TrieNode *currNode1 = root;
  TrieNode *lastBranchNode = nullptr;
  int lastBranchChar = -1;
  int len = wordInName.length();
  /* Cases:
    1)Last element has no branches and has only element in its linked list which is to be deleted
    2)Last element has branches and has only element in its linked list which is to be deleted
    3)Last element has no branches and there are >1 elemnets in linked list
  
   */

  //getting last node of wordinname
  for(int i=0;i<len;i++){
    int k= toupper(wordInName.at(i)) - 'A';
    if( currNode->numNonNullBranches>1 || currNode->isWord){
      lastBranchNode=currNode;
      lastBranchChar=k;
    }
    currNode=currNode->branch[k];
    
  }
  
  if(currNode->indices->next==NULL){
    if(currNode->numNonNullBranches==0){
      //case 1
      TrieNode *a = lastBranchNode->branch[lastBranchChar];  
      lastBranchNode->branch[lastBranchChar] = nullptr;
      lastBranchNode->numNonNullBranches -= 1;  
      recursiveDelete(a); //recursively deleting from branch of lastbranchnode 
      return true;


    }
    else{
      //case 2
      currNode->indices=NULL; //deleting the elemnt in indices list
      return true;
    }

  }
  else{
    // case 3
    if(name==nameDict->getKeyAtIndex(currNode->indices->object)){
      currNode->indices=currNode->indices->next; //deleting the elemnt in indices list
      return true;
    }
    else{
      listOfObjects<int>*r=currNode->indices;
      listOfObjects<int>*pre;
      // deleting the element in list and assigining to next node in linked list
      while(r!=NULL){
        if(name==nameDict->getKeyAtIndex(r->object)){
          pre->next=r->next;
          return true;
        }
        pre=r;
        r=r->next;
      }
    }
  }
  

  // Insert your code here
  return false;
}

listOfObjects<string> * Trie::completions(string prefix) {
   TrieNode *currNode = root;
   int len = prefix.length();
   listOfObjects<string> *currCompletions = nullptr;
   // traversing through bottom of prefix
   for(int i=0;i<len;i++){
    int k= toupper(prefix.at(i)) - 'A';
    
    currNode=currNode->branch[k];
    if(currNode==NULL){
      return NULL;
    }
  }
  //adding dummy element
  currCompletions=new listOfObjects<string>("##");
  recursiveAddCompletions(currNode,currCompletions);


  // returning without dummy element
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

    if(node->indices==NULL) return true; //returning without adding anything

    listOfObjects<string>*obj=currCompletions; //traversing to last node
    while(obj->next!=NULL){
      obj=obj->next;
    }
    //taking elements from indices list and adding it to currcompletions(after converting it into string)
    listOfObjects<int>*s=node->indices;
    while(s!=NULL){
      obj->next=new listOfObjects<string>(nameDict->getKeyAtIndex(s->object));
      obj=obj->next;
      s=s->next;
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
    
    cout << ((branchId == 0) ? "|-" : (branchId == -1)? " ":"|_" ) << (char) ((branchId != -1) ? 'A'+branchId: '*');
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
