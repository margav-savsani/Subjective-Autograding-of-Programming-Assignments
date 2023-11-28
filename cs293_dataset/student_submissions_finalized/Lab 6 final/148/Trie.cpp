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

int index(char c){
    if(!((c<='z' && c>='a') || (c <= 'Z' && c >= 'A'))){
      // Not alphabetical
      return 0; // Shouldnt happen ever but handle the case
    }
    return tolower(c)-'a'; // returns a number in 0 to 25
}
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

  for (int i = 0; i < len; i++) {
          if(currNode->branch[index(wordInName[i])] == nullptr){
                  // First time encountered this pattern, need to make a new node
                  currNode->branch[index(wordInName[i])] = new TrieNode();
                  currNode->branch[index(wordInName[i])]->parent = currNode;
                  currNode->numNonNullBranches += 1;
          }
          // Update currNode
          currNode = currNode->branch[index(wordInName[i])];
  }
  currNode->isWord = true;
  //Add indexOfName to the end of indices
    
 listOfObjects<int> *list = currNode->indices;
 // Traverse the linked list
 if (list == nullptr){
    currNode->indices = new listOfObjects<int>(indexOfName);
    return true;
 }
 while(list->next!=nullptr){
    list = list->next;
 } 
 // Append at the end
 list->next = new listOfObjects<int>(indexOfName);
  return true;
}

bool Trie::del(string wordInName, string name) {
  TrieNode *currNode = root;
  TrieNode *lastBranchNode = root;
  int lastBranchChar =index(wordInName[0]) ;
  int len = wordInName.length();

  // Insert your code here
  for (int i = 0; i < len; i++) {
        if(currNode->numNonNullBranches > 1 || currNode->isWord){
          // Present node is branched, update last branched node
          // Also update if currNode is a word, because say we input both "central" and "centrally", and then delete "centrally"
          lastBranchNode = currNode;
          lastBranchChar = index(wordInName[i]);
        }

        // move down the trie
        currNode = currNode->branch[index(wordInName[i])];
        if(currNode == nullptr){
                // Prefix not found :(
                return false;
        }
  }

  // The linked list associated with the last node
 listOfObjects<int> *list = currNode->indices;
 // Traverse the linked list
    if(nameDict->getKeyAtIndex(list->object) == name){
      // The first element was what we wanted. 
        currNode->indices = list->next;
        delete list;
        if(currNode->indices == nullptr){
          // Only need to test this case here, because this could only happen when the found element is the first element
          currNode->isWord = false;
        
          listOfObjects<string> *childrenCompletions = new listOfObjects<string>("");
          childrenCompletions = childrenCompletions->next;
          recursiveAddCompletions(currNode,childrenCompletions);
          if(childrenCompletions == nullptr){
            //No children
            recursiveDelete(lastBranchNode->branch[lastBranchChar]);
            lastBranchNode->branch[lastBranchChar] = nullptr;
            lastBranchNode->numNonNullBranches-=1;
          }
        }
        return true; 
    }
 while(list->next!=nullptr){
    if(nameDict->getKeyAtIndex(list->next->object) == name){
       listOfObjects<int> *todel = list->next;
        list->next = list->next->next;
        delete todel;
        return true;
    }
    list = list->next;
 } 

    if(nameDict->getKeyAtIndex(list->object) == name){
        currNode->indices = list->next;
        delete list;
        return true; 
    }
  // Traverse the linked list in currNode and delete our string if present

  return false;
}


listOfObjects<string> * Trie::completions(string prefix) {
  TrieNode *currNode = root;
  int len = prefix.length();
  listOfObjects<string> *currCompletions = new listOfObjects<string>(""); //Dummy first element so that we don't have to worry about nu

  // Insert your code here
  for (int i = 0; i < len; i++) {
        currNode = currNode->branch[index(prefix[i])];
        if(currNode == nullptr){
                // Prefix not found :(
                return nullptr;
        }
  }
  recursiveAddCompletions(currNode, currCompletions);

  return currCompletions->next;
  
}

bool Trie::recursiveAddCompletions(TrieNode *node, listOfObjects<string> *currCompletions) {
  // Add all completions in the node + children of the given node
  if (node->isWord) {
    if (!addCompletions(node, currCompletions)) {
      return false;
    }
  }

  TrieNode *currNode = node;
  for (int i = 0; i < NUM_CHARS; i++) {
    if (currNode->branch[i] != nullptr) {
      // Go to each branch
      if (!recursiveAddCompletions(currNode->branch[i], currCompletions)) {
	return false;
      }
    }
  }

  return true;
}

bool Trie::addCompletions(TrieNode *node, listOfObjects<string> *currCompletions) {
  // adds the indices stored in node into the currCompletions list
  // Insert your code here
  if(!node->isWord) return false; // Can't add if not a word
  // We assume curr completions is not nullptr
  if(currCompletions == nullptr){
    return false;
  }  
  while(currCompletions->next != nullptr){
    currCompletions = currCompletions->next;
  }

  listOfObjects<int> *storedIndex = node->indices;
  while(storedIndex != nullptr){
    currCompletions->next = new listOfObjects<string>(nameDict->getKeyAtIndex(storedIndex->object));
    currCompletions->next = currCompletions->next;
    storedIndex = storedIndex->next;
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
#endif
