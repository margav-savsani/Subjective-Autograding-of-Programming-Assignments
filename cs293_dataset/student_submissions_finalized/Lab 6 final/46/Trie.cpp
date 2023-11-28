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

bool Trie::ins( TrieNode* curr, string wordInName,int indexOfName) {  

  TrieNode *currNode = curr;
  int len = wordInName.length();
  if(len==0) return true;
  int letter = toupper(wordInName[0]) - 'A'; // getting indices to store alphabets

    if(currNode->branch[letter]==nullptr)  { // if there is no node, we create a new one
        currNode->branch[letter] = new TrieNode();
        currNode->numNonNullBranches++; //increasing braches
      }
      
  if(len==1) { // if there is only one element in string
          currNode->branch[letter]->isWord = true;
          if(currNode->branch[letter]->indices==nullptr) {// if there is no node, we create a new one
            currNode->branch[letter]->indices = new listOfObjects<int> (indexOfName);
          }
          else {
            listOfObjects<int>* p;
            listOfObjects<int>* q;
            p = currNode->branch[letter]->indices;
            q = new listOfObjects<int> (indexOfName); // if already node exits, then just append to it.
            q->next = p;
            currNode->branch[letter]->indices = q;
          }
          return true;
        }
      string new_name = wordInName;
      new_name.erase(0,1);  // doing in a recursive manner.
      ins(currNode->branch[letter],new_name,indexOfName);
      return true;
}

bool Trie::insert(string wordInName, int indexOfName) {
  return ins(root,wordInName,indexOfName);   // calling new function for the sake of recursion.
}

listOfObjects<int>* Trie::deleteKey(listOfObjects<int>* head, int x){
    if (!head) 
        return head; 
    while (head && head->object == x)
        head = head->next;
    listOfObjects<int> *curr = head, *prev = nullptr;
  
    while (curr) {
        if (curr->object == x)
            prev->next = curr->next;
        else
            prev = curr;
        curr = curr->next; // iteration
    }
    return head;
}

bool Trie::del(string wordInName, string name) {
  TrieNode *currNode = root;
  TrieNode *lastBranchNode = currNode;
  int lastBranchChar = -1;
  int len = wordInName.length();
  int tmp=0; // for edge cases

  string word = wordInName;
  char c = word[0];
  int ind_1 = toupper(c)-'A'; // getting indices to store alphabets
  lastBranchNode = currNode->branch[ind_1]; // pointing to the first element in the word
  lastBranchChar = ind_1;
  for(int i=0;i<len;i++) {
    if((currNode->isWord==true || ( currNode->numNonNullBranches>=2)) && i!=0 && i < len-1) {
      char c = word[i];
      int ind = toupper(c)-'A'; // getting indices to store alphabets
      lastBranchNode = currNode;
      lastBranchChar = ind;
      tmp=1; // for most of the general cases it is true
    }
    char c = word[i];
    int ind = toupper(c)-'A';
    currNode = currNode->branch[ind];
  }

  listOfObjects<int>* p = currNode->indices;
  int index = (nameDict->get(name))->value; // getting the key
  p = deleteKey(p,index); // calling this to delete a node from list with key
  currNode->indices = p;
  int cnt=0;
  while(p!=NULL) { // number of indices in the linked list
    cnt++;
    p=p->next;
  }
  if(cnt==0) {
     if(tmp==0) { // edge case of braching at first index itself
      if(currNode->numNonNullBranches>0) {
        currNode->isWord=false;
      }
      else{
      recursiveDelete(root->branch[ind_1]);
      root->branch[ind_1]=nullptr;
      root->numNonNullBranches--; //decresing brances
      }
     }
     else if(tmp==1){
      if(currNode->numNonNullBranches>0) { // edge case of braching at first index itself
        currNode->isWord=false;
      }
      else {
     recursiveDelete(lastBranchNode->branch[lastBranchChar]);
     lastBranchNode->numNonNullBranches--; //decresing brances
     lastBranchNode->branch[lastBranchChar] = nullptr;
      }
     }
  }
  return true;
}

listOfObjects<string> * Trie::completions(string prefix) {
  TrieNode *currNode = root;
  int len = prefix.length();
  listOfObjects<string> *currCompletions = nullptr;
  while(prefix.length()>=1) {
    char c = prefix[0];
    int letter = toupper(c)-'A';
    if(currNode->branch[letter]==nullptr){
      return nullptr;
    }
    else{
      currNode = currNode->branch[letter];
      prefix.erase(0,1);
    }
  }
  string bh = "adjh"; // dummy string
  currCompletions = new listOfObjects<string> (bh);  
  recursiveAddCompletions(currNode,currCompletions);
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
  if(node->isWord==false) return false; // it is not a word
  listOfObjects<int> *tmp = node->indices;
  while(tmp!=nullptr) {
    string name = nameDict->getKeyAtIndex(tmp->object);
    listOfObjects<string>* p = new listOfObjects<string> (name);
    p->next =currCompletions->next; // simply,appending the new node into the list
    currCompletions->next = p;
    tmp = tmp->next; //iteration
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
