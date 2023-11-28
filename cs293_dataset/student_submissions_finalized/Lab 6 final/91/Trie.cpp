#ifndef TRIE_CPP
#define TRIE_CPP

#include "std_headers.h"
#include "dictionary.h"
#include "Trie.h"

#include <iostream>

TrieNode::TrieNode()
    : isWord(false), indices(nullptr), numNonNullBranches(0)
{
    for (int i = 0; i < NUM_CHARS; i++) {
        branch[i] = nullptr;
    }
}

TrieNode::~TrieNode()
{
    listOfObjects<int>* currIndex = indices;
    while (currIndex != nullptr) {
        listOfObjects<int>* toDeleteIndex = currIndex;
        currIndex = currIndex->next;
        delete toDeleteIndex;
    }
}

// FIXME
void Trie::recursiveDelete(TrieNode* node)
{
    if (node != nullptr) {
        for (int i = 0; i < NUM_CHARS; i++) {
            TrieNode* currNode = node->branch[i];
            recursiveDelete(currNode);
            node->branch[i] = nullptr;
        }
        if (node != root) {
            delete node;
        }
    }
}

bool Trie::isPresentInCompletions(listOfObjects<std::string>* completions, std::string name)
{
    listOfObjects<std::string>* currCompletion = completions;
    while (currCompletion != nullptr) {
        if (currCompletion->object == name) {
            return true;
        }
        currCompletion = currCompletion->next;
    }
    return false;
}

void Trie::freeCompletionList(listOfObjects<std::string>* completions)
{
    listOfObjects<std::string>* currCompl = completions;
    while (currCompl != nullptr) {
        listOfObjects<std::string>* toDeleteCompl = currCompl;
        currCompl = currCompl->next;
        delete toDeleteCompl;
    }
}

bool Trie::recursiveAddCompletions(TrieNode* node, listOfObjects<std::string>*& currCompletions)
{
    if (node->isWord && !addCompletions(node, currCompletions)) {
        return false;
    }

    TrieNode* currNode = node;
    for (int i = 0; i < NUM_CHARS; i++) {
        if (currNode->branch[i] != nullptr && !recursiveAddCompletions(currNode->branch[i], currCompletions)) {
            return false;
        }
    }

    return true;
}

bool Trie::addCompletions(TrieNode* node, listOfObjects<std::string>*& currCompletions)
{
    listOfObjects<int>* headIndex = node->indices;
    if (currCompletions == nullptr) {
        currCompletions = new listOfObjects<std::string>(nameDict->getKeyAtIndex(headIndex->object));
        headIndex = headIndex->next;
        std::cout << currCompletions->object << '\n';
    }
    listOfObjects<std::string>* headName = nullptr;
    listOfObjects<std::string>* tail = currCompletions;
    while (tail != nullptr) {
        headName = tail;
        tail = tail->next;
    }
    std::cout << headName->object << '\n';
    while (!headIndex) {
        headName->next = new listOfObjects<std::string>(nameDict->getKeyAtIndex(headIndex->object));
        headName = headName->next;
        headIndex = headIndex->next;
        std::cout << headName->object << '\n';
    }
    if (headName == nullptr) {
        return false;
    }
    return true;
}

Trie::Trie(Dictionary<int>* nameToIndex)
    : nameDict(nameToIndex), root(new TrieNode)
{
    if (root == nullptr) {
        std::cout << "Memory allocation failure.\n";
        exit(-1);
    }
}

Trie::~Trie()
{
    recursiveDelete(root);
}

bool Trie::insert(std::string wordInName, int indexOfName)
{
    TrieNode* currNode = root;

    for (int i = 0; i < wordInName.length(); i++) {
        TrieNode* nextNode = currNode->branch[toupper(wordInName[i]) - 'A'];
        if (nextNode == nullptr) {
            nextNode = new TrieNode();
            currNode->branch[toupper(wordInName[i]) - 'A'] = nextNode;
            currNode->numNonNullBranches += 1;
        }
        currNode = nextNode;
    }
    if (currNode->indices == nullptr)
        currNode->indices = new listOfObjects<int>(indexOfName);
    else {
        currNode->indices->next = new listOfObjects<int>(indexOfName);
    }
    currNode->isWord = true;
    return true;
}

bool Trie::del(std::string wordInName, std::string name)
{
    TrieNode* currNode = root;
    TrieNode* lastBranchNode = nullptr;
    int lastBranchChar = -1;
    int len = wordInName.length();

    // Insert your code here

    return false;
}

listOfObjects<std::string>* Trie::completions(std::string prefix)
{
    TrieNode* currNode = root;
    int len = prefix.length();

    for (int i = 0; i < len && currNode != nullptr; i++) {
        currNode = currNode->branch[toupper(prefix[i]) - 'A'];
    }
    if (currNode == nullptr)
        return nullptr;

    listOfObjects<std::string>* completions = nullptr;
    if (!recursiveAddCompletions(currNode, completions))
        return nullptr;
    return completions;
}



bool Trie::isPresent(std::string wordInName)
{
    TrieNode* currNode = root;
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

void Trie::printTrie()
{
    recursivePrintTrie(root, "", -1, false);
}

// Adapted from Adrian Schneider's code on StackOverflow
// Basically a variation of the function we've been using
// print binary search trees in previous labs

void Trie::recursivePrintTrie(TrieNode* node, std::string const& prefix, int branchId, bool siblingsToRight)
{
    if (node != nullptr) {
        std::cout << prefix;
    
        std::cout << ((branchId == 0) ? "|-" : (branchId == -1)? " *" : "|_" ) << (char) ((branchId != -1) ? 'A' + branchId : '*');
        std::cout << ((branchId == 0) ? '-' : (branchId == -1) ? '*' : '_');
        
        // If this trie node has isWord set to true, print "(isWord)" and
        // also the list of complete station names (accessed through indices
        // in nameDict) associated with this trie node.
        if (node->isWord) {
            std::cout << "(isWord)";
            listOfObjects<int>* currIndices = node->indices;
            while (currIndices != nullptr) {
                std::cout << '\n' << prefix << "     " << nameDict->getKeyAtIndex(currIndices->object);
                currIndices = currIndices->next;
            }
        }
        else {
            std::cout << "()";
        }
        std::cout << '\n';
        for (int i = 0; i < NUM_CHARS; i++) {
            TrieNode* currNode = node->branch[i];
            bool childrenToRight = false;
            for (int j = i + 1; j < NUM_CHARS; j++) {
                if (node->branch[j] != nullptr) {
                    childrenToRight = true;
                    break;
                }
            }
            if (currNode != nullptr) {
                recursivePrintTrie(currNode, prefix + (siblingsToRight ? "│   " : "    "), i, childrenToRight);
            }
        }
    } 
}

#endif
