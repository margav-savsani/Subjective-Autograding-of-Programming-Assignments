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

bool Trie::insert(string wordInName, int indexOfName)
{
  
  TrieNode *currNode = root;

  int j = 0;
  while (j != wordInName.length())
  {
    bool letterFound=false;

    int letter = wordInName[j]-'A'; //each letter corresponds to a branch. int letter gives the index of that branch.

    if(currNode->branch[letter] != nullptr)
    {
      letterFound=true;
      currNode = currNode->branch[letter]; //Go inside the trie when branch is found
      j++;
    }
    if (letterFound)
      continue;
    else //Create a new branch
    {
      TrieNode *node = new TrieNode;
      currNode->branch[letter] = node;
      currNode->numNonNullBranches++;

      node->parent = currNode;
      currNode = currNode->branch[letter];
      j++;
    }
  }

  currNode->isWord = true; //The word is exhausted. Hence the current node stores a word and isWord is set to true.

  listOfObjects<int> *tmp = currNode->indices;
  bool nameFound=false;
  if(currNode->indices == nullptr) //If list doesn't exist, we create a new node.
  {
    listOfObjects<int> *newIndex = new listOfObjects<int>(indexOfName);
    currNode->indices = newIndex;
    return true;
  }
  tmp = currNode->indices;

  while (currNode->indices->next != nullptr) //Traverse thr list
  {
    if(currNode->indices->object == indexOfName) //If match is found, return false.
    {
      nameFound=true;
      break;
    }
    currNode->indices = currNode->indices->next;
  }

  if(currNode->indices->object == indexOfName) //Since we don't check the last node in the loop.
  {
    nameFound=true;
  }

  if(nameFound) return false;

  listOfObjects<int> *newIndex = new listOfObjects<int>(indexOfName); //No match found. Create a new node and add to the linked list.
  currNode->indices->next = newIndex;

  currNode->indices = tmp;
  // Insert your code here

  return true;
}

bool Trie::del(string wordInName, string name) {
  // Insert your code here

  TrieNode *currNode = root;
  int j=0;
  while(j!= wordInName.length()) //Traverses trie until word is exhausted or mismatch is found.
  {
    int letter = wordInName[j]- 'A';
    if(currNode->branch[letter] != nullptr)
    {
      currNode = currNode->branch[letter];
      j++;
    }
    else return false; //If mismatch is found, return false.
  }

  if(currNode->indices==nullptr)
  {

    return false; 
  }

  if(name == nameDict->getKeyAtIndex(currNode->indices->object)) //Condition when the head of linked list gives a match.
  {
    listOfObjects<int> *n = currNode->indices->next;
    delete currNode->indices;
    currNode->indices = n;

    if(currNode->indices==nullptr) //After deleting, if linked list is empty, delete the branch in trie.
    {
      currNode->isWord=false;

      TrieNode* lastBranchNode; //The node at which the branch for the specific word is rooted.

      if(currNode->numNonNullBranches!=0)
      {
        return true;
      }

      while(currNode->numNonNullBranches <=1 && currNode->isWord==false) //Traverse up till a node has more than 1 branch 
      {
        lastBranchNode = currNode;
        currNode = currNode->parent;
        if(currNode==root) break;
      }

      for(int i=0;i<NUM_CHARS;i++) //Update the number of branches and pointers.
      {
        if(currNode->branch[i]== lastBranchNode){
          currNode->branch[i]=nullptr;
          currNode->numNonNullBranches--;
        }
      }
      recursiveDelete(lastBranchNode);

    }
    return true;
  }

  listOfObjects<int> *tmp1 = currNode->indices;
  listOfObjects<int> *tmp2;
  while(currNode->indices != nullptr) //Traverse list until match is found.
  {
    tmp2 = currNode->indices;
    currNode->indices = currNode->indices->next;
    if(currNode->indices==nullptr) return false; //No match found. List ended.
    if(name == nameDict->getKeyAtIndex(currNode->indices->object))
    {
      tmp2->next = currNode->indices->next;
      // currNode->indices->next = nullptr;
      delete currNode->indices;

      currNode->indices = tmp1;

      return true;
    }
  }

  currNode->indices = tmp1;


  return false;
}

listOfObjects<string> * Trie::completions(string prefix) {
  TrieNode *currNode = root;
  int len = prefix.length();
  listOfObjects<string> *currCompletions = new listOfObjects<string>(""); //Dummy node.

  int i=0;
  while(prefix[i] != 0) //Traverseuntil prefix is exhausted.
  {
    int letter = prefix[i] - 'A';

    if(currNode->branch[letter] != nullptr)
    {
      currNode = currNode->branch[letter];
      i++;
    }
    else return nullptr;//If mismatch is found, return nullptr.
  }
  recursiveAddCompletions(currNode, currCompletions);

  // Insert your code here
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
  listOfObjects<int> * indicesTmp = node->indices;
  if(currCompletions->object=="") //When currCompletions is empty.
  {
    currCompletions->object = nameDict->getKeyAtIndex(node->indices->object);
    node->indices = node->indices->next;
  }

  listOfObjects<string> *tmp =  currCompletions;
  while(currCompletions->next != nullptr)//Traverse till the tail of completions list.
  {
    currCompletions = currCompletions->next;
  }

  while(node->indices != nullptr) //Traverse till the end of indices list.
  {
    listOfObjects<string> *comp = new listOfObjects<string>(nameDict->getKeyAtIndex(node->indices->object)); //Create new completionsList node and add to list.
    currCompletions->next = comp;
    currCompletions = currCompletions->next;
    node->indices = node->indices->next;
  }
  node->indices = indicesTmp;
  currCompletions = tmp;
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
