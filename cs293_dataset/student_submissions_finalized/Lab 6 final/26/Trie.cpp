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
/*
We start with root and calulate the index of the next branch using ascii code of letters . If the branch is null, we create a new node and insert it otherwise we move forward.
After reaching the last letter, we make the isWord of that branch true and insert the index of name in the indices list of that node.

*/
bool Trie::insert(string wordInName, int indexOfName)
{
  TrieNode *currNode = root;
  int len = wordInName.length();
  TrieNode *newNode;
  for (int i = 0; i < len; i++)
  {
    int index = toupper(wordInName[i]) - 'A';
    if(index<0 && index>26){
      return false;
    }

    if (currNode->branch[index] == nullptr)
    {

      currNode->branch[index] = new TrieNode();
      currNode->numNonNullBranches++;
    }
    currNode = currNode->branch[index];
  }
  currNode->isWord = true;
  listOfObjects<int> *l = currNode->indices;
  listOfObjects<int> *p = nullptr;
  while (l != nullptr)
  {
    p = l;
    l = l->next;
  }
  listOfObjects<int> *n;
  n = new listOfObjects<int>(-1);
  l = n;
  l->object = indexOfName;
  if (p == nullptr)
  {
    currNode->indices = n;
  }
  else
  {
    l = n;
    p->next = l;
  }

  // Insert your code here

  return true;
}
/*
WE RECURSIVE GO DOWN THE TRIE TILL THE LAST ELEMENT. IF ITS ISWORD IS FALSE WE DELETE THE NODE AND RECURSIVELY COME UP DELETING THE NODE IF ITS ALL BRANCHES ARE NULL.
*/
void Trie::remove(TrieNode *node, string key, TrieNode *p, int index, int depth = 0)
{
  // If tree is empty
  if (node == nullptr)
  {

    return;
  }

  // If last character of key is being processed
  if (depth == key.size())
  {

    // This node is no more end of word after
    // removal of given key
    
    if (!node->isWord)
    {
      
      // If given is not prefix of any other word
      int flag = 0;
      for (int i = 0; i < 26; i++)
      {
        if (node->branch[i] != nullptr)
          flag = 1;
      }
      
      if (flag == 0)
      {

        recursiveDelete(node);
        p->branch[index] = nullptr;
      }
    }
  }
  // If not last character, recur for the child
  // obtained using ASCII value
  else
  {
    
    int in = toupper(key[depth]) - 'A';
    remove(node->branch[in], key, node, in, depth + 1);
    
    // If node does not have any child (its only child got
    // deleted), and it is not end of another word.
    if (node != root)
    {
      int check = 0;
      for (int i = 0; i < 26; i++)
      {
        if (node->branch[i] != nullptr)
        {
          
          check = 1;
        }
      }
      
      if (check == 0 && node->isWord == false)
      {
        
        recursiveDelete(node);
        
        p->branch[index] = nullptr;
      }
    }
    else
    {
    }
  }
}
/*
WE TRAVERSE DOWN THE ROOT USING THE ASCII CODE OF LETTER. IF WE FOUND THAT A PARTICULAR BRANCH IS NULL, WE RETURN FALSE, OTHERWISE WE CONTINUE TILL THE  LAST LETTER.
AFTER REACHING THAT LETTER WE CHECK IF ITS ISWORD IS TRUE OR NOT. WE THEN DELETE THAT INDEX FROM THE INDICES LIST AND MOVE UP THE REST OF THE INDICES UP THE LIST
AFTER THAT WE CALL THE REMOVE FUNCTION
*/
bool Trie::del(string wordInName, string name)
{
  TrieNode *currNode = root;
  TrieNode *lastBranchNode = nullptr;
  int lastBranchChar = -1;
  int len = wordInName.length();
  int depth = 0;
  int check = 0;
  while (check == 0)
  {
    int index = toupper(wordInName[depth]) - 'A';
    if (!currNode)
    {
      return false;
    }
    // If last character of key is being processed
    if (depth == len)
    {
      // This node is no more end of word after
      // removal of given key
      if (!currNode->isWord)
      {
        return false;
      }
      else
      {
        listOfObjects<int> *ind = currNode->indices;
        int flag = 0;
        int c = 0;
        int d = 0;
        int count=0;
        while (ind != nullptr)
        {
          if (nameDict->getKeyAtIndex(ind->object) == name)
          {
            flag = 1;
           
          }
          if (flag == 1)
          {
            if (ind->next != nullptr)
            {
             
              ind->object = ind->next->object;
              d = 1;

              if (ind->next->next == nullptr)
              {
                
                c = 1;
                ind->next = nullptr;
                break;
              }
            }
            else
            {
             
              c = 1;
              ind = nullptr;
              break;
            }
          }
          ind = ind->next;
          count++;
        }
       
        if (c == 1 && d == 0 && count==0)
        {

          currNode->isWord = false;
        }
      }
      check = 1;

      // If given is not prefix of any other word
    }

    // If not last character, recur for the child
    // obtained using ASCII value
    else
    {
      if (currNode->branch[index] == nullptr)
      {
        return false;
      }
      depth++;
      lastBranchChar = index;
      lastBranchNode = currNode;
      currNode = currNode->branch[index];
    }

    
  }
  TrieNode *current = root;
  TrieNode *p = nullptr;
  
  remove(current, wordInName, p, -1, 0);
  return true;
}
/*
SIMILAR TO DEL, WE GO TODAY THE LAST LETTER OF THE PREFIX AND THEN CALL RESURSIVE ADD COMPLETIONS ON THAT NODE. IF THE ANY BRANCH FOUND IS NULL THEN WE RETURN EMPTY CURRCOMLPLETIONS.
*/
listOfObjects<string> *Trie::completions(string prefix)
{
  TrieNode *currNode = root;
  int len = prefix.length();
  listOfObjects<string> *currCompletions;
  currCompletions = new listOfObjects<string>(" ");
  int i = 0;
  while (currNode != nullptr && i < len)
  {
    
    int letter = toupper(prefix.at(i)) - 'A';
    if (i == len)
    {
      break;
    }
    i++;
    currNode = currNode->branch[letter];
  }
  if (i == len && currNode!=nullptr)
  {
    if (!recursiveAddCompletions(currNode, currCompletions))
    {
    }
  }
  // Insert your code here
  if(currCompletions->object==" "){
    currCompletions=nullptr;
  }
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
/*
WE FIND THE FIRST EMPTY POSITION IN THE CURRCOMPLETIONS. IF IT HAS AN DUMMY ENTRY(INSERTING THE FIRST ENTRY) WE UPDATE IT AND THEN CONTINUE NORMALLY.
AFTER FINDING IT WE GO THROUGH THE NODE'S INDICES LIST AND COPY ITS VALUE INTO IT.
*/
bool Trie::addCompletions(TrieNode *node, listOfObjects<string> *currCompletions)
{
  listOfObjects<string> *p = nullptr;
  listOfObjects<int> *l = node->indices;

  while (currCompletions != nullptr)
  {
    if (currCompletions != nullptr && currCompletions->object == " ")
    {
      currCompletions->object = nameDict->getKeyAtIndex(l->object);
      l = l->next;
    }
    p = currCompletions;
    currCompletions = currCompletions->next;
  }
  while (l != nullptr)
  {
    listOfObjects<string> *n;
    n = new listOfObjects<string>(nameDict->getKeyAtIndex(l->object));
    currCompletions = n;
    p->next = currCompletions;
    p=currCompletions;
    currCompletions = currCompletions->next;
    l = l->next;
  }
  // Insert your code here
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
