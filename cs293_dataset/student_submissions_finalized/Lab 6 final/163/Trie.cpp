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
  for (int i = 0; i < len; i++) // iterating over each letter of the word
  {
    if (currNode->branch[wordInName[i] - 'A'] == nullptr) // if the child of currNode corresponding to this letter doesn't exist
    {
      currNode->numNonNullBranches++;
      currNode->branch[wordInName[i] - 'A'] = new TrieNode(); // corresponding node is added
    }
    currNode = currNode->branch[wordInName[i] - 'A']; // currNode is shifted down
  }
  currNode->isWord = true; // the last node is complete word
  if (currNode->indices == nullptr)
  {
    currNode->indices = new listOfObjects<int>(indexOfName); // if indices is nullptr, new list is added with given index
  }
  else
  {
    listOfObjects<int> *listNode = currNode->indices;
    while (listNode->next != nullptr)
    {
      listNode = listNode->next; // iterate till next pointer is null
    }
    listNode->next = new listOfObjects<int>(indexOfName); // insert new index at next pointer
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
  for (int i = 0; i < len; i++) // iterating over the string wordInName
  {
    if (currNode->branch[wordInName[i] - 'A'] == nullptr)
    {
      return false; // it would mean the word to be deleted doesn't even exist
    }
    currNode = currNode->branch[wordInName[i] - 'A']; // we go to the next node in trie
    if (i != len - 1 && (currNode->isWord || currNode->numNonNullBranches > 1))
    {
      lastBranchNode = currNode;                // lastBranchNode stores the last node in the trie, before the leaf node, which can not be deleted before it also leads to other stations.
      lastBranchChar = wordInName[i + 1] - 'A'; // lastBranchChar stores the index for child of lastBranchNode which we want to delete.
    }
  }
  // currNode is now the node where the last char of wordInName is stored.
  if (!currNode->isWord)
  {
    return false; // if the currNode is not a word, that means wordInName doesn't exist in trie, return false.
  }
  else if (currNode->indices->next != nullptr) // if indices list at currNode has more than 1 elements.
  {
    // we only need to remove the indices node corresponding to string name given
    if (nameDict->getKeyAtIndex(currNode->indices->object) == name)
    {
      currNode->indices = currNode->indices->next; // if the very first element of list is to be deleted
      return true;
    }
    listOfObjects<int> *temp = currNode->indices->next;
    listOfObjects<int> *prev = currNode->indices;
    while (temp != nullptr)
    {
      if (name == nameDict->getKeyAtIndex(temp->object))
      {
        prev->next = temp->next;
        return true; // we iterate in the indices list, and delete node if found.
      }
      prev = prev->next;
      temp = temp->next;
    }
    // if reached here, station not found
    return false;
  }
  else // we need to delete some branch of lastBranchNode
  {
    if (lastBranchNode == nullptr) // That means the whole branch at root is to be deleted
    {
      root->branch[wordInName[0] - 'A'] = nullptr;
      root->numNonNullBranches--;
    }
    else // Required node at lastBranchNode is deleted
    {
      lastBranchNode->branch[lastBranchChar] = nullptr;
      lastBranchNode->numNonNullBranches--;
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
  for (int i = 0; i < len; i++) // the entire prefix should match a word from root.
  {
    if (currNode->branch[prefix[i] - 'A'] == nullptr) // if the letter doesn't exist, we return nullptr
      return currCompletions;
    currNode = currNode->branch[prefix[i] - 'A']; // currNode shifted to next
  }
  if (currCompletions == nullptr)
  {
    currCompletions = new listOfObjects<string>("tombstone"); // Tombstone if initially empty
  }
  recursiveAddCompletions(currNode, currCompletions); // prefix is found, so Completions are added recursively

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
  listOfObjects<int> *listNode = node->indices;
  if (currCompletions->object == "tombstone")
  {
    currCompletions->object = nameDict->getKeyAtIndex(listNode->object);
    listNode = listNode->next; // if temobstone, one element is added manually
  }
  listOfObjects<string> *completionsNode = currCompletions;
  while (completionsNode->next != nullptr)
  {
    completionsNode = completionsNode->next; // iterated, so that we have to insert at next node now
  }
  while (listNode != nullptr)
  {
    listOfObjects<string> *temp = currCompletions;
    bool already_inserted = false;
    while (temp->next != nullptr)
    {
      if (temp->object == nameDict->getKeyAtIndex(listNode->object))
      {
        already_inserted = true; // checking if current listNode is already inserted
        break;
      }
      temp = temp->next;
    }
    if (!already_inserted)
    {
      completionsNode->next = new listOfObjects<string>(nameDict->getKeyAtIndex(listNode->object));
      completionsNode = completionsNode->next; // If not already inserted, we insert listNode at next
    }
    listNode = listNode->next;
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
