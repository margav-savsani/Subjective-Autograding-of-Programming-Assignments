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
  for (int i = 0; i < wordInName.length(); i++)
  {
    int index = toupper(wordInName[i]) - 'A';
    if (!currNode->branch[index])
    {
      // if that branch dosent exists, creates a new branch and inserts it.
      currNode->branch[index] = new TrieNode();
      currNode->numNonNullBranches++;
    }
    // else, just traverses to that corresponding branch.
    currNode = currNode->branch[index];
  }

  // marks end of word as isWord to true if isnt a new word . else, this node will be maked as isWord=true before because the word already exists before.
  if (!currNode->isWord)
    currNode->isWord = true;

  // traversing to the end of the linked list to insert the new one.
  if (currNode->isWord)
  {
    listOfObjects<int> *LastNode = currNode->indices;
    if (LastNode == nullptr)
    {
      LastNode = new listOfObjects<int>(indexOfName);
      currNode->indices = LastNode;
      return true;
    }
    while (LastNode->next != nullptr)
    {
      LastNode = LastNode->next;
    }
    // inserting the new index at end of linked list.
    LastNode->next = new listOfObjects<int>(indexOfName);

    return true;
  }
  return false;
}

bool Trie::del(string wordInName, string name)
{
  TrieNode *currNode = root;
  TrieNode *lastBranchNode = nullptr;
  int lastBranchChar = -1;
  int len = wordInName.length();

  // finding at which index the name was situated.
  int indexOfName = nameDict->get(name)->value;

  // if root exists, we proceed. else, failed.
  if (root)
  {
    // traversing if the word exists.
    for (int i = 0; i < wordInName.length(); i++)
    {
      int index = toupper(wordInName[i]) - 'A';
      if (!currNode->branch[index])
      {
        // if that branch dosent exists, failed to delete.
        return false;
      }
      if (currNode->isWord)
      {
        lastBranchNode = currNode;
        lastBranchChar = index;
      }
      // else, just traverses to that corresponding branch.
      currNode = currNode->branch[index];
    }
    if (currNode->isWord)
    {
      // dummy prev initialisation and curernt for traversing.

      listOfObjects<int> *Prev = new listOfObjects<int>(-1), *Current = currNode->indices;
      int size = 1;
      while (Current->object != indexOfName)
      {
        // traversing in linked list until we reach our desired index.
        Prev = Current;
        Current = Current->next;
        size++;
      }
      if (Current == nullptr)
      {
        // can't find the index so, failed to delete
        return false;
      }
      if (size == 1)
      {
        // if size is 1, it means only one word, then we need to delete that even and disable is word property.
        currNode->indices = nullptr;
        currNode->isWord = false;
        lastBranchNode->branch[lastBranchChar] = nullptr;
        return true;
      }
      if (Prev->object < 0)
      {
        // this means the starting of the linked list ,we found our index.
        currNode->indices = Current->next;
        // if prev's obj is -1, then it means the index is the starting of the linked list, so we donot care about prev index.
      }
      else
      {
        // mapping the prev node's next to currnt indice's next.
        Prev->next = Current->next;
        delete Current;
      }
      // deleting the node which contains the index.
      return true;
    }
    return false;
  }

  return false;
}

listOfObjects<string> *Trie::completions(string prefix)
{
  TrieNode *currNode = root;
  int len = prefix.length();
  listOfObjects<string> *currCompletions = nullptr;
  // creating a dummy head for the pointer instead of null.
  currCompletions = new listOfObjects<string>("");
  // traverse to the last branch until you last node of the prefix because,
  // you need to add all the elements after that which contains this prefix.
  for (int i = 0; i < len; i++)
  {
    int index = toupper(prefix[i]) - 'A';
    //if that branch dosent exists, then it failed to search. terminates function.
    if (!currNode->branch[index])
      return nullptr;
    currNode = currNode->branch[index];
  }
  // recursively add completions from currnode.
  recursiveAddCompletions(currNode, currCompletions);
  // excluding the dummy head, we just need to exclude that and return that
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
  //if node istermination of word, then only we proceeed. else false.
  if (node->isWord)
  {
    // sanity check
    if (node->indices == nullptr)
      return false;
    listOfObjects<int> *Indices = node->indices;
    //traversing through the indices and adding onebyone.
    while (Indices != nullptr)
    {
      //going to tail of list and appending this.
      while (currCompletions->next == nullptr)
      {
        //constructing new node according to index.
        currCompletions->next = new listOfObjects<string>(nameDict->getKeyAtIndex(Indices->object));
        Indices = Indices->next;
      }
      currCompletions = currCompletions->next;
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
