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

template <typename T> void insertInto(listOfObjects<T>* l1, listOfObjects<T>* obj);

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

/**
 * @brief Inserts a possible word completion corresponding to `indexOfName` into the trie node corresponding to `wordInName`
 * If the word `wordInName` doesn't exist in the tree, it first creates it and then adds the association with `indexOfName`
 * 
 * @param wordInName The word corresponding to which a possible name completion has to be inserted into the tree.
 * @param indexOfName Index of the name completion corresponding to `wordInName`
 * @return true, if the insert was successful
 * @return false, otherwise
 */
bool Trie::insert(string wordInName, int indexOfName) {
  TrieNode *currNode = root;
  int len = wordInName.length(), c_pos;
  int c_char;

  // Traverse the Trie to match the longest possible prefix of wordInName
  for(c_pos=0; c_pos < len; c_pos++){
    c_char = toupper(wordInName.at(c_pos)) - 'A';
    if(currNode->branch[c_char] == nullptr) break;

    currNode = currNode->branch[c_char];
  }
  // Insert your code here

  if(c_pos < len){
    //Entire word not matched, must make the remaining path
    currNode = this->makePath(currNode, wordInName.substr(c_pos, len-c_pos));
  }

  // Adding the new index to the start of the list of indices
  listOfObjects<int> *new_index = new listOfObjects<int>(indexOfName);
  new_index->next = currNode->indices;
  currNode->indices = new_index;
  currNode->isWord = true;

  return true;
}

/**
 * @brief Deletes an association of the word `wordInName` with the complete `name`
 * If `wordInName` has no remaining associations, it is deleted from the Trie
 * 
 * @param wordInName The word corresponding to which the name association is to be deleted. Assumed to be case-insensitive.
 * @param name The name that is no longer to be associated with `wordInName`
 * @return true, if the association was deleted successfully
 * @return false, otherwise
 */
bool Trie::del(string wordInName, string name) {
  TrieNode *currNode = root;
  TrieNode *lastBranchNode = nullptr;
  int lastBranchChar = -1;
  int len = wordInName.length(), c_pos, c_char;

  // Traverse the Trie to match the longest possible prefix of wordInName
  for(c_pos=0; c_pos < len; c_pos++){
    c_char = toupper(wordInName.at(c_pos)) - 'A';
    if(currNode->branch[c_char] == nullptr) break;

    currNode = currNode->branch[c_char];
  }

  if(c_pos < len) return false;

  listOfObjects<int> *ind = currNode->indices, *prev = nullptr;
  while(ind != nullptr && this->nameDict->getKeyAtIndex(ind->object) != name) {
    prev = ind;
    ind = ind->next;
  }
  if(ind == nullptr) return false;
  else{
    if(prev == nullptr) currNode->indices = ind->next;
    else prev->next = ind->next;

    delete ind;
    ind = nullptr;

    this->pruneTrie(currNode);
    return true;
  }

  // Insert your code here
  return false;
}

/**
 * @brief Returns a list of name completions corresponding to the given `prefix` 
 * 
 * @param prefix The prefix corresponding to which the name completions are to be offered.
 * @return listOfObjects<string>*, the first of possibly multiple elements in a linked list containing the possible name completions
 */
listOfObjects<string> * Trie::completions(string prefix) {
  TrieNode *currNode = root;
  int len = prefix.length(), cur_char, cur_pos;
  listOfObjects<string> *currCompletions = nullptr;

  bool prefix_exists = true;
  for(cur_pos=0; cur_pos<len; cur_pos++){
    cur_char = toupper(prefix.at(cur_pos)) - 'A';
    if(currNode->branch[cur_char] == nullptr) break;

    currNode = currNode->branch[cur_char];
  }

  if(cur_pos < len) return nullptr; // No completions found.

  listOfObjects<string>* res = new listOfObjects<string>("sentinel");
  this->recursiveAddCompletions(currNode, res);
  return res->next;
}

/**
 * @brief Gets all the word suggestions from and after `node` 
 * 
 * @param node The node including and following which the word endings are to be found
 * @param currCompletions The first element of the list of suggestions at the time of calling the function.
 * @return listOfObjects<string>*, the first element of the list of suggestions after adding the suggestions corresponding to the function arguments
 */
bool Trie::recursiveAddCompletions(TrieNode *node, listOfObjects<string> *currCompletions) {
  if (node->isWord) {
    if (!addCompletions(node, currCompletions)) {
      return false;
    }
  }

  for (int i = 0; i < NUM_CHARS; i++) {
    if (node->branch[i] != nullptr) {
      if (!recursiveAddCompletions(node->branch[i], currCompletions)) {
	return false;
      }
    }
  }

  return true;
}

/**
 * @brief Adds all completions in `node` into the `currCompletions` list
 * 
 * @param node The node from which completions are to be added into `currCompletions` list
 * @param currCompletions Pointer to the first element of the list of completions.
 * @return true, if the completions of the node were successfully added to the list
 * @return false, otherwise.
 */
bool Trie::addCompletions(TrieNode *node, listOfObjects<string> *currCompletions) {
  // Insert your code here
  if(currCompletions == nullptr) return false;
  listOfObjects<int>* ind_elem = node->indices;

  while(ind_elem!=nullptr){
    insertInto(currCompletions, new listOfObjects<string>(this->nameDict->getKeyAtIndex(ind_elem->object)));

    ind_elem = ind_elem->next;
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

/**
 * @brief Makes a path in the trie starting from some node `begin` and ending at it's leaf, suitable for adding suffixes to a trie as well. 
 * Does not set the corresponding leaf to indicate that it is the end of a word, because it may not be. Caller function must handle that.
 * 
 * @param begin The node from which the path is to be made.
 * @param sub_str The sub-string to be added starting after `begin`
 * @return TrieNode*, the node corresponding to the last character in `sub_str`
 */
TrieNode* Trie::makePath(TrieNode *begin, string sub_str){
  TrieNode* cur = begin;

  for(int i=0; i<sub_str.length(); i++){
    int letter = toupper(sub_str.at(i)) - 'A';

    if(cur->branch[letter] != nullptr) cerr << "\tDEBUG: makePath called to make a path which already exists partially, overwriting now.\n";
    cur->branch[letter] = new TrieNode();
    cur->branch[letter]->parent = cur;
    cur->numNonNullBranches++;
    cur=cur->branch[letter];
  }

  return cur;
}

/**
 * @brief Prunes a branch of a trie if it is not assigned a matching complete word. 
 * 
 * @param node The node from which pruning is to be started, moving towards the root.
 */
void Trie::pruneTrie(TrieNode* node){
  if(node == nullptr) return;

  if(node->numNonNullBranches == 0){
    if(node->indices == nullptr){
      TrieNode* p = node->parent;
      for(int i=0;i<26;i++){
        if(p->branch[i] == node){
          p->branch[i] = nullptr;
          p->numNonNullBranches--;
          break;
        }
      }

      delete node;
      node=nullptr;
      this->pruneTrie(p);
    }
  }else{
    //TODO: If node is not empty, prune the branches emanating from it, then proceed with the node itself. Or maybe just ignore this case, maybe.
  }
}

template <typename T>
void insertInto(listOfObjects<T>* l1, listOfObjects<T>* obj){
  if(l1 == nullptr || obj == nullptr) return;

  listOfObjects<T>* second=l1->next;
  l1->next = obj;
  obj->next = second;
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