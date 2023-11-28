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

listOfObjects<string> * Z=nullptr;

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
  string s=wordInName;
  for (int i=0; i<len; i++)
      {
           int j= toupper(s.at(i))-'A';  // j is the index of the array branch where pointer to char at wordInName[i] is stored 
              
            
                 if(currNode->branch[j]==NULL)  
                  {                                     // if pointer to branch[j] is null, create a node and equate it to branch[j] and
                    currNode->branch[j]=new TrieNode;      // then increase numNonNullBranches of the parent of the branch[j] by one unit
                    currNode->numNonNullBranches++;     
                   }	
                  
               currNode=currNode->branch[j]; 
               if(i==len-1)
                {
                   if(currNode->isWord==false) currNode->isWord=true;      // if currNode->isWord is true, set it to false
                   if(currNode->indices==NULL) 
                    {
                      currNode->indices=new listOfObjects<int>(indexOfName);
                      return true;
                     } 
                   
                   listOfObjects<int> *currIndex=currNode->indices;
                   
                   while(currIndex->next!=NULL)
                     {                                                        // if the linked list associated with the word is not empty, move through the  
                       if(currIndex->next->object==indexOfName) return false;    // list upto the null pointer
                       currIndex=currIndex->next;
                      } 
                   currIndex->next=new listOfObjects<int>(indexOfName);
                 }
                                     
         } 
  return true;
}

bool Trie::del(string wordInName, string name) {
  TrieNode *currNode = root;
  TrieNode *lastBranchNode = nullptr;
  int lastBranchChar = -1;
  int len = wordInName.length();
   
  string s=wordInName; 
  // Insert your code here
  for (int i=0; i<len; i++)
      { 
         int j= toupper(s.at(i))-'A';
              
            if(currNode->branch[j]==NULL)
              return false;
              
              if(currNode==root || currNode->numNonNullBranches>1 || currNode->indices!=NULL)
                  {
                    lastBranchNode=currNode;    // update lastBranchNode to the currNode whenever currNode is root or it has numNonNullBranches > 1 or
                    lastBranchChar=j;                 // bool isWord is true and update lastBranchChar to the index of the branch array at wordInName[i]
                   } 
                  
              currNode=currNode->branch[j];
              
           if(i==len-1)
             {
               if(currNode->isWord==false) return false;
               
               listOfObjects<int> *currIndex=currNode->indices;
               if(currIndex->next==NULL) 
                 {
                    currIndex=NULL;
                    if(currNode->numNonNullBranches==0)
                     {
                       lastBranchNode->numNonNullBranches-=1;
                       lastBranchNode->branch[lastBranchChar]=NULL;
                       }
                    currNode->isWord=false; 
                     return true; 
                   }   
                  if(nameDict->getKeyAtIndex(currIndex->object)==name)
                       {
                         currNode->indices=currNode->indices->next;
                          return true;
                        } 
                  while(currIndex->next!=NULL)
                    {
                      if(nameDict->getKeyAtIndex(currIndex->next->object)==name)
                       {
                         currIndex->next=currIndex->next->next;
                          return true;
                        } 
                     } 
              }                      
         }    
 
}

listOfObjects<string> * Trie::completions(string prefix) {
  TrieNode *currNode = root;
  int len = prefix.length();
  listOfObjects<string> *currCompletions = nullptr;
  string s=prefix;
  // Insert your code here
  
  for(int i=0; i<len; i++)
    {
      int j=toupper(s.at(i))-'A';
      currNode=currNode->branch[j];
      }
    recursiveAddCompletions(currNode, Z);
    currCompletions=Z;
    return currCompletions;
}

bool Trie::recursiveAddCompletions(TrieNode *node, listOfObjects<string> *currCompletions) {
  if (node->isWord) {
    if (!addCompletions(node, Z)) {
      return false;
    }
  }

  TrieNode *currNode = node;
  for (int i = 0; i < NUM_CHARS; i++) {
    if (currNode->branch[i] != nullptr) {
      if (!recursiveAddCompletions(currNode->branch[i], Z)) {
	return false;
      }
    }
  }
  currCompletions=Z;
  return true;
}

bool Trie::addCompletions(TrieNode *node, listOfObjects<string> *currCompletions) {
  
  // Insert your code here
if(node->isWord==true){
    while(node->indices){
      string s=nameDict->getKeyAtIndex(node->indices->object);
      if(!currCompletions){
        currCompletions=new listOfObjects<string>(s);
      }
      else{
        listOfObjects<string>*temp=currCompletions;
        int r = 0;
        if(temp->object==s){r++;}
        while(temp->next){
          temp=temp->next;
          if(temp->object==s)r++;
        }
        if(r==0){
        temp->next=new listOfObjects<string>(s);}
      }
      node->indices=node->indices->next;
    }
    Z=currCompletions;
    return true;
  }
  else{
    return false;
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
