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

//constructor for the trie.
Trie::Trie(Dictionary<int> *nameToIndex) {
  nameDict = nameToIndex;   //dictionary storing all the station names.
  root = new TrieNode();
  if (root == nullptr) {
    cout << "Memory allocation failure." << endl;
    exit(-1);
  }
}

//destructor for the trie.
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

//a function I have defined to insert a new node into a linked list of type listOfObects<int>
bool insertIntoList(int val,listOfObjects<int>* linkedList){
  while(linkedList->next){
    if(linkedList->object==val){
      return false;   //the given value already exists
    }
    linkedList=linkedList->next;    //goes to the next node.
  }
  linkedList->next=new listOfObjects<int>(val);   //creates a new node with the required value
  return true;
}

//inserts a station word into the trie.
bool Trie::insert(string wordInName, int indexOfName) {
  TrieNode *currNode = root;
  int len = wordInName.length();    //length of the word to be inserted

  int hit=-1;   //variable checks if we have reached the last existing node for the required word's insertion
  //this variable takes value equal to the index of the word which is the last existing node.
  bool first=true;
  for(int i=0;i<len;i++){
    int index=toupper(wordInName.at(i))-'A';
    if(hit<0 && !currNode->branch[index]){
      //we have found the last existing node
      hit=i;
    }
    else if(hit<0){
      currNode=currNode->branch[index];   //goes to its child
      if(i==len-1){
        hit=i;
        first=false;
      }
    }

    if(hit>=0){
      if(first){
        currNode->branch[index]=new TrieNode();
        currNode->numNonNullBranches++;
        currNode=currNode->branch[index];
      }
      if(i==len-1){
        currNode->isWord=true;
        if(currNode->indices){
          insertIntoList(indexOfName,currNode->indices);    //inserting the node into the list
        }
        else{
          currNode->indices=new listOfObjects<int>(indexOfName);    //case where list was null, we create a new list
        }
      }
    }
  }

  return true;
}

//deletes a station word from the trie.
bool Trie::del(string wordInName, string name) {
  TrieNode *currNode = root;
  TrieNode *lastBranchNode = nullptr;
  int lastBranchChar = -1;
  int len = wordInName.length();

  bool hasWord=false;   //checks if there is another word which is a prefix of our word
  bool hasBranch=false;
  int depth=0;
  int branchDepth;
  int wordDepth;
  for(int i=0;i<len;i++){
    int index=toupper(wordInName.at(i))-'A';
    if(!currNode->branch[index]){
      return false;   //false if the word isnt in the trie.
    }
    else{
      if(currNode->isWord){
        hasWord=true;
        wordDepth=depth;
      }
      currNode=currNode->branch[index];
      depth++;
      if(currNode->numNonNullBranches>1){
        hasBranch=true;
        hasWord=false;
        branchDepth=depth;
      }
    }
  }
  if(currNode->numNonNullBranches>0){   //case where the word to be deleted is a prefix
    if(currNode->indices){
      listOfObjects<int>* temp=currNode->indices;
      if(nameDict->getKeyAtIndex(temp->object)==name){
        listOfObjects<int>* toDelete=temp;
        currNode->indices=toDelete->next;
        delete toDelete;
        if(!currNode->indices){
          currNode->isWord=false;
        }
        return true;
      }
      while(temp->next){    //when there are multiple indices in the list.
        if(nameDict->getKeyAtIndex(temp->next->object)==name){
          listOfObjects<int>* toDelete=temp->next;
          temp->next=toDelete->next;
          delete toDelete;
          return true;
        }
      }
    }
  }
  if(!hasWord){   //there exists no prefix to this word which is also a word
    if(currNode->indices->next){    //multiple indices in the list  
      //just delete name from the list which has >=2 station indices
      listOfObjects<int>* temp=currNode->indices;
      if(nameDict->getKeyAtIndex(temp->object)==name){
        listOfObjects<int>* toDelete=temp;
        currNode->indices=toDelete->next;
        delete toDelete;
        return true;
      }
      while(temp->next){
        if(nameDict->getKeyAtIndex(temp->next->object)==name){
          listOfObjects<int>* toDelete=temp->next;
          temp->next=toDelete->next;
          delete toDelete;
          return true;
        }
      }
    }
    else{
      //list has 1 element which is to be deleted and the word is to be removed from the trie
      if(!hasBranch){
        root->branch[toupper(wordInName.at(0))-'A']=nullptr;
      }
      else{
        currNode=root;
        for(int i=0;i<branchDepth;i++){
          int index=toupper(wordInName.at(i))-'A';
          currNode=currNode->branch[index];
        }
        currNode->branch[toupper(wordInName.at(branchDepth))-'A']=nullptr;
      }
      return true;
    }
  }
  else{   //there is a prefix which is a word.
    if(currNode->indices->next){
      //just delete name from the list which has >=2 station indices
      listOfObjects<int>* temp=currNode->indices;
      if(nameDict->getKeyAtIndex(temp->object)==name){
        listOfObjects<int>* toDelete=temp;
        currNode->indices=toDelete->next;
        delete toDelete;
        return true;
      }
      while(temp->next){
        if(nameDict->getKeyAtIndex(temp->next->object)==name){
          listOfObjects<int>* toDelete=temp->next;
          temp->next=toDelete->next;
          delete toDelete;
          return true;
        }
      }
    }
    else{
      currNode=root;
      for(int i=0;i<wordDepth;i++){
        int index=toupper(wordInName.at(i))-'A';
        currNode=currNode->branch[index];
      }
      currNode->branch[toupper(wordInName.at(wordDepth))-'A']=nullptr;
      return true;
    }
  }

}

listOfObjects<string> * Trie::completions(string prefix) {
  TrieNode *currNode = root;
  int len = prefix.length();
  listOfObjects<string> *currCompletions = new listOfObjects<string>("placeholder");
  //placeholder basically just ensures we don't start with a nullptr, which gives error.
  // Insert your code here
  for(int i=0;i<len;i++){
    int index=toupper(prefix.at(i))-'A';
    if(!currNode->branch[index]){   //not found in the trie
      break;
    }
    else{
      currNode=currNode->branch[index];
    }
    if(i==len-1){
      recursiveAddCompletions(currNode,currCompletions);    //adds the completions given currNode which is the node where the prefix ends
    }
  }
  return currCompletions->next;   //we return this so that placeholder doesn't also get returned.
  
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


bool insertCompletion(string val,listOfObjects<string>* linkedList){
  while(linkedList->next){
    if(linkedList->object==val){
      return false;   //the given value already exists
    }
    linkedList=linkedList->next;
  }
  linkedList->next=new listOfObjects<string>(val);
  return true;
}

bool Trie::addCompletions(TrieNode *node, listOfObjects<string> *currCompletions) {
  listOfObjects<int>* indexList=node->indices;
  while(indexList){
    if(currCompletions){
      insertCompletion(nameDict->getKeyAtIndex(indexList->object),currCompletions);   //inserts to the linkedList.
    }
    else{
      currCompletions=new listOfObjects<string>(nameDict->getKeyAtIndex(indexList->object));
    }
    indexList=indexList->next;
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
