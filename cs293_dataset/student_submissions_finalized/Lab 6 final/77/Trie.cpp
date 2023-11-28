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
  //Adding letter in Trie one by one.
  for (int i = 0; i < len; i++)
  {
    int letter = toupper(wordInName[i]) - 'A';

    if (currNode->branch[letter] == nullptr)
    {
      TrieNode *newNode = new TrieNode();
      currNode->branch[letter] = newNode;
      currNode->numNonNullBranches++;
    }
    currNode = currNode->branch[letter];
  }
  currNode->isWord = true;
  // Checking if station is allready present or not.
  listOfObjects<int> *currIndices = currNode->indices;
  while (currIndices != NULL)
  {
    if (currIndices->object == indexOfName)
    {
      cout << "Already station is inserted in the past." << endl;
      return true;
    }
    currIndices = currIndices->next;
  }
  // If new station is added
  listOfObjects<int> *newIndex = new listOfObjects<int>(indexOfName);
  newIndex->next = currNode->indices;
  currNode->indices = newIndex;
  return true;
}

bool Trie::del(string wordInName, string name)
{
  TrieNode *currNode = root;
  TrieNode *lastBranchNode = nullptr;
  int lastBranchChar = -1;
  int len = wordInName.length();
  // Checking the prefix in Trie letter by letter
  for (int i = 0; i < len; i++)
  {
    int letter = toupper(wordInName.at(i)) - 'A';
    // If no branch for that letter return false
    if (currNode->branch[letter] == nullptr)
    {
      cout << wordInName << " NOT FOUND" << name << endl;
      return false;
    }
    if (currNode->numNonNullBranches > 1 || currNode->isWord)
    {
      lastBranchNode = currNode;
      lastBranchChar = i;
    }
    currNode = currNode->branch[letter];
  }
  // If word is not having isWord true.
  if (!currNode->isWord)
  {
    cout << wordInName << " NOT FOUND" << name << endl;
    return false;
  }

  if (currNode->numNonNullBranches != 0)
  {
    currNode->isWord = false;
    return true;
  }
   //Deletion starts from here
  listOfObjects<int> *currIndex = currNode->indices;
  listOfObjects<int> *prevIndex = nullptr;
  while (currIndex != nullptr)
  {
    if (nameDict->getKeyAtIndex(currIndex->object) == name)
    {
      if (prevIndex == nullptr)
      {
        currNode->indices = currIndex->next;
      }
      else
      {
        prevIndex->next = currIndex->next;
      }
      delete currIndex;
      currNode->indices = prevIndex;
      // If there are more than 1 indices at currNode.
      if (currNode->indices != nullptr)
      {
        return true;
      }
      // If only 1 index is present.
      else
      {
        currNode->isWord = false;
        // If word is subpart of big string. MUMB in MUMBAI
        if (currNode->numNonNullBranches > 0)
        {
          return true;
        }
        // branching/allready a word before is subpart case and it is not a subpart
        if (lastBranchNode != nullptr)
        {
          int lastBranchIndex = toupper(wordInName[lastBranchChar]) - 'A';
          currNode = lastBranchNode->branch[lastBranchIndex];
          lastBranchNode->branch[lastBranchIndex] = nullptr;
          lastBranchNode->numNonNullBranches--;
        }
        else
        {
          // direct path from root delete if no subbranch,no other is-word true in that branch and no substring or superstring.
          int rootBranchIndex = toupper(wordInName.at(0)) - 'A';
          currNode = root->branch[rootBranchIndex];
          root->branch[rootBranchIndex] = nullptr;
          root->numNonNullBranches--;
          lastBranchChar = 0;
        }
        // Deleting removed part
        TrieNode *prevNode;
        for (int i = lastBranchChar + 1; i < len; i++)
        {
          int letter = toupper(wordInName[i]) - 'A';
          prevNode = currNode;
          currNode = currNode->branch[letter];
          delete prevNode;
        }
        return true;
      }
    }
    else
    {
      prevIndex = currIndex;
      currIndex = currIndex->next;
    }
  }
  return false;
}

listOfObjects<string> *Trie::completions(string prefix)
{
  TrieNode *currNode = root;
  int len = prefix.length();
  listOfObjects<string> *currCompletions = new listOfObjects<string>("!@#$%^&*()"); // DUMMY OBJECT
  for (int i = 0; i < len; i++)
  {
    int letter = toupper(prefix[i]) - 'A';

    if (currNode->branch[letter] == nullptr)
    {
      return nullptr;
    }
    currNode = currNode->branch[letter];
  }
  // Calls recursiveAddCompletions and returns currCompletions if it is true
  if (recursiveAddCompletions(currNode, currCompletions))
  {
    return currCompletions;
  }
  // returns nullptr if it is false
  else
  {
    return nullptr;
  }
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

  listOfObjects<int> *currIndex = node->indices;
  while (currIndex != nullptr)
  {
    string completeName = nameDict->getKeyAtIndex(currIndex->object);
    // Check if allready Index of that station name is present in currCompletions
    if (!isPresentInCompletions(currCompletions, completeName))
    {
      //If first object we have add in currCompletions
      if (currCompletions->object == "!@#$%^&*()") // created in bool Trie::completions()
      {
        currCompletions->object = completeName;
      }
      // all other objects except 1 adding in currCompletions
      else
      {
        listOfObjects<string> *newCompletion = new listOfObjects<string>(currCompletions->object);
        newCompletion->next = currCompletions->next;
        currCompletions->object = completeName;
        currCompletions->next = newCompletion;
      }
    }
    currIndex = currIndex->next;
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
