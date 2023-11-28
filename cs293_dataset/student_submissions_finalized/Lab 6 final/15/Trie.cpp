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
#include <string>
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
    if (root == nullptr)
    {
        root = new TrieNode();
    }
    TrieNode *currNode = root;
    int len = wordInName.length();
    for (int i = 0; i < len; i++)
    {
        int letter = toupper(wordInName[i]) - 'A';
        if (currNode->branch[letter] == nullptr)
        {
            TrieNode *k = new TrieNode();
            currNode->numNonNullBranches++;
            currNode->branch[letter] = k;
        }
        currNode = currNode->branch[letter];
    }
    // Insert your code here
    if (currNode->indices == nullptr)
    {
        currNode->indices = new listOfObjects<int>(indexOfName);
    }
    else
    {
        listOfObjects<int> *k = currNode->indices;
        while (k->next != NULL)
        {
            k = k->next;
        }
        k->next = new listOfObjects<int>(indexOfName);
    }
    currNode->isWord = true;
    return true;
}

bool ll_del(listOfObjects<int> *&L, int k) // USING THIS FUNTION TO DELETE FROM A LINKED LIST
{
    if (L == nullptr)
    {
        return false;
    }
    if (L->object == k)
    {
        L = L->next;
        return true;
    }
    listOfObjects<int> *dummy = L;
    while (dummy->next != nullptr)
    {
        if (dummy->next->object == k)
        {
            break;
        }
        dummy = dummy->next;
    }
    if (dummy->next == nullptr)
    {
        return false;
    }
    dummy->next = dummy->next->next;
    {
        return true;
    }
}

// void print_ll(listOfObjects<int> *L) JUST FOR CHECKING PURPOSES
// {
//     listOfObjects<int> *m = L;
//     while (m != nullptr)
//     {
//         cout << m->object << endl;
//         m = m->next;
//     }
// }

bool Trie::del(string wordInName, string name) // USING RECURSION TO DELETE
{
    // printTrie();
    // cout<<wordInName<<endl;
    if (root == nullptr) // A BASE CASE WHEN THE WORD IS NOT PRESENT
    {
        return false;
    }
    if (wordInName.length() == 0) // THE BASE CASE WHEN WE REACHED THE END SO THE WORD IS PRESENT
    {
        // cout<<"l1"<<endl;
        int k = nameDict->get(name)->value; // THE INDEX WEHRE THE WORD IS STORED
        ll_del(root->indices, k);           // DELETING FROM THE LINKED LIST
        if (root->indices == nullptr)       // IF NO OTHER STATION HAS THIS WORD IN ITS NAME
        {
            root->isWord = false;

            if (root->numNonNullBranches == 0) // IF IT DOESN'T HAVE ANY BRANCHES
            {                                  // THEN WE SHOULD KILL THIS NODE
                // cout<<"Hi"<<endl;
                root = nullptr;
            }
        }
        return true;
    }
    else // IN THE OTHER CASE WE JUST CHANGE THE ROOT TEMPORATILY AND THEN DELETE RECURSIVELY
    {
        // cout<<"l2"<<endl;
        TrieNode *curr = root;
        int letter = toupper(wordInName[0]) - 'A';
        root = root->branch[letter];
        if (!del(wordInName.substr(1, wordInName.length() - 1), name)) // IF DELETE FAILED
        {
            root = curr;
            return false;
        }
        if (root == nullptr) // IF DELETE SUCCEEDEDED AND WE DELETED THE CHILD OF THE NODE
        {
            root = curr;
            root->branch[letter] = nullptr; // THAT BRANCH IS GONE NOW
            root->numNonNullBranches--;
            // cout<<root->isWord<<" "<<root->numNonNullBranches<<endl;
            if (!root->isWord && (root->numNonNullBranches == 0)) // IF THIS HAPPENS WE MAY HAVE TO DELETE THIS ROOT ALSO
            {
                // cout<<"hello"<<endl;
                root = nullptr;
            }
        }
        else
        {
            root = curr;
        } // REASSIGNING ROOT
        return true;
    }
    // TrieNode *currNode = root;
    // TrieNode *lastBranchNode = nullptr;
    // int lastBranchChar = -1;
    // int len = wordInName.length();
    // for (int i = 0; i < len; i++)
    // {
    //     int letter = toupper(wordInName[i]) - 'A';
    //     currNode = currNode->branch[letter];
    //     if (currNode == nullptr)
    //     {
    //         return false;
    //     }
    // }

    // int k = nameDict->get(name)->value;
    // ll_del(currNode->indices, k);
    // nameDict->remove(name);
    // if (currNode->indices==nullptr){
    //     currNode->isWord=false;
    // }
    // if(currNode->numNonNullBranches==0){
    //     while(true){
    //         if(currNode->isWord){break;}
    //         if(currNode->numNonNullBranches>1){break;}
    //         if(currNode==nullptr){break;}
    //     }
    // }
    // // Insert your code here
    // return true;
}

