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
  int cur_letter = 0;
  while (cur_letter < len)
  {
    int ascvalue = int(wordInName[cur_letter]);
    if (ascvalue >= 97 && ascvalue <= 122)
      ascvalue = ascvalue - 97;
    else if (ascvalue >= 65 && ascvalue <= 90)
      ascvalue = ascvalue - 65;
    if (currNode->branch[ascvalue] == nullptr)
    {
      currNode->numNonNullBranches++;
      currNode->branch[ascvalue] = new TrieNode();
    }
    currNode = currNode->branch[ascvalue];
    cur_letter++;
  }
  if (cur_letter == len)
  {
    currNode->isWord = true;
    listOfObjects<int> *search = currNode->indices;
    if (search == nullptr) {currNode->indices = new listOfObjects<int> (indexOfName); }
    else
    {
      while (search != nullptr)
      {
        if(search->next == nullptr) {search->next = new listOfObjects<int> (indexOfName); break;}
        search = search->next;
      }
    }
  }
  return true;
}

bool Trie::del(string wordInName, string name)
{
  TrieNode *currNode = root;
  TrieNode *todelete = nullptr;
  int len = wordInName.length();
  if (!isPresent(wordInName))
    return false;
  TrieNode *last = getlastnode(wordInName);
  listOfObjects<int> *search = last->indices, *prev;
  if (search == nullptr){
    return false;}
  else if (nameDict->getKeyAtIndex(search->object) == name)
    last->indices = search->next;
  else
  {
    prev = search;
    search = search->next;
    while (search != nullptr)
    {
      int index = search->object;
      if (nameDict->getKeyAtIndex(index) == name)
      {
        prev->next = search->next;
        break;
      }
      else
      {
        prev = search;
        search = search->next;
      }
    }
    if (search == nullptr)
      return false;
  }
  if (last->indices == nullptr)
  {
    int nextletter;
    for (int i = 0; i < len; i++)
    {
      int letter = int(wordInName[i]);
      if (letter >= 97 && letter <= 122)
        letter = letter - 97;
      else if (letter >= 65 && letter <= 90)
        letter = letter - 65;

      if (currNode->numNonNullBranches > 1)
      {
        todelete = currNode;
        nextletter = letter;
      }
      currNode = currNode->branch[letter];
    }
    if (todelete == nullptr)
      recursiveDelete(root);
    else
    {
      recursiveDelete(todelete->branch[nextletter]);
      todelete->branch[nextletter] = nullptr;
      todelete->numNonNullBranches--;
    }
  }
  return true;
}

listOfObjects<string> *Trie::completions(string prefix)
{
  TrieNode *currNode = root;
  int len = prefix.length();
  listOfObjects<string> *currCompletions = nullptr;

  // Insert your code here
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
    int letter = int(wordInName[i]);
    if (letter >= 97 && letter <= 122)
      letter = letter - 97;
    else if (letter >= 65 && letter <= 90)
      letter = letter - 65;

    if (currNode->branch[letter] == nullptr)
    {
      return false;
    }
    currNode = currNode->branch[letter];
  }

  return currNode->isWord;
}

TrieNode *Trie::getlastnode(string wordInName)
{
  TrieNode *currNode = root;
  int len = wordInName.length();

  for (int i = 0; i < len; i++)
  {
    int letter = int(wordInName[i]);
    if (letter >= 97 && letter <= 122)
      letter = letter - 97;
    else if (letter >= 65 && letter <= 90)
      letter = letter - 65;

    if (currNode->branch[letter] == nullptr)
    {
      return nullptr;
    }
    currNode = currNode->branch[letter];
  }

  return currNode;
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
