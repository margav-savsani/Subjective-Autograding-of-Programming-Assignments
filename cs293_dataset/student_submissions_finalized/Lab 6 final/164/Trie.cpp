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
  int k;
  int i=0;
  while (true){//checks until there is a mis match between the trie and the wordInName

    k=int(wordInName[i])-int('A');
    if(currNode->branch[k]==NULL){break;}
    currNode=currNode->branch[k];
    i++;
    if(i==len){
      if(currNode->isWord==false)
      {
        currNode->isWord=true;
        currNode->indices=new listOfObjects<int>(indexOfName); // creates a new node if the is word is false
        currNode->last=currNode->indices;
        return true;
      }
      currNode->last->next=new listOfObjects<int> (indexOfName);
      currNode->last=currNode->last->next;
      return true;}
  }
  while (true)  //creates new branches as there is not further matchiing 
  {
    k=int(wordInName[i])-int('A');
    currNode->branch[k]=new TrieNode();
    currNode->numNonNullBranches++;
    currNode=currNode->branch[k];
    i++;
    if(i==len)
    {
      if(currNode->isWord==false)
      {
        currNode->isWord=true;
        currNode->indices=new listOfObjects<int>(indexOfName); // vreates a new index when the is word is false
        currNode->last=currNode->indices;
        return true;
      }
      currNode->last->next->object=indexOfName;
      currNode->last=currNode->last->next;
      return true; //returns true if the insertion is done
    }
  } 
  return false;
}

bool Trie::del(string wordInName, string name)
{
    TrieNode *currNode = root;
    TrieNode *lastBranchNode = nullptr;
    int lastBranchChar = -1;
    int len = wordInName.length();
    int i = 0;
    int k;

    while (true)
    {
        k = int(wordInName[i]) - int('A');
        if (currNode->branch[k] == NULL)
        {
            break;
        }
        if(currNode->numNonNullBranches>1 || currNode->isword){
            lastBranchNode=currNode; //updates the lastBranchNode to the last which have more than one branch 
            lastBranchChar=k;//updates the lastBranchChar to the character from which we want to apply reccursive del
        }
        currNode = currNode->branch[k];
        i++;
        if (i == wordInName.length())
        {
            

                listOfObjects<int> *a = currNode->indices;
                if(a->next==NULL){// no of indices is equal to one
                    if(currNode->numNonNullBranches==0){
                        TrieNode*a=lastBranchNode->branch[lastBranchChar];
                            lastBranchNode->branch[lastBranchChar]=NULL;
                        lastBranchNode->numNonNullBranches=-1;
                        recursiveDelete(a);//deletes all the nodes reccursively below the char a
                        return true;
                    }
                    else{
                        currNode->indices=NULL;
                        return true;
                    }
                }
                else{//no of indices is more than one


                
                    if (nameDict->getKeyAtIndex(a->object) == name)// if the name is at the start of the list
                    {
                        currNode->indices = currNode->indices->next;
                        return true;
                    }
                    else
                    {   
                        while(true){
                            if(nameDict->getKeyAtIndex(a->next->object)==name){// if the
                                a->next=a->next->next;
                            if (a->next == NULL)
                            {
                            currNode->last = a;
                            }
                            return true;

                            }
                            a=a->next;
                            
                        }
                       
                    }
                }
            
        }
    }
    // Insert your code here
    return false;
}

listOfObjects<string> * Trie::completions(string prefix) {
  TrieNode *currNode = root;
  int len = prefix.length();
  listOfObjects<string> *currCompletions = nullptr;
  currCompletions=new listOfObjects<string>("m");//creates a dummy currCompletion at the start.
  int k;
  // Insert your code here
  for (int i=0;i<len;i++)
  {
    k=int(prefix[i])-int('A');
    currNode=currNode->branch[k];
  }

  recursiveAddCompletions(currNode,currCompletions);
  return currCompletions->next;//ignores the dummy currCompletion
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
  listOfObjects<int> *a=node->indices;//creates a new variable to store the address of the indices
  listOfObjects<string> *c=currCompletions;
  while(c->next!=NULL)
  {
    c=c->next;
  }
  while(a!=NULL)
  {
    c->next=new listOfObjects<string>(nameDict->getKeyAtIndex(a->object));
    c=c->next;
    a=a->next;
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
