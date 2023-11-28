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
  int len = wordInName.length(); //length of word in name
  for(int i=0;i<len;i++){
    int letter = toupper(wordInName.at(i)) - 'A'; // toupper converts the lowercase to uppercase 
        if (currNode->branch[letter] == nullptr){
            currNode->branch[letter] = new TrieNode(); //use constructor to insert 
            currNode->numNonNullBranches++;
            currNode->branch[letter]->parent=currNode;}
  
        currNode = currNode->branch[letter];
    }// Insert your code here
  
    currNode->isWord=true;
    if(!currNode->indices){
      currNode->indices=new listOfObjects<int>(indexOfName); 
    }
    else{
      listOfObjects<int>*t=currNode->indices;
      while(t->next){
        if(t->object==indexOfName){return false;}
        t=t->next;
      }
      if(t->object==indexOfName){return false;}
      t->next=new listOfObjects<int>(indexOfName);

    }
    return true;
}

bool Trie::del(string wordInName, string name) { 
  TrieNode *currNode = root;
  TrieNode *lastBranchNode = root;
  int lastBranchChar = -1;
  int h=0;
    int Len = wordInName.length();
    if(!root) return false;
    if(!isPresent(wordInName)) return false;
    else{
        
        for(int i=0; i<Len; ++i){
            int letter = toupper(wordInName.at(i)) - 'A';
            if(i==Len-1){
                h++;
            }
            if((currNode->isWord==true)||(currNode->numNonNullBranches>1)||(currNode==root)){
              lastBranchNode =currNode;
              lastBranchChar=letter;
            }
            currNode= currNode->branch[letter];
          }
        if(h==1){
          if(currNode->isWord==false) return false;
          listOfObjects<int>*before=nullptr;
          listOfObjects<int>*curr=currNode->indices;
          int k=curr->object;
          string r=nameDict->getKeyAtIndex(k);
          
          if(r==name){
            
            currNode->indices=currNode->indices->next;
            if(currNode->indices){return true;}
            else{currNode->isWord=false;}
          }
          if(!currNode->indices){
            if(currNode->numNonNullBranches>0){return true;}
            lastBranchNode->branch[lastBranchChar]=nullptr;
            lastBranchNode->numNonNullBranches--;
            return true;
            }
          else{
            while(curr->next){
              before=curr;
              curr=curr->next;
              int k=curr->object;
              string r=nameDict->getKeyAtIndex(k);
              if(r==name){
                before->next=curr->next;
                curr=nullptr;                
                return true;
              }
            }
            return false;
          }

        }
      // Insert your code here
      
    }
}
listOfObjects<string> *s = nullptr;
listOfObjects<string> * Trie::completions(string prefix) {
  TrieNode *currNode = root;
  int len = prefix.length();
  listOfObjects<string> *currCompletions = nullptr;
  for(int i=0;i<len;i++){
    int letter = toupper(prefix.at(i)) - 'A';
    currNode= currNode->branch[letter];
  }
  recursiveAddCompletions(currNode,s);
  currCompletions=s;
  return currCompletions;
  
}

bool Trie::recursiveAddCompletions(TrieNode *node, listOfObjects<string> *currCompletions){
  
  if (node->isWord) {
    if (!addCompletions(node,s)) {
      return false;
    }
  }

  TrieNode *currNode = node;
  for (int i = 0; i < NUM_CHARS; i++) {
    if (currNode->branch[i] != nullptr) {
      if (!recursiveAddCompletions(currNode->branch[i], s)) {
	       return false;
      }
    }
  }
  currCompletions=s;

  return true;
}

bool Trie::addCompletions(TrieNode *node, listOfObjects<string> *currCompletions) {

  if(node->isWord==true){
    while(node->indices){
      string p=nameDict->getKeyAtIndex(node->indices->object);
      if(!currCompletions){
        currCompletions=new listOfObjects<string>(p);
        
      }
      else{
        listOfObjects<string>*pre=currCompletions;
        int h=0;
        if(pre->object==p){h++;}
        while(pre->next){ pre=pre->next;
            if(pre->object==p){h++;}
        }
        if(h==0){
          pre->next=new listOfObjects<string>(p);
        }
      }
      node->indices=node->indices->next;
      
  }
    s=currCompletions;
    return true;

  }
  else return false;
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
