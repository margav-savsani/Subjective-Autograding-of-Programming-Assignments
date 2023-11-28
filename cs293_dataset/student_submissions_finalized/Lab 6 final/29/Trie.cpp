#ifndef TRIE_CPP
#define TRIE_CPP

#include <algorithm>
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
  // convert all to upper case
  transform(wordInName.begin(), wordInName.end(), wordInName.begin(), ::toupper);
  // find currect position
  for (int i = 0 ; i < len ; i++) {
    int index = (int)(wordInName[i] - 'A');
    if (currNode->branch[index] == nullptr) {
      (currNode->numNonNullBranches) ++;
      currNode->branch[index] = new TrieNode;
    }
    currNode = currNode->branch[index];
  }
  // currNode is a word now 
  currNode->isWord = true;
  listOfObjects<int> *newIndex = new listOfObjects<int> (indexOfName);
  listOfObjects<int> *Node = currNode->indices;
  // if no linkList exist, then create a new 
  if (Node == nullptr) currNode->indices = newIndex;
  else {
    // go to last pointer
    while (Node->next != nullptr) {
      if (Node->object == indexOfName) return false;
      Node = Node->next;
    }
    // add new node at the end
    Node->next = newIndex;
  }
  return true;
}

bool Trie::del(string wordInName, string name) {
  TrieNode *currNode = root;
  TrieNode *lastBranchNode = root;
  int branchId = (int)(wordInName[0] - 'A');
  int len = wordInName.length();
  // convert all to upper case
  transform(wordInName.begin(), wordInName.end(), wordInName.begin(), ::toupper);
  // find currect position
  for (int i = 0 ; i < len ; i++) {
    int index = (int)(wordInName[i] - 'A');
    if (currNode->branch[index] == nullptr) return false;
    if (currNode->numNonNullBranches > 1 or currNode->isWord) {
      lastBranchNode = currNode;
      branchId = index;
    }
    currNode = currNode->branch[index];
  }
  // delete the index
  listOfObjects<int> * currList = currNode->indices;
  listOfObjects<int> * parentList = currNode->indices;
  // find currect positon 
  while (nameDict->getKeyAtIndex(currList->object) != name) currList = currList->next;
  // shift all nodes
  while (currList->next != nullptr) {
    currList->object = currList->next->object;
    parentList = currList;
    currList = currList->next;
  }
  // if only one node present then delete that node
  if (currNode->indices->next == nullptr) {
    delete currNode->indices;
    currNode->indices = nullptr;
    currNode->isWord = false;
  }
  else {
    // delete last node
    delete parentList ->next;
    parentList->next = nullptr;
  }

  // update tree
  if (currNode->indices == nullptr and currNode->numNonNullBranches == 0) {
    recursiveDelete(lastBranchNode->branch[branchId]);
    lastBranchNode->branch[branchId] = nullptr;
    lastBranchNode->numNonNullBranches --;
  }
  return true;
}

listOfObjects<string> * Trie::completions(string prefix) {
  TrieNode *currNode = root;
  transform(prefix.begin(), prefix.end(), prefix.begin(), ::toupper);
  int len = prefix.length();
  listOfObjects<string> *currCompletions = nullptr;
  // go to currect position
  for (auto e : prefix)
  {
    if (currNode->branch[(int)(e - 'A')] == nullptr) return nullptr;
    currNode = currNode->branch[(int)(e - 'A')];
  }
  // recursiveAddCompletions
  recursiveAddCompletions(currNode, currCompletions);
  return currCompletions;

}

bool Trie::recursiveAddCompletions(TrieNode *node, listOfObjects<string> *&currCompletions) {
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

bool Trie::addCompletions(TrieNode *node, listOfObjects<string> *&currCompletions) {
  // if node is not word then return false
  if (! node->isWord) return false;
  listOfObjects<int> *currList = node->indices;
  // if currCompletions in null then create a new listOfObjects
  if (currCompletions == nullptr) {
    currCompletions = new listOfObjects<string> (nameDict->getKeyAtIndex(currList->object));
    currList = currList->next;
  }
  // go to the end of currCompletions
  listOfObjects<string> *endOfCompletions = currCompletions;
  while (endOfCompletions->next != nullptr) endOfCompletions = endOfCompletions->next;
  // store all words from dictionary
  while (currList != nullptr) {
    endOfCompletions->next = new listOfObjects<string> (nameDict->getKeyAtIndex(currList->object));
    endOfCompletions = endOfCompletions->next;
    currList = currList->next;
  }
  return true;
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

  for (int i = 0; i < len; i++) {
    int letter = toupper(wordInName.at(i)) - 'A';

    if (currNode->branch[letter] == nullptr) {
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

    cout << ((branchId == 0) ? "|-" : (branchId == -1) ? " *" : "|_" ) << (char) ((branchId != -1) ? 'A' + branchId : '*');
    cout << ((branchId == 0) ? '-' : (branchId == -1) ? '*' : '_');

    // If this trie node has isWord set to true, print "(isWord)" and
    // also the list of complete station names (accessed through indices
    // in nameDict) associated with this trie node.
    if (node->isWord) {
      cout << "(isWord)";
      listOfObjects<int> *currIndices = node->indices;
      while (currIndices != nullptr) {
        cout << endl << prefix << "     " << nameDict->getKeyAtIndex(currIndices->object);
        currIndices = currIndices->next;
      }
    }
    else {
      cout << "()";
    }
    cout << endl;
    for (int i = 0; i < NUM_CHARS; i++) {
      TrieNode *currNode = node->branch[i];
      bool childrenToRight = false;
      for (int j = i + 1; j < NUM_CHARS; j++) {
        if (node->branch[j] != nullptr) {
          childrenToRight = true;
          break;
        }
      }
      if (currNode != nullptr) {
        recursivePrintTrie(currNode, prefix + ((siblingsToRight) ? "│   " : "    "), i, childrenToRight);
      }
    }
  }
}
// End edit version 1

#endif
