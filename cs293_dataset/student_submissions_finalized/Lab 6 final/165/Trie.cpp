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
  int index;
  for (int i = 0; i < len; i++)
  {

    if (currNode->branch[tolower(wordInName[i]) - 97] == nullptr)
    { // if the next letter is null

      currNode->branch[tolower(wordInName[i]) - 97] = new TrieNode(); // create a new trienode in that letter
      currNode->numNonNullBranches++;                                 // icrease number of non null branches
    }
    currNode = currNode->branch[tolower(wordInName[i]) - 97]; // move to the next letter
  }
  if (currNode->indices == nullptr)
  { // if linked list is being accessed for the first time
    currNode->indices = new listOfObjects<int>(indexOfName);
    currNode->isWord = true; // if end of word is reached
  }
  else
  {
    listOfObjects<int> *index = currNode->indices;
    while (index->next != nullptr)
    { // linked list is updated
      index = index->next;
    }
    index->next = new listOfObjects<int>(indexOfName); // new node in linked list created
  }

  return true;
}

bool Trie::del(string wordInName, string name)
{ 
  TrieNode *currNode = root;
  TrieNode *lastBranchNode = root;
  int lastBranchChar = tolower(wordInName[0]) - 97;
  int len = wordInName.length();
  if(!isPresent(wordInName)){//if wordInName is not present in trie
    return false;
  }
  // Insert your code here
  for (int i = 0; i < len; i++)
  {
    if (currNode->numNonNullBranches > 1)//setting the last branch node and last branch char
    {
      lastBranchNode = currNode;
      lastBranchChar = tolower(wordInName[i]) - 97;
    }
    else if (currNode->isWord == true)//setting the last branch node and last branch char
    {
      lastBranchNode = currNode;
      lastBranchChar = tolower(wordInName[i]) - 97;
    }
    currNode = currNode->branch[tolower(wordInName[i]) - 97];
  } // reached word ka last node
  if (currNode->isWord == false)
    return false;
  listOfObjects<int> *nodeindex = currNode->indices; // storing this currnode
  if ((nameDict->getKeyAtIndex(currNode->indices->object) == name))
  {
    currNode->indices = nodeindex->next;
    delete (nodeindex);
    if (currNode->indices == nullptr)//linked list is empty for this node
    {
      currNode->isWord = false;
    }
  }
  else
  {
    listOfObjects<int> *prev = nodeindex; // prev node
    nodeindex = nodeindex->next;
    while (nodeindex != nullptr)
    {
      if ((nameDict->getKeyAtIndex(nodeindex->object) == name))
      {
        prev->next = nodeindex->next; // removing element from linked list
        delete (nodeindex);
        break;
      }

      prev = nodeindex; // prev node
      nodeindex = nodeindex->next;
    }
  }
  if (currNode->indices == nullptr && currNode->numNonNullBranches == 0)
  {                                                       // no elements left in linked list and no c
    recursiveDelete(lastBranchNode->branch[lastBranchChar]); // delete entire node from last branch char
    lastBranchNode->branch[lastBranchChar] = nullptr;
    lastBranchNode->numNonNullBranches--;
  }

  return true;
}

listOfObjects<string> *Trie::completions(string prefix)
{
  
  TrieNode *currNode = root;
  listOfObjects<string> *currCompletions = new listOfObjects<string>("null");
  if(currNode == nullptr)
    return nullptr;
  // Insert your code here
  for (int i = 0; i < prefix.length(); i++)
  {
    if (currNode->branch[tolower(prefix[i]) - 97] == nullptr)//check if prefix is present
    {
      return nullptr;
    }
    currNode = currNode->branch[tolower(prefix[i]) - 97];
  }
  recursiveAddCompletions(currNode, currCompletions);//call completing function
  return currCompletions;//return list of completions
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

bool Trie::addCompletions(TrieNode *node, listOfObjects<string> *&currCompletions)
{

  // Insert your code here
  if (currCompletions->object == "null")//first time insertion
  {
    listOfObjects<int> *currIndex = node->indices;
    if(currIndex == nullptr)
      return true;
    currCompletions->object = nameDict->getKeyAtIndex(currIndex->object);//first object created
    listOfObjects<string> *current_node_of_currcompeltions = currCompletions;
    while (currIndex->next != nullptr)//loop over and enter into currcompletions
    {
      current_node_of_currcompeltions->next = new listOfObjects<string>(nameDict->getKeyAtIndex(currIndex->next->object));
      current_node_of_currcompeltions = current_node_of_currcompeltions->next;
      currIndex = currIndex->next;
    }
  }
  else
  {
    listOfObjects<string> *current_node_of_currcompeltions = currCompletions;
    listOfObjects<int> *currIndex = node->indices;
    if(currIndex == nullptr)
      return true;
    while(current_node_of_currcompeltions->next!=nullptr){//reach tail of currcompletions
      current_node_of_currcompeltions = current_node_of_currcompeltions->next;
    }
    current_node_of_currcompeltions->next = new listOfObjects<string>(nameDict->getKeyAtIndex(currIndex->object));//add first object
    current_node_of_currcompeltions = current_node_of_currcompeltions->next;
    while (currIndex->next != nullptr)
    {
      current_node_of_currcompeltions->next = new listOfObjects<string>(nameDict->getKeyAtIndex(currIndex->next->object));
      current_node_of_currcompeltions = current_node_of_currcompeltions->next;//add all next objects
      currIndex = currIndex->next;
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
