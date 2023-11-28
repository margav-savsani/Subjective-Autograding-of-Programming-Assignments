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

// Constructor for the trie
Trie::Trie(Dictionary<int> *nameToIndex)
{
  // Initialising the variables
  nameDict = nameToIndex;
  root = new TrieNode();
  if (root == nullptr)
  {
    cout << "Memory allocation failure." << endl;
    exit(-1);
  }
}

// Destructor of the trie
Trie::~Trie()
{
  recursiveDelete(root);
}

// Function to recursively delete every pointer coming under the given node
void Trie::recursiveDelete(TrieNode *node)
{
  // Base case when node is null
  if (node == nullptr)
  {
    return;
  }
  else
  {
    // Iterating through every child of node and calling recursively the function
    // for each of its child
    for (int i = 0; i < NUM_CHARS; i++)
    {
      TrieNode *currNode = node->branch[i];
      recursiveDelete(currNode);
      node->branch[i] = nullptr;
    }
    // Deleting the node only if it is not root, else we would face error if we try
    // to insert again in the trie after emptying it first.
    if (node != root)
    {
      delete node;
    }
    return;
  }
}

// Function to insert a node in the trie
bool Trie::insert(string wordInName, int indexOfName)
{
  // Pointer to mark the location of node in whose branch I need
  // to add my new node
  TrieNode *currNode = root;
  int len = wordInName.length();

  // Insert your code here

  // Iterating through each character of the word, adding a new tree node
  // in branch of current node if node not present else moving down the trie
  for (int i = 0; i < len; i++)
  {
    // Finding the index of branch array where I need to go
    int letter = toupper(wordInName.at(i)) - 'A';

    // Adding new node in case not present initially
    if (currNode->branch[letter] == nullptr)
    {
      TrieNode *temp_node = new TrieNode();

      // Updating the number of children count of current node, as new
      // child is being inserted
      currNode->numNonNullBranches += 1;
      currNode->branch[letter] = temp_node;
    }
    currNode = currNode->branch[letter];
  }

  // Creating a new object that is to be added for the given word in the
  // indices list
  listOfObjects<int> *node = new listOfObjects<int>(indexOfName);

  // If the node is already a word
  if (currNode->isWord)
  {
    // Creating a pointer to traverse my indices and reach the last object in
    // the inidices whose next element would be my new insertion
    listOfObjects<int> *temp = currNode->indices;
    listOfObjects<int> *temp2;
    while (temp != nullptr)
    {
      // This condition checks if the word is already present in the indices or not
      // If already present, it returns false
      if (temp->object == indexOfName)
      {
        return false;
      }
      temp2 = temp;
      temp = temp->next;
    }
    // Adding the new node in the indices
    temp2->next = node;
  }
  // If the node was not a word prior to current insertion
  else
  {
    // Marking the node as word
    currNode->isWord = true;
    // Initialising its indices list
    currNode->indices = node;
  }
  return true;
}


// A helper recursive function to assist my del function
// It deletes all the nodes under the given node including given too, the condition
// being that every node must have only one child and the index of whose can be found
// using the parameter wordInName.
void Trie::delete_intermediate(TrieNode *ptr, int index, string wordInName)
{
  // Base case for the leaf node
  if (ptr->numNonNullBranches == 0)
  {
    delete ptr;
    return;
  }
  delete_intermediate(ptr->branch[toupper(wordInName.at(index)) - 'A'], index + 1, wordInName);
  delete ptr;
  return;
}

