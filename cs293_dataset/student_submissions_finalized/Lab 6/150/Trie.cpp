#include <vector>
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
  Entry<int> a;
  a.key = wordInName;
  TrieNode *currNode = root;
  int len = wordInName.length();
  vector<string> names;
  string word = "";
  for (int i = 0; i < len; i++)
  {
    if (wordInName[i] != ' ')
    {
      word += wordInName[i];
    }
    else
    {
      names.push_back(word);
      word = "";
    }
  }
  if (word != "")
  {
    names.push_back(word);
  }
  for (int j = 0; j < names.size(); j++)
  {
    for (int i = 0; i < names[j].length(); i++)
    {
      int letter = toupper(names[j].at(i)) - 'A';
      if (currNode->branch[letter] != nullptr)
      {
        currNode = currNode->branch[letter];
      }
      else
      {
        currNode->branch[letter] = new TrieNode();
        currNode = currNode->branch[letter];
      }

      if (j == names[j].length() - 1)
      {
        currNode->isWord = true;
        currNode->indices->next = new listOfObjects<int>(indexOfName);
      }
      // Insert your code here

      return true;
    }
  }
}

bool Trie::del(string wordInName, string name)
{
  TrieNode *currNode = root;
  TrieNode *lastBranchNode = nullptr;
  int lastBranchChar = -1;
  int len = wordInName.length();
  return false;
}



listOfObjects<string>* Trie::completions(string prefix) {
  TrieNode *currNode = root;
  int len = prefix.length();
  listOfObjects<string> *currCompletions = nullptr;
    for (int i = 0; i < len; i++)
    {
      int letter = toupper(prefix.at(i)) - 'A';
      if (currNode->branch[letter] != nullptr)
      {
         currNode = currNode->branch[letter];
      }
      else
      {
        return nullptr;
      }
       if (i == prefix.length() - 1)
      {
        while (currNode->indices == nullptr)
        {
        currCompletions = new listOfObjects();
        }
      }
  // Insert your code here
  return currCompletions;
}
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

#endif
