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

#define MAGIC_STRING "###"

/* Note that the while loops everywhere can be rewritten as a for loop!
currNode = root
while(currNode != nullptr){
  // do stuff
  currNode = currNode->branch[index];
}

is the same as

int index;
for (auto currNode = root; currNode != nullptr; currNode = currNode->branch[index]){
  // do stuff
}

*/

/* 
When modifying a pointer's value, a pointer/reference to this pointer must be passed, not a copy of the pointer(else only the copy is modified) 
*/

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
    // if (node != root) {
      delete node;
    // }
    return;
  }
}

bool Trie::insert(const string &wordInName, int indexOfName) {
  TrieNode *currNode = root;

  // Notice in an iteration currNode is behaving like a parentNode and only at the end of the loop it is being updated one step down.
  for (int i = 0; i < wordInName.length(); i++){
    int index = toupper(wordInName.at(i)) - 'A';    
    if (currNode->branch[index] == nullptr) {
      TrieNode *newNode = new TrieNode();
      if (newNode == nullptr) {
      	cout << "Memory allocation failure" << endl;
	      return false;
      }
      currNode->branch[index] = newNode;
      currNode->numNonNullBranches++;
    }
    currNode = currNode->branch[index];
  }

  currNode->isWord = true; // it now (might already have done so) represents a word in the trie.
  
  // check whether for this word this index has already been inserted before. Usecase: we won't store two identical indices if the 
  listOfObjects<int> *currIndex = currNode->indices; // linked list of indices
  while (currIndex != nullptr) {
    // make insert O(n) instead of 1 but check for repetitions. A bst does this + gives us log(n) + sorted, amazing. A hashtable gives us O(1) on average but no order, still great.
    if (currIndex->object == indexOfName) {
      cout << "Insertion already done in the past." << endl;
      return true;
    }
    else {
      currIndex = currIndex->next;
    }
  }

  // Need to insert indexOfName in currNode->indices
  
  listOfObjects<int> *newEntry = new listOfObjects<int> (indexOfName);
  if (newEntry == nullptr) {
    cout << "Memory allocation failure." << endl;
    return false;
  }
  else {
    // insert NewEntry at the head of the linked list indices.
    newEntry->next = currNode->indices;
    currNode->indices = newEntry;
    return true;
  }
}

bool Trie::del(const string &wordInName, const string &name) {
  if (wordInName.length() == 0) return true;

  TrieNode *currNode = root;
  TrieNode *lastSharedNode = root; // here's the last non-word node along the path that is shared by another word.
  int depthAtShared = 0; // depthAtShared := number of steps taken down from root to reach the last SharedNode
  string prefix = "";
  // go to the square-(end-of-word)-node for this word. Notice we go down only at the end of the iteration. We first check whether we can go down, and then go down if we can.
  for (int i = 0; i < wordInName.length(); i++) {
    // cout << "Prefix: *" << prefix << "*" << endl;
    
    // at the start of the ith iteration, we have made i steps down the tree.
    
    int index = toupper(wordInName.at(i)) - 'A'; // where to go next.

    // the word we're looking for is not there in the trie.
    if (!(currNode->branch[index])) {
      cout << "Couldn't find " << "\"" << wordInName << "\"" << " in \"" << name << "\"" << endl;
      return false;
    }

    // if the current node is part of another word apart from this, then surely we cannot delete the nodes until here. Even if it is exactly one, but the current string so far is also a valid word (ie this prefix of our word is a valid word), even then we must not delete these nodes. This is also a kind of branching, notice.
    if (currNode->numNonNullBranches > 1 || currNode->isWord) {
      lastSharedNode = currNode; // here's where the node is shared.
      depthAtShared = i; // depthAtShared := number of steps taken down from root to reach the last SharedNode, which is exactly i.
    }
    currNode = currNode->branch[index]; /* once at depth i, we go down wordInName[i], notice! And not i+1. */
    prefix += char('a' + index);
  }

  // we have reached where we our word must terminate, if the word is in the trie.

  // this node isn't marked as end-of-word implies that the word we're looking for is't there in the trie.
  if (!currNode->isWord) {
    cout << "Couldn't find " << wordInName << " in " << name << endl;
    return false;
  }

  // delete the index corresponding to `name` in the linked list at currNode
  listOfObjects<int> *currIndex = currNode->indices;
  listOfObjects<int> *prevIndex = nullptr;
  
  while (currIndex != nullptr) {
    if (nameDict->getKeyAtIndex(currIndex->object) != name) {
      prevIndex = currIndex;
      currIndex = currIndex->next;
      continue;
    }

    // we have found our index. delete it.
    currNode->indices = currIndex->next;
    
    if (prevIndex != nullptr) // chenge previous element(if exists)'s next pointer to the element ahead of currIndex (possibly nullptr)
      prevIndex->next = currIndex->next;

    delete currIndex;
    // cout << "deleted index from indices" << endl;
    break;
  }

  // There is at least one other station name for which one of its words is this same word, so we cannot delete nodes corresponding to this word, we have removed the index, that's all we need to do.
  if (currNode->indices != nullptr){
    return true;
  }
    
  // currNode->indices == nullptr, so if this word isn't a prefix we can delete it. If it is, well, all we can do is set isWord to false and return.
  if (currNode->numNonNullBranches >= 1){
    currNode->isWord = false;
    return true;
  }
  
  /* else: */

  // so currNode is a leaf, so we can delete all nodes starting from the next node after the lastSharedNode.
  // The path is unique (numNonNullBranches is 1 the whole way) to this Word, and so we can delete every node along the path.
  // we could call recursive delete on the first node of this word, but that's slower since it tries to go everywhere. We know exactly the path to go along so can delete in O(length of word).

  // go to the first node to be deleted. It has parent lastSharedNode, which is at depth i = depthAtShared
  int index = toupper(wordInName[depthAtShared]) - 'A';
  currNode = lastSharedNode->branch[index]; // (reusing currNode)

  // cleanup at lastSharedNode. Can do before/after the deletion.
  lastSharedNode->branch[index] = nullptr; // since there's no word here now.
  lastSharedNode->numNonNullBranches--;
  
  // go on deleting all nodes from here on.
  for (int i = depthAtShared + 1; i < wordInName.length(); i++){
    TrieNode *to_delete = currNode;
    
    // save a pointer to the child node before deleting the node.
    int index = toupper(wordInName[i]) - 'A';
    currNode = currNode->branch[index]; // notice we can just move forward, no set to nullptr etc required because all these cnodes are to be deleted anyway. The nullptr is only at the lastSharedNode or root where the node isn't deleted, but a child (corresponding to this word) is deleted.

    delete to_delete;
  }
  return true;
}

