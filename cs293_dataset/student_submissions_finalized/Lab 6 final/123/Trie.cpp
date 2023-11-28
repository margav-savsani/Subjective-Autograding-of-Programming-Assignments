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

// Imported from Geeks For Geeks

vector<string> tokenize(string s, string del = " ")
{
    vector<string> subs;
    int start, end = -1*del.size();
    do {
        start = end + del.size();
        end = s.find(del, start);
        subs.push_back(s.substr(start, end - start));
    } while (end != -1);

    return subs;
}

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
  //We will go till " " and add that word by checking each letter by using currNode->branch[wordInName[i] - 'a'] and if it is not null, then we go to next branch, else initiate a new TrieNode and point it to currNode and go to its branch and add recursively 
    for(int j=0; j<len; j++){
      if (currNode->branch[wordInName.at(j) - 'A'] != nullptr)
      {
        currNode = currNode->branch[wordInName.at(j) - 'A'];
      }
      else{
        currNode->branch[wordInName.at(j) - 'A'] = new TrieNode();
        currNode = currNode->branch[wordInName.at(j) - 'A'];
      }
    }
  listOfObjects<int> *node;
  node = currNode->indices;
  if(currNode->indices != nullptr){
    while(node->next != nullptr){
      node = node->next;
    }
    listOfObjects<int> *newnode = new listOfObjects<int>(indexOfName);
    node->next = newnode;
  }
  else{
    currNode->indices = new listOfObjects<int>(indexOfName);
  }
  currNode->isWord = true;
  return true;
}

bool Trie::del(string wordInName, string name) {
  TrieNode *currNode = root;
  TrieNode *lastBranchNode = nullptr;
  int lastBranchChar = -1;
  int len = wordInName.length();

  // Insert your code here
  for (int i = 0; i<len; i++)
  {
    if (currNode->branch[wordInName.at(i) - 'A'] == nullptr)
    {
      return false;
    }
    else
    {
      currNode = currNode->branch[wordInName.at(i) - 'A'];
    }    
  }
  listOfObjects<int> *node = currNode->indices;
      if(node == nullptr){
          return false; //Edit
      }
  listOfObjects<int> *prevnode = nullptr;
  listOfObjects<int> *nextnode = currNode->indices->next;
  while (node->next != nullptr)
  {
    int val = node->object;
    if(nameDict->getKeyAtIndex(val) == name){
      if (prevnode == nullptr)
      {
        currNode->indices = nextnode;
      }
      else{
        prevnode->next = nextnode;
      }
      delete node;
      return true; //Sure?
    }
    prevnode = node;
    node = nextnode;
    nextnode = nextnode->next; 
  }
  if (node->next == nullptr)
  {
    int val = node->object;
    if(!(nameDict->getKeyAtIndex(val) != name)){
      node = nullptr;
      if (prevnode != nullptr)
      {
        prevnode->next = nullptr;
      }
      else{
        currNode->indices = nullptr;
        currNode->isWord = false;
      }
      return true;
    }
  }
  
  return false;
}

listOfObjects<string> * Trie::completions(string prefix) {
  TrieNode *currNode = root;
  int len = prefix.length();
  listOfObjects<string> *currCompletions = new listOfObjects<string>("KUSAL");

  // Insert your code here
  vector<int> ints;
    for (int i = 0; i < len; i++)
    {
      if(currNode->branch[prefix.at(i)-'A'] == nullptr){
        break;
      }
      else{
        currNode = currNode->branch[prefix.at(i) - 'A'];
      }
    }
     recursiveAddCompletions(currNode,currCompletions);
  currCompletions = currCompletions->next;
  return currCompletions;  
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
  listOfObjects<int> *indice = node->indices;
  listOfObjects<string> *strs = currCompletions;
  while(strs->next != nullptr){
    strs = strs->next;
  }
  while (indice != nullptr)
  {
    listOfObjects<string> *newnode = new listOfObjects<string>(nameDict->getKeyAtIndex(indice->object));
    strs->next = newnode;
    strs = strs->next;
    indice = indice->next;
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
