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

//recursive function for inserting
TrieNode *ins(TrieNode *node, string word, int count)
{
  if (node->branch[word[count] - 65] == nullptr)
  {
    node->branch[word[count] - 65] = new TrieNode();
    node->numNonNullBranches++;
  }
  count++;
  if (count < word.length())
  {
    return ins(node->branch[word[count - 1] - 65], word, count);
  }
  else
    return node->branch[word[count - 1] - 65];
}

/// @brief inserting nodes in trie
/// @param wordInName one of the word of the railway station
/// @param indexOfName index given from dictionary
/// @return true if inserted
bool Trie::insert(string wordInName, int indexOfName)
{
  TrieNode *currNode = root;
  int len = wordInName.length();
  currNode = ins(root, wordInName, 0);
  currNode->isWord = true;
  listOfObjects<int> *a = currNode->indices;
  currNode->indices = new listOfObjects<int>(indexOfName);
  currNode->indices->next = a;
  return true;
}

//function for searching last node of a name
TrieNode *search(TrieNode *node, string word, int count)
{
  if (count < word.length() - 1)
  {
    count++;
    return search(node->branch[word[count - 1] - 'A'], word, count);
  }
  else
  {
    return node->branch[word[count] - 'A'];
  }
}

/// @brief function for deleting nodes in the trie
/// @param wordInName word of the name odf the station
/// @param name full name of the station
/// @return true if successfully deleted
bool Trie::del(string wordInName, string name)
{
  TrieNode *currNode = root;
  TrieNode *lastBranchNode = nullptr;
  int lastBranchChar = -1;
  int len = wordInName.length();

  // Insert your code here

  if (isPresent(wordInName))
  {
    lastBranchNode = search(root, wordInName, 0);
    listOfObjects<int> *k = lastBranchNode->indices;
    if (k->next == nullptr)
    {
      lastBranchNode->indices = nullptr;
      lastBranchNode->isWord = false;
    }
    else
    {
      while (k->next != nullptr)
      {
        if (nameDict->getKeyAtIndex(k->object) == name)
        {
          lastBranchNode->indices = lastBranchNode->indices->next;
          break;
        }
        if (nameDict->getKeyAtIndex(k->next->object) == name)
        {
          k->next = k->next->next;
          break;
        }
        else
        {
          k->next = k->next->next;
        }
      }
    }

    // deleting the full node if only one word exists 
    if (lastBranchNode->indices == nullptr && lastBranchNode->numNonNullBranches == 0)
    {
      int i = 0;
      TrieNode *current = root;
      TrieNode *l = current;
      int y = -1;
      for (int i = 0; i < wordInName.length(); i++)
      {
        if (current->numNonNullBranches > 1)
        {
          l = current;
          y = i;
        }
        if (current->isWord == true)
        {
          l = current;
          y = i;
        }
        current = current->branch[wordInName[i] - 'A'];
      }
      if (y == -1 || y == 0)
      {
        recursiveDelete(root->branch[wordInName[0] - 'A']);
        root->branch[wordInName[0] - 'A'] = nullptr;
      }
      else
      {
        recursiveDelete(l->branch[wordInName[y] - 'A']);
        l->numNonNullBranches--;
        l->branch[wordInName[y] - 'A'] = nullptr;
      }
    }
  }
  else
    return false;

  return true;
}

/// @brief autocompletion functiuon
/// @param prefix orefix to be searched and to be autocompleted
/// @return a linked list of strings of station
listOfObjects<string> *Trie::completions(string prefix)
{
  TrieNode *currNode = root;
  int len = prefix.length();
  listOfObjects<string> *currCompletions = nullptr;
  // Insert your code here
  int i = 0;
  while (currNode != nullptr && i < len)
  {
    int index = prefix[i] - 'A';
    currNode = currNode->branch[index];
    i++;
  }
  if (i == len)
  {
    recursiveAddCompletions(currNode, currCompletions);
  }
  return currCompletions;
}

bool Trie::recursiveAddCompletions(TrieNode *node, listOfObjects<string> *&currCompletions)
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

/// @brief add the completions to the linked list when the word is completed. Also check if the cases are repeated.
/// @param node the node with isWord is true.
/// @param currCompletions linked list of autocompletion
/// @return true if the completions are successfully added
bool Trie::addCompletions(TrieNode *node, listOfObjects<string> *&currCompletions)
{

  // Insert your code here

  listOfObjects<int> *k = node->indices;
  while (k != nullptr)
  {
    string s = nameDict->getKeyAtIndex(k->object);
    if (!isPresentInCompletions(currCompletions, s))
    {
      listOfObjects<string> *x = currCompletions;
      currCompletions = new listOfObjects<string>(s);
      currCompletions->next = x;
    }
    k = k->next;
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