listOfObjects<string> * Trie::completions(const string &prefix) {
  ptr_type currNode = root;
  for (char c: prefix){
    int index = toupper(c) - 'A';
    if (!(currNode->branch[index])) return nullptr;
    currNode = currNode->branch[index];
  }
  listOfObjects<string> *validcompletions = nullptr;
  recursiveCompletions(currNode, &validcompletions);
  return validcompletions;
}

bool Trie::recursiveCompletions(TrieNode *node, listOfObjects<string> **currCompletions) {
  if (!node) return true;
  // add all words from node and lower. So if node is a word we add it, and thne for node's branches we recursively call this function.
  if (node->isWord){
    //  A preliminary check for whether currCompletions is empty.

    // add all indices of this word to the list of completions.

    auto currNode = node->indices; // not nullptr since isWord is true, so indices has atleast one element
    
    // get all indices to their string form in list newCompletions
    listOfObjects<string> *newCompletions = new listOfObjects<string>(nameDict->getKeyAtIndex(currNode->object));
    currNode = currNode->next;
    auto tail = newCompletions;
    for (; currNode; currNode = currNode->next){
      tail->next = new listOfObjects<string>(nameDict->getKeyAtIndex(currNode->object));
      tail = tail->next;
    }

    // add these to currCompletions
    tail = *currCompletions; // currCompletions is guaranteed to be a valid pointer to a pointer. it will not be the nullptr.
    if (tail) while(tail->next) tail = tail->next;

    if (!tail) *currCompletions = newCompletions; // the pointer *currCompletions is modified to point to the memory on the heap that newCompletions is also pointing to. Also, this line is the ONLY line that actually changes currCompletions, and so a ptr to the pointer is to be passed, and *(this-pointer) is changed, so that dereferencing the ** in the calling function gives us, indeed, the pointer to the linked list. In fact, we can get rid of the ** and keep it * if currCompletions as passed will never be empty. Can we assume that? Let's not, for variety. Also note, a reference to the pointer can be used instead of a pointer to it.
    else tail->next = newCompletions; // form nullptr to newCompletions
  }

  for (int i = 0; i < NUM_CHARS; i++)
    if (node->branch[i]) // just for speed.
      recursiveCompletions(node->branch[i], currCompletions);
  return true; // change to void.
}

// not required.
bool Trie::addCompletions(TrieNode *node, listOfObjects<string> *currCompletions) {
  return true;
}

bool Trie::isPresentInCompletions(listOfObjects<string> *completions, const string &name) {
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

// free the linked list completions.
void Trie::freeCompletionList(listOfObjects<string> *completions) {
  listOfObjects<string> *currCompl = completions;
  while (currCompl != nullptr) {
    listOfObjects<string> *toDeleteCompl = currCompl;
    currCompl = currCompl->next;
    delete toDeleteCompl;
  }
  return;
}

// check if wordInName is present in the Trie
bool Trie::isPresent(const string &wordInName) { TrieNode *currNode = root;
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

// Edit version 1: Added printTrie and recursivePrintTrie functions to help in debugging

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
