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
 
  // moving in the trie tree with prefix
  // if the alphabet branch is null then intializing it.
  // after reaching at last characters node
  // adding up the indexOfName at last of index linked list
  // if index linked list is null then intializing it 
  // and also making isWord true in that case.

  for (int i = 0; i < len; i++) {
    int letter = toupper(wordInName.at(i)) - 'A';
  if (currNode->branch[letter] == nullptr) {
        currNode->numNonNullBranches++;
        currNode->branch[letter] = new TrieNode();
    }
    currNode = currNode->branch[letter];
  }
  listOfObjects<int> *currval= currNode->indices;
  if (currNode->isWord)
  {  
     while(currval->next!=nullptr){
      currval =currval->next;
      }
      currval->next= new listOfObjects<int>(indexOfName);
  }
  else {
      currNode->indices=new listOfObjects<int>(indexOfName);
      currNode->isWord = true;
  }
  // Insert your code here
  return true;
}

// deleting the wordInName and name from indices list
// also deleting above link if deleted one is the only station in link
bool Trie::del(string wordInName, string name) {

  TrieNode *currNode = root;
  // setting up the last branch which has multiple branch or is word.
  TrieNode *lastBranchNode = root;
  int lastBranchChar = toupper(wordInName.at(0)) - 'A';
  int len = wordInName.length();

  // Insert your code here
  // traversing to the last node with updating lastBranchNode.
  for (int i = 0; i < len; i++) {
    int letter = toupper(wordInName.at(i)) - 'A';
  if (currNode->branch[letter] == nullptr) {
       return false;
  } if(currNode->numNonNullBranches > 1 || currNode->indices != nullptr){
       lastBranchNode=currNode;
       lastBranchChar=letter;
  }
    currNode = currNode->branch[letter];
  }
  if(currNode->numNonNullBranches > 0 || currNode->indices->next != nullptr){
   listOfObjects<int> *preval=  currNode->indices;
   listOfObjects<int> *currval= currNode->indices;

  // deleting the element in indices list.
  // if indices list become empty then setting isWord = false
  // preval holds the previous node so that we can update its next to next 
  // of current node if current node is to be deleted.
         while(currval != nullptr){
         string value = nameDict->getKeyAtIndex(currval->object);
         if (value==name && currval!= preval){
            preval->next= currval->next;
            return true;
         }
        else if(value==name && currval == preval){
                 currNode->indices = currval->next;
              if (currNode->indices== nullptr)
                 { currNode->isWord = false;}
                 return true;
        }
        else {
                 preval=currval;
                 currval=currval->next;
         }
      }
  }
  else{
      lastBranchNode->numNonNullBranches--;
      // deleting the branch recursively
      recursiveDelete(lastBranchNode->branch[lastBranchChar]);
      // setting last branch char node pointer to null.
      lastBranchNode->branch[lastBranchChar]=nullptr;
  }
  return true;
}

listOfObjects<string> * Trie::completions(string prefix) {
  TrieNode *currNode = root;
  int len = prefix.length();
  // adding dummy at start of currcompetions
  // while returning return its next
  // moving till the end of prefix traversing through trie tree.
  // callling the addcompletions on it. 
  listOfObjects<string> *currCompletions = new listOfObjects<string>("DUMMY");
  for (int i = 0; i < len; i++) {
    int letter = toupper(prefix.at(i)) - 'A';
    if (currNode->branch[letter]!=nullptr)
    {currNode = currNode->branch[letter];}
    else {
      return nullptr;
    }
  }
  addCompletions(currNode,currCompletions);
  return currCompletions->next;
  
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
   listOfObjects<string> *currlist=currCompletions;
   while(currlist->next!=nullptr){
        currlist=currlist->next;
   }
  
   // if node is word ,traversing the indices list 
   // and adding the stations in completions.
    if (node->isWord){
      listOfObjects<int> *currval= node->indices;
      while(currval != nullptr){
         string value = nameDict->getKeyAtIndex(currval->object);
         currval=currval->next;
         if (!isPresentInCompletions(currCompletions,value))
        {currlist->next = new listOfObjects<string>(value);
         currlist=currlist->next;
        }
      }
    }

    // CHECKING for its childen and calling recursively add completions.
    for (int i = 0; i < NUM_CHARS; i++) {
    if (node->branch[i] != nullptr)   
     {
      addCompletions(node->branch[i],currCompletions);
     }
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
