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
      node= nullptr;
    }
    return;
  }
}

bool Trie::insert(string wordInName, int indexOfName) {
  TrieNode *currNode = root;
  int len = wordInName.length();
  for (int i=0;i<len;i++)
  {
    int k=wordInName[i]-'A';//checking the node is null or not
    if (currNode->branch[k]==nullptr)
    {//if null then incr the numnonnullbranches
      currNode->numNonNullBranches++;
      currNode->branch[k]=new TrieNode;
    }
    currNode=currNode->branch[k];
  }
  //keep the last trie isword to true and the index to the indices
  currNode->isWord=true;
  listOfObjects<int> *dummy;
  dummy=currNode->indices;
  if (currNode->indices == nullptr)
  {//if null ptr create new
    currNode->indices=new listOfObjects(indexOfName);
    return true;
  }
  else
  {//if not null search for end of list
    while(dummy->next!=nullptr)
    {
      dummy=dummy->next;
    }
    dummy->next=new listOfObjects(indexOfName);
    return true;
  }
  return true;
}
TrieNode* Trie::remove(TrieNode* node, string key,int depth=1)
{
  if (node == nullptr)
    return nullptr;
  if (depth == key.length())
  {
    if (node->indices!=nullptr)
    {
      if (node->isWord)
        node->isWord=false;
    }
    if (node->numNonNullBranches == 0)
    {
      delete(node);
      node=nullptr;
    }
    return node;
  }
  int index = key[depth] - 'A';
    node->branch[index] =
          remove(node->branch[index], key, depth + 1);
 
    // If root does not have any child (its only child got
    // deleted), and it is not end of another word.
    if (node->numNonNullBranches==0 && node->isWord == false) {
        delete (node);
        node = NULL;
    }
 
    return node;
}
bool Trie::del(string wordInName, string name) {
  TrieNode *currNode = root;
  TrieNode *lastBranchNode = nullptr;
  int lastBranchChar = -1;
  int len = wordInName.length();
  for(int i=0;i<len;i++)
  {//checking for the word
    int k=wordInName[i]-'A';
    if (currNode->branch[k] == nullptr)
      return false;
    if (currNode->numNonNullBranches>1)
    {//if multiple brances are present find the last multiple branch
      lastBranchNode=currNode;
      lastBranchChar=k;
    }
    currNode=currNode->branch[k];
  }
  if (currNode->isWord == false)
    return false;
  if (currNode->indices->next == nullptr)
  {//if list contains only one word
    if (currNode->numNonNullBranches==0)
    {//next is a all empty
      if (name == nameDict->getKeyAtIndex(currNode->indices->object))
      {
        lastBranchNode->numNonNullBranches--;
        recursiveDelete(lastBranchNode->branch[lastBranchChar]);
        lastBranchNode->branch[lastBranchChar]=nullptr;
        return true;
      }
      else
        return false;
    }
    else
    {//next some words are present
      if (name == nameDict->getKeyAtIndex(currNode->indices->object))
      {
        currNode->isWord=false;
        currNode->indices=nullptr;
        return true;
      }
      else
        return false;
    }
  }
  else
  {//if it is not only one
    listOfObjects<int> *sample=currNode->indices;
    if (name == nameDict->getKeyAtIndex(sample->object))
    {
      sample=sample->next;
      return true;
    }
    while(sample->next != nullptr)
    {
      if(name == nameDict->getKeyAtIndex(sample->next->object))
      {

        sample->next=sample->next->next;
        return true;
      }
      sample=sample->next;
    }
  }
  return false;
}

listOfObjects<string> * Trie::completions(string prefix) {
  TrieNode *currNode = root;
  int len = prefix.length();
  listOfObjects<string> currCompletions("");
  for (int i=0;i<len;i++)
  {//going to last node of given prefix
    int k=prefix[i]-'A';
    if (currNode->branch[k] == nullptr)
      return nullptr;
    currNode=currNode->branch[k];
  }
  //adding elements recursively
  recursiveAddCompletions(currNode,&currCompletions);
  // Insert your code here
  return currCompletions.next;
  
}

bool Trie::recursiveAddCompletions(TrieNode *node, listOfObjects<string> *currCompletions) {
  if (node == nullptr)
    return false;
  if (node->isWord)
  {//adding all words at last of the word
    addCompletions(node,currCompletions);
    return true;
  }
  for (int i=0;i<26;i++)
  {//going to all tries
    if (node->branch[i] != nullptr)
      recursiveAddCompletions(node->branch[i],currCompletions);
  }
  return true;
}

bool Trie::addCompletions(TrieNode *node, listOfObjects<string> *currCompletions) {

  if (currCompletions == nullptr)
  {//adding the list of string at the index using nameDic
    currCompletions=new listOfObjects(nameDict->getKeyAtIndex(node->indices->object));
    listOfObjects<int> *sample=node->indices->next;
    listOfObjects<string> *strsample=currCompletions;
    while (sample!=nullptr)
    {
      strsample->next=new listOfObjects(nameDict->getKeyAtIndex(sample->object));
      strsample=strsample->next;
      sample=sample->next;
    }
  }
  else
  {
    listOfObjects<string> *strsample=currCompletions;
    listOfObjects<int> *sample=node->indices;
    while (strsample->next != nullptr)
      strsample=strsample->next;
    while (sample!=nullptr)
    {
      strsample->next=new listOfObjects(nameDict->getKeyAtIndex(sample->object));
      strsample=strsample->next;
      sample=sample->next;
    }
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
//by saran 210050036
