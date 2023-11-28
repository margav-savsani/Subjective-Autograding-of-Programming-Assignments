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
  char Word[len];

  for (int i = 0; i < len; i++)
  {
    Word[i] = (char)toupper(wordInName[i]); //Convert word to upper case
  }

  for (int i = 0;i < len; i++)
  {
    int index = (int(Word[i]) - 65);//Calculate index of a word

    if (currNode->branch[index] == nullptr)
    {
      TrieNode * newnode=new TrieNode();
      currNode->branch[index]=newnode;
      currNode->numNonNullBranches++; //Increase number of branches of currNode by 1
    }
    currNode = currNode->branch[index];
  }

  currNode->isWord=true;

  if(currNode->indices != nullptr)
  {
    listOfObjects<int> *curr;
    curr=currNode->indices;

    while(curr->next != nullptr)
    {// Keep moving to next of the current node
      curr=curr->next;
    }

    curr->next=new listOfObjects<int>(indexOfName);
  }

  else
  {
    currNode->indices = new listOfObjects<int>(indexOfName);
  }
  // Insert your code here
  return true;
}

bool Trie::del(string wordInName, string name) 
{
  TrieNode *currNode = root;
  TrieNode *lastBranchNode = nullptr;
  int lastBranchChar = -1;
  int len = wordInName.length();
  char Word[len];

  for (int i=0;i<len;i++)
  { //Convert word to upper case
    Word[i] = (char)toupper(wordInName[i]);
  }

  int i=0;
  int index=(int(Word[i]-65)); //Calculate index of word

  while (currNode->branch[index] != nullptr && i<len)
  {
    if(currNode->numNonNullBranches>1 || currNode->isWord)
    {
      lastBranchNode = currNode;
      lastBranchChar = index;
    }

    currNode = currNode->branch[index];
    i++;

    if(i < len)
    {
      index = (int(Word[i])-65);
    }
  }

  bool noindex = false;
  if(i == len)
  {
    if(currNode->indices != nullptr)
    {
      listOfObjects<int> *curr;
      curr=currNode->indices;
      if(!(name != nameDict->getKeyAtIndex(curr->object)))
      {
        if(curr->next == nullptr)
        {
          currNode->indices = nullptr;
          noindex = true;
        }

        else
        {
          currNode->indices = curr->next;
          curr = curr->next;
        }
      }
      else
      {
        while (curr->next != nullptr && name != nameDict->getKeyAtIndex(curr->next->object))
        {
          curr = curr->next;
        }

        if(curr->next!=nullptr)
        {
          if(curr->next->next == nullptr)
          {
            curr->next = nullptr;
          }

          else
          {
            curr->next = curr->next->next;
          }
        }
      }
    }
  }

  if(noindex)
  {
    TrieNode *currNode = lastBranchNode;
    currNode->branch[lastBranchChar] = nullptr;
  }
  // Insert your code here
  return true;
}

listOfObjects<string> * Trie::completions(string prefix) 
{
  TrieNode *currNode = root;
  int len = prefix.length();
  char Word[len];

  for (int i=0;i<len;i++)
  {
    Word[i] = (char)toupper(prefix[i]);
  }

  listOfObjects<string> *currCompletions = nullptr;
  int i = 0;
  int index = (int(Word[i])-65);

  while(currNode->branch[index] != nullptr && i<len)
  {
    currNode = currNode->branch[index];
    i++;

    if(i<len)
    {
      index = (int(Word[i])-65);
    }
  }

  if (i == len)
  {
    recursiveAddCompletions(currNode,currCompletions);
  }


  // Insert your code here
  return currCompletions;
   
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
  TrieNode *currNode=node;
  if (currCompletions == nullptr)
  {
    if(currNode->indices != nullptr)
    {
      listOfObjects<int> *curr;
      curr = currNode->indices;
      currCompletions=new listOfObjects<string>(nameDict->getKeyAtIndex(curr->object));

      while (curr->next!=nullptr)
      {
        curr = curr->next;
        currCompletions->next = new listOfObjects<string>(nameDict->getKeyAtIndex(curr->object));
        currCompletions = currCompletions->next;
      } 
    }
    return true;
  }

  else
  {
    if(currNode->indices != nullptr)
    {
      listOfObjects<int> *curr;
      curr = currNode->indices;
      currCompletions->next = new listOfObjects<string>(nameDict->getKeyAtIndex(curr->object));

      while(curr->next!=nullptr)
      {
        curr = curr->next;
        currCompletions->next = new listOfObjects<string>(nameDict->getKeyAtIndex(curr->object));
        currCompletions = currCompletions->next;
      }
    }
    return true;
  }
  // Insert your code here
  return false;
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

  for (int i = 0; i < len; i++) {
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

void Trie::recursivePrintTrie(TrieNode *node, const string& prefix, int branchId, bool siblingsToRight)
{
  if (node != nullptr) {
    cout << prefix;
    
    cout << ((branchId == 0) ? "|-" : (branchId == -1)? " *":"|_" ) << (char) ((branchId != -1) ? 'A'+branchId: '*');
    cout << ((branchId == 0) ? '-' : (branchId == -1) ? '*':'_');
    
    // If this trie node has isWord set to true, print "(isWord)" and
    // also the list of complete station names (accessed through indices
    // in nameDict) associated with this trie node.
    if (node->isWord) 
    {
      cout << "(isWord)";
      listOfObjects<int> *currIndices = node->indices;
      while (currIndices != nullptr) 
      {
	        cout << endl << prefix << "     " << nameDict->getKeyAtIndex(currIndices->object);
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
      for (int j = i+1; j < NUM_CHARS; j++) 
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
