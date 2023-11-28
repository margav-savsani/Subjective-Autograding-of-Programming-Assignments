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
  TrieNode* currNode = root;
  int len = wordInName.length();
  int word_index = 0;

  while((word_index < len) && (currNode -> branch[tolower(wordInName.at(word_index))-'a'] != nullptr)) {currNode = currNode -> branch[tolower(wordInName.at(word_index++))-'a'];}

  while (word_index < len) {
    currNode -> numNonNullBranches++;
    currNode -> branch[(int)tolower(wordInName.at(word_index))-'a'] = new TrieNode;
    currNode = currNode -> branch[(int)tolower(wordInName.at(word_index++))-'a'];
  }

  currNode -> isWord = true;
  listOfObjects<int>* tmp = currNode -> indices;

  if (tmp == nullptr) {currNode -> indices = new listOfObjects<int>(indexOfName); return true;}
  else{
    while (tmp -> next != nullptr) tmp = tmp -> next;
    tmp -> next = new listOfObjects<int>(indexOfName);
    return true;
  }
  return false;
}

bool Trie::del(string wordInName, string name) {
   
  TrieNode* currNode = root;
  TrieNode* lastBranchNode = nullptr;
  int lastBranchChar = tolower(wordInName.at(0))-'a';
  int len = wordInName.length();
  int word_index = 0;

  while ((word_index < len)){
    currNode = currNode -> branch[tolower(wordInName.at(word_index++))-'a'];
    if ((currNode -> numNonNullBranches > 1) && (word_index < len)) {lastBranchNode = currNode; lastBranchChar = tolower(wordInName.at(word_index))-'a';}
  }

  if (!currNode -> isWord) return false;

  if (currNode -> numNonNullBranches > 0){

    listOfObjects<int>* lst = currNode -> indices;
    if (nameDict -> getKeyAtIndex(lst -> object) == name) {lst = lst -> next; return true;}

    else{

      listOfObjects<int>* parent = lst;
      listOfObjects<int>* current = nullptr;
      listOfObjects<int>* current_next = nullptr;

      if (lst != nullptr) current = lst -> next;
      if (current != nullptr) current_next = current -> next;

      while (current != nullptr){
        if (nameDict -> getKeyAtIndex(current -> object) == name){
          parent -> next = current_next;
          delete current;
          if (currNode -> indices == nullptr) currNode -> isWord = false;
          return true;
        }
        else{
          parent = parent -> next;
          current = current -> next;
          if (current_next != nullptr) current_next = current_next -> next;
        }
      }


    }
  } 

  else {
    if (lastBranchNode == nullptr) {recursiveDelete(root -> branch[lastBranchChar]); root -> branch[lastBranchChar] = nullptr; return true;}

    else{
      lastBranchNode -> numNonNullBranches--;
      recursiveDelete(lastBranchNode -> branch[lastBranchChar]); 
      lastBranchNode -> branch[lastBranchChar] = nullptr;
      return true;
    }
  }  
  return false;
}

listOfObjects<string> * Trie::completions(string prefix) {
  TrieNode* currNode = root;
  int len = prefix.length();
  listOfObjects<string>* currCompletions = nullptr;

  int prefix_index = 0;

  while (prefix_index < len){
    if (currNode -> branch[tolower(prefix.at(prefix_index))-'a'] == nullptr) {return nullptr;}
    currNode = currNode -> branch[tolower(prefix.at(prefix_index++))-'a'];
  }

  recursiveAddCompletions(currNode,currCompletions);
  return currCompletions;
  
}

bool Trie::recursiveAddCompletions(TrieNode *node, listOfObjects<string>* &currCompletions) {
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

bool Trie::addCompletions(TrieNode* node, listOfObjects<string>* &currCompletions) {
  listOfObjects<int>* index_list_element = node -> indices;

  while(index_list_element != nullptr)
  {
    listOfObjects<string>* string_to_add = new listOfObjects<string>(nameDict -> getKeyAtIndex(index_list_element -> object));
    string_to_add -> next = currCompletions;
    currCompletions = string_to_add;

    index_list_element = index_list_element -> next;
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
    
    cout << ((branchId == 0) ? "|-" : (branchId == -1)? " *":"|_" ) << (char) ((branchId != -1) ? 'A'+branchId: '*');
    cout << ((branchId == 0) ? '-' : (branchId == -1) ? '*':'_');
    
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
      for (int j = i+1; j < NUM_CHARS; j++) {
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
