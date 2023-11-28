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
  TrieNode *curr = root  ; 
  int len = wordInName.length();  

  for (int i =0 ; i < len ; i++ ) {  //loop for all chars of the string .
        int index = toupper(wordInName.at(i)) - 'A' ; 
        if ( curr->branch[index] == nullptr )  {  //if the char is not found , then create a new char 
          curr->branch[index] = new TrieNode() ; curr->numNonNullBranches++; 
        }
        curr = curr->branch[index];
  }
  curr->isWord = true ; //the last char is word = true , curr is pointing to last char in trie 
  
  listOfObjects<int>* word_index = curr->indices , *last = nullptr ; //inserting the index in the linked list indices 
  while ( word_index != nullptr )  { last = word_index ; word_index = word_index->next ; } //find the last element of ll .
  
  if (last == nullptr) curr->indices = new listOfObjects(indexOfName) ; //no elements in ll .
  else last->next = new listOfObjects(indexOfName) ;  

  return true ;
}


bool Trie::del(string wordInName, string fullWord) { //function to delete the string in the trie 
  Entry<int>* entry = nameDict->get(fullWord) ; //entry of the given string in dict 
  int indexOfName ;  
  if ( entry == nullptr) return false ; 
  else { indexOfName = entry->value ; } //index of the wordInName 

  // wordInName => current delete word in full station name && name => the full name of the station .
  TrieNode *curr = root;
  // lastBranchNode => it stores the last character which has one or more indices 
  // or 
  // if it has number of non null entries > 1 .
  TrieNode *lastBranchNode = root ;
  int lastBranchIndex = -1 ; 
  int len = wordInName.length();
  for (int i =0 ; i < len ; i++ ) {
        int index = toupper(wordInName.at(i)) - 'A' ; 
        curr = curr->branch[index] ;
        if ( curr == nullptr )  return false ;  //the word is not found .
        if ( i != len-1 && (curr->isWord || curr->numNonNullBranches > 1 )) { 
            lastBranchNode = curr ;
            lastBranchIndex = i  ;
        }
  }
  //insert the fullWord in the indices of the last char . 
  listOfObjects<int>* currWord = curr->indices , *prevWord =  nullptr ; 
  while(currWord != nullptr) { 
           if (currWord->object == indexOfName) { 
              if (prevWord == nullptr) {
                  curr->indices = currWord->next  ; 
                  if ( curr->indices == nullptr ) curr->isWord = false ;  
              }
              else if (currWord->next == nullptr) prevWord->next = nullptr ; 
              else  prevWord->next = currWord->next ; 
              delete currWord ;
              break ;
           } 
           prevWord = currWord ; 
           currWord = currWord->next ;
   }
  // If the last char has no words or no chars , then 
  //delete the characters from the next node of the lastBranchNode to last character of the string . 
  if ( curr->numNonNullBranches == 0 and curr->isWord == false ) { 
      int index = toupper(wordInName.at(lastBranchIndex + 1)) - 'A' ; 
      TrieNode* next=lastBranchNode->branch[index] ;  
      lastBranchNode->numNonNullBranches--; //handle the last where the trie diverge or has a word in it 
      recursiveDelete(next);
      lastBranchNode->branch[index] = nullptr ; 
  }
  return true;
}

listOfObjects<string> * Trie::completions(string prefix) {
  TrieNode *curr = root;
  int len = prefix.length();
  //find the last character of the prefix in the trie .
  for (int i =0 ; i < len ; i++ ) { 
        int index = toupper(prefix.at(i)) - 'A' ; 
        if ( curr->branch[index] == nullptr ) return nullptr  ; //no prefix match found .
        curr = curr->branch[index]; 
  }
  //curr has the last char of the prefix in trie 
  listOfObjects<string>* currCompletions = nullptr ; 
  recursiveAddCompletions(curr,currCompletions);  //call recursive add in curr node .
  return currCompletions;
}

bool Trie::recursiveAddCompletions(TrieNode *node, listOfObjects<string>* &currCompletions) {
  //this adds  the currCompletions from the child nodes .
  if (node->isWord) {
    if (!addCompletions(node, currCompletions)) { //call add completions for each child of the prefix .
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

bool Trie::addCompletions(TrieNode *node, listOfObjects<string>* &currCompletions) {
  //given a node , add all the words ending in the node to currCompletions 
  if (node->isWord == false) return false ; 
  listOfObjects<int>* wordIndex = node->indices ; 
  
  while(wordIndex != nullptr) { 
      string name = nameDict->getKeyAtIndex(wordIndex->object);
     if (currCompletions == nullptr) currCompletions = new listOfObjects<string>(name)  ;
     else  {
       listOfObjects<string>* temp = currCompletions->next ,*last = currCompletions ; 
       while (temp != nullptr) { last = temp ; temp = temp->next ; }
       last->next = new listOfObjects<string>(name); 
     }
     wordIndex = wordIndex->next ; 
  }

  return true ;
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
