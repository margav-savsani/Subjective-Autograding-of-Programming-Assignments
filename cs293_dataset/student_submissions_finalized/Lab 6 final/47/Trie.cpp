#ifndef TRIE_CPP
#define TRIE_CPP

#ifndef STD_HEADERS
#include "std_headers.h"
#endif

#ifndef DICTIONARY_H
#endif

#ifndef TRIE_H
#include "Trie.h"
#endif

#include<vector>
#include<bits/stdc++.h>


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



bool Trie::insert(string wordInName, int indexOfName) { // to insert the wordInName into Trie

		transform(wordInName.begin(), wordInName.end(), wordInName.begin(), ::toupper);// changing everyword into upper
  		TrieNode *currNode = root;
  		int len = wordInName.length(); // length of word.
  		int n=0; // to Keep tract of no of wordInName inserted.
  		
 		while ( n < len ) {
  
  			if ( currNode->branch[int((wordInName[n]))-65] != nullptr ) {// always insert capital words, otherwise it shows errors.
  		
  					
  				
  				currNode = currNode->branch[int((wordInName[n]))-65];
				n++;
  				
  			
  			}
  			
  			else {
  		
  			 
  			 	for ( int j = n; j<len; j++){
  			 	
  			 		
  			 		currNode->branch[int((wordInName[n]))-65] = new TrieNode(); // since the corresponding char is inserted, change current Node to its branch.
  			 		currNode->numNonNullBranches++;
  			 		currNode = currNode->branch[int((wordInName[n]))-65];
					n++;
						
  			 	}
  			
  			}
  		}
  
  		if ( currNode->isWord == false ) { // if it is the first indices 
  
  			currNode->isWord = true;
  			currNode->indices = new listOfObjects<int>( indexOfName );

  		}
  		
 		else {
  
  			listOfObjects<int> *curr = currNode->indices; // pointer to the current Node
  			listOfObjects<int> *prev; // pointer to the previous node of the current Node
  			bool found = false;
  	
  			while ( curr != nullptr ) {
  	
  				prev = curr;
  				if (curr->object == indexOfName){ // check whether current Node has object as IndexOfName
  			
  					found = true;
  					break;
  				}	
  		
  		
  				curr = curr->next;
  			}
  	
  			if ( !found ) { // if the IndexOfname is not found, just insert the indices 
  	
  				prev->next = new listOfObjects<int>(indexOfName);
  		
  			}

  			
  		}
  			 	
 
    		return true;				 
}


bool Trie::del(string wordInName, string name) {

  Entry<int>* e = nameDict->get( name ); // checks whether the name is present in the dictionary or not.
  
  if ( e != nullptr ){// if it is present 
  
  	TrieNode *currNode = root;
 	//TrieNode *lastBranchNode = nullptr;
  	//int lastBranchChar = -1;
  	int len = wordInName.length();
  	int n = 0;
  
  	while ( n < len ) {
  	
  	
  			
  		if ( currNode->branch[int((wordInName[n]))-65] != nullptr ) { // if the char is present 
  		
  				
  			currNode = currNode->branch[int((wordInName[n]))-65];
			n++; 
  		}
  		
  		else { // break the loop if the char is not present in the trie, but it doesnt happen, because we already checked the condition before.
  			
  			break;
  		}

  	
  	}
  	
  	if ( n != len ) { // this case doesnt happen but just in case, if it happens
  
  		return false;
  	}
  
  	else { // after coming to the end of the trie.
  
  		int index = e->value; // finding the value that we have to delete
  		
  		listOfObjects<int>* x = currNode->indices;
  		listOfObjects<int>* prev = x;
  		
  		while ( x != nullptr ) { // move untill u find the index
  	
  			prev = x;
  			if ( x-> object == index ) {
  				
  				break;
  			}
  			x = x->next;
  			
  		}
  		prev = x->next;

  		
  	
  	}
  
  
  	return true;
  }
  
  else { // if the string is not present in dictionary
  
  	return false;
  }
  
  
}

listOfObjects<string> * Trie::completions(string prefix) {
  
  TrieNode *currNode = root;
  int len = prefix.length();
  //listOfObjects<string> *currCompletions = nullptr;
  int n = 0;
  bool change = false;
  while ( n < len && !change ) {
  	
 
  	if ( currNode->branch[int((prefix[n]))-65] != nullptr ) { // prefix char is present in the trie.
  		
  			
  		currNode = currNode->branch[int((prefix[n]))-65];
		n++;
		
  	}
  	else { // prefix char is not present in the trie
  			
  		change = true;
  		break;

  	}
  	
  }
  
  if ( change == true ) {
  
  	return nullptr;
  }
  
  else if ( n == len &&  currNode->isWord == true){ // return the strings in the indices.
  
  	listOfObjects<int>* x = currNode->indices;
  	listOfObjects<string>* y = new listOfObjects<string>(nameDict->getKeyAtIndex(x->object));// get the key at corresponding index.
  	listOfObjects<string>* z = y;
  	x = x->next;
  	while ( x != nullptr ) {
  	
  		z->next =  new listOfObjects<string>(nameDict->getKeyAtIndex(x->object));
  		z = z->next;
		x = x->next;
  	}
  	return y;// return the list of strings
  	
  }
  else if ( n==len ) {
  
  	listOfObjects<string>* y ;
	y = nullptr;
  	y = addCompletions( currNode, y);
  	
  	
	return y;
  }
  
  return nullptr;
  		
  
  	
  
  // Insert your code here
  
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

listOfObjects<string> * add ( listOfObjects<string> *currCompletions, string s){// check whether string s is present in currCompletions or not, then add the string s into currCompletions


	if ( currCompletions == nullptr ) {
	
		currCompletions = new listOfObjects<string>(s);
		return currCompletions;
	}
	listOfObjects<string> * curr = currCompletions;
	listOfObjects<string> * prev = curr;
	
	
	while ( curr != nullptr ) {
		
		prev = curr;
	    
		if ( curr->next != nullptr)
		curr = curr->next;
		else 
		curr = nullptr;
		
	}
	
	if ( prev != nullptr){
	
	prev->next = new listOfObjects<string>( s );// add string s at the last of the currCompletions.
	}
	return currCompletions;
}
	
listOfObjects<string> * Trie::addCompletions(TrieNode *node, listOfObjects<string> *currCompletions) {

  // Insert your code here
  
  if ( node != nullptr ){
  
  	
  	if ( node -> isWord == true ) {
  	
  		listOfObjects<int> *x = node->indices;
  	
  		while ( x!= nullptr ){
  	
  			string s = nameDict->getKeyAtIndex( x->object );
  			currCompletions = add ( currCompletions, s);// insert s into currCompletions.
  			x = x->next;// update x.
  		}
  	
  	return currCompletions;
  	}
  	
  	for ( int i=0; i< 26; i++){
  			
  		currCompletions = addCompletions (  node->branch[i], currCompletions);
  	}
  	
  	return currCompletions;
  
 }
  
  return currCompletions;
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
