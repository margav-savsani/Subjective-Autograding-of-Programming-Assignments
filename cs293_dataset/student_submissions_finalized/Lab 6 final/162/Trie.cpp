#ifndef TRIE_CPP
#define TRIE_CPP

#include <stack>
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
  TrieNode *prevNode = nullptr;
  int len = wordInName.length();
  int j = 0;
  while (wordInName[j] != '\0')
  {
    int character = wordInName[j] >= 'a' ? wordInName[j] - 'a' : wordInName[j] - 'A';
    prevNode = currNode;
    if (currNode->branch[character] == nullptr)
    {
      currNode->branch[character] = new TrieNode();
      prevNode->numNonNullBranches++;
    }
    currNode = currNode->branch[character];
    j++;
  }
  currNode->isWord = true;

  if (currNode->indices == nullptr)
  {
    currNode->indices = new listOfObjects<int>(indexOfName);
    return true;
  }
  listOfObjects<int> *indices = currNode->indices;
  while (indices->next != nullptr)
  {
    if (indices->object == indexOfName)
      return false;
    indices = indices->next;
  }

  indices->next = new listOfObjects<int>(indexOfName);

  // Insert your code here

  return true;
}

bool Trie::del(string wordInName, string name)
{
  TrieNode *currNode = root;
  TrieNode *lastBranchNode = nullptr;
  int lastBranchChar = -1;
  int lastChar = -1;
  int len = wordInName.length();
  int j = 0;

  while (wordInName[j] != '\0' && currNode != nullptr)
  {
    int character = wordInName[j] >= 'a' ? wordInName[j] - 'a' : wordInName[j] - 'A';
    lastChar = wordInName[j];
    if (currNode->numNonNullBranches > 1 || currNode->isWord == true)
    {
      lastBranchChar = character;
      lastBranchNode = currNode;
    }

    currNode = currNode->branch[character];
    j++;
  }
  listOfObjects<int> *prevIndex = nullptr;
  listOfObjects<int> *currIndex = currNode->indices;

  if (lastChar == wordInName[len - 1]) // found in trie
  {
    while (currIndex != nullptr)
    {
      if (nameDict->getKeyAtIndex(currIndex->object) == name)
        break;
      prevIndex = currIndex;
      currIndex = currIndex->next;
    }

    if (currIndex == nullptr)
      return false; // not found in dict
    else
    {
      if (prevIndex == nullptr) // first element is to be deleted
      {
        currNode->indices = currNode->indices->next;
      }
      else
      {
        prevIndex->next = currIndex->next;
      }
      delete currIndex;
    }
    if (currNode->indices == nullptr)
    {
      currNode->isWord = false;
      if (lastBranchChar == -1)
      {
        lastBranchChar = wordInName[0] >= 'a' ? wordInName[0] - 'a' : wordInName[0] - 'A';
        lastBranchNode = root;
      }
      recursiveDelete(lastBranchNode->branch[lastBranchChar]);
      lastBranchNode->branch[lastBranchChar] = nullptr;
      lastBranchNode->numNonNullBranches--;
    }

    return true;
  }

  return false;
}

listOfObjects<string> *Trie::completions(string prefix)
{
  TrieNode *currNode = root;
  int len = prefix.length();
  listOfObjects<string> *currCompletions = new listOfObjects<string>("$");
  int j = 0;
  // Insert your code here
  while (prefix[j] != '\0' && currNode != nullptr)
  {
    int character = prefix[j] >= 'a' ? prefix[j] - 'a' : prefix[j] - 'A';
    currNode = currNode->branch[character];
    j++;
  }
  if (currNode == nullptr)
    return nullptr;
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
  if (node->isWord && node->indices != nullptr)
  {
    listOfObjects<int> *indices = node->indices;
    listOfObjects<string> *ptr = currCompletions;
    while (indices != nullptr)
    {
      
      if (!isPresentInCompletions(currCompletions, nameDict->getKeyAtIndex(indices->object)))
      {

        if (ptr->object == "$")
        {
          ptr->object = nameDict->getKeyAtIndex(indices->object);
        }
        else
        {

          while (ptr->next != nullptr)
          {
            ptr = ptr->next;
          }

          ptr->next = new listOfObjects<string>(nameDict->getKeyAtIndex(indices->object));
        }
      }
      indices = indices->next;
    }
    return true;
  }
  return false;
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
