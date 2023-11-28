#ifndef TRIE_CPP
#define TRIE_CPP
#include <vector>
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
  int letter;
  // Insert your code here
  
  for(int i=0;i<len;i++){ 

  char word=wordInName[i];
  int letter = int(word)-'A';
  
  if(currNode->branch[letter]==nullptr){
    currNode->branch[letter]=new TrieNode();
    currNode->numNonNullBranches++;

    if(i==len-1){
      currNode->branch[letter]->isWord=true;
      listOfObjects<int> *list= currNode->branch[letter]->indices;

      if(list==nullptr){
        currNode->branch[letter]->indices=new listOfObjects<int>(indexOfName);
        list=new listOfObjects<int>(indexOfName);
      }
      else{
        while(list->next!=nullptr){
          list=list->next;
        }   
        list->next=new listOfObjects<int>(indexOfName);

      } 
    }
    currNode=currNode->branch[letter];
  }
  
  else if(currNode->branch[letter]!=nullptr and i==len-1){
      currNode->branch[letter]->isWord=true;
      listOfObjects<int> *list= currNode->branch[letter]->indices;

      if(list==nullptr){
        currNode->branch[letter]->indices=new listOfObjects<int>(indexOfName);
        list=new listOfObjects<int>(indexOfName);
      }
      else{
        while(list->next!=nullptr){
          list=list->next;
        }   
        list->next=new listOfObjects<int>(indexOfName);
      } 
    
    currNode=currNode->branch[letter];
  }
  else{
    currNode=currNode->branch[letter];
  }

  }
  return true;
  

}
bool Trie::del(string wordInName, string name) {
  TrieNode *currNode = root;
  int len = wordInName.length();
  TrieNode *dummy=nullptr;
  int dumm;
  // Insert your code here
  for(int i=0;i<len-1;i++){
    int let=int(wordInName[i]-'A');
    if(currNode->isWord){
      dummy=currNode;
      dumm=i;
    }
    currNode=currNode->branch[let];
  }

  int let=int(wordInName[len-1]-'A');
  currNode=currNode->branch[let];


  listOfObjects<int> *list=currNode->indices;
  
  if(nameDict->getKeyAtIndex(currNode->indices->object)==name){
    currNode->indices=currNode->indices->next;
    if(currNode->indices==nullptr){
      currNode->isWord=false;
    //  delete dummy->branch[int(wordInName[dumm+1])-'A'];
    }
  }
  else{
  while(nameDict->getKeyAtIndex(list->next->object)!=name && list->next!=nullptr){
  
    list=list->next;
  }
  list->next=list->next->next;

  }
  return true;
}

listOfObjects<string> * Trie::completions(string prefix) {
  TrieNode *currNode = root;
  int len = prefix.length();
  listOfObjects<string> *currCompletions = nullptr;
  currCompletions=new listOfObjects<string>("Srithan");
  // Insert your code here

   for(int i=0;i<len;i++){

     int position=int(prefix[i])-'A';
     currNode=currNode->branch[position];
  
   }   
  

  recursiveAddCompletions(currNode,currCompletions);
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

  // Insert your code here
  listOfObjects<int> *list= node->indices;

  
  
  
    while(list!=nullptr){

      while(currCompletions->next==nullptr){
      
      int index=list->object;
      
      currCompletions->next=new listOfObjects<string>(nameDict->getKeyAtIndex(index));

      listOfObjects<int> *Srithan= nullptr;

      Srithan=list->next;
     
      list=Srithan;
      
      }

      currCompletions=currCompletions->next;
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
  cout<<len<<endl;
  int letter;
  for (int i = 0; i < len; i++) {
    if(toupper(wordInName.at(i)!=32)){
    letter = toupper(wordInName.at(i)) - 'A';
    }
    else {letter=26;}

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
