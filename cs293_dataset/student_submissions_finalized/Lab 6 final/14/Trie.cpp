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
  for(int i=0; i<len; i++)
  {
    //to allow both smaller and bigger letters
    //as input
    int letter = toupper(wordInName[i]) - 'A';
    //if the branch of that letter is null
    if(!currNode->branch[letter]) 
    {
      currNode->branch[letter] = new TrieNode();
      currNode->numNonNullBranches++;
    }
    currNode = currNode->branch[letter];
  }

  currNode->isWord = true;
  //if indices is empty then create a new object
  if(!currNode->indices) currNode->indices = new listOfObjects<int>(indexOfName);
  //if the indices list aldready contains some indices
  //go till null is reached and insert a new node in the singly linked list
  else
  {
    //move until it is null
    listOfObjects<int>* help = currNode->indices;
    while(help->next) help = help->next;
    //add new node
    help->next = new listOfObjects<int>(indexOfName);
  }

  return true;
}

bool Trie::del(string wordInName, string name) {
  TrieNode *currNode = root;
  TrieNode *lastBranchNode = NULL;
  int lastBranchChar = -1;
  int len = wordInName.length();

  //going till the last node
  //getting last branch node and last branch char
  for(int i=0;i<len;i++)
  {
    int index = toupper(wordInName[i]) - 'A';
    if(currNode -> branch[index]==NULL) return false;
    if(i < len && (currNode->isWord || currNode->numNonNullBranches > 1))
    {
      //when a branch division occurs
      //useful to  store since we have to delete the word from trie 
      //starting from here
      lastBranchNode=currNode;
      lastBranchChar=index;
    }
    currNode = currNode->branch[index];
  }

  //if reached end
  //else there is no such word
  if(currNode->isWord)
  {
    //to find if the full station is present
    bool isthere = 0;
    listOfObjects<int> * help = currNode->indices;
    listOfObjects<int> * prev = NULL;
  
    //searching in singly linked list
    while(help && !isthere)
    {
      if(nameDict->getKeyAtIndex(help->object)==name) isthere = true;
      else
      {
        prev = help;
        help = help->next;
      }
    }
    
    if(isthere)
    {
      //if matches at the first word then remove
      if(nameDict->getKeyAtIndex(currNode->indices->object)==name) currNode->indices = currNode->indices->next;
      //else removing as in singly linked list
      else 
      {
        prev->next = help->next;
        delete help; //free the space
      }
      if(currNode->indices == NULL) currNode->isWord = false; //if no word with that prefix
      if(currNode->isWord == false && currNode->numNonNullBranches == 0)
      {
        if(lastBranchChar!=-1)
        {
          recursiveDelete(lastBranchNode->branch[lastBranchChar]); //free the space
          lastBranchNode->branch[lastBranchChar] = NULL; 
          lastBranchNode->numNonNullBranches--; //as a branch became null, update
        }
        else
        {
          //case when there is only one word in the trie
          for(int i=0;i<26;i++)
          {
            if(root->branch[i]!=NULL)
            {
              recursiveDelete(root->branch[i]); //free the space
              root->branch[i] = NULL;
              root->numNonNullBranches--; //as a branch became null, update
            }
          }
        }
      }
      return true;
    }
  }
  return false;
}

listOfObjects<string> * Trie::completions(string prefix) {
  //returns the completions of all suffixes of prefix
  TrieNode *currNode = root;
  int len = prefix.length();
  listOfObjects<string> *currCompletions = NULL;
  // Insert your code here
  for(int i=0; i<len;i++)
  {
    int index = toupper(prefix[i]) - 'A';
    //if word stopped matching
    if(!currNode->branch[index]) return currCompletions;
    //else go to end
    currNode = currNode->branch[index];
  }
  recursiveAddCompletions(currNode,*&currCompletions);
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
    if (currNode->branch[i] != NULL) {
      if (!recursiveAddCompletions(currNode->branch[i], currCompletions)) {
	return false;
      }
    }
  }

  return true;
}

bool Trie::addCompletions(TrieNode *node, listOfObjects<string> *&currCompletions) {
  // should pass currCompetions with reference
  // Insert your code here
  if(node->isWord)
  {
    listOfObjects<int> *ind = node->indices;
    listOfObjects<string> *dupcom = currCompletions, *help = new listOfObjects<string>(nameDict->getKeyAtIndex(ind->object));

    //if it is empty then insert at the start
    if(!currCompletions) currCompletions = help;
    else
    {
      //if not empty insert at the end as in singly linked list
      while(dupcom->next) dupcom = dupcom->next;
      dupcom->next = help;
    }

    while(ind->next)
    {
      ind = ind->next;
      if(isPresentInCompletions(currCompletions,nameDict->getKeyAtIndex(ind->object)))
      {
        //skip if aldready present
        ind = ind->next;
      }
      else
      {
        listOfObjects<string> *node = new listOfObjects<string>(nameDict->getKeyAtIndex(ind->object));
        //adding all words corresponding to the indices
        help->next = node;
        help = help->next;
      }
    }
    help = currCompletions;
    return true;
  }
  //if there is no such word 
  return false;
}

bool Trie::isPresentInCompletions(listOfObjects<string> *completions, string name) {
  listOfObjects<string> *currCompletion = completions;
  bool isPresent = false;
  while (currCompletion != NULL) {
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
  while (currCompl != NULL) {
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

    if (currNode->branch[letter] == NULL) {
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
  if (node != NULL) {
    cout << prefix;
    
    cout << ((branchId == 0) ? "|-" : (branchId == -1)? " *":"|_" ) << (char) ((branchId != -1) ? 'A'+branchId: '*');
    cout << ((branchId == 0) ? '-' : (branchId == -1) ? '*':'_');
    
    // If this trie node has isWord set to true, print "(isWord)" and
    // also the list of complete station names (accessed through indices
    // in nameDict) associated with this trie node.
    if (node->isWord) {
      cout << "(isWord)";
      listOfObjects<int> *currIndices = node->indices;
      while (currIndices != NULL) {
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
	if (node->branch[j] != NULL) {
	  childrenToRight = true;
	  break;
	}
      }
      if (currNode != NULL) {
	recursivePrintTrie(currNode, prefix + ((siblingsToRight) ? "│   " : "    "), i, childrenToRight);
      }
    }
  }
}
// End edit version 1
#endif
