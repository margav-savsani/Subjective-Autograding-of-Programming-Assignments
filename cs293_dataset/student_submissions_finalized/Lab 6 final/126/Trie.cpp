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
  int i=0;
  while(true){
    currNode=root;
    while(true){
        if(i==len){
            currNode->isWord=true;
            listOfObjects<int> *curr=currNode->indices;
            if(curr==nullptr){
                currNode->indices=new listOfObjects<int>(indexOfName);
            }
            else{
                while(curr->next!=nullptr){
                    curr=curr->next;
                }
                curr->next=new listOfObjects<int>(indexOfName);
            }
            i++;
            break;
        }
        else{
            if(wordInName[i]>='a'&&wordInName[i]<='z'){
                if(currNode->branch[wordInName[i]-'a']==nullptr){
                    TrieNode *newNode=new TrieNode;
                    currNode->branch[wordInName[i]-'a']=newNode;
                    currNode->numNonNullBranches+=1;
                    listOfObjects<int> *curr=currNode->indices;
                    if(curr==nullptr){
                        currNode->indices=new listOfObjects<int>(indexOfName);
                    }
                    else{
                        while(curr->next!=nullptr){
                            curr=curr->next;
                        }
                        curr->next=new listOfObjects<int>(indexOfName);
                    }
                    currNode=currNode->branch[wordInName[i]-'a'];
                    i++;
                }
                else{
                    currNode->numNonNullBranches+=1;
                    listOfObjects<int> *curr=currNode->indices;
                    if(curr==nullptr){
                        currNode->indices=new listOfObjects<int>(indexOfName);
                    }
                    else{
                        while(curr->next!=nullptr){
                            curr=curr->next;
                        }
                        curr->next=new listOfObjects<int>(indexOfName);
                    }
                    currNode=currNode->branch[wordInName[i]-'a'];
                    i++;
                }
            }
            else{
                if(currNode->branch[wordInName[i]-'A']==nullptr){
                    TrieNode *newNode=new TrieNode;
                    currNode->branch[wordInName[i]-'A']=newNode;
                    currNode->numNonNullBranches+=1;
                    listOfObjects<int> *curr=currNode->indices;
                    if(curr==nullptr){
                        currNode->indices=new listOfObjects<int>(indexOfName);
                    }
                    else{
                        while(curr->next!=nullptr){
                            curr=curr->next;
                        }
                        curr->next=new listOfObjects<int>(indexOfName);
                    }
                    currNode=currNode->branch[wordInName[i]-'A'];
                    i++;
                }
                else{
                    currNode->numNonNullBranches+=1;
                    listOfObjects<int> *curr=currNode->indices;
                    if(curr==nullptr){
                        currNode->indices=new listOfObjects<int>(indexOfName);
                    }
                    else{
                        while(curr->next!=nullptr){
                            curr=curr->next;
                        }
                        curr->next=new listOfObjects<int>(indexOfName);
                    }
                    currNode=currNode->branch[wordInName[i]-'A'];
                    i++;
                }
            }
        }
    }
    if(i>len){
        break;
    }
  }
  return true;
}

bool Trie::del(string wordInName, string name) {
  TrieNode *currNode = root;
  TrieNode *lastForkOrWord = root;
  TrieNode *lastBranchNode = nullptr;
  int lastIndex=0;
  int lastBranchChar = -1;
  int len = wordInName.length();
   
  int flag=0;
  // Insert your code here
  int i=0;
    for(int i=0; i<len; i++){
        if(wordInName[i]>='a' && wordInName[i]<='z'){
            if(currNode->branch[wordInName[i]-'a'] == nullptr){
                return false;
            }
            else{
                listOfObjects<int> *curr=currNode->indices;
                if(nameDict->getKeyAtIndex(currNode->indices->object) == name){
                    currNode->indices=currNode->indices->next;
                }
                else{
                    while(curr->next!=nullptr){
                        if(nameDict->getKeyAtIndex(curr->next->object) == name){
                            curr->next=curr->next->next;
                        }
                    }
                }
                for(int j=0; j<26; j++){
                    if(currNode->branch[j]!=nullptr && (j != (int)wordInName[i]-'a')){
                        lastForkOrWord=currNode;
                        lastIndex=j;
                        break;
                    }
                }
                if(currNode->isWord==true and (i<len-1)){
                    lastForkOrWord=currNode;
                    lastIndex = wordInName[i]-'a';
                }
                currNode=currNode->branch[wordInName[i]-'a'];
            }
        }
        else{
            if(currNode->branch[wordInName[i]-'A'] == nullptr){
                return false;
            }
            else{
                listOfObjects<int> *curr=currNode->indices;
                if(nameDict->getKeyAtIndex(currNode->indices->object) == name){
                    currNode->indices=currNode->indices->next;
                }
                else{
                    while(curr->next!=nullptr){
                        if(nameDict->getKeyAtIndex(curr->next->object) == name){
                            curr->next=curr->next->next;
                        }
                    }
                }
                for(int j=0; j<26; j++){
                    if(currNode->branch[j]!=nullptr && (j != (int)wordInName[i]-'A')){
                        lastForkOrWord=currNode;
                        lastIndex=j;
                        break;
                    }
                }
                if(currNode->isWord==true and (i<len-1)){
                    lastForkOrWord=currNode;
                    lastIndex= wordInName[i]-'A';
                }
                currNode=currNode->branch[wordInName[i]-'A'];
            }
        }
    }
    for(int i=0; i<26; i++){
        if(currNode->branch[i]!=nullptr){
            return true;
        }
    }
    if(currNode->indices != nullptr){
        return true;
    }
    
    lastForkOrWord->branch[lastIndex]=nullptr;
  
  return true;
}

listOfObjects<string> * Trie::completions(string prefix) {
  TrieNode *currNode = root;
  int len = prefix.length();
  listOfObjects<string> *currCompletions = nullptr;
  listOfObjects<string> *curr=currCompletions;

  // Insert your code here
  for(int i=0; i<len; i++){
        if(prefix[i]>='a' && prefix[i]<='z'){
            if(currNode->branch[prefix[i]-'a'] == nullptr){
                break;
            }
            else{
                currNode=currNode->branch[prefix[i]-'a'];
            }
        }
        else{
            if(currNode->branch[prefix[i]-'A'] == nullptr){
                break;
            }
            else{
                currNode=currNode->branch[prefix[i]-'A'];
            }
        }
    }
    listOfObjects<int> *curr1=currNode->indices;
    while(curr1!=nullptr){
        listOfObjects<string> *newString=new listOfObjects<string>(nameDict->getKeyAtIndex(curr1->object));
        if(curr==nullptr){
            currCompletions=newString;
            curr=currCompletions;
            curr1=curr1->next;
            continue;
        }
        else{
            curr->next=newString;
        }
        curr=curr->next;
        curr1=curr1->next;
    }
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
  return false;
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
