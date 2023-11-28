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

Trie::Trie(Dictionary<int> *nameToIndex) 
{
    nameDict = nameToIndex;
    root = new TrieNode();
    if (root == nullptr)
    {
        cout << "Memory allocation failure." << endl;
        exit(-1);
    }
}

Trie::~Trie() 
{
    recursiveDelete(root);
}

void Trie::recursiveDelete(TrieNode *node) 
{
    if (node == nullptr)
    {
        return;
    }
    else
    {
        for (int i = 0; i < NUM_CHARS; i++)
        {
            TrieNode *currNode = node->branch[i];
            recursiveDelete(currNode);
            node->branch[i] = nullptr;
        }
        if (node != root)
        {
            delete node;
        }
        return;
    }
}

bool Trie::insert(string wordInName, int indexOfName)
{
    TrieNode *currNode = root;
    int len = wordInName.length();
    for (int i = 0; i < len; i++)
    {
        int letter = toupper(wordInName[i]) - 'A';
        if (currNode->branch[letter] == nullptr)
        {
            currNode->branch[letter] = new TrieNode();
            currNode->numNonNullBranches++;
        }
        currNode = currNode->branch[letter];
    }
    if (currNode->isWord == false)
    {
        currNode->isWord = true;
        currNode->indices = new listOfObjects<int>(indexOfName);
        return true;
    }
    listOfObjects<int> * x = currNode->indices;
    while (x->next != nullptr)
    {
        if (x->object == indexOfName) return true;
        x = x->next;
    }
    x->next = new listOfObjects<int>(indexOfName);
    return true;
}

bool Trie::del(string wordInName, string name)
{
    TrieNode *currNode = root;
    TrieNode *lastBranchNode = nullptr;
    int lastBranchChar = -1;
    int len = wordInName.length();
    // go to the end of the word
    for (int i = 0; i < len; i++)
    {
        int letter = toupper(wordInName[i]) - 'A';
        if (currNode->branch[letter] == nullptr) return 0;
        if (i <= len - 1 && (currNode->numNonNullBranches > 1 || currNode->isWord))
        {
            lastBranchNode = currNode;
            lastBranchChar = letter;
        }
        //lastBranchNode = currNode;
        //lastBranchChar = letter;
        currNode = currNode->branch[letter];
    }
    // if it is not a word
    if (!currNode->isWord) return false;
    // find the index of the name in the dictionary
    bool found = 0;
    listOfObjects<int> * x = currNode->indices;
    listOfObjects<int> * prnt = nullptr;
    while (found == 0 && x != nullptr)
    {
        if (x == nullptr) break;
        int indexindict = x->object;
        string s = nameDict->getKeyAtIndex(indexindict);
        if (s == name)
        {
            found = 1;
            break;
        }
        else
        {
            prnt = x;
            x = x->next;
        }
    }
    // name not found
    if (!found) return false;
    // removing that index
    if (prnt == nullptr) currNode->indices = (currNode->indices)->next;
    else prnt->next = x->next;
    // if the word is not associated with any name in the dictionary
    if (currNode->indices == nullptr) currNode->isWord = false;
    // if it is not the prefix of any other word and is not a word itself
    if (currNode->isWord == false && currNode->numNonNullBranches == 0 && lastBranchChar != -1)
    {
        recursiveDelete(lastBranchNode->branch[lastBranchChar]);
        lastBranchNode->branch[lastBranchChar] = nullptr;
        lastBranchNode->numNonNullBranches--;
    }
    // only one word in the trie
    else if (currNode->isWord == false && currNode->numNonNullBranches == 0 && lastBranchChar == -1)
    {
        for (int i = 0; i < 26; i++)
        {
            if (root->branch[i] != nullptr)
            {
                recursiveDelete(root->branch[i]);
                root->branch[i] = nullptr;
                root->numNonNullBranches--;
            }
        }
    }
    return true;
}

listOfObjects<string> * Trie::completions(string prefix)
{
    TrieNode *currNode = root;
    int len = prefix.length();
    listOfObjects<string> *currCompletions = nullptr;
    for (int i = 0; i < len; i++)
    {
        int letter = toupper(prefix[i]) - 'A';
        if (currNode->branch[letter] == nullptr) return currCompletions;
        currNode = currNode->branch[letter];
    }
    recursiveAddCompletions(currNode, currCompletions);
    return currCompletions;
    
}

