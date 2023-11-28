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
//while inserting string wordInName we will find for 1st letter is it already there
//in branch if there go to next letter and change currnode to that branch if not there
//we create it by new trienode() constructor.we do this recursively till we reach end of the word.
//now there are 3 cases
//case1: if this word is prefix of previously inserted word then we will make isword at lat letter 
//to be true and add indexofname in indices linked list.
//case2: if this word is newly created not as case1 then also we will do same as case1 did.
//case3: if exact word is there before then already isword is set to true we just need to add index to tail of 
//indices linked list.for that we iteratively run over linked list till tail and insert index.
bool Trie::insert(string wordInName, int indexOfName) {
  TrieNode *currNode = root;
  int len = wordInName.length();
  for (int i = 0; i < len; i++) {
    int letter = toupper(wordInName.at(i)) - 'A';
    if (currNode->branch[letter] == nullptr) {
      currNode->branch[letter]=new TrieNode();
      currNode->numNonNullBranches++;
      currNode = currNode->branch[letter];
    }
    else {
      currNode = currNode->branch[letter];
    }
  }
  if((currNode->isWord==false)){
    currNode->isWord=true;
    currNode->indices=new listOfObjects<int>(indexOfName);
    return true;
  }
  else{
    listOfObjects<int> *tmp = new listOfObjects<int>(indexOfName);
    listOfObjects<int> *ran;
    ran=currNode->indices;
    while(ran->next!=nullptr){
      ran=ran->next;
    }
    ran->next=tmp;
    return true;
  }
}
//this delete function first traverses for wordInName string and if not found at 
//any letter it returns false if found it iterates until currnode if last letter.
//now isword is false it means it is not exact word present there its just prefix to some other word so return false.
//if isword is true now it will search in indices whether full name is there or not
//if there it will delete that node from linked list and return true otherwise return false.
//special case is when it has only 1 indice and it match with full name if we delete it again for next
//insert or delete we isword is settedto be true and it will function wrongly so while deleteing it 
//we should set isword as false and delete it.
bool Trie::del(string wordInName, string name) {
  TrieNode *currNode = root;
  TrieNode *lastBranchNode = nullptr;
  int lastBranchChar = -1;
  int len = wordInName.length();
  for (int i = 0; i < len; i++) {
    int letter = toupper(wordInName.at(i)) - 'A';
    if (currNode->branch[letter] == nullptr) {
      return false;
    }
    else {
      currNode = currNode->branch[letter];
    }
  }
  if(currNode->isWord==false){return false;}
  else{
    listOfObjects<int> *ran=currNode->indices;
    listOfObjects<int> *prev=nullptr;
    if(nameDict->getKeyAtIndex(ran->object)==name){
      if(ran->next==nullptr){
      currNode->indices=ran->next;
      currNode->isWord=false;
      delete ran;
      return true;}
      else{
      currNode->indices=ran->next;
      delete ran;
      return true;
      }
    }
    else{
    while(ran!=nullptr&&nameDict->getKeyAtIndex(ran->object)!=name){
        prev=ran;
        ran=ran->next;
    }
    if(ran==nullptr){return false;}
    else{
    prev->next=ran->next;
    delete ran;
    return true;}
  }}
  return false;
}
//firstly we check letter by letter of prefix is there branch exists correspondss to 
//it is not if not prefix is not present and returns nullptr.if it is present then we will move to last
//node of prefix recursively and call recursive completions over that node.
listOfObjects<string> * Trie::completions(string prefix) {
  TrieNode *currNode = root;
  int len = prefix.length();
  listOfObjects<string> *currCompletions = new listOfObjects<string>("a");
  for(int i=0;i<len;i++){
    int letter = toupper(prefix.at(i)) - 'A';
    if(currNode->branch[letter]==nullptr){
        return nullptr;
    }
    else{
      currNode=currNode->branch[letter];
    }
  }
  bool x=recursiveAddCompletions(currNode,currCompletions);
  return currCompletions->next;
}
//when recursive completions for last node of prefix.it does it recursively move to all leafs
//of branches at that node and call add completions.
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
//when add completions is called at leafs as we know indices linked list is stored at leafs.
//now we iterate over linked list up to tail and we make each index to string using namedict->getkeyatindex() function
//and add that string in currcompletions list.
bool Trie::addCompletions(TrieNode *node, listOfObjects<string> *currCompletions) {
  listOfObjects<int> *r=node->indices;
  listOfObjects<string> *y=currCompletions;
  while(y->next!=nullptr){
    y=y->next;
  }
   while(r!=nullptr){
    y->next=new listOfObjects<string>( nameDict->getKeyAtIndex(r->object));
    y=y->next;
    r=r->next;
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
