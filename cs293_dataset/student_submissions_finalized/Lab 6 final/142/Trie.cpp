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

Trie::Trie(Dictionary<int> *nameToIndex) {
  nameDict = nameToIndex;
  root = new TrieNode();
  if (root == nullptr) {
    cout << "Memory allocation failure." << endl;
    exit(-1);
  }
}

Trie::~Trie() {
  recursiveDelete(root);
}

void Trie::recursiveDelete(TrieNode *node) {
  if (node == nullptr) {
    return;
  }
  else {
    for (int i = 0; i < NUM_CHARS; i++) {
      TrieNode *currNode = node->branch[i];
      recursiveDelete(currNode);
      node->branch[i] = nullptr;
    }
    if (node != root) {
      delete node;
    }
    return;
  }
}

bool Trie::insert(string wordInName, int indexOfName) {
  TrieNode *currNode = root;
  int len = wordInName.length();
  // Insert your code here
  for(int i = 0; i <= len; i++)
  {
    if(i == len)
    {
      listOfObjects<int> *new_node = new listOfObjects<int>(indexOfName);
      listOfObjects<int> *temp = currNode->indices;
      currNode->indices = new_node;
      new_node->next = temp;
      currNode->isWord = true;
      return true;
    }
    int ascii_code = (int)wordInName[i];
    currNode->numNonNullBranches++;
    
    if(currNode->branch[ascii_code-'A']==nullptr)
    {
      TrieNode *new_node = new TrieNode();
      currNode->branch[ascii_code-'A'] = new_node;
      currNode = new_node;
      continue;
    }
    else
    {
      currNode = (currNode->branch)[ascii_code-'A'];
      continue;
    }
  }
  return false;
}

bool Trie::del(string wordInName, string name) {

  TrieNode *currNode = root;
  TrieNode *lastBranchNode = nullptr;
  int lastBranchChar = -1;
  int len = wordInName.length();

  // Insert your code here
  // for(int i = 0; i < len; i++)
  // {
  //   if(i==len-1)
  //   {
  //     currNode->branch[i]=lastBranchNode;
  //     break;
  //   }
  //   int ascii_code = (int)wordInName[i];
  //   currNode = currNode->branch[ascii_code-'A'];
  // }
  // for(int i = 0; i < len; i++)
  // {
  //   int ascii_code = (int)wordInName[i];
    
  //   if(currNode->branch[i]->numNonNullBranches > 1)
  //   {
  //     currNode->br
  //   }
  // }
  return false;
}

listOfObjects<string> *Trie::completions(string prefix) {
  TrieNode *currNode = root;
  int len = prefix.length();
  listOfObjects<string> *currCompletions = nullptr;

  // Insert your code here
  for(int i = 0; i < len; i++)
  {
    //int ascii_code = (int)prefix[i];
    int ascii_code = toupper(prefix.at(i)) - 'A';
    if(currNode->branch[ascii_code]== nullptr)
    {
      return nullptr;
    }
    currNode = currNode->branch[ascii_code];
  }
  recursiveAddCompletions(currNode,currCompletions);
  return currCompletions;
}
  
  //   if(currNode->isWord)
  //   {
  //     addCompletions(currNode,currCompletions);
  //     listOfObjects<string>    = new 
  //     currCompletions getkey->
  //     continue;
  //   }
  //   if(!(currNode->isWord))
  //   {

  //   }
  //   if(currNode->numNonNullBranches > 1)
  //   {
  //     recursiveAddCompletions(currNode,currCompletions);
  //     break;
  //   }
  //   if(currNode->branch[i]!=nullptr)
  //   {
  //     currNode = currNode->branch[i];
  //     continue;

  //     for(int j = 0; j < NUM_CHARS; j++)
  //     {
  //       if(prefix[i]==currNode->branch[j])
  //       {
  //         if(currNode->isWord)
  //         {
  //           currCompletions getkey->
  //         }
  //         else
  //         {
  //           recaddCompletions (currNode->branch[j], currCompletions);
  //         }
  //       }
  //     }
  //   }
    
  // }
  // // for (int i = 0; i < len; i++)
  // // {
  // //   int ascii_code = (int)wordInName[i];
  // //   currCompletions[i] = currNode->branch;
  // // }
  // return currCompletions;
  


bool Trie::recursiveAddCompletions(TrieNode *node, listOfObjects<string> *currCompletions) {
  if (node->isWord) {
    if (!addCompletions(node, currCompletions)) {
      return false;
    }
  }

  TrieNode *currNode = node;
  for (int i = 0; i < NUM_CHARS; i++) {
    if (currNode->branch[i] != nullptr) {
      if (!recursiveAddCompletions(currNode->branch[i], currCompletions)) {
	      return false;
      }
    }
  }

  return true;
}

bool Trie::addCompletions(TrieNode *node, listOfObjects<string> *currCompletions) {

  // Insert your code here
  listOfObjects<string> *names = new listOfObjects<string>(nameDict->getKeyAtIndex(node->indices->object));
  
  // listOfObjects<int> *x = indices;
    //listOfObjects<int> *new_node = new listOfObjects<int>(indexOfName);
  // x = node->indices;
  listOfObjects<string> *x = names;
  while(x != nullptr)
  {
    listOfObjects<string> *temp = currCompletions;
    currCompletions = x;
    currCompletions->next = temp;
    x = x->next;
  }
  
  return true;
  // if(currNode->isWord)
  //   {
  //     listOfObjects<int> *indices = new listOfObjects<int>(indices);
  //     continue;
  //   }
  //   else
  //   {

  //   }
  // if (node->isWord)
  // {
  //   if (!addCompletions(node, currCompletions)) 
  //   {
  //     return false;
  //   }
  // }

  // TrieNode *currNode = node;
  // for (int i = 0; i < NUM_CHARS; i++) 
  // {
  //   currNode = currNode->branch[i];
  //   if (currNode != nullptr) 
  //   {
  //     return false;
  //   }
  //   else
  //   {
  //     continue;
  //   }
  // }

  // return true;
}

bool Trie::isPresentInCompletions(listOfObjects<string> *completions, string name) {
  listOfObjects<string> *currCompletion = completions;
  bool isPresent = false;
  while (currCompletion != nullptr) {
    if (currCompletion->object == name) {
      isPresent = true;
      break;
    }
    currCompletion = currCompletion->next;
  }
  return isPresent;
}

void Trie::freeCompletionList(listOfObjects<string> *completions) {
  listOfObjects<string> *currCompl = completions;
  while (currCompl != nullptr) {
    listOfObjects<string> *toDeleteCompl = currCompl;
    currCompl = currCompl->next;
    delete toDeleteCompl;
  }
  return;
}

bool Trie::isPresent(string wordInName) {
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
