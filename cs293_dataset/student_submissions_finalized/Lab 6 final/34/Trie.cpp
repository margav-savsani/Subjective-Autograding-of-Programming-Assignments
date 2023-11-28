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
//the below function converts an alphabet into int regardless of cases
int char_int(char c)
{
  int index;
  if (c <= 90)
    index = c - 65;
  else
    index = c - 97;
  return index;
}
Trie::Trie(Dictionary<int> *nameToIndex)
{
  nameDict = nameToIndex;
  root = new TrieNode();
  if (root == nullptr)
  {
    cout << "Memory allocation failure." << endl;
    exit(-1);
  }
}

Trie::~Trie()
{
  recursiveDelete(root);
}

void Trie::recursiveDelete(TrieNode *node)
{
  if (node == nullptr)
  {
    return;
  }
  else
  {
    for (int i = 0; i < NUM_CHARS; i++)
    {
      TrieNode *currNode = node->branch[i];
      recursiveDelete(currNode);
      node->branch[i] = nullptr;
    }
    if (node != root)
    {
      delete node;
    }
    return;
  }
}

bool Trie::insert(string wordInName, int indexOfName)
{
  TrieNode *currNode = root;
  int len = wordInName.length();

  // Insert your code here
  // the below code snippet goes to the leaf of the word.
  for (int i = 0; i < len; i++)
  {
    int index = char_int(wordInName[i]);

    if (root->branch[index] == nullptr)
    {
      root->numNonNullBranches++;
      root->branch[index] = new TrieNode;
    }
    root = root->branch[index];
  }
  //isWord becomes true since the word is added.
  root->isWord = true;
  if (root->indices == nullptr)
  {
    root->indices = new listOfObjects<int>(indexOfName);
  }
  else
  {
    //goes to end of linked list and adds the the indexOfName.
    listOfObjects<int> *currIndices = root->indices;
    while (currIndices->next != nullptr)
    {
      currIndices = currIndices->next;
    }
    currIndices->next = new listOfObjects<int>(indexOfName);
  }
  root = currNode;
  return true;
}

bool Trie::del(string wordInName, string name)
{
  TrieNode *currNode = root;
  TrieNode *lastBranchNode = nullptr;
  int lastBranchChar = -1;
  int len = wordInName.length();
  // Insert your code here
  //the below arr stores true for each index of word if it branches out or if it has names stored.
  int *arr = new int[len];
  //the below loop updates the values of arr.
  for (int i = 0; i < len; i++)
  {
    int index = char_int(wordInName[i]);
    if (currNode->branch[index] == nullptr){
      return false;
    }
    currNode = currNode->branch[index];
    if (currNode->isWord || currNode->numNonNullBranches > 1)
      arr[i] = true;
    else
      arr[i] = false;
  }
  //The case when branches are there for the last word.
  if (currNode->numNonNullBranches >= 1)
  {
    listOfObjects<int> *indices = currNode->indices;
    listOfObjects<int> *parent = currNode->indices;
    string s = nameDict->getKeyAtIndex(indices->object);
    if (s == name)
    {
      currNode->indices = indices->next;
      delete indices;
      if(currNode->indices == nullptr)currNode->isWord = false;
      return true;
    }
    indices = indices->next;
    while (indices != nullptr)
    {
      s = nameDict->getKeyAtIndex(indices->object);
      if (s == name)
        {
          parent->next = indices->next;
          delete indices;
          return true;
        }
      parent = parent->next;
      indices = indices->next;
    }
  }
  //when the last word has more than 1 names stored
  if (currNode->indices->next != nullptr)
  {
    listOfObjects<int> *indices = currNode->indices;
    listOfObjects<int> *parent = currNode->indices;
    string s = nameDict->getKeyAtIndex(indices->object);
    if (s == name)
    {
      currNode->indices = indices->next;
      delete indices;
      return true;
    }
    indices = indices->next;
    while (indices != nullptr)
    {
      s = nameDict->getKeyAtIndex(indices->object);
      if (s == name)
        {
          parent->next = indices->next;
          delete indices;
          return true;
        }
      parent = parent->next;
      indices = indices->next;
    }
  }
  //when the last letter has only one name stored which is to be deleted
  else
  {
    int kth = len;
    for (int i = 0; i < len-1; i++)
    {
      if (!arr[len-i-2])
      {
        kth--;
      }
      else
        break;
    }
    currNode = root;
    for (int i = 0; i < kth-1; i++)
    {
      int index = char_int(wordInName[i]);
      currNode = currNode->branch[index];
    }
    int index = char_int(wordInName[kth-1]);
    recursiveDelete(currNode->branch[index]);
    currNode->branch[index] = nullptr;
    currNode->numNonNullBranches--;
    return true;
  }
  cout << "sdhfkjas\n";
  return true;
}

