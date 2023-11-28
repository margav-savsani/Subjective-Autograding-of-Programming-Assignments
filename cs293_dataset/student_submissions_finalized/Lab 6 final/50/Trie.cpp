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

  for (int i = 0; i < len; i++)
  {
    if (currNode->branch[toupper(wordInName[i]) - 'A'] == nullptr)
    {
      currNode->branch[toupper(wordInName[i]) - 'A'] = new TrieNode();
      currNode->numNonNullBranches++;
    }
    currNode = currNode->branch[toupper(wordInName[i]) - 'A'];
  }
  currNode->isWord = true;
  if (currNode->indices == nullptr)
    currNode->indices = new listOfObjects<int>(indexOfName);
  else
  {
    listOfObjects<int> *move = currNode->indices;
    while(move->next != nullptr){
      move = move->next;
    }
    move->next = new listOfObjects<int>(indexOfName);
  }
  return true;
}

bool Trie::del(string wordInName, string name)
{
  TrieNode *currNode = root;
  TrieNode *lastBranchNode = root;
  int lastBranchChar = 0;
  int len = wordInName.length();

  for (int i = 0; i < len; i++)
  {
    if (currNode->branch[toupper(wordInName[i]) - 'A'] == nullptr)
      return false;
    if (currNode->numNonNullBranches > 1 || currNode->isWord == true)
    {
      lastBranchChar = i;
      lastBranchNode = currNode;
    }
    currNode = currNode->branch[toupper(wordInName[i]) - 'A'];
  }

  if (currNode->isWord == false)
    return false;
  int count = 0;
  listOfObjects<int> *move = currNode->indices;
  while (move != nullptr)
  {
    count++;
    move = move->next;
  }
  move = currNode->indices;
  if (count == 1)
  {
    // cout << "JUST ONE WORD" << endl;
    if (nameDict->getKeyAtIndex(move->object) != name)
      return false;
    delete move;
    currNode->indices = nullptr;
    currNode->isWord = false;
    // cout << "IS WORD FALSE" << endl;
    if (currNode->numNonNullBranches == 0)
    {
      recursiveDelete(lastBranchNode->branch[toupper(wordInName[lastBranchChar]) - 'A']);
      lastBranchNode->branch[toupper(wordInName[lastBranchChar]) - 'A'] = nullptr;
      lastBranchNode->numNonNullBranches--;
    }
  }
  else
  {
    if (nameDict->getKeyAtIndex(currNode->indices->object) == name)
    {
      currNode->indices = move->next;
      delete move;
    }
    else
    {
      while (move->next != nullptr)
      {
        if(nameDict->getKeyAtIndex(move->next->object) == name) break;
        move = move->next;
      }
      if (move->next == nullptr)
        return false;
      else
      {
        listOfObjects<int> *temp;
        temp = move->next;
        if (temp->next == nullptr)
        {
          delete temp;
          move->next = nullptr;
        }
        else
        {
          move->next = temp->next;
          delete temp;
        }
      }
    }
  }

  return true;
}

listOfObjects<string> *Trie::completions(string prefix)
{
  TrieNode *currNode = root;
  int len = prefix.length();
  listOfObjects<string> *currCompletions = nullptr;

  for (int i = 0; i < len; i++)
  {
    if (currNode->branch[toupper(prefix[i]) - 'A'] == nullptr)
      return currCompletions;
    currNode = currNode->branch[toupper(prefix[i]) - 'A'];
  }
  currCompletions = new listOfObjects<string>("*");
  recursiveAddCompletions(currNode, currCompletions);
  listOfObjects<string> *final = currCompletions->next;
  delete currCompletions;

  return final;
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
  listOfObjects<int> *jump = node->indices;
  while (jump != nullptr)
  {
    listOfObjects<string> *move = currCompletions;
    while (move->next != nullptr)
    {
      move = move->next;
    }
    move->next = new listOfObjects<string>(nameDict->getKeyAtIndex(node->indices->object));
    jump = jump->next;
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
