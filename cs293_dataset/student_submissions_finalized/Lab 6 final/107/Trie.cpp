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
    int letter = toupper(wordInName.at(i)) - 'A';

    if (currNode->branch[letter] == nullptr) {
      // if this branch wasn't present earlier... we will create it and increase numNonNullBranches by 1
      currNode->branch[letter]= new TrieNode();
      currNode->numNonNullBranches++;
    }
    currNode = currNode->branch[letter];  // proceed further into this branch
  }

  if(!currNode->isWord) // if already no word ends here
  {
    currNode->isWord=true;  // now a word ends here!!!
    currNode->indices=new listOfObjects<int>(indexOfName); // since isWord, therefore a list of indices with new entry
    return true; // successful insertion
  }
  // if we are here, then already a words end here, so we will check if new index is already present,
  // if present, do no addition and return true, else add new index at end of list of indices and return true
  listOfObjects<int> *ind=currNode->indices;
  listOfObjects<int> *prevind=nullptr;
  while(ind!=nullptr)
  {
    if(ind->object==indexOfName)  // already present
    {
      return true;  // successful insertion
    }
    prevind=ind;
    ind=ind->next;
  }
  prevind->next=new listOfObjects<int>(indexOfName); // new addition
  return true;  // successful insertion
}

bool Trie::del(string wordInName, string name) {
  TrieNode *currNode = root;
  listOfObjects<TrieNode*> *lastBranchNode = nullptr; // a list of BranchNode as we move down the trie... first element is immediate previous
  listOfObjects<int> *lastBranchChar = nullptr;  // a list of BranchChar as we move down the trie... first element is immediate previous
  int len = wordInName.length();

  // Insert your code here
  for(int i=0; i<len; i++)
  {
    int letter = toupper(wordInName.at(i)) - 'A';

    if (currNode->branch[letter] == nullptr) {
      // not present in trie
      return false;
    }
    // insertion of currNode at head of lastBranchNode
    listOfObjects<TrieNode*> *lastNode=new listOfObjects<TrieNode*>(currNode);
    lastNode->next=lastBranchNode;
    lastBranchNode=lastNode;

    // insertion of letter at head of lastBranchChar
    listOfObjects<int> *lastChar=new listOfObjects<int>(letter);
    lastChar->next=lastBranchChar;
    lastBranchChar=lastChar;

    // proceeding down the trie
    currNode = currNode->branch[letter];
  }
  if(!currNode->isWord)  // no word present to delete
    return false;
  int index = (nameDict->get(name))->value; // index of name passed
  // if we have further trie down... example let MUMBAI and MUM are there... if we are to delete MUM then it isPrefix of MUMBAI
  bool isPrefix=(currNode->numNonNullBranches>0)?true:false;
  listOfObjects<int> *ind=currNode->indices;  // all indices of words which end here
  listOfObjects<int> *prevind=nullptr;
  while(ind!=nullptr)
  {
    if(index==ind->object)  // matched index
    {
      if(prevind==nullptr)  // matched at head, so move head by one
        currNode->indices=(currNode->indices)->next;
      else  // matched in middle, remove it by making it's next it's previous's next
        prevind->next=ind->next;
      delete ind; // delete ind as we were asked
      break;  // end of search
    }
    prevind=ind;
    ind=ind->next;
  }
  if(ind==nullptr)  // index not present in list of indices (ind)
    return false;
  if(currNode->indices==nullptr)  // no more word ended here and so isWord becomes false
    currNode->isWord=false;
  if(isPrefix || currNode->isWord)  // if it is prefix or some other word also ended here, we do not have to delete TrieNode
    return true;  // successful deletion
  while((lastBranchNode->object)!=nullptr)  // move up in Trie such that we either find root or a node which isWord or a node such that it has otherchild
  {
    (lastBranchNode->object)->branch[lastBranchChar->object]=nullptr; // delete this branch
    (lastBranchNode->object)->numNonNullBranches--; // decrease numNonNullBranches by 1
    if((lastBranchNode->object)==root)  // we are at root... no more moving up required
      return true;  // successful deletion
    if((lastBranchNode->object)->isWord)  // we are at node which isWord, so no need to delete further
      return true;  // successful deletion
    bool otherchild=((lastBranchNode->object)->numNonNullBranches>0)?true:false;  // if node still has a child
    if(otherchild)  // otherchild so no need to delete further
      return true;  // successful deletion
    lastBranchNode=lastBranchNode->next;  // move up
    lastBranchChar=lastBranchChar->next;  // move up
  }
  return true;
}

listOfObjects<string> * Trie::completions(string prefix) {
  TrieNode *currNode = root;
  int len = prefix.length();
  listOfObjects<string> *currCompletions = nullptr;

  // Insert your code here
  // move upto that node which is last letter of prefix
  for (int i = 0; i < len; i++) {
    int letter = toupper(prefix.at(i)) - 'A';

    if (currNode->branch[letter] == nullptr) {
      // no match possible
      return currCompletions;  // this is nullptr
    }
    currNode = currNode->branch[letter];  // move down
  }
  currCompletions=new listOfObjects<string>("");  // dummy initialisation
  if(!recursiveAddCompletions(currNode, currCompletions))
  {
    freeCompletionList(currCompletions);
    return nullptr;
  }
  return currCompletions->next;  // remove dummy completion
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
  if(node==nullptr || currCompletions==nullptr) // trivial checks
    return false;
  listOfObjects<int>* ind=node->indices;  // list of indices at node
  while(ind!=nullptr) // traverse whole list of indices
  {
    if(!isPresentInCompletions(currCompletions, nameDict->getKeyAtIndex(ind->object)))
    {
      // it was not already present so add it at the last
      while(currCompletions->next!=nullptr)
      {
        currCompletions=currCompletions->next;
      }
      currCompletions->next=new listOfObjects<string>(nameDict->getKeyAtIndex(ind->object));
    }
    ind=ind->next;
  }
  return true;  // successfully added to currCompletions
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
