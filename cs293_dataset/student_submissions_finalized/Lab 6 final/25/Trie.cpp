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

    // Insert your code here
    char c;
    for (int i = 0; i < len; i++)
    {
        c = wordInName[i];
        int letter = toupper(c) - 'A';
        if (currNode->branch[letter] != nullptr)
        {
            currNode = currNode->branch[letter];
        }
        else
        {
            currNode->branch[letter] = new TrieNode();
            currNode->numNonNullBranches++;
            currNode = currNode->branch[letter];
        }
    }
    currNode->isWord = 1;
    if (currNode->indices == nullptr)
    {
        currNode->indices = new listOfObjects<int>(indexOfName);
    }
    else
    {
        listOfObjects<int> *ind = currNode->indices;
        currNode->indices = new listOfObjects<int>(indexOfName);
        currNode->indices->next = ind;
    }
    return true;
}

bool recDelete(TrieNode* head){
    for (int i=0; i<NUM_CHARS; i++) {
        if (head->branch[i]!=nullptr){
            recDelete(head->branch[i]);
            head->branch[i]=nullptr;
        }
    }
    delete head;
    return true;
}

bool Trie::del(string wordInName, string name) {
    TrieNode *currNode = root;
    TrieNode *lastBranchNode = root;
    int lastBranchChar = toupper(wordInName[0]) - 'A';
    int len = wordInName.length();

    // Insert your code here
    char c;
    for (int i=0; i<len; i++) {
        c = wordInName[i];
        int letter = toupper(c) - 'A';
        if (currNode->branch[letter]==nullptr){
            cout<<"prefix not found at "<<c<<endl;
            return false;
        }
        currNode = currNode->branch[letter];
        if (currNode->isWord && i!=len-1){
            lastBranchNode = currNode;
            lastBranchChar = toupper(wordInName[i+1]) - 'A';
        }
    }
    listOfObjects<int> *nums = currNode->indices;
    listOfObjects<int> *prev = nullptr;
    while (nums!=nullptr){
        if (nameDict->getKeyAtIndex(nums->object)==name){
            if (prev==nullptr){
                currNode->indices = nums->next;
            }
            else {prev->next = nums->next;}
            delete nums;
            if (currNode->indices==nullptr){
                currNode->isWord=0;
            }
            break;
        }
        prev = nums;
        nums = nums->next;
    }
    // If the wordInName had its only occurrence in name, need to remove it from trie.
    if (currNode->indices==nullptr && currNode->numNonNullBranches==0){
        TrieNode* deleted = lastBranchNode->branch[lastBranchChar];
        lastBranchNode->branch[lastBranchChar]=nullptr;
        lastBranchNode->numNonNullBranches--;
        return (recDelete(deleted));
    }
    return true;
}
/*
void recursiveComplete(TrieNode *root, listOfObjects<string> *completions, string& word) {
    if (root->isWord){
        listOfObjects<string> *ind = completions;
        completions = new listOfObjects<string>(word);
        completions->next = ind;
        word.pop_back();
        return;
    }
    for (int i=0; i<NUM_CHARS; i++) {
        if (root->branch[i]!=nullptr){
            word.push_back('A' + i);
            recursiveComplete(root->branch[i], completions, word);
        }
    }
    word.pop_back();
    return;
}
/*
listOfObjects<string> *Trie::completions(string prefix) {
    TrieNode *currNode = root;
    int len = prefix.length();
    listOfObjects<string> *currCompletions = nullptr;

    // Insert your code here
    char c;
    for (int i = 0; i < len; i++) {
        c = prefix[i];
        int letter = toupper(c) - 'A';
        if (currNode->branch[letter] == nullptr) {
            return currCompletions;
        }
        currNode = currNode->branch[letter];
    }
    for (int i = 0; i < NUM_CHARS; i++) {
        if (currNode->branch[i] != nullptr) {
            string word = "";
            word.push_back(char('A' + i));
            recursiveComplete(currNode->branch[i], currCompletions, word);
        }
    }
    return currCompletions;
}
*/

listOfObjects<string> *Trie::completions(string prefix) {
    TrieNode *currNode = root;
    int len = prefix.length();
    listOfObjects<string> *currCompletions = nullptr;
    char c;
    for (int i=0; i<len; i++) {
        c = prefix[i];
        int letter = toupper(c) - 'A';
        if (currNode->branch[letter] == nullptr) {
            cout<<"Not found"<<endl;
            return currCompletions;
        }
        currNode = currNode->branch[letter];
    }
    recursiveAddCompletions(currNode, currCompletions);

    return currCompletions;
}

bool Trie::recursiveAddCompletions(TrieNode *node, listOfObjects<string>* &currCompletions) {
    if (node->isWord){
        if (!addCompletions(node, currCompletions)){
            return false;
        }
    }
    TrieNode *currNode = node;
    for (int i = 0; i < NUM_CHARS; i++){
        if (currNode->branch[i] != nullptr){
            if (!recursiveAddCompletions(currNode->branch[i], currCompletions)){
                return false;
            }
        }
    }
    return true;
}

bool Trie::addCompletions(TrieNode *node, listOfObjects<string>* &currCompletions){

    // Insert your code here
    listOfObjects<int>* words = node->indices;
    while (words!=nullptr){
        string comple = nameDict->getKeyAtIndex(words->object);
        // cout<<comple<<endl;
        if (isPresentInCompletions(currCompletions, comple)){
            return true;
        }
        listOfObjects<string> *temp = currCompletions;
        currCompletions = new listOfObjects<string>(comple);
        currCompletions->next = temp;
        words = words->next;
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