listOfObjects<string> *Trie::completions(string prefix)
{
  TrieNode *currNode = root;
  int len = prefix.length();
  listOfObjects<string> *currCompletions = new listOfObjects<string>("null");

  // Insert your code here
  //the below loop takes us to the last word.
  for (int i = 0; i < len; i++)
  {
    int index = char_int(prefix[i]);
    if (currNode->branch[index] == nullptr)
      return nullptr;
    currNode = currNode->branch[index];
  }
  //used recursive add completions
  if (!recursiveAddCompletions(currNode, currCompletions))
  {
    return nullptr;
  }
  listOfObjects<string> *tempCompletions = currCompletions;
  return currCompletions->next;
}

bool Trie::recursiveAddCompletions(TrieNode *node, listOfObjects<string> *currCompletions)
{
  if (node->isWord)
  {
    if (!addCompletions(node, currCompletions))
    {
      return false;
    }
  }

  TrieNode *currNode = node;
  for (int i = 0; i < NUM_CHARS; i++)
  {
    if (currNode->branch[i] != nullptr)
    {
      if (!recursiveAddCompletions(currNode->branch[i], currCompletions))
      {
        return false;
      }
    }
  }

  return true;
}

bool Trie::addCompletions(TrieNode *node, listOfObjects<string> *currCompletions)
{
  
  TrieNode *curr = node;
  listOfObjects<int> *indices = node->indices;
  //the below code converts indices to name and stores in currCompletions.
  if (currCompletions == nullptr)
  {
    currCompletions = new listOfObjects<string>(nameDict->getKeyAtIndex(indices->object));
    indices = indices->next;
  }
  listOfObjects<string> *tempCompletions = currCompletions;
  while (tempCompletions->next != nullptr)
  {
    tempCompletions = tempCompletions->next;
  }
  while (indices != nullptr)
  {
    tempCompletions->next = new listOfObjects<string>(nameDict->getKeyAtIndex(indices->object));
    indices = indices->next;
    tempCompletions = tempCompletions->next;
  }
  tempCompletions = currCompletions;
  return true;
}

bool Trie::isPresentInCompletions(listOfObjects<string> *completions, string name)
{
  listOfObjects<string> *currCompletion = completions;
  bool isPresent = false;
  while (currCompletion != nullptr)
  {
    if (currCompletion->object == name)
    {
      isPresent = true;
      break;
    }
    currCompletion = currCompletion->next;
  }
  return isPresent;
}

void Trie::freeCompletionList(listOfObjects<string> *completions)
{
  listOfObjects<string> *currCompl = completions;
  while (currCompl != nullptr)
  {
    listOfObjects<string> *toDeleteCompl = currCompl;
    currCompl = currCompl->next;
    delete toDeleteCompl;
  }
  return;
}

bool Trie::isPresent(string wordInName)
{
  TrieNode *currNode = root;
  int len = wordInName.length();

  for (int i = 0; i < len; i++)
  {
    int letter = toupper(wordInName.at(i)) - 'A';

    if (currNode->branch[letter] == nullptr)
    {
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

void Trie::recursivePrintTrie(TrieNode *node, const string &prefix, int branchId, bool siblingsToRight)
{
  if (node != nullptr)
  {
    cout << prefix;

    cout << ((branchId == 0) ? "|-" : (branchId == -1) ? " *"
                                                       : "|_")
         << (char)((branchId != -1) ? 'A' + branchId : '*');
    cout << ((branchId == 0) ? '-' : (branchId == -1) ? '*'
                                                      : '_');

    // If this trie node has isWord set to true, print "(isWord)" and
    // also the list of complete station names (accessed through indices
    // in nameDict) associated with this trie node.
    if (node->isWord)
    {
      cout << "(isWord)";
      listOfObjects<int> *currIndices = node->indices;
      while (currIndices != nullptr)
      {
        cout << endl
             << prefix << "     " << nameDict->getKeyAtIndex(currIndices->object);
        currIndices = currIndices->next;
      }
    }
    else
    {
      cout << "()";
    }
    cout << endl;
    for (int i = 0; i < NUM_CHARS; i++)
    {
      TrieNode *currNode = node->branch[i];
      bool childrenToRight = false;
      for (int j = i + 1; j < NUM_CHARS; j++)
      {
        if (node->branch[j] != nullptr)
        {
          childrenToRight = true;
          break;
        }
      }
      if (currNode != nullptr)
      {
        recursivePrintTrie(currNode, prefix + ((siblingsToRight) ? "│   " : "    "), i, childrenToRight);
      }
    }
  }
}
// End edit version 1

#endif
