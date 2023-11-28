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
TrieNode *Trie::search(string key) //function to return the node
{
  TrieNode *pCrawl = root;

  for (int i = 0; i < key.length(); i++)
  {
    int index = toupper(key[i]) - 'A';
    if (pCrawl->branch[index] == nullptr)
      return NULL;
    pCrawl = pCrawl->branch[index];
  }
  return (pCrawl);
}

bool Trie::insert(string wordInName, int indexOfName)
{
  TrieNode *currNode = root;
  int len = wordInName.length();

  // Insert your code here
  for (int i = 0; i < len; i++)
  {
    int index = toupper(wordInName.at(i)) - 'A';
    if (currNode->branch[index] == nullptr)
    {
      currNode->branch[index] = new TrieNode();
      currNode->numNonNullBranches += 1;
    }

    currNode = currNode->branch[index];
  }

  // mark last node as leaf
  currNode->isWord = true;   //isWord is set to be true
  if (currNode->indices == NULL)
  {
    currNode->indices = new listOfObjects<int>(indexOfName); //inserted in the linked list
  }
  else
  {
    listOfObjects<int> *curr = currNode->indices;
    while (curr->next != NULL)
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
  TrieNode *lastBranchNode = nullptr;

  int lastBranchChar = -1;
  int len = wordInName.length();
  TrieNode *t = search(wordInName);  //searching the node

  for (int i = 0; i < wordInName.length(); i++)
  {
    int index = toupper(wordInName[i]) - 'A';
    if (currNode->numNonNullBranches > 1 || currNode->isWord) //if the number of non null branches is more than 1
    {
      lastBranchNode = currNode;   //updating the last branch node
      lastBranchChar = index;
    }
    currNode = currNode->branch[index];
  }

  int value = (nameDict->get(name))->value;  //value stored
  listOfObjects<int> *curr;   
  curr = t->indices;
  if (t->indices->object == value)
  {
    t->indices = t->indices->next;
  }
  else
  {
    while (curr != NULL)   //updating the linkedlist
    {
      if (curr->next->object == value)
      {
        curr->next = (curr->next)->next;

        break;
      }
      curr = curr->next;
    }
  }

  if ((t->indices == NULL) && t->numNonNullBranches != 0) 
    t->isWord = false;
  else if ((t->indices == NULL) && t->numNonNullBranches == 0)
  {
    lastBranchNode->branch[lastBranchChar] = NULL;
  }

  // Insert your code here

  return true;
}

listOfObjects<string> *Trie::completions(string prefix)
{
  TrieNode *currNode = root;
  int len = prefix.length();
  listOfObjects<string> *currCompletions = nullptr;

  // Insert your code here

  TrieNode *t = search(prefix); 
  if (t == NULL)
    return NULL;
  recursiveAddCompletions(t, currCompletions);
  
  return currCompletions;
}

bool Trie::recursiveAddCompletions(TrieNode *node, listOfObjects<string> *&currCompletions)
{
  if (node->isWord)   //checking
  {
    if (!addCompletions(node, currCompletions))
    {
      return false;
    }
  }
  TrieNode *currNode = node;
  for (int i = 0; i < NUM_CHARS; i++)  //iterating over
  {
    if (currNode->branch[i] != nullptr)
    {
      if (!recursiveAddCompletions(currNode->branch[i], currCompletions)) //recursively adding 
      {
        return false;
      }
    }
  }

  return true;
}

bool Trie::addCompletions(TrieNode *node, listOfObjects<string> *&currCompletions)
{
  listOfObjects<int> *curr = node->indices;
  while (curr != NULL)
  {
    int value = curr->object;
    string s = nameDict->getKeyAtIndex(value);  //getting value at the key
    if (currCompletions == NULL)
    {
      currCompletions = new listOfObjects<string>(s);
    }
    else if (!isPresentInCompletions(currCompletions, s)) //adding if not present already
    {
      listOfObjects<string> *a = currCompletions;
      while (a->next != NULL)
      {
        a = a->next;
      }
      a->next = new listOfObjects<string>(s);
    }
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