bool ll_find(listOfObjects<string> *L, string k)
{ // FOR FINDING IN A LINKED LIST
    if (L == nullptr)
        return false;
    else if (L->object == k)
        return true;
    else
        return (ll_find(L->next, k));
}

bool ll_add(listOfObjects<string> *&L, string k) // FOR ADDING IN A LINKED LIST
{
    if (L == nullptr)
    {
        // cout<<"hello"<<endl;
        L = new listOfObjects<string>(k);
        return true;
    }
    listOfObjects<string> *dummy = L;
    while (dummy->next != nullptr)
    {
        dummy = dummy->next;
    }
    dummy->next = new listOfObjects<string>(k);
    return true;
}
listOfObjects<string> *Trie::completions(string prefix) // THIS RETURNS A LIST OF STATIONS BEGINING FROM PREFIX
{
    // cout<<"hm"<<endl;
    TrieNode *currNode = root;
    int len = prefix.length();
    listOfObjects<string> *currCompletions = nullptr;
    for (int i = 0; i < len; i++)
    { // REACHING THE POINT WHERE THE PREFIX OCCURS
        int letter = toupper(prefix[i]) - 'A';
        currNode = currNode->branch[letter];
        if (currNode == nullptr)
        {
            return nullptr;
        }
    }

    // Insert your code here
    // listOfObjects<string> *completons=nullptr;
    currCompletions = new listOfObjects<string>("dummy"); // WE CANNOT ADD TO THE FIRST ELEMENT OF A LIST
                                                          // SO ADDING A DUMMY HERE
    recursiveAddCompletions(currNode, currCompletions);   // THIS ADDS ALL STATIONS TO currcompletions
    currCompletions = currCompletions->next;              // DELETING DUMMY
    return currCompletions;
}

bool Trie::recursiveAddCompletions(TrieNode *node, listOfObjects<string> *currCompletions)
{
    if (node->isWord)
    {
        if (!addCompletions(node, currCompletions)) // FOR A NODE WHICH DOESNT HAVE SONS
        {
            return false;
        }
    }

    TrieNode *currNode = node;
    for (int i = 0; i < NUM_CHARS; i++) // GOING THROUGH ALL ITS CHILDREN
    {
        if (currNode->branch[i] != nullptr)
        {
            recursiveAddCompletions(currNode->branch[i], currCompletions);
        }
    }

    return true;
}

bool Trie::addCompletions(TrieNode *node, listOfObjects<string> *currCompletions)
// RETURNS FALSE FOR A NODE WHICH DOESNT HAVE SONS
{
    listOfObjects<int> *k = node->indices;
    while (k != nullptr)
    {
        string S = nameDict->getKeyAtIndex(k->object); // GETTING THE WORD THROUGH THE DICTIONARY
        // cout<<S<<endl;
        if (!ll_find(currCompletions, S))
        { // IF THE WORD ISN'T ALREADY THERE
            ll_add(currCompletions, S);
        }
        k = k->next;
    }
    return (node->numNonNullBranches);
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
        // cout << " " << node->numNonNullBranches << " ";
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
