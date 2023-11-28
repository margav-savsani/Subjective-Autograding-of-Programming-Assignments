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
  if (root == NULL)
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
  if (node == NULL)
  {
    return;
  }
  else
  {
    for (int i = 0; i < NUM_CHARS; i++)
    {
      TrieNode *currNode = node->branch[i];
      recursiveDelete(currNode);
      node->branch[i] = NULL;
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

  for (int wordIterator = 0; wordIterator < len; wordIterator++)
  {
    char letter = wordInName[wordIterator];
    int letterValue = toupper(letter) - 'A'; // letter is converted into an integer in range [0, NUM_CHARS]
    if (root->branch[letterValue] == NULL)
    {
      root->branch[letterValue] = new TrieNode();
      root->numNonNullBranches += 1;
    }
    if (wordIterator == len - 1)
    {
      if (root->branch[letterValue]->isWord == false)
      {
        root->branch[letterValue]->isWord = true;
        root->branch[letterValue]->indices = new listOfObjects<int>(indexOfName);
      }
      else
      {
        listOfObjects<int> *counter = root->branch[letterValue]->indices;
        while (counter->next != NULL)
        {
          counter = counter->next;
        }
        counter->next = new listOfObjects<int>(indexOfName);
      }
    }
    root = root->branch[letterValue];
  }
  root = currNode;
  return true;
}

bool Trie::del(string wordInName, string name)
{
  TrieNode *currNode = root;
  TrieNode *lastBranchNode = NULL;
  int lastBranchChar = -1;
  int len = wordInName.length();

  // Insert your code here
  lastBranchNode = root; // we may not need to delete as many nodes as len

  for (int wordIterator = 0; wordIterator < len; wordIterator++) // 2 purposes of this for loop. 1)find lastBranchNode  2)return false if word is absent
  {
    char letter = wordInName[wordIterator];
    int letterValue = toupper(letter) - 'A'; // letter is converted into an integer in range [0, NUM_CHARS]
    root = root->branch[letterValue];
    if (root == NULL)
    {
      return false; // not found in trie
    }
    if (wordIterator != len - 1 && (root->numNonNullBranches > 1 || root->isWord))
    {
      lastBranchNode = root;
      lastBranchChar = wordIterator;
    }
  }
  if (!root->isWord)
  {
    return false; // not found
  }
  if (root->isWord && root->indices->next != NULL || root->numNonNullBranches > 0)
  {
    lastBranchNode = NULL;
  }
  // lastBranchNode and lastBranchChar have been identified
  listOfObjects<int> *counter = root->indices;
  listOfObjects<int> *prev = NULL;
  bool deleted = false;
  while (counter != NULL)
  {
    if (nameDict->getKeyAtIndex(counter->object) == name)
    {
      deleted = true;
      if (prev != NULL)
      {
        prev->next = counter->next;
      }
      else // the to-be-deleted station is the first station
      {
        root->indices = counter->next;
        root->isWord = root->indices != NULL;
      }
      delete counter;
      break;
    }
    prev = counter;
    counter = counter->next;
  }
  if (deleted == false)
  {
    return false;
  }
  // now i will delete all nodes below lastBranchChar
  if (lastBranchNode != NULL)
  {
    recursiveDelete(lastBranchNode->branch[int(toupper(wordInName[lastBranchChar + 1])) - int('A')]);
    lastBranchNode->branch[int(toupper(wordInName[lastBranchChar + 1])) - int('A')] = NULL;
    lastBranchNode->numNonNullBranches -= 1;
  }
  // deletion completed
  root = currNode;
  return true;
}

listOfObjects<string> *Trie::completions(string prefix) // seta of all completions of the prefinx
{
  TrieNode *currNode = root;
  int len = prefix.length();
  listOfObjects<string> *currCompletions = new listOfObjects<string>("^&*("); // dummy string

  for (int i = 0; i < len; i++)
  {
    int letterValue = toupper(prefix[i]) - 'A'; // case insensitive

    if (currNode->branch[letterValue] == NULL)
    {
      delete currCompletions; // not found
      return NULL;
    }
    else
    {
      currNode = currNode->branch[letterValue];
    }
  }
  // prefix has been found in the trie
  if (recursiveAddCompletions(currNode, currCompletions)) // passed
  {
    return currCompletions;
  }
  else // failed
  {
    freeCompletionList(currCompletions);
    return NULL;
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
    if (currNode->branch[i] != NULL)
    {
      if (!recursiveAddCompletions(currNode->branch[i], currCompletions))
      {
        return false;
      }
    }
  }

  return true;
}

// add all station Names in the node to currCompletions
bool Trie::addCompletions(TrieNode *node, listOfObjects<string> *currCompletions)
{
  if (!node->isWord)
  {
    return true;
  }
  else
  {
    listOfObjects<int> *curr = node->indices;
    while (curr != NULL)
    {
      string name = nameDict->getKeyAtIndex(curr->object);
      if (isPresentInCompletions(currCompletions, name)) // no need to add
      {
        curr = curr->next;
        continue;
      }
      else
      {
        if (currCompletions->object == "^&*(")
        {
          currCompletions->object = name;
        }
        else
        {
          // adding and linking the new completion
          string tempString = currCompletions->object;
          listOfObjects<string> *tempPtr = currCompletions->next;

          currCompletions->object = name;
          currCompletions->next = new listOfObjects<string>(tempString);
          currCompletions->next->next = tempPtr;
        }
        curr = curr->next;
        continue;
      }
    }
    return true;
  }
}

bool Trie::isPresentInCompletions(listOfObjects<string> *completions, string name)
{
  listOfObjects<string> *currCompletion = completions;
  bool isPresent = false;
  while (currCompletion != NULL)
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
  while (currCompl != NULL)
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

    if (currNode->branch[letter] == NULL)
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
  if (node != NULL)
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
      while (currIndices != NULL)
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
        if (node->branch[j] != NULL)
        {
          childrenToRight = true;
          break;
        }
      }
      if (currNode != NULL)
      {
        recursivePrintTrie(currNode, prefix + ((siblingsToRight) ? "│   " : "    "), i, childrenToRight);
      }
    }
  }
}
// End edit version 1

#endif
