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

  

  bool isPresent = false;
  for (int i = 0; i < len; i++){
    //check if nodes are already present of the corresponding word.
    if(currNode->branch[int(tolower(wordInName[i])) - 97] != nullptr){
      
      currNode = currNode->branch[int(tolower(wordInName[i])) - 97];
    } else {
      //add new nodes if the nodes are not found
      TrieNode * newNode = new TrieNode();
      if (i == len - 1) newNode->isWord = true;

      //increase the number of non null branches
      currNode->numNonNullBranches++;
      currNode->branch[int(tolower(wordInName[i])) - 97] = newNode;
      currNode = currNode->branch[int(tolower(wordInName[i]) - 97)]; //go to the next node




    }
  } 
  //add the station name index to the list of objects.
  listOfObjects<int>* currIndex = currNode->indices;
  listOfObjects<int>* prevIndex = nullptr;
  
  // update the list if it was previously a null pointer
  if (currIndex == nullptr) {
    currNode->indices = new listOfObjects<int>(indexOfName);
    return true;
  }



  bool inserted = false;
  // add the index at the last
  while(currIndex != nullptr){
    if(currIndex->object == indexOfName){
      return false;
      break;
    } else {
      prevIndex = currIndex; //update previous index and the curr index
      currIndex = currIndex->next; 

    }
  }

  prevIndex->next = new listOfObjects<int>(indexOfName); //add the index at the last
  return true;

  
}


bool Trie::del(string wordInName, string name) {
  
  TrieNode *currNode = root;
  TrieNode *lastBranchNode = root;
  int lastBranchChar = int(tolower(wordInName[0])) - 97;
  int len = wordInName.length();
  

  //check if the all the letters of the word are present in the Trie or not

  for(int i = 0; i < len; i++){
      if(currNode->branch[int(tolower(wordInName[i])) - 97] != nullptr){
          if(currNode->numNonNullBranches > 1){
            //update the values of the last node with more than two branches
            lastBranchNode = currNode;
            lastBranchChar = int(tolower(wordInName[i])) - 97; 
          }
          currNode = currNode->branch[int(tolower(wordInName[i])) - 97]; // 
      } else {
        //if the word isnt found in the trie then return false
        return false;
      }
  }

    bool deleted = false;
    //if the word is found in the trie, delete the station name
    if(currNode->isWord){
      // delete the station in the list if the list is non empty
      listOfObjects<int> * currIndex = currNode->indices;
      listOfObjects<int> * prevIndex = nullptr;

      if (currIndex == nullptr){
        currNode->isWord = false; 
      }

      while(currIndex != nullptr){
        //check if the name of the station entered matches with the one in the dictionary.
        if (nameDict->getKeyAtIndex(currIndex->object) == name){
            if(prevIndex == nullptr){
              //if deleting the first element of the list, then update the pointer to the head.
              currNode->indices = currNode->indices->next;
              delete currIndex;
              deleted = true;
              

              if (currNode->indices == nullptr){
                //if the length of the list is zero, set isWord to false
                currNode->isWord = false;
              }

              break;
            } else {
              //update the previous index to point to the next index.
              prevIndex->next = currIndex->next;
              delete currIndex;
              deleted = true;
              break;
            } 
          } else {
            //if the names arent equal, then go to the next element of the list.
            prevIndex = currIndex;
            currIndex = currIndex->next;
            
          }
      }
    }


    //if no station name exists corresponding to that word

    if (currNode->isWord == false){
      //delete all the nodes till the last node having more than 1 children.
      
      recursiveDelete(lastBranchNode->branch[lastBranchChar]);
      // update the pointer of the node having more than 1 children.
      // decrease the number of non null branches.
      lastBranchNode->branch[lastBranchChar] = nullptr;
      lastBranchNode->numNonNullBranches--;
    }
    //return true if the word was deleted.
    return deleted;

}






listOfObjects<string> * Trie::completions(string prefix) {
  TrieNode *currNode = root;
  int len = prefix.length();
  listOfObjects<string> *currCompletions = nullptr;

  
  //go to the last node of the prefix desired
  for(int i = 0; i < len; i++){
    if (currNode->branch[int(prefix[i]) - 97] != nullptr){
      currNode = currNode->branch[int(prefix[i] - 97)];


    } else {
      // if the prefix doesnt match with any word in the trie, then return a null pointer.
      
      return currCompletions;
    }
  }
  //add the value of the names recursively in the list.
  bool found = recursiveAddCompletions(currNode, currCompletions);
  
  //return the final list.
  return currCompletions;
  
}

bool Trie::recursiveAddCompletions(TrieNode *node, listOfObjects<string> * &currCompletions) {
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

  
  listOfObjects<string> * currCompNode = currCompletions;
  //find the last element of the current completions found
  if (currCompletions != nullptr){
    while(currCompNode->next != nullptr){
      currCompNode = currCompNode -> next;
    }
  }

  
  listOfObjects<int> *currNode = node->indices;

  //add all the names of the completions found in the leaf node to the list of completions.
  while(currNode != nullptr){
    //create a new node with the name of station same as the one found.
    listOfObjects<string> * newNode = new listOfObjects<string>(nameDict->getKeyAtIndex(currNode->object));
    if(currCompNode == nullptr){
      currCompNode = newNode;
      currCompletions = newNode;
    } else {
      //keep on adding the new nodes till you reach a null pointer
      currCompNode->next = newNode;
      currCompNode = currCompNode->next;
    }


    // go to the next element to be added.
    currNode = currNode ->next;
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
