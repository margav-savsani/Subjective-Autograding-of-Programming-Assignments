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
    //Traversing down the trie
    {
        int letter = toupper(wordInName.at(i)) - 'A';
        TrieNode *newNode = currNode->branch[letter];
        if (newNode == nullptr)
        {
            currNode->numNonNullBranches += 1;
            newNode = new TrieNode();
        }
        currNode->branch[wordInName[i]-'A'] = newNode;
        currNode = newNode;
    }

    //Adding index to the linked list of indices
    currNode->isWord = true;
    listOfObjects<int> *newList = currNode->indices;
    listOfObjects<int> *newNode = new listOfObjects(indexOfName);
    newNode->next = newList;
    currNode->indices = newNode;

    return true;
}

bool Trie::del(string wordInName, string name)
{
    TrieNode *currNode = root;
    TrieNode *lastBranchNode = nullptr;
    int lastBranchChar = -1;
    int len = wordInName.length();

    // Traversing the wordInName
    for(int i = 0; i < len; i++)
    {
        int letter = toupper(wordInName.at(i)) - 'A';

        if (currNode->branch[letter] == nullptr) return false;
        if(currNode->numNonNullBranches > 1 || currNode->isWord) 
        //Updating lastBranch Node, Char
        {
            lastBranchNode = currNode;
            lastBranchChar = letter;
        }
        currNode = currNode->branch[letter];
    }


    if (currNode->isWord)
    //After traversing
    {
        listOfObjects<int> *indexes = currNode->indices;
        if (name == nameDict->getKeyAtIndex(indexes->object))
        //the above case
        {
            if (indexes->next != nullptr) 
            {
                indexes = indexes->next;
                currNode->indices = indexes;
                return true;
            }
            else 
            {
                if ((lastBranchNode->branch[lastBranchChar]->numNonNullBranches == 1)) 
                //Complicating the cases
                {
                    if (currNode->numNonNullBranches == 0)
                    {
                        TrieNode *a = lastBranchNode->branch[lastBranchChar];
                        lastBranchNode->numNonNullBranches -= 1;
                        lastBranchNode->branch[lastBranchChar] = nullptr;
                        recursiveDelete(a);
                    }
                    else 
                    {
                        currNode->indices = nullptr;
                        currNode->isWord = false;
                    }
                    return true;
                }
            }
        }
        else 
        {
            while (name != nameDict->getKeyAtIndex(indexes->next->object)) 
            {
                if (indexes->next->next != nullptr) indexes = indexes->next;
                else return false;
            }
            indexes->next = indexes->next->next;
            return true;
        }
    }
    return false;
}

listOfObjects<string> *Trie::completions(string prefix)
{
    TrieNode *currNode = root;
    int len = prefix.length();
    listOfObjects<string> *currCompletions = nullptr;

    for (int i = 0; i < len; i++)
    //Traversing down prefix
    {
        int letter = toupper(prefix.at(i)) - 'A';
        TrieNode *newNode = currNode->branch[letter];
        if (newNode == nullptr) return currCompletions;
        else currNode = newNode;
    }

    string s = "$$$";
    //Adding some random string as starting element
    currCompletions = new listOfObjects(s);
    recursiveAddCompletions(currNode, currCompletions);
    //recursive complete

    return currCompletions->next;
}

bool Trie::recursiveAddCompletions(TrieNode *node, listOfObjects<string> *currCompletions)
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

bool Trie::addCompletions(TrieNode *node, listOfObjects<string> *currCompletions)
{
    listOfObjects<string> *tempCompletions = currCompletions;
    listOfObjects<int> *newObj = node->indices;

    while (newObj != nullptr)
    //Going down the indices
    {
        string s = nameDict->getKeyAtIndex(newObj->object);
        while (tempCompletions->next != nullptr) tempCompletions = tempCompletions->next;
        //Going down the completions
        tempCompletions->next = new listOfObjects(s);
        newObj = newObj->next;
    }

    return true;

}

bool Trie::isPresentInCompletions(listOfObjects<string> *completions, string name)
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

// Edit version 1: Added printTrie and recursivePrintTrie functions
// to help in debugging

void Trie::printTrie()
{
    recursivePrintTrie(root, "", -1, false);
}

// Adapted from Adrian Schneider's code on StackOverflow
// Basically a variation of the function we've been using
// print binary search trees in previous labs

void Trie::recursivePrintTrie(TrieNode *node, const string &prefix, int branchId, bool siblingsToRight)
{
    if (node != nullptr)
    {
        cout << prefix;

        cout << ((branchId == 0) ? "|-" : (branchId == -1) ? " *"
                                                           : "|_")
             << (char)((branchId != -1) ? 'A' + branchId : '*');
        cout << ((branchId == 0) ? '-' : (branchId == -1) ? '*'
                                                          : '_');

        // If this trie node has isWord set to true, print "(isWord)" and
        // also the list of complete station names (accessed through indices
        // in nameDict) associated with this trie node.
        if (node->isWord)
        {
            cout << "(isWord)";
            listOfObjects<int> *currIndices = node->indices;
            while (currIndices != nullptr)
            {
                cout << endl
                     << prefix << "     " << nameDict->getKeyAtIndex(currIndices->object);
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
            for (int j = i + 1; j < NUM_CHARS; j++)
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
