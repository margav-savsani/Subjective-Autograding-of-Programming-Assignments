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
//This function update the indices of the node whose isWord is True i.e. we add the name in the indices of this word.
void updateindices(listOfObjects<int> *indices, int indexOfName , TrieNode* root){
  if(indices==nullptr){
    indices = new listOfObjects<int>(indexOfName);
    root->indices=indices;
  }
  else{
    listOfObjects<int> *indices1 = indices;
    while(indices->next!=nullptr){
      indices=indices->next;
    }
    if(indices->next==nullptr){
      indices->next=new listOfObjects<int>(indexOfName);
      root->indices=indices1;
    }
  }
}

void insertWord(TrieNode *root, string word, int indexOfName)
{
    // using recursion base case ;
    if (word.length() == 0)
    {
      if(root->isWord==true){
        updateindices(root->indices, indexOfName, root);
      }else{
        root->isWord = true;
        updateindices(root->indices, indexOfName, root);
      }
      return;
    }
    // taking every word in caps latter ;
    int index = toupper(word[0]) - 'A'; // here word[0] is the word at first postion and givin it to its assci value;
    TrieNode *child;
    // there are two case to insert word into the trie 1) word is present 2) word is not present ;

    // first if the word is peresent into the trie
    if (root->branch[index] != nullptr)
    {
      child = root->branch[index];
    }
    else // word is not present into the trie so we have to insert;
    {
      child = new TrieNode(word[0]);
      root->branch[index] = child;
    }

    // now further word will done by recursion
    insertWord(child, word.substr(1), indexOfName);
}

bool Trie::insert(string wordInName, int indexOfName) {

  // Insert your code here
  insertWord(root, wordInName, indexOfName);
  return true;
}

//function to delete the indice with key as name
bool deleteinlist(listOfObjects<int> *indices, string name, TrieNode* root, Dictionary<int>* nameDict, bool &onlyOneindice){
  if(indices->next==nullptr){  //base case where only one indice at the node
      indices=nullptr;
      root->indices=indices;
      root->isWord=false;
      onlyOneindice=true;
      return true;
  }else{                      //more than one indices at the node
    listOfObjects<int> *indices_parent=nullptr;   //pointer to keep track of the prev indice while iteration over the indices list
    listOfObjects<int> *head=indices;
    bool found =false;
    if(!nameDict->getKeyAtIndex(indices->object).compare(name)){  //if name matches with the key at the first indice only
      root->indices=indices->next;
      return true;
    }
    while(indices!=nullptr){
      indices_parent=indices;
      indices=indices->next;
      if(!nameDict->getKeyAtIndex(indices->object).compare(name)){
        if(indices->next!=nullptr){
          indices_parent->next=indices->next;
          found=true;
          break;
        }else{
          indices_parent->next=nullptr;
          found=true;
          break;
        }
      }
    }
    if(found==false){   //if no indice is found in the list
      return false;
    }else{
      root->indices=head;
      return true;
    }
  }
}

//return true if there are no nonempty children of the node otherwise false.
bool isEmpty(TrieNode* root){
  for(int i=0; i<26; i++){
    if(root->branch[i]!=nullptr){
      return false;
    }
  }
  return true;
}



TrieNode* remove(TrieNode* root, string wordInName, int depth, string name, Dictionary<int>* nameDict){
  if(root==nullptr){
    return nullptr;
  }
  if(depth==wordInName.size()){  //we reach the end of the word
    bool onlyOneindice = false;  //boolean to check if there is only one indice of the node with isWord true
    if(root->isWord){
      deleteinlist(root->indices, name, root, nameDict, onlyOneindice); //this function is called to delete the indice with the key as name
    }
    if(onlyOneindice){            //if onlyOneIndice was true then we delete this node if isEmpty is true for this node 
      if(isEmpty(root)){          //and return null pointer to the recursive call that was made.
        delete(root);
        root=nullptr;
      }
    }
    return root;
  }

  int index = toupper(wordInName[depth])-'A';                          //finding index
  root->branch[index]=remove(root->branch[index], wordInName, depth+1, name, nameDict);  //recursive call with depth+1
  if(isEmpty(root) && root->isWord==false){                   //delete the node if isEmpty is true for this node
    delete(root);
    root=nullptr;
  }
  return root;
}


//function to check if there is only one word stored in the trie.
bool onlyOneWordInTrie(TrieNode* root){
  while(root!=nullptr){
    int count = 0;   //variable to store the number of children of a node
    for(int i=0; i<26; i++){
      if(root->branch[i]!=nullptr){
        count+=1;
        if(count>1){
          return false;
        }
      }
    }
    for(int i=0; i<26; i++){
      if(isEmpty(root)){     //check for root
        return true;
      }
      if(root->branch[i]!=nullptr){
        root=root->branch[i];
      }
    }
  }
  return true;
}


//delete function in trie
bool Trie::del(string wordInName, string name) {

  // Insert your code here
  if(remove(root,wordInName,0,name,nameDict)==nullptr && !onlyOneWordInTrie(root)){
    return false;
  }else{
    return true;
  }
}


listOfObjects<string> * Trie::completions(string prefix) {
  TrieNode *currNode = root;
  int len = prefix.length();
  listOfObjects<string> *currCompletions = nullptr;

  // Insert your code here
  for(int i=0; i<=len; i++){
    if(i==len){    //when we reach to the node corresponding to the letter at the end of the prefix
      listOfObjects<string> * comp = recursiveAddCompletions(currNode, currCompletions);
      return comp;
    }else{
      int index = toupper(prefix[i]) - 'A';
      if(currNode->branch[index]!=nullptr){
        currNode=currNode->branch[index];
      }
    }
  }
  
}

listOfObjects<string>* Trie::recursiveAddCompletions(TrieNode *node, listOfObjects<string> *currCompletions) {
  if (node->isWord) {
    currCompletions = addCompletions(node, currCompletions);
  }
  TrieNode *currNode = node;
  for (int i = 0; i < NUM_CHARS; i++) {
    if (currNode->branch[i] != nullptr) {
      currCompletions = recursiveAddCompletions(currNode->branch[i], currCompletions);
    }
  }
  return currCompletions;
}

listOfObjects<string>* Trie::addCompletions(TrieNode *node, listOfObjects<string> *currCompletions) {

  // Insert your code here
  if(node==nullptr){
    return nullptr;
  }
  if(currCompletions==nullptr){  //case when the list currCompletions is empty initially
    listOfObjects<string> *currCompletions1 = new listOfObjects<string>(nameDict->getKeyAtIndex(node->indices->object));
    listOfObjects<string> *currCompletions2 = currCompletions1;  // pointer to keep track of the head node of the list
    listOfObjects<int> * indices = node->indices->next;
    while(indices!=nullptr){
      listOfObjects<string> *a = new listOfObjects<string>(nameDict->getKeyAtIndex(indices->object));
      currCompletions1->next = a;
      indices=indices->next;
      currCompletions1=currCompletions1->next;
    }
    currCompletions = currCompletions2;
    return currCompletions;
  }else{                             //case when the list of completions already has some nodes
    listOfObjects<string> * a = currCompletions;
    while(a->next!=nullptr){         //reach at the end of the list of currcompletions from where we have to insert the nodes
      a=a->next;
    }
    listOfObjects<int> * indices = node->indices;
    while(indices!=nullptr){
      listOfObjects<string> *b = new listOfObjects<string>(nameDict->getKeyAtIndex(indices->object));
      a->next = b;
      indices=indices->next;
      a=a->next;
    }
    return currCompletions;
  }
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


