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

// Inserting into the trie
bool Trie::insert(string wordInName, int indexOfName) {
    TrieNode *currNode = root;
    int len = wordInName.length();

    // Insert your code here
    for (int i=0; i<len; i++) {
        int c { (int)wordInName[i]%32 - 1 };
        if (!currNode->branch[c]) {
            currNode->branch[c] = new TrieNode {};
            currNode->numNonNullBranches++;
        }
        currNode = currNode->branch[c];
    }
    currNode->isWord = true;
    listOfObjects<int>* i = currNode->indices;
    if (i) {
        while (i->next) i = i->next;
        i->next = new listOfObjects<int> { indexOfName };
    } else currNode->indices = new listOfObjects<int> { indexOfName };

    return true;
}

// Deleting from the trie
bool Trie::del(string wordInName, string name) {
    TrieNode *currNode = root;
    TrieNode *lastBranchNode = nullptr;
    int lastBranchChar = -1;
    int len = wordInName.length();

    // Insert your code here
    TrieNode* path[len+1];
    path[0] = root;
    for (int i=0; i<len; i++) {
        int c { (int)wordInName[i]%32 - 1 };
        if (!currNode) return false;
        currNode = currNode->branch[c];
        path[i+1] = currNode;
    }

    // Remove obscure nodes created after deletion of name
    if (!currNode->indices->next && !currNode->numNonNullBranches) {
        int i = len-1;
        while (path[i]->numNonNullBranches <= 1 && !path[i]->indices) i--;
        path[i]->numNonNullBranches--;

        TrieNode* n { root };
        for (int j=0; j<=i; j++) {
            int c { (int)wordInName[j]%32 - 1 };
            if (j < i) n = n->branch[c];
            else n->branch[c] = nullptr;
        }

    } else if (currNode->indices->next) {
        listOfObjects<int>* prev = nullptr;
        listOfObjects<int>* cur = currNode->indices;
        if (nameDict->getKeyAtIndex(cur->object) != name) {
            while (name != nameDict->getKeyAtIndex(cur->object)) {
                prev = cur;
                cur = cur->next;
            }
        }
        (prev ? prev->next : currNode->indices) = cur->next;

        delete cur;
    } else {
        currNode->isWord = false;
        delete currNode->indices;
    }

    return true;
}

listOfObjects<string>* Trie::completions(string prefix) {
    TrieNode *currNode = root;
    int len = prefix.length();
    listOfObjects<string> *currCompletions = nullptr;

    // Insert your code here
    // Go to the node where prefix ends
    for (int i=0; i<len; i++) {
        int c { (int)prefix[i]%32 - 1 };
        if (!currNode) return nullptr;
        currNode = currNode->branch[c];
    }

    // Get all completions from this node
    recursiveAddCompletions(currNode, currCompletions);

    return currCompletions;
}

// Recursively go over all the nodes to find all completions
// If a word node is found then add its' word to the completions list(if not already present)
bool Trie::recursiveAddCompletions(TrieNode *node, listOfObjects<string>*& currCompletions) {
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

// Add another completion to the list of completions if it's not present already
bool Trie::addCompletions(TrieNode *node, listOfObjects<string>*& currCompletions) {
    // Insert your code here
    listOfObjects<int>* i = node->indices;

    while (i) {  // For all strings that end at node check if they are already present or not
        bool present { false };
        listOfObjects<string>* comp = currCompletions;

        if (currCompletions) {
            while (comp->next) {
                if (nameDict->getKeyAtIndex(i->object) == comp->object) {
                    present = true;
                    break;
                }
                comp = comp->next;
            }
            if (!present) comp->next = new listOfObjects<string> { nameDict->getKeyAtIndex(i->object) };
        } else currCompletions = new listOfObjects<string> { nameDict->getKeyAtIndex(i->object) };
        
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

    return currNode->isWord;
}

// Edit version 1: Added printTrie and recursivePrintTrie functions
// to help in debugging

void Trie::printTrie() {
    recursivePrintTrie(root, "", -1, false);
}

// Adapted from Adrian Schneider's code on StackOverflow
// Basically a variation of the function we've been using
// print binary search trees in previous labs

void Trie::recursivePrintTrie(TrieNode *node, const string& prefix, int branchId, bool siblingsToRight) {
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
        else cout << "()";

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