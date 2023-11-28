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
  for (int i = 0; i < len; i++) // running throughout the string
  {
    int r = toupper(wordInName[i]) - 'A'; // branch number of each letter
    if (currNode->branch[r] == nullptr)   // if null update
    {
      currNode->branch[r] = new TrieNode(); // creating new if not there
      currNode->numNonNullBranches++;       // increasing branches number
    }
    currNode = currNode->branch[r]; // traversing down
  }
  currNode->isWord = true;                                     // changing that its a word from root to this node
  listOfObjects<int> *r = new listOfObjects<int>(indexOfName); // updating indices
  r->next = currNode->indices;                                 // updating indices
  r->object = indexOfName;                                     // updating indices
  currNode->indices = r;                                       // updating indices
  return true;
}

bool Trie::del(string wordInName, string name)
{
  TrieNode *currNode = root;
  TrieNode *lastBranchNode = nullptr;
  int lastBranchChar = -1;
  int len = wordInName.length();

  // Insert your code here
  if (!isPresent(wordInName)) // if not present
  {
    return false;
  }
  TrieNode *T = root;//initialisng to top
  int k = (toupper(wordInName[wordInName[0]]) - 'A');//initialised to first letter
  for (int i = 0; i <= len - 1; i++)//traversing down the path of prefix
  {
    int r = toupper(wordInName[i] - 'A');//branch number
    if (currNode->numNonNullBranches > 1 || currNode->isWord)//cases where nodes shouldnt be deleted
    {
      T = currNode;//updating from where it should change
      k = r;//branch to be changed
    }
    currNode = currNode->branch[r];//traversing down
  }
  int index = nameDict->get(name)->value;//index of station in dictionary
  listOfObjects<int> *currIndex = currNode->indices;//accesing indices
  listOfObjects<int> *prevIndex = NULL;//updating indices into this
  listOfObjects<int> *w = new listOfObjects(currIndex->object);//variable used to update indices
  while (currIndex != NULL)//till the end
  {
    if (currIndex->object != index)//except index all should be added
    {
      listOfObjects<int> *w = new listOfObjects(currIndex->object);//updating new indexes
      w->next = prevIndex;//updating new indexes
      prevIndex = w;//updating new indexes
    }
    currIndex = currIndex->next;//traversing down the trie
  }
  currNode->indices = prevIndex;//updating indices

  if (currNode->numNonNullBranches == 0 && currNode->indices == NULL)//if deleting some nodes is required
  {
    T->branch[k] = NULL;//deleting branch
    T->numNonNullBranches--;//updating branches number
  }
  if ((currNode->numNonNullBranches != 0) && (currNode->indices == NULL))//if some are left below
  {
    currNode->isWord = false;//no more words here
  }
  return true;
}

listOfObjects<string> *Trie::completions(string prefix)
{
  TrieNode *currNode = root;
  int len = prefix.length();
  listOfObjects<string> *currCompletions = new listOfObjects<string>(" ");
  // Insert your code here
  for (int i = 0; i < len; i++) // running down the trie seeing prefix
  {
    int r = toupper(prefix[i]) - 'A'; // branch number
    if (currNode->branch[r] == NULL)  // if a null is encountered in between
    {
      return nullptr; // if prefix itself not there
    }
    else
    {
      currNode = currNode->branch[r]; // traversing down
    }
  }
  if (recursiveAddCompletions(currNode, currCompletions)) // r//updating currCompletionsecursive completions
  {
    return currCompletions; // final completions
  }
  return nullptr;
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

  listOfObjects<int> *currIndex = node->indices; // accesing indices
  while (currIndex != nullptr)                   // until its no more available
  {
    string Name = nameDict->getKeyAtIndex(currIndex->object); // full name
    if (!isPresentInCompletions(currCompletions, Name))       // if already present shouldnt add again
    {
      if (currCompletions->object == " ") // base initialisation
      {
        currCompletions->object = Name; // updating object
      }
      else
      {
        listOfObjects<string> *newCompletion = new listOfObjects<string>(currCompletions->object); // updating currCompletions
        newCompletion->next = currCompletions->next;                                               // updating currCompletions
        currCompletions->object = Name;                                                            // updating currCompletions
        currCompletions->next = newCompletion;                                                     // updating currCompletions
      }
    }
    currIndex = currIndex->next; // current index traversing below
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
