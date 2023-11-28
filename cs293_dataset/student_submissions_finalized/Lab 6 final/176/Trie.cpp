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

    for(int i=0; i<len; i++) {
        int index = toupper(wordInName.at(i)) - 'A';
        if(!currNode->branch[index]){                   // no previous words with prefix upto this point
            currNode->branch[index] = new TrieNode();
            currNode->numNonNullBranches++;
        }
        currNode = currNode->branch[index];     // traversing down the tri
    }

    currNode->isWord = true;    // end of a word
    if(currNode->indices == nullptr)    // no words completed here yet
        currNode->indices = new listOfObjects<int>(indexOfName);
    
    // this word already exists for some other index  
    else {
        listOfObjects<int> *temp = (currNode->indices);
        while(temp->next != nullptr)        // traversing across the indices list
            temp = temp->next;
        temp->next = new listOfObjects<int>(indexOfName);
    }

    return true;
}

bool Trie::del(string wordInName, string name) {
    TrieNode *currNode = root;
    TrieNode *lastBranchNode = nullptr;
    int lastBranchChar = -1;
    int len = wordInName.length();

    if(!isPresent(wordInName))  // word to delete not present
        return false;

    for(int i=0; i<len; i++) {
        int index = toupper(wordInName[i]) - 'A';
        if(currNode->branch[index] == nullptr)      // end of the word not reached
            return false;
        
        if(currNode->numNonNullBranches > 1 || currNode->isWord){   // multiple branches from this node
                                                                   // or if there exists a word prefix of this word
            lastBranchNode = currNode;
            lastBranchChar = index;
        }
        currNode = currNode->branch[index];     // traversing down the trie to end of word
    }

    if(currNode->indices->next == nullptr && currNode->numNonNullBranches == 0){  // only one index at this node
        if(lastBranchNode == nullptr){      // no branching ever occured, or only one word in trie
            root = new TrieNode();
        }
        else {                            // the particular branching of this word will be nullified
            lastBranchNode->branch[lastBranchChar] = nullptr;
            lastBranchNode->numNonNullBranches--;
        }
    }
    else {      // multiple indices at the end of word
               // or if this word is prefix of another word
        listOfObjects<int> *temp = currNode->indices;
        if(nameDict->getKeyAtIndex(temp->object) == name)   // index to be deleted is first in list
            currNode->indices = temp->next;
        else {
            while(temp->next != nullptr) {                  // index is further down the list
                if(nameDict->getKeyAtIndex(temp->next->object) == name)
                    temp->next = temp->next->next;
            }
        }

        if(currNode->indices == nullptr)
            currNode->isWord = false;
    }
    
    return true;
}

listOfObjects<string> *Trie::completions(string prefix) {
    TrieNode *currNode = root;
    int len = prefix.length();
    listOfObjects<string> *currCompletions = new listOfObjects<string>("");
    if(!isPresent(prefix))
        return nullptr;
    
    for(int i=0; i<len; i++) {
        int index = toupper(prefix.at(i)) - 'A';
        currNode = currNode->branch[index];         // traversing down the trie to end of prefix
    }
    
    recursiveAddCompletions(currNode, currCompletions); // add all completions starting with this prefix
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

    listOfObjects<int> *i = node->indices;
    if(i == nullptr)    // no string here to be added
        return false;

    while(i != nullptr) {
        if(currCompletions->object == "")   // first completion being added
            currCompletions->object = nameDict->getKeyAtIndex(i->object);
        else {
            listOfObjects<string> *temp = currCompletions;
            while(temp->next != nullptr)
                temp = temp->next;
            if(!isPresentInCompletions(currCompletions, nameDict->getKeyAtIndex(i->object)))    // avoiding multiple inclusions
                temp->next = new listOfObjects<string>(nameDict->getKeyAtIndex(i->object));
        }
        i = i->next;
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

