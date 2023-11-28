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

   for(int i=0; i <len; i++){
      
      int d;                                          // integer for storing index of character in branch array
      if(wordInName[i]-97>=0){ d=wordInName[i]-97; }
      else { d=wordInName[i]-65; }
      
      if(currNode->branch[d]==nullptr){                         
          currNode->branch[d] = new TrieNode();       // intialising element at index d in branch array if it is nullptr
          currNode->numNonNullBranches+=1;    
      }     
      currNode = currNode->branch[d];
      
      if( i==len-1 ){
           
            currNode->isWord=true;                    // making isWord  of TrieNode in which it is last character branch as true
            listOfObjects<int> *x = currNode->indices;int i=0;
            
            while( x!=nullptr ){  i++; x = x->next; }
            
            x=currNode->indices;
            
            if(i==0) {  currNode->indices = new listOfObjects(indexOfName);}   // inserting indexofname in indices of the last TrieNode
            else{
                 for(int l=1;l<i;l++){ x=x->next; }
                 x->next=new listOfObjects(indexOfName);                       // inserting indexofname in indices of the last TrieNode
            }            
      }
   }
  
  return true;
  
}

bool Trie::del(string wordInName, string name) {
   TrieNode *currNode = root;
   TrieNode *lastBranchNode = nullptr;
   int lastBranchChar = -1;
   int len = wordInName.length();
   
   // for loop for finding pointer TrieNode which represents second last character(will be stored in currNode)
   for(int i=0;i<len-1;i++){  int d;
   
        if(wordInName[i]-97>=0) { d=wordInName[i]-97; }   else { d=wordInName[i]-65; }
        
        currNode = currNode->branch[d];
        if( currNode == nullptr ) return false;             // returning false if given character TrieNode is not present
   }
   
   int kn;
   if(wordInName[len-1]-97>=0) kn=wordInName[len-1]-97; else { kn=wordInName[len-1]-65; }
   
   if(currNode->branch[kn]==nullptr) {return false;}        // returning false if last character TrieNode is not present
   else { 
        Entry<int> *k=nameDict->get(name);                  // getting entry at which name is stored in dictionary 
        int value = k->value,l=0,found=0;                   // getting index at which name is stored in dictionary
        
        TrieNode *ln = currNode->branch[kn];
        
        listOfObjects<int> *x = ln->indices;
        
        // while loop for position at which index of name is stored in indices of TrieNode
        while(x!=nullptr){
            l++;
            if(x->object==value){ found=1; break;  }
            x=x->next;
        }
        
        if(found==0) {return false;}                  // returning false if index of name is not stored in indices of TrieNode
        else{ 
             x = ln->indices;
             
             //below if else statements remove that index of given name and making previous index stored in indices to point out to next index stored 
             if(l==1) { ln->indices = ln->indices->next; }
             else{
                  for(int y=0;y<l-2;y++){ x=x->next; }
                  x->next = (x->next)->next;
             }
             
       //below if statement deletes some or all charcters of wordinname in Trie if not required (i.e if characters have only 1 branch till last characters from middle or start of character trienode)
             if(ln->indices==nullptr&&ln->numNonNullBranches==0){ 
              
                 int q,level;
                 if(wordInName[0]>96) { q=wordInName[0]-97; } else { q=wordInName[0]-65; }
                 
                 TrieNode *p1=root->branch[q],*p2=root;level=0;
                 
                 //below for loop finds pointer from where Trienodes below it has to be deleted in Trie 
                 for(int i=0;i<len;i++){ 
                 
                      if(wordInName[i]>96) { q=wordInName[i]-97; } else { q=wordInName[i]-65; }
                      p2=p2->branch[q];
                      
                      if(p2->numNonNullBranches>1) { 
                      
                          if(wordInName[i+1]>96) { q=wordInName[i+1]-97; } else { q=wordInName[i+1]-65; }
                          p1=p2->branch[q]; level = i+1;
                      }
                  }
                  
                  p2=root;  
                  
                  //below if else statements delete those trienodes and make branch to nullptr
                  if(level==0){
                       if(wordInName[0]>96) { q=wordInName[0]-97; } else { q=wordInName[0]-65; } root->branch[q]=nullptr;
                       }
                  else{  
                      for(int i=0;i<level;i++){
                           if(wordInName[i]>96) { q=wordInName[i]-97; } else { q=wordInName[i]-65; }
                       
                           p2=p2->branch[q];
                      }
                      if(wordInName[level]>96) { q=wordInName[level]-97; } else { q=wordInName[level]-65; }
                      recursiveDelete(p2->branch[q]);
                      p2->branch[q]=nullptr;  
                  }             
              }
            
            return true;
         }        
    }
}

listOfObjects<string> * Trie::completions(string prefix) {
 
   TrieNode *currNode = root;
   int len = prefix.length();
   listOfObjects<string> *currCompletions = new listOfObjects<string>("for");   // intialised so to make it non empty

   bool isp=true;int ch,d;
   
   //below for loop is used to find pointer pointing out to last character TrieNode
   for(int i=0;i<len;i++){
   
      if(prefix[i]>=97){d=prefix[i]-97;} else{ d=prefix[i]-65; }
      ch=d;
      
      if(currNode->branch[d]==nullptr){isp=false;return currCompletions;}
      currNode=currNode->branch[d];
   }
   
   recursiveAddCompletions(currNode,currCompletions );
   
   return currCompletions->next;     // as it is given one intial string ("for") so returning next of it
  
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
   
   listOfObjects<int> *l = node->indices;
   int i=0;
   listOfObjects<string> *x=currCompletions;
   
   if(x!=nullptr){ i++;x=x->next; }        // if loop for finding positon of nullptr in currCompletions
   x=currCompletions;
   for(int k=0;k<i-1;k++){ x=x->next; } 
    
   // in below while loop we are adding string at last  
   while(l!=nullptr){
   
       x->next =new listOfObjects(nameDict->getKeyAtIndex(l->object));   
       x=x->next;l=l->next;
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
