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

   
  for(int i = 0; i < len; i++) {
    int index = toupper(wordInName.at(i)) - 'A';
    currNode = currNode->branch[index];
    
    if (currNode == nullptr) {
      currNode = new TrieNode();
    }

    // termination condition. 

    if (i == len - 1){
      currNode->isWord = true;

      // add the indexOfName to the list of Objects iteratively. 
      listOfObjects<int> *currObj = currNode->indices;

      while (currObj->next != nullptr) {
        currObj = currObj->next;
      }

      // reached at the end of the listOfObjects. 
      currObj->next = new listOfObjects<int>(indexOfName);

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

  
  for (int i = 0; i < len; i++) {
    int index = toupper(wordInName.at(i)) - 'A';

    if (currNode->branch[index] == nullptr) {return false; } // word does not exist in the trie. 

    else { 
      currNode = currNode->branch[index];
    }

    if (i == len - 1) {
      // we have reached the "leaf"
      // now searching for the word. 

      // base case
      if (currNode->isWord == false) {return false; } 

      
      listOfObjects<int> *currObj = currNode->indices;
      // now running a loop until the word is found, or it does not exist. 

      while (currObj->next != nullptr) {
        currObj = currObj->next; 
        
        if (currObj->next->object == nameDict->get(name)->value) {
          // removing that name from the dictionary. 
          nameDict->remove(name);

          // removing the object from the linkedlist. 
          delete currObj->next; // deleting the next node. 

          currObj->next = currObj->next->next;
          break; 
        }
      }
    }
  }

  return false;
}

listOfObjects<string> * Trie::completions(string prefix) {
  TrieNode *currNode = root;
  int len = prefix.length();
  listOfObjects<string> *currCompletions = nullptr;

  // Insert your code here

  // prefix is searched, and all children containing isWord = true have all their linked lists printed. 

  for (int i = 0; i < len; i++) {
    int index = toupper(prefix.at(i)) - 'A';
    currNode = currNode->branch[index];
  } 

  // now we have the correct node from which we need to print. 
  // 1. search recursively in all child nodes. 
  // 2. If a node has isWord = true, search its linked list
  // 3. In that linkedlist, get the index and get the corresponding name from Dictionary<int>* nameDict. 
  // 4. To get the name iterate through Entry<T> using numfilled and concatenate key of all Entries to the string we want. 
  // 5. Once string is formed, insert it in the linkedlist
  // 6. Keep doing this till all nodes are exhausted. 

  for (int i = 0; i < NUM_CHARS; i++){
    TrieNode* newNode = currNode->branch[i];

    
  }
  
  return currCompletions;
  
}

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
  return false;
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


#endif