// Function to delete the given name of station from the list of
// station names of node having the word stored same as word passed
// as parameter
bool Trie::del(string wordInName, string name)
{
  // Initialsing the variables
  TrieNode *currNode = root;
  TrieNode *lastBranchNode = nullptr;
  int lastBranchChar = -1;
  int len = wordInName.length();

  // Insert your code here

  // These two variables store the last node apart from the node from which deletion will
  // be performed such that it is either a word or have 2 non null children
  TrieNode *last = root;
  int index_of_Word = -1;

  // First finding the node from which deletion is to be done
  for (int i = 0; i < len; i++)
  {
    int letter = toupper(wordInName.at(i)) - 'A';

    // In case the word doesn't already exist, no deletion can be performed
    // and hence false will be returned
    if (currNode->branch[letter] == nullptr)
    {
      return false;
    }
    currNode = currNode->branch[letter];
    // Updating the last node having the aforementioned properties, if possible
    if ((currNode->isWord || currNode->numNonNullBranches > 1) && (i != len - 1))
    {
      index_of_Word = i;
      last = currNode;
    }
  }

  // Checking if the word exists or not in trie, if not return false as deletion
  // can't be done
  if (!currNode->isWord)
  {
    return false;
  }

  // Creating a pointer to Entry datatype as it would be used to get the index
  // corresponding the station name stored in the dictionary
  Entry<int> *A = nameDict->get(name);
  // Checking if the given element that is to be deleted exist or not in dictionary
  if (A == nullptr)
  {
    return false;
  }
  // Iterating through all the station names in which the given word exists
  listOfObjects<int> *temp = currNode->indices;
  // Is the predecessor of the temp in the list
  listOfObjects<int> *temp2 = nullptr;
  while (temp != nullptr)
  {
    // Checking if the station index matches the required one or not
    if (temp->object == A->value)
    {
      // Need to delete here as match is found

      // For the case when only a single station name corresponds the word given
      if (temp2 == nullptr && temp->next == nullptr)
      {
        // Means no more word would now exist at the given node
        // Hence isWord would be false post deletion
        currNode->isWord = false;

        // Checking if I should delete the given node too in case it is usless
        // as it now neither has any children nor is a word anymore
        if (currNode->numNonNullBranches == 0)
        {
          // Deleting all the nodes upto the first node which is a word or is a prefix
          // to another word too
          last->numNonNullBranches -= 1;
          delete_intermediate(last->branch[toupper(wordInName.at(index_of_Word + 1)) - 'A'], index_of_Word + 2, wordInName);
          last->branch[toupper(wordInName.at(index_of_Word + 1)) - 'A'] = nullptr;
        }
      }
      // If deletion is done not from the start of the list of station names
      else if (temp2 != nullptr)
      {
        // Doesn't matter even if the next is nullptr
        temp2->next = temp->next;
        delete temp;
      }
      // If deletion is done from the start of the list of station names
      else
      {
        currNode->indices = temp->next;
        delete temp;
      }
      return true;
    }
    temp2 = temp;
    temp = temp->next;
  }
  return false;
}

// Function to return a list of station names having a word with given
// prefix
listOfObjects<string> *Trie::completions(string prefix)
{
  // Initialsing the variables
  TrieNode *currNode = root;
  int len = prefix.length();
  listOfObjects<string> *currCompletions = nullptr;

  // Insert your code here
  // First of all going to the node where this prefix ends, if the prefix
  // does not exist we return nullptr
  for (int i = 0; i < len; i++)
  {
    int letter = toupper(prefix.at(i)) - 'A';

    if (currNode->branch[letter] == nullptr)
    {
      return currCompletions;
    }
    currNode = currNode->branch[letter];
  }

  // recursively adding all the station names once we find the node with
  // given prefix
  if (recursiveAddCompletions(currNode, currCompletions))
  {
    return currCompletions;
  }
  return nullptr;
}

// Boiler plate code which recursively updates the list of station names
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

// Function which given a node and a list of station names, appends the list with all the station
// names stored in that node
// This function is only called iff the node is a word and hence we dont need to
// check for that again here
bool Trie::addCompletions(TrieNode *node, listOfObjects<string> *&currCompletions)
{
  // Insert your code here
  // Pointer that would point to the end of list where insertion would be done
  listOfObjects<string> *end = currCompletions;

  // If the list is not empty prior coming to this node
  if (end != nullptr)
  {
    // finding the last element of list
    while (end->next != nullptr)
    {
      end = end->next;
    }

    // Iterating through the station names of the node and adding them
    // to the list and returning true post completion
    listOfObjects<int> *ptr = node->indices;
    while (ptr != nullptr)
    {
      string str = nameDict->getKeyAtIndex(ptr->object);
      if (!isPresentInCompletions(currCompletions, str))
      {
        listOfObjects<string> *temp = new listOfObjects<string>(str);
        end->next = temp;
        end = end->next;
      }
      ptr = ptr->next;
    }
    return true;
  }

  // In case the list is empty initially
  else
  {
    // Iterating through the station names of the node
    listOfObjects<int> *ptr = node->indices;
    while (ptr != nullptr)
    {
      string str = nameDict->getKeyAtIndex(ptr->object);
      if (!isPresentInCompletions(currCompletions, str))
      {
        listOfObjects<string> *temp = new listOfObjects<string>(str);
        // To add the first element in the list we need to handle it separately
        // That is being done using this if case
        if (end == nullptr)
        {
          end = temp;
          currCompletions = end;
        }
        // Once an element is added, remaining task is same had the given list been non-empty
        else
        {
          end->next = temp;
          end = end->next;
        }
      }
      ptr = ptr->next;
    }
    return true;
  }
}

// Boiler plate code
bool Trie::isPresentInCompletions(listOfObjects<string> *&completions, string name)
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

// Boiler plate code
void Trie::freeCompletionList(listOfObjects<string> *&completions)
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

// Boiler plate code
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