bool Trie::recursiveAddCompletions(TrieNode *node, listOfObjects<string> *&currCompletions)
{
    if (node->isWord)
    {
        if (!addCompletions(node, currCompletions))
        {
            return false;
        }
    }

    TrieNode *currNode = node;
    for (int i = 0; i < NUM_CHARS; i++)
    {
        if (currNode->branch[i] != nullptr)
        {
            if (!recursiveAddCompletions(currNode->branch[i], currCompletions))
            {
	            return false;
            }
        }
    }

    return true;
}

bool Trie::addCompletions(TrieNode *node, listOfObjects<string> *&currCompletions)
{
    if (!node->isWord) return true;
    listOfObjects<int> * indx = node->indices;
    int index0 = indx->object;
    string s0 = nameDict->getKeyAtIndex(index0);
    if (currCompletions == nullptr)
    {
        currCompletions = new listOfObjects<string>(s0);
        indx = indx->next;
    }
    listOfObjects<string> * end = currCompletions;
    while (end->next != nullptr) end = end->next;
    while (indx != nullptr)
    {
        int index = indx->object;
        string s = nameDict->getKeyAtIndex(index);
        if (isPresentInCompletions(currCompletions, s))
        {
            indx = indx->next;
            continue;
        }
        end->next = new listOfObjects<string>(s);
        end = end->next;
        indx = indx->next;
    }
    return true;
}

bool Trie::isPresentInCompletions(listOfObjects<string> * completions, string name)
{
    listOfObjects<string> *currCompletion = completions;
    bool isPresent = false;
    while (currCompletion != nullptr)
    {
        if (currCompletion->object == name)
        {
            isPresent = true;
            break;
        }
        currCompletion = currCompletion->next;
    }
    return isPresent;
}

void Trie::freeCompletionList(listOfObjects<string> *completions)
{
    listOfObjects<string> *currCompl = completions;
    while (currCompl != nullptr)
    {
        listOfObjects<string> *toDeleteCompl = currCompl;
        currCompl = currCompl->next;
        delete toDeleteCompl;
    }
    return;
}

bool Trie::isPresent(string wordInName)
{
    TrieNode *currNode = root;
    int len = wordInName.length();

    for (int i = 0; i < len; i++)
    {
        int letter = toupper(wordInName.at(i)) - 'A';
        if (currNode->branch[letter] == nullptr)
        {
            return false;
        }
        currNode = currNode->branch[letter];
    }
    return currNode->isWord; 
}


void Trie::printTrie()
{
  recursivePrintTrie(root, "", -1, false);
}

// Adapted from Adrian Schneider's code on StackOverflow
// Basically a variation of the function we've been using
// print binary search trees in previous labs

void Trie::recursivePrintTrie(TrieNode *node, const string& prefix, int branchId, bool siblingsToRight)
{
    if (node != nullptr) 
    {
        cout << prefix;
        
        cout << ((branchId == 0) ? "|-" : (branchId == -1)? " *":"|_" ) << (char) ((branchId != -1) ? 'A'+branchId: '*');
        cout << ((branchId == 0) ? '-' : (branchId == -1) ? '*':'_');
        
        // If this trie node has isWord set to true, print "(isWord)" and
        // also the list of complete station names (accessed through indices
        // in nameDict) associated with this trie node.
        if (node->isWord) 
        {
            cout << "(isWord)";
            listOfObjects<int> *currIndices = node->indices;
            while (currIndices != nullptr) 
            {
                cout << endl << prefix << "     " << nameDict->getKeyAtIndex(currIndices->object);
                currIndices = currIndices->next;
            }
        }
        else 
        {
            cout << "()";
        }
        cout << endl;
        for (int i = 0; i < NUM_CHARS; i++) 
        {
            TrieNode *currNode = node->branch[i];
            bool childrenToRight = false;
            for (int j = i+1; j < NUM_CHARS; j++) 
            {
                if (node->branch[j] != nullptr) 
                {
                    childrenToRight = true;
                    break;
                }
            }
            if (currNode != nullptr) 
            {
                recursivePrintTrie(currNode, prefix + ((siblingsToRight) ? "│   " : "    "), i, childrenToRight);
            }
        }
    }
}
// End edit version 1


#endif
