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

#include<cstring>
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
  int i=0; // the length of the string wordInName traversed
  for(auto c:wordInName){ 
	i++; 	
  	int d = toupper(c);
  	d-=65; // finding index of a character in branches array
  	if(currNode->branch[d] != nullptr){
  		currNode = currNode->branch[d]; // updating currNode
  		if(i==len){ // final point of addition(need to update the indices linked list as well
  			currNode->isWord = true; // making isWord true to show that on this index the word ends and also to let the calling function know that the linked list at this TrieNode is not null.
  			listOfObjects<int> *y = new listOfObjects<int>(indexOfName); //objects list 
  			//inserting the required node in the liked list of indices
  			y->next = currNode->indices; 
  			currNode->indices = y;
  			y=nullptr;
  		}
  	}
  	else{
  		if(i>len){
  			break;
  		}
  		currNode->numNonNullBranches += 1;
  		currNode->branch[d] = new TrieNode;
  		currNode = currNode->branch[d];
  		if(i==len){
  			currNode->isWord = true;// making isWord true to show that on this index the word ends and also to let the calling function know that the linked list at this TrieNode is not null.
  			listOfObjects<int> *y = new listOfObjects<int>(indexOfName);
  			//inserting the required node in the liked list of indices
  			y->next = currNode->indices;
  			currNode->indices = y;
  			y=nullptr;
  		}
  	}
  }
  return true;
  // Insert your code here

}

bool Trie::del(string wordInName, string name){
  TrieNode *currNode = root;
  TrieNode *lastBranchNode = nullptr;
  int lastBranchChar = -1;
  int len = wordInName.length();
  int i=0;
  TrieNode *flag = root; // flag represents the node representing the char in wordInName after which we may need to delete all the pointers to TrieNodes representing the following characters in wordInName
  char flag_letter{wordInName[0]};//letter including and follwwing which all letters may be needed to be deleted from Trie
  for(auto c:wordInName){
  	i++; 	
  	int d = toupper(c);
  	d-=65;
  	if(currNode->branch[d] != nullptr){ //traversing through the wordInName
  		currNode = currNode->branch[d];
  		if(currNode->numNonNullBranches >= 2){ //flag are the Trienodes having more than two non null branches except in some special cases
  			flag = currNode; 
  			flag_letter = wordInName[i];
  		}
  		if(i==len){ // found the wordInName, now does all the messy delete stuff
  			
  			auto currIndices = currNode->indices;
  			if(currIndices == nullptr) // if currIndices are not even a word 
  				return false;
  			int j=-1;
  			bool returnv{true};
  			//loops through the indices in the currNode finds if the station name given by name is present in it or not. If present ,it sets the returnv boolean to false indicating to carry forward the deletion,e else it sets the returnv to false indicating to return false.
  			while (currIndices != nullptr) {
  				j++;
  				string add{nameDict->getKeyAtIndex(currIndices->object)};
  				currIndices = currIndices->next;	
  				if(add == name){
  					returnv = false;
  					if(j==0){
  						currNode->indices = currIndices;
  					}
  					else{
  						auto r = currNode->indices;
  						for(int k=0;k<j-1;k++){
  							r = r->next;
  						}
  						r->next = currIndices;
  					}
  					break;
  				}
  			}
  			if(returnv){
  				return false;
  			}
  			//delete tteh entries in Trie if the indices list becomes empty
  			if(currNode->indices == nullptr){
	  			if(currNode -> numNonNullBranches >= 1){
	  				currNode->isWord = false;
	  			}
	  			else{
	  				currNode->isWord = false;
	  				int d =toupper(flag_letter);
	  				d-=65;
	  				flag->numNonNullBranches--;
	  				recursiveDelete(flag->branch[d]);
	  				flag->branch[d] = nullptr;
	  			}
  			}
  		}
  	}
  	else{
  		return false;
  	}
  }
  // Insert your code here
  return true;
}

listOfObjects<string> * Trie::completions(string prefix) {
  TrieNode *currNode = root;
  int len = prefix.length();
  listOfObjects<string> *currCompletions = new listOfObjects<string>(""); //intialiase with a linked list node
  
  int i=0;
  for(auto c:prefix){
  	i++;
  	int d=toupper(c);
  	d-=65;
  	//finds the node matching the last char in prefix and calls another function responsible for actually making the currCompletions 
  	if(currNode->branch[d] != nullptr){
  		currNode = currNode->branch[d];
  		if(i==len){
  			recursiveAddCompletions(currNode, currCompletions); 
  			break;
  		}
  	}
  	else{
  		return nullptr;
  	}
  }
  
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
  
  listOfObjects<int> *currIndices = node->indices;
  bool addon{true};
  while (currIndices != nullptr) {
  	string add{nameDict->getKeyAtIndex(currIndices->object)};
  	auto y = currCompletions;
  	//checks whether the station name is already present in the currCompletions list or not
  	while(y->next!=nullptr){
  		if(y->object == add)
  			addon = false;
  		y = y->next;
  	}
  	if(y->object == add)
  		addon = false;
  	if(addon){//if station name is not present in the currCompletions list then add it
		if(currCompletions->object == ""){ //updating the currCompletions first node if it is till now unchanged/not updated even once
			currCompletions->object = add;
		}
		else{
			auto x = new listOfObjects<string>(add); // makes new nodes and adds it to the linked list represented by currCompletions
			y->next = x;
		}
		y=nullptr;
	}
	addon = true;
	currIndices = currIndices->next; // updating the value of currIndices for loop
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
