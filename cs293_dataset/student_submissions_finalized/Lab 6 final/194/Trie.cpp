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
  for (int i = 0; i < len; i++) {
    int index = wordInName[i] - 'A';
    if (currNode->branch[index]== nullptr){
      currNode->branch[index] = new TrieNode();
      currNode->numNonNullBranches++; 
    }
    currNode = currNode->branch[index];
  }
  currNode->isWord = true;
  //currNode->indices= new listOfObjects(indexOfName);
  
  if(currNode->indices==nullptr){ 
    currNode->indices=new listOfObjects(indexOfName);
  }
  else{
    listOfObjects<int> *temp = currNode->indices; 
    while(temp->next!=nullptr){
      //currNode->indices->next=currNode->indices->next->next;
      temp = temp->next;
    }
    temp->next = new listOfObjects(indexOfName);
  }
  return true;
}

bool Trie::del(string wordInName, string name) {
  TrieNode *currNode = root;
  TrieNode *lastBranchNode = nullptr;
  int lastBranchChar = -1;
  int len = wordInName.length();

  // Insert your code here
  for(int i = 0; i < len; i++){
    int index = wordInName[i]-'A';
    if(currNode->branch[index] == nullptr){
      return false;
    }
    else{
      if(i==len-1){ 
        if(currNode->branch[index]->isWord==true){
          listOfObjects<int> *temp = currNode->branch[index]->indices;
          if(nameDict->getKeyAtIndex(temp->object)==name){  
            if(temp->next != nullptr){
              currNode->branch[index]->indices=temp->next;
              //delete temp;
              temp=nullptr;
            }
            else if(temp->next == nullptr){ 
              temp==nullptr;
              if(lastBranchChar>0){
                bool hasChild = false;
                for(int j=0;j<NUM_CHARS;j++){
                  if(currNode->branch[index]->branch[j]!=nullptr){
                    hasChild = true;
                    break;
                  }
                }

                if(hasChild==false){ 
                  
                  recursiveDelete(lastBranchNode->branch[wordInName[lastBranchChar]-'A']);
                  lastBranchNode->branch[wordInName[lastBranchChar]-'A']=nullptr;

                /*TrieNode* delNode=lastBranchNode->branch[index];
                TrieNode* traverseNode;
                while(delNode!=nullptr){
                  traverseNode=delNode->branch[index];
                  delete delNode;
                  delNode=traverseNode;
                }*/
                }
              }
              else{
                bool hasChild = false;
                for(int j=0;j<NUM_CHARS;j++){
                  if(currNode->branch[index]->branch[j]!=nullptr){
                    hasChild = true;
                    break;
                  }
                }
                if(hasChild==false){
                  recursiveDelete(root->branch[wordInName[0]-'A']);
                  root->branch[wordInName[0]-'A']=nullptr;
                }
              }
            
            }
            return true;
          }
          while(temp->next!=nullptr){
            if(nameDict->getKeyAtIndex(temp->next->object)==name){
              if(temp->next->next==nullptr){
                //delete temp->next;
                temp->next=nullptr;
              }
              else{
                listOfObjects<int> *temp2 = temp->next;
                
                temp->next=temp->next->next;
                //delete temp2;
                temp2=nullptr;
              }
              return true;
            }
            else{
              temp=temp->next;
            }
          }
        }
        else{
          return false;
        }
      }
      else{
        bool hasChild = false;
        int count=0;
        for(int j=0;j<NUM_CHARS;j++){
          if(currNode->branch[index]->branch[j]!=nullptr){
            count++;
            if(count>1){ 
              hasChild = true;
              break;
            }
          }
        }
        if(hasChild==true){
          lastBranchNode = currNode->branch[index];
          lastBranchChar=i+1;
        }
        currNode=currNode->branch[index];
      }
    }
  }

  return false;
}

listOfObjects<string> * Trie::completions(string prefix) {
  TrieNode *currNode = root;
  int len = prefix.length();
  string placeholder="no";
  listOfObjects<string> *currCompletions = new listOfObjects(placeholder);

  // Insert your code here
  for (int i = 0; i < len; i++) {
    int index = prefix[i] - 'A';
    if (currNode->branch[index]== nullptr){
      break;
    }
    else{ 
      currNode = currNode->branch[index];
    }
  }
  recursiveAddCompletions(currNode,currCompletions);
  /*if (currNode->isWord ==true){
    listOfObjects<int> *temp = currNode->indices;
    //int temp = currNode->indices->object;
    //  currCompletions = new listOfObjects(nameDict->get.key);
    currCompletions = new listOfObjects(nameDict->getKeyAtIndex(temp->object));
    listOfObjects<string> *temp2 = currCompletions;
    temp= temp->next;
    while(temp!=nullptr){
      temp2->next= new listOfObjects(nameDict->getKeyAtIndex(temp->object));
      temp = temp->next;
      temp2 = temp2->next;
    }
  }*/
  
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

  // Insert your code here
  if (node->isWord ==true){
    listOfObjects<int> *temp = node->indices;
    //int temp = currNode->indices->object;
    currCompletions->next=new listOfObjects(nameDict->getKeyAtIndex(temp->object));
    listOfObjects<string> *temp2 = currCompletions->next;
    temp= temp->next;
    while(temp!=nullptr){
      temp2->next= new listOfObjects(nameDict->getKeyAtIndex(temp->object));
      temp = temp->next;
      temp2 = temp2->next;
    }
    return true;
  }
  else{
    for(int i=0;i<NUM_CHARS; i++){
      addCompletions(node->branch[i],currCompletions);
    }
    return true;
  }
  //return false;
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
