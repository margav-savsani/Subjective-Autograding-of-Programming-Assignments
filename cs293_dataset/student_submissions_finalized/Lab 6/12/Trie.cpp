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
  cout << 1 << endl;
  for (int i = 0; i < len; i++)
  {
    int index = wordInName[i] - 'A';
    if (!currNode->branch[index])
    {
      currNode->branch[index] = new TrieNode();
      currNode->numNonNullBranches++;
      currNode = currNode->branch[index];
    }
    else
    {
      currNode = currNode->branch[index];
    }
  }
  cout << 2 << endl;
  currNode->isWord = true;
  if (currNode->indices == nullptr)
  {
    cout << 3 << endl;
    currNode->indices = new listOfObjects<int>(indexOfName);
  }
  else
  {
    cout << 4 << endl;
    listOfObjects<int> *currindice = currNode->indices;
    while (!!currindice->next)
    {
      currindice = currindice->next;
    }
    currindice->next = new listOfObjects<int>(indexOfName);
  }

  return true;
}

bool Trie::del(string wordInName, string name)
{
  TrieNode *currNode = root;
  TrieNode *lastBranchNode = nullptr;
  int lastBranchChar = -1;
  int len = wordInName.length();

  // Insert your code here
  lastBranchNode = root;
  lastBranchChar = wordInName[0] - 'A';
  for (int i = 0; i < len; i++)
  {
    int index = wordInName[i] - 'A';
    if (!currNode->branch[index])
    {
      return false;
    }
    else
    {
      currNode = currNode->branch[index];
      if (i < len - 1)
      {
        if (currNode->isWord == true || currNode->numNonNullBranches > 1)
        {
          lastBranchNode = currNode;
          lastBranchChar = wordInName[i + 1] - 'A';
        }
      }
    }
  }
  if (!currNode->indices->next)
  {
    lastBranchNode->branch[lastBranchChar] = nullptr;
    lastBranchNode->numNonNullBranches--;
  }
  else
  {
    if (nameDict->getKeyAtIndex(currNode->indices->object) == name)
    {
      currNode->indices = currNode->indices->next;
      return true;
    }
    listOfObjects<int> *current = currNode->indices->next;
    listOfObjects<int> *previous = currNode->indices;
    while (!current)
    {
      if (nameDict->getKeyAtIndex(current->object) == name)
      {
        previous->next = current->next;
        return true;
      }
      previous = current;
      current = current->next;
    }
    return false;
  }

  return true;
}

listOfObjects<string> *Trie::completions(string prefix)
{
  TrieNode *currNode = root;
  int len = prefix.length();
  listOfObjects<string> *currCompletions = nullptr;

  // Insert your code here

  for (int i = 0; i < len; i++)
  {
    int index = prefix[i] - 'A';
    if (!currNode->branch[index])
    {
      return nullptr;
    }
    else
    {
      currNode = currNode->branch[index];
    }
  }

  currCompletions = new listOfObjects<string>("x");

  recursiveAddCompletions(currNode, currCompletions);
  return currCompletions;
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

  // Insert your code here
  listOfObjects<int> *nodeindex = node->indices;
  if (currCompletions->object == "x")
  {
    currCompletions->object = nameDict->getKeyAtIndex(nodeindex->object);
    nodeindex = nodeindex->next;
  }
  else
  {
    listOfObjects<string> *currcomp = currCompletions;
    while (!currcomp->next)
    {
      currcomp = currcomp->next;
    }
    bool inserted = false;
    while (!nodeindex)
    {
      listOfObjects<string> *currcomps = currCompletions;
      while (!currcomps)
      {
        if (currCompletions->object == nameDict->getKeyAtIndex(nodeindex->object))
        {
          inserted = true;
        }
        currcomps = currcomps->next;
      }
      if (inserted == false)
      {
        currcomp->next = new listOfObjects<string>(nameDict->getKeyAtIndex(nodeindex->object));
        currcomp = currcomp->next;
      }
      nodeindex = nodeindex->next;
    }
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
