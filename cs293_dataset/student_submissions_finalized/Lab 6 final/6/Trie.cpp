//1879
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
  // cout<<wordInName<<endl;
  for(int i=0; i<len; i++)
  {
    int low = toupper(wordInName[i]) - 'A';
    if(currNode->branch[low] == nullptr)
    {
      currNode->branch[low] = new TrieNode();
      (currNode->numNonNullBranches) ++;
      // cout<<wordInName<<" "<<wordInName[i]<<" "<<currNode->numNonNullBranches<<endl;     
    }
    currNode = currNode->branch[low];
    
  }
  currNode->isWord = true;
  listOfObjects<int> *node = new listOfObjects<int>(indexOfName);
  listOfObjects<int> *temp_indices = currNode->indices;
  currNode->indices = node;
  node->next = temp_indices;
  
  // Insert your code here

  return true;
}

bool Trie::del(string wordInName, string name)
{
  
  TrieNode *currNode = root;
  TrieNode *lastBranchNode = nullptr;
  int lastBranchChar = -1;
  int len = wordInName.length();
  for (int i = 0; i < len; i++)
  {
    int letter = toupper(wordInName.at(i)) - 'A';
    // cout<<letter<<endl;
    if (currNode->branch[letter] == nullptr)
    {
      return false;
    }
    int no = currNode->numNonNullBranches; 
    // cout<<"No is "<<no<<endl;
    // cout<<"Letter of prefix is "<<currNode->branch[letter]<<" "<<letter<<endl;
    
    if(no > 1)
    {
      lastBranchNode = currNode;
      //cout<<"root is "<<root<<endl;
      //cout<<"lastBranchNode ASSIGNED "<<lastBranchNode<<endl;
      lastBranchChar = letter;
    }

    currNode = currNode->branch[letter];

  }
  listOfObjects<int> *ind = currNode->indices;
  //cout<<"currNode->indices "<<currNode->indices<<endl;
  if((ind!=nullptr) && (name == nameDict->getKeyAtIndex(ind->object)))
  {
    currNode->indices = ind->next;
    if(currNode->indices == nullptr)
    {
      //cout<<"lastBranchNode to delete "<<lastBranchNode<<endl;
      recursiveDelete(lastBranchNode->branch[lastBranchChar]);
      lastBranchNode->branch[lastBranchChar]  = nullptr;

    }
  }
  else
  {
    while(ind!=nullptr)
    {
    // Insert your code here
      //cout<<"String is "<<nameDict->getKeyAtIndex(ind->object)<<endl;
      if ((ind->next!=nullptr) && (name == nameDict->getKeyAtIndex(ind->next->object)))
      {
        //cout<<name<<" name"<<endl;
        ind->next = ind->next->next;
        break;
      }
      ind = ind->next;
    }
  }
  
  // Insert your code here
  return true;
  
}

listOfObjects<string> *Trie::completions(string prefix)
{
  TrieNode *currNode = root;
  int len = prefix.length();
  listOfObjects<string> *currCompletions = nullptr;
  //cout<<"abcd "<<endl;
  for (int i = 0; i < len; i++)
  {
    int letter = toupper(prefix.at(i)) - 'A';
    //cout<<i<<endl;
    if (currNode->branch[letter] == nullptr)
    {
      return nullptr;
    }
    //cout<<"Letter of prefix is "<<currNode->branch[letter]<<" "<<letter<<endl;
    currNode = currNode->branch[letter];
  }
  //cout<<"CURRnODE "<<currNode<<endl;
  recursiveAddCompletions(currNode,currCompletions);
  //cout<<currCompletions<<endl;
  // Insert your code here
  return currCompletions;
}

bool Trie::recursiveAddCompletions(TrieNode *node, listOfObjects<string>* &currCompletions)
{
  //cout<<"address of node"<<node<<" "<<node->numNonNullBranches<<endl;
  if(node->isWord)
  {
    bool x = addCompletions(node, currCompletions);
    //cout<<"value of x "<<x<<endl;
  }
  for (int i = 0; i < NUM_CHARS; i++)
  {
    if (node->branch[i] != nullptr)
    {
      bool y = recursiveAddCompletions(node->branch[i], currCompletions);
      //cout<<"value of y "<<y<<endl;
    }
  }

  return true;
}
void Trie::print_comp(listOfObjects<string>* &currCompletions)
{
  //cout<<endl;
  listOfObjects<string> *curr = currCompletions;
  while(curr!=nullptr)
  {
    //cout<<"address of curr-object "<<curr->object<<endl;
    curr = curr->next;
  }
  //cout<<endl;
}
bool Trie::addCompletions(TrieNode *node, listOfObjects<string>* &currCompletions)
{
  listOfObjects<int> *ind = node->indices;
  //cout<<"ind ka object "<<ind->object<<endl;
  //cout<<ind<<endl;
  while(ind!=nullptr)
  {
  // Insert your code here
    //cout<<"String is "<<nameDict->getKeyAtIndex(ind->object)<<endl;
    listOfObjects<string> *node = new listOfObjects<string>(nameDict->getKeyAtIndex(ind->object));
    listOfObjects<string> *curr = currCompletions;
    //cout<<"comp is "<<curr<<endl;
    listOfObjects<string> *temp_currCompletions = currCompletions;
    currCompletions = node;
    node->next = temp_currCompletions;
    //print_comp(currCompletions);
    //cout<<"ind ka object in while "<<ind->object<<endl;
    ind = ind->next;
    
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
