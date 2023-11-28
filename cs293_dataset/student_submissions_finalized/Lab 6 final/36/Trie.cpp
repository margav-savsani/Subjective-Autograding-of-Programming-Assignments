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
#include <bits/stdc++.h>
using namespace std;

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
  string str = wordInName;
  transform(str.begin(), str.end(), str.begin(), ::tolower);
  for (int i = 0; i < len; i++) // creating branches
  {
    char c = str[i];
    if (currNode->branch[int(c) - 'a'] == nullptr)
    {
      currNode->branch[int(c) - 'a'] = new TrieNode();
      currNode->numNonNullBranches++;
      currNode = currNode->branch[int(c) - 'a'];
      continue;
    }
    else
    {
      currNode = currNode->branch[int(c) - 'a'];
    }
  }
  if (currNode->isWord != 1) // making isword true
  {
    currNode->isWord = true;
  }
  if (currNode->indices == nullptr) // updating indices
  {
    currNode->indices = new listOfObjects<int>(indexOfName);
  }
  else
  {
    listOfObjects<int> *curr = currNode->indices;
    while (curr->next != nullptr)
    {
      curr = curr->next;
    }
    curr->next = new listOfObjects<int>(indexOfName);
  }
  return true;
}

bool Trie::del(string wordInName, string name)
{
  TrieNode *currNode = root;
  int len = wordInName.length();
  string str = wordInName;
  transform(str.begin(), str.end(), str.begin(), ::tolower);
  TrieNode *lastBranchNode = root;
  int lastBranchChar = str[0] - 'a';
  for (int i = 0; i < len; i++)
  {
    char c = str[i];
    currNode = currNode->branch[int(c) - 'a'];
  }
  listOfObjects<int> *curr = currNode->indices;
  if (name == nameDict->getKeyAtIndex(currNode->indices->object))
  {
    currNode->indices = currNode->indices->next;
    if (currNode->indices == nullptr)
    {
      currNode->isWord = false;
    }
    return true;
  }
  else
  {
    while (curr->next != nullptr)
    {
      if (name == nameDict->getKeyAtIndex(curr->next->object))
      {
        curr->next = curr->next->next;
        return true;
      }
      curr = curr->next;
    }
  }

  return false;
}

listOfObjects<string> *Trie::completions(string prefix)
{
  TrieNode *currNode = root;
  int len = prefix.length();
  listOfObjects<string> *currCompletions = nullptr;
  string str = prefix;
  transform(str.begin(), str.end(), str.begin(), ::tolower);
  for (int i = 0; i < len; i++)
  {
    currNode = currNode->branch[str[i] - 'a'];
  }
  currCompletions = new listOfObjects<string>("");
  recursiveAddCompletions(currNode, currCompletions);
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
  if (node->isWord == false)
  {
    return false;
  }
  listOfObjects<int> *curr = node->indices;
  listOfObjects<string> *tempcomp = currCompletions;
  while (tempcomp->next != nullptr)
  {
    tempcomp = tempcomp->next;
  }
  while (curr != nullptr)
  {
    tempcomp->next = new listOfObjects<string>(nameDict->getKeyAtIndex(curr->object));
    tempcomp = tempcomp->next;
    curr = curr->next;
  }
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
