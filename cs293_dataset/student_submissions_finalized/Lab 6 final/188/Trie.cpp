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
  // Incomplete code. Search through branches of trienode. branch is an array of trienode pointers.
  // the planner splits the word if there is any space in wordInName
  for (int i = 0; i < len; i++)
  {
    if (currNode->branch[toupper(wordInName.at(i)) - 'A'] == NULL)
    {
      currNode->numNonNullBranches++;//non nullbranch increases
      TrieNode *node = new TrieNode();
      currNode->branch[toupper(wordInName.at(i)) - 'A'] = node;// traversing through branches. Creating a new branch if branch is null
    }
    currNode = currNode->branch[toupper(wordInName.at(i)) - 'A'];
  }
  currNode->isWord = true;
  listOfObjects<int> *obj = new listOfObjects<int>(indexOfName);
  listOfObjects<int> *ptr = currNode->indices;// adding index to the indices of the last Node
  if (ptr == nullptr)
  {
    currNode->indices = obj;
  }
  else
  {
    while (ptr->next != nullptr)
    {
      ptr = ptr->next;
    }
    ptr->next = obj;
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
  for (int i = 0; i < len; i++)
  {

    currNode = currNode->branch[toupper(wordInName.at(i)) - 'A'];
  }
  // Entry<int> *entry = nameDict->get(name);

  listOfObjects<int> *ptr1 = currNode->indices;
  listOfObjects<int> *ptr2 = nullptr;
  while (ptr1 != nullptr && nameDict->getKeyAtIndex(ptr1->object) != name)
  {

    ptr2 = ptr1;// it stores the previous pointer of the pointer to be deleted
    ptr1 = ptr1->next;
  }
  if (ptr1 == nullptr)
    return false;
  else
  {
    if (ptr2 == nullptr)
    {
      currNode->indices = ptr1->next;// if we want to delete the first element we have to move the head to the next one
      delete ptr1;
    }
    else
    {
      ptr2->next = ptr1->next;// updating prev->next to the next of pointer ot be deleted
      delete ptr1;
    }
  }
  if(currNode->indices == nullptr) currNode->isWord=false;
  return true;
}

listOfObjects<string> *Trie::completions(string prefix)
{
  TrieNode *currNode = root;
  int len = prefix.length();
  listOfObjects<string> *currCompletions = new listOfObjects<string>("");// initialising into a nullstring instead of using nullptr as it does not function with a nullptr
  for (int i = 0; i < len; i++)
  {
    currNode = currNode->branch[toupper(prefix.at(i)) - 'A'];
  }
  recursiveAddCompletions(currNode, currCompletions);// calling recursiveAddCompletions to add all completions with prefix given
  // Insert your code here
  return currCompletions->next;// return currcompletions->next to escape from "" string
}

bool Trie::recursiveAddCompletions(TrieNode *node, listOfObjects<string> *currCompletions)
{
  if (node->isWord)
  {
    if (!addCompletions(node, currCompletions))// if 0

    {
      return false;
    }
  }

  TrieNode *currNode = node;
  for (int i = 0; i < NUM_CHARS; i++)// this loop checks all the branches from the node
  {
    if (currNode->branch[i] != nullptr)
    {
      if (!recursiveAddCompletions(currNode->branch[i], currCompletions))//recursive calling of the function
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
  if (node->isWord)
  {
    listOfObjects<int> *ptr = node->indices;//ptr for moving through linked list int
    if(ptr == nullptr) return false;
    listOfObjects<string> *strptr = currCompletions;// ptr for moving through string linked list
    while (strptr->next != nullptr)
    {
      strptr = strptr->next;// strptr going to the tail of linked list 
    }
    while (ptr != NULL)
    {
      int index = ptr->object;
      string str = nameDict->getKeyAtIndex(index);// gets the key at the index
      
      listOfObjects<string> *strobj = new listOfObjects<string>(str);// creating a new string object with the station name
      strptr->next = strobj;// adding the object to the next of node
      ptr = ptr->next;//moving to the next index in the linked lists
      strptr = strptr->next;// moving the strptr to its next
      
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

// Adapted from Adrian Schneider's code on StackOverflows
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
