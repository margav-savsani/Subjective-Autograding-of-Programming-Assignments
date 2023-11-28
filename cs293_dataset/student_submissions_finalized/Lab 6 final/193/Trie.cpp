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
  if (indexOfName < 0)
  {
    return false;
  }
  // indexOfName stores the index of the name being inserted into the list of names.
  TrieNode *currNode = root;
  int len = wordInName.length(); // The length of the word in the name to be inserted

  for (int i = 0; i < len; i++)
  {
    int letter = toupper(wordInName.at(i)) - 'A';
    // Index of the letter to be inserted.
    if (currNode->branch[letter] == nullptr)
    {
      currNode->branch[letter] = new TrieNode(); // New TrieNode
      currNode->numNonNullBranches++;            // Whenever a new branch is inserted this is incremented.
    }
    currNode = currNode->branch[letter];
  }
  if (currNode->isWord == false)
  {
    currNode->isWord = true;
    currNode->indices = new listOfObjects<int>(indexOfName); // Assigning a new
  }
  else
  {
    listOfObjects<int> *currlistelem = currNode->indices;
    while (currlistelem->next != NULL)
    {
      currlistelem = currlistelem->next;
    }
    currlistelem->next = new listOfObjects<int>(indexOfName);
  }
  return true; // True return on successful insertion
}

bool Trie::del(string wordInName, string name)
{
  // If successfully deleted then return true, otherwise false.
  TrieNode *currNode = root;          // Current Node being checked.
  TrieNode *lastBranchNode = nullptr; // The Last Node which has a branch from it.
  // Along the Path to find the word
  int lastBranchChar = -1; //
  int len = wordInName.length();
  for (int i = 0; i < len; i++)
  {
    int letter = toupper(wordInName.at(i)) - 'A';
    // Index of the next letter.
    if (currNode->branch[letter] == nullptr)
    {
      // When the word itself is not present in the trie.
      return false;
    }
    if ((currNode->numNonNullBranches > 1) || (currNode->isWord))
    {
      lastBranchNode = currNode; // Assigned the last branch
      lastBranchChar = letter;   // Assigned the last character.
    }
    currNode = currNode->branch[letter];
  }
  if (currNode->numNonNullBranches != 0)
  { // When the NODE has elements after that
    if (currNode->indices->object == nameDict->get(name)->value)
    { // If the first index itself has to be deleted.
      listOfObjects<int> *todelete = currNode->indices;
      currNode->indices = currNode->indices->next;
      delete (todelete);
    }
    else
    { // Some other index in between has to be deleted.
      listOfObjects<int> *iterator = currNode->indices;
      while (iterator->next->object != nameDict->get(name)->value)
      {
        iterator = iterator->next;
      }
      // Finally we reach the node of linked list which is to be deleted.
      listOfObjects<int> *todelete = iterator->next;
      iterator->next = iterator->next->next;
      delete (todelete);
    }
    // If there is no name left at the NODE.
    if (currNode->indices == NULL)
    {
      currNode->isWord = false;
    }
  }
  else // Case when the Node doesnt contain any branches
  {
    if (currNode->indices->next == NULL) // Tough case NODE deletion (only single element present in the list.)
    {                   
        lastBranchNode->numNonNullBranches--;
        for(int i =0; i<NUM_CHARS; i++){
          recursiveDelete(lastBranchNode->branch[lastBranchChar]->branch[i]);
        }
        lastBranchNode->branch[lastBranchChar] = NULL; 
    }
    else // Means there are more than one name (easy case NO node deletion)
    {
      if (currNode->indices->object == nameDict->get(name)->value)
      { // If the first index itself has to be deleted.
        listOfObjects<int> *todelete = currNode->indices;
        currNode->indices = currNode->indices->next;
        delete (todelete);
      }
      else
      { // Some other index in between has to be deleted.
        listOfObjects<int> *iterator = currNode->indices;
        while (iterator->next->object != nameDict->get(name)->value)
        {
          iterator = iterator->next;
        }
        // Finally we reach the node of linked list which is to be deleted.
        listOfObjects<int> *todelete = iterator->next;
        iterator->next = iterator->next->next;
        delete (todelete);
      }
    }
  }
  return true;
}
// This function is used to add all the stations that are present on or after the given NODE
// This function takes in the current end of list and finally returns the final end
listOfObjects<string> *Trie::allstation(TrieNode *current, listOfObjects<string> *currentend,listOfObjects<string> *origihead)
{
  if (current == NULL)
  { // If the NODE is itself NULL then list is unaffected.
    return currentend;
  }
  // Else This node appends some stations to list.
  listOfObjects<int> *currIndices = current->indices; // Indices present in currentNode
  listOfObjects<string> *copy = currentend;           // Copy of currentend

  while (currIndices != NULL)
  { 
    if(!(isPresentInCompletions(origihead,nameDict->getKeyAtIndex(currIndices->object)))){
      //Adding only when it is not present in completions
      copy->next = new listOfObjects<string>(nameDict->getKeyAtIndex(currIndices->object));
      copy = copy->next;
      currIndices = currIndices->next;
    }
    else{
      currIndices = currIndices->next;
      // continue;
    }
  }
  if (current->numNonNullBranches == 0)
  {
    return copy; // Return the last if it is the final element in the trie.
  }
  else
  {
    for (int i = 0; i < NUM_CHARS; i++) // For each branch of this node recursively apply the function
    {
      copy = allstation(current->branch[i],copy,origihead); //Recursively calling the function to the end of each list
    }
  }
  return copy;
}

listOfObjects<string> *Trie::completions(string prefix)
{
  TrieNode *currNode = root; // given the trie we need to find all the stations which have this word.
  int len = prefix.length();
  listOfObjects<string> *currCompletions = new listOfObjects<string>("_#*."); // A list of station names.
  // Initialising the lists first element by a dummy variable.
  for (int i = 0; i < len; i++)
  {
    int letter = toupper(prefix.at(i)) - 'A';
    // Index of the letter to be found
    if (currNode->branch[letter] == nullptr) // If the prefix is not present return NULL
    {
      return NULL; // When the prefix itself is not present in the list.
    }
    currNode = currNode->branch[letter];
  }
  // Finally we arrive at the node of trie on and after which we need to find
  // All the station names.
  listOfObjects<string> *orighead = currCompletions;
  allstation(currNode, currCompletions, orighead);
  currCompletions = currCompletions->next; // Since the first one was Dummy hence assign the next.
  return currCompletions;
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
