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
#include<string.h>
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
  TrieNode *currNode = root, *prev_node=nullptr;
  int len = wordInName.length();
  
  // This loop iteratively places alphabets (as indices) into the Trie
  for (int i=0;i<len;i++){
    int curr_char = wordInName[i] - 'A';
    if (curr_char<0 or curr_char>25) return false;
    if(currNode->branch[curr_char]==nullptr){
      
      currNode->branch[curr_char]=new TrieNode;
      currNode->numNonNullBranches+=1;
    }
    
    prev_node=currNode;
    currNode = currNode->branch[curr_char];
    currNode->prev=prev_node;
  }
  
  //Update list of Index of Name
  {
    
    
    if(currNode->indices==nullptr)currNode->indices=new listOfObjects<int>(indexOfName);
    else{
    listOfObjects<int>* empty_list_element = currNode->indices;
    while (empty_list_element->next!=nullptr){
      cout<<empty_list_element->object<<endl;
      empty_list_element=empty_list_element->next;
    }
    empty_list_element->next=new listOfObjects<int>(indexOfName);
    cout<<empty_list_element->object<<endl;
    }
  }

  // Mark as end of a word  
  currNode->isWord=true;
  return true;



  
}

bool Trie::del(string wordInName, string name) {
  TrieNode *currNode = root;
  
  int delete_result = 0;

  int lastBranchChar = -1;
  int len = wordInName.length();
  
  for (int i=0;i<len;i++){
  char curr_char_index = wordInName[i] - 'A';
  if (currNode->branch[curr_char_index]!=nullptr){
   lastBranchChar=curr_char_index;
   
   currNode=currNode->branch[curr_char_index];
      
  }
  else return false;
  }
  
  if(currNode->isWord){
    //check if any index associated matches requirement.
    listOfObjects<int>* moving_pointer=currNode->indices, *prev_pointer=nullptr;

    while(true){
      if(nameDict->getKeyAtIndex( moving_pointer->object)==name) break;
      else if (moving_pointer==nullptr) return false;
      prev_pointer=moving_pointer;
      moving_pointer=moving_pointer->next;
    }
    
    if(prev_pointer==nullptr){currNode->indices=currNode->indices->next;}
    else {prev_pointer->next = moving_pointer->next; delete moving_pointer;}

    if(currNode->indices==nullptr)currNode->isWord=false;

    while(currNode->numNonNullBranches==0 and currNode->isWord==false){
      len--;
      currNode=currNode->prev;
      delete currNode->branch[wordInName[len]-'A'];
      currNode->numNonNullBranches-=1;
      currNode->branch[wordInName[len]-'A'] = nullptr;
    }

    return true;
  }
  else return 0;

}

listOfObjects<string>* Trie::findCompletions(TrieNode* node){
  if(node==nullptr){return nullptr;}
  else{
    listOfObjects<int>* moving_node=node->indices;
    listOfObjects<string>* string_node = new listOfObjects<string>(nameDict->getKeyAtIndex(moving_node->object));
    listOfObjects<string>* marker = string_node;
    

    if(node->isWord){
      
      

      while(moving_node->next!=nullptr){
        
        string_node->next = new listOfObjects<string>(nameDict->getKeyAtIndex(moving_node->next->object));
        string_node= string_node->next;
        
        moving_node= moving_node->next;
      }
    }

    for(int i=0;i<=25;i++){
      string_node = findCompletions(node->branch[i]);

      listOfObjects<string>* end_finder = string_node;
      while(string_node->next!=nullptr){
        string_node=string_node->next;
      }
    }

    return marker;
  }


}
  

listOfObjects<string> * Trie::completions(string prefix) {
  TrieNode *currNode = root;
  

  int len = prefix.length();
  listOfObjects<string> *currCompletions = new listOfObjects<string>("__Placeholder__");
  
  if(isPresent(prefix)){
    
    int i=0;
    
    while(i<len){
      prefix[i] = toupper(prefix[i]);
      currNode=currNode->branch[prefix[i]-'A'];
      i++;
    }
    recursiveAddCompletions(currNode, currCompletions);

    currCompletions=currCompletions->next;
    
    return currCompletions;
  }
  else return nullptr;
  
  
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
  listOfObjects<int>* index_node = node->indices;
  while(currCompletions->next!=nullptr){
    
    currCompletions=currCompletions->next;
    
  }
  while(index_node!=nullptr){
    
    currCompletions->next= new listOfObjects<string>(nameDict->getKeyAtIndex(index_node->object));
    
    currCompletions=currCompletions->next;
    index_node=index_node->next;
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

  return true;
  
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
