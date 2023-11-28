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
  for (int i = 0; i < len; i++)
  {
    int s = toupper(wordInName[i]) - 65;
    if (currNode->branch[s] == nullptr) // creating nodes
    {
      TrieNode *x = new TrieNode();
      currNode->branch[s] = x;
      currNode->numNonNullBranches++;
    }
    currNode = currNode->branch[s];
  }
  currNode->isWord = true; // making isword to be true
  listOfObjects<int> *lis = currNode->indices;
  if (lis == nullptr)
  {
    currNode->indices = new listOfObjects<int>(indexOfName); // pointing it to the newly created linked-list if it;s empty initialy
  }
  else
  {
    currNode->indices = new listOfObjects<int>(indexOfName); // adding at the front because it's easy and time effficient
    currNode->indices->next = lis;
  }
  return true;
}

bool Trie::del(string wordInName, string name)
{
  TrieNode *currNode = root;
  TrieNode *lastBranchNode = root;
  int lastBranchChar = -1;
  int len = wordInName.length();
  // if(currNode->numNonNullBranches >1){
  //   lastBranchChar = 0;
  //   lastBranchNode = root;
  // }
  // Insert your code here
  for (int i = 0; i < len; i++)
  {
    if (currNode->numNonNullBranches > 1) // storing the lastbranchnode and lastbranchchar because it's required while deleting a word
    {
      lastBranchChar = i;
      lastBranchNode = currNode;
    }
    if (currNode->isWord == true) // we should'nt delete this too!
    {
      lastBranchChar = i;
      lastBranchNode = currNode;
    }

    int s = toupper(wordInName[i]) - 65;
    //  if(currNode->branch[s] == nullptr){
    //   return false;
    //  }

    currNode = currNode->branch[s]; // getting to the last node
  }
  listOfObjects<int> *lis = currNode->indices->next; // it is the pointer next to the linked list of currentnode

  while (true)
  {
    if (lis == nullptr) // if this is null our linked list after deletion becomes empty
    {
      if (nameDict->getKeyAtIndex(currNode->indices->object) == name)
      {
        currNode->indices = lis;
        currNode->isWord = false; // set it to false because now the word does'nt exist
      }
      break;
    }
    else
    {
      if (nameDict->getKeyAtIndex(currNode->indices->object) == name) // searching for the string and deleting it
      {
        currNode->indices = lis;
        break;
      }
      else if (nameDict->getKeyAtIndex(lis->object) == name)
      {
        currNode->indices->next = lis->next;
        break;
      }
      else
      {
        currNode->indices = lis;
        lis = lis->next;
      }
    }
  }
  if (currNode->isWord == false) // now the word has to be deleted if it does'nt contain anything below it
  {
    if (currNode->numNonNullBranches == 0)
    {
      if (lastBranchChar == -1) // deleting right from the root
      {
        int s = toupper(wordInName[0]) - 65;
        root->numNonNullBranches --;
        recursiveDelete(root->branch[s]);
        
        root->branch[s] = nullptr;
      }
      else // deleting from the last node , now storing the last node becomes handy for us
      {
        int s = toupper(wordInName[lastBranchChar]) - 65;
        lastBranchNode->numNonNullBranches --;
        recursiveDelete(lastBranchNode->branch[s]);
        lastBranchNode->branch[s] = nullptr;
      }
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
  for (int i = 0; i < len; i++) // getting to the node
  {
    int s = toupper(prefix[i]) - 65;
    currNode = currNode->branch[s];
  }
  recursiveAddCompletions(currNode, currCompletions); // calling recursiveAddCompletions to complete it
  // if(currNode->isWord == true){
  //   currCompletions
  // }

  return currCompletions;
}

bool Trie::recursiveAddCompletions(TrieNode *node, listOfObjects<string> *&currCompletions) // passing by reference to chase listofobjects
{
  if (node->isWord) // when we reach node having word we call addCompletions to change it
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
  listOfObjects<int> *ky = node->indices; // noting that it is always called when node has a string inside it
  while (ky != nullptr)
  {
    bool found = false;
    string s = nameDict->getKeyAtIndex(ky->object); // just storing that string into listofobjects
    listOfObjects<string> *y = new listOfObjects<string>(s);
    listOfObjects<string> *z = currCompletions;
    // while(z!=nullptr){ this is a commented out snippet of code for which if a string has matching prefixes for some word it would complete it once , but it increases time complexity by large extent so I commentes it out
    //   if(z->object == s){
    //     found =true;
    //     break;
    //   }
    //   z=z->next;
    // }
    // if(found){
    //   ky=ky->next;
    //   continue;
    // }
    // z=currCompletions;
    currCompletions = y;
    currCompletions->next = z;
    ky = ky->next;
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

