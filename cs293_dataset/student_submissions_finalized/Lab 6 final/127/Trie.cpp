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
  char current_char;
  int char_index;

  for(int i=0; i<len; i++) {

    current_char=wordInName[i];
    char_index=current_char;

    if(char_index>=97 && char_index<=122) char_index=current_char-97;
    else if(char_index>=65 && current_char<=90) char_index=current_char-65;
    else char_index=0;

    if(currNode->branch[char_index]==nullptr) {
      TrieNode* newNode=new TrieNode();
      currNode->branch[char_index]=newNode;
      currNode->numNonNullBranches+=1;
    }

    currNode=currNode->branch[char_index];

  }

  currNode->isWord=true;

  if(currNode->indices==nullptr) {
    currNode->indices=new listOfObjects<int>(indexOfName);
    return true;
  }

  listOfObjects<int>* cur_indices=currNode->indices;

  while(cur_indices!=nullptr) {
    if(cur_indices->object==indexOfName) return false;
    
    if(cur_indices->next==nullptr) {
      listOfObjects<int>* new_indices=new listOfObjects<int>(indexOfName);
      cur_indices->next=new_indices;
      return true;
    }
    else cur_indices=cur_indices->next;
  }

  // Insert your code here

  return false;
}

bool Trie::del(string wordInName, string name) {
  TrieNode *currNode = root;
  TrieNode *lastBranchNode = nullptr;
  int lastBranchChar = -1;
  int len = wordInName.length();

  char current_char;
  int char_index;

  for(int i=0; i<len; i++) {

    current_char=wordInName[i];
    char_index=current_char;

    if(char_index>=97 && char_index<=122) char_index=current_char-97;
    else if(char_index>=65 && current_char<=90) char_index=current_char-65;
    else char_index=0;

    if(currNode->branch[char_index]==nullptr) {
      return false;
    }

    currNode=currNode->branch[char_index];

  }

  if(!currNode->isWord) return false;

  listOfObjects<int>* cur_indices = currNode->indices;

  if(cur_indices==nullptr) {
    if(nameDict->getKeyAtIndex(cur_indices->object)==name) {
      currNode->indices=nullptr;
      return true;
    }
  }

  while(cur_indices!=nullptr) {
    if(cur_indices->next==nullptr) return false;
    if(nameDict->getKeyAtIndex(cur_indices->next->object)==name) {
      cur_indices->next=cur_indices->next->next;
      return true;
    }
    cur_indices=cur_indices->next;

  }

  return false;

  // Insert your code here
  return false;
}

listOfObjects<string> * Trie::completions(string prefix) {
  TrieNode *currNode = root;
  int len = prefix.length();
  char current_char;
  int char_index;

  for(int j=0; j<len; j++) {

    current_char=prefix[j];
    char_index=current_char;

    if(char_index>=97 && char_index<=122) char_index=current_char-97;
    else if(char_index>=65 && current_char<=90) char_index=current_char-65;
    else char_index=0;

    if(currNode->branch[char_index]==nullptr) {
      return nullptr;
    }

    currNode=currNode->branch[char_index];

  }

  listOfObjects<string>* currCompletions=new listOfObjects<string>("");
  listOfObjects<string>* head=currCompletions;

  currCompletions=recursiveAddCompletions(currNode, currCompletions);

  currCompletions=head;

  if(currCompletions->next==nullptr) {
    head=nullptr;
  }
  
  while(currCompletions->next!=nullptr) {
    if((currCompletions->next)->object=="") {
      currCompletions->next=nullptr;
      break;
    }
    currCompletions=currCompletions->next;
  }

  

  // Insert your code here
  return head;
  
}

listOfObjects<string>* Trie::recursiveAddCompletions(TrieNode *node, listOfObjects<string> *currCompletions) {
  if (node->isWord) {
    currCompletions=addCompletions(node, currCompletions);
  }

  TrieNode *currNode = node;
  for (int i = 0; i < NUM_CHARS; i++) {
    if (currNode->branch[i] != nullptr) {
      currCompletions=recursiveAddCompletions(currNode->branch[i], currCompletions);
    }
  }

  return currCompletions;
}

listOfObjects<string>* Trie::addCompletions(TrieNode *node, listOfObjects<string> *currCompletions) {

  listOfObjects<int>* cur_indices = node->indices;
  listOfObjects<string>* new_completions;

  while(cur_indices!=nullptr) {
    currCompletions->object=nameDict->getKeyAtIndex(cur_indices->object);
    new_completions=new listOfObjects<string>("");
    currCompletions->next=new_completions;
    currCompletions=new_completions;

    cur_indices=cur_indices->next;

  }
  
  return currCompletions;



  // Insert your code here

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
