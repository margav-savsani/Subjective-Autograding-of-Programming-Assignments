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

Trie::Trie(Dictionary<int>* nameToIndex)
{
    nameDict = nameToIndex;
    root = new TrieNode;
    if (root == nullptr) {
        std::cout << "Memory allocation failure.\n";
        exit(-1);
    }
}

Trie::~Trie()
{
    recursiveDelete(root);
}

void Trie::recursiveDelete(TrieNode* node)
{
    if (node == nullptr) {
        return;
    }
    else {
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

listOfObjects<std::string>* Trie::recursiveCompletions(TrieNode* currNode, listOfObjects<std::string>* l = nullptr)
{
    // TODO : remove repeated station names
    listOfObjects<std::string>* headName = nullptr;
    if (currNode->isWord) {
        listOfObjects<int>* headIndex = currNode->indices;
        if (l == nullptr) {
            l = new listOfObjects<std::string>(nameDict->getKeyAtIndex[headIndex->object]);
            headName = l;
        }
        else {
            l->next = new listOfObjects<std::string>(nameDict->getKeyAtIndex[headIndex->object]);
            headName = l->next;
        }
        while (headIndex != nullptr) {
            headIndex = headIndex->next;
            headName->next = new listOfObjects<std::string>(nameDict->getKeyAtIndex[headIndex->object]);
            headName = headName->next;
        }
    }
    for (int i = 0; i < NUM_CHARS; i++) {
        if (currNode->branch[i] != nullptr) {
            recursiveCompletions(currNode->branch[i], headName);
        }
    }
    return l;
}

listOfObjects<std::string>* Trie::completions(std::string prefix)
{
    TrieNode* currNode = root;
    int len = prefix.length();
    listOfObjects<std::string>* currCompletions = nullptr;

    for (int i = 0; i < len && currNode != nullptr; i++) {
        currNode = currNode->branch[toupper(prefix[i]) - 'A'];
    }
    if (currNode == nullptr)
        return nullptr;

    return recursiveCompletions(currNode);
}

bool Trie::recursiveAddCompletions(TrieNode* node, listOfObjects<std::string>* currCompletions)
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

bool Trie::addCompletions(TrieNode* node, listOfObjects<std::string>* currCompletions)
{

    // Insert your code here
    return false;
}

bool Trie::isPresentInCompletions(listOfObjects<std::string>* completions, std::string name)
{
    listOfObjects<std::string>* currCompletion = completions;
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

void Trie::freeCompletionList(listOfObjects<std::string>* completions)
{
    listOfObjects<std::string>* currCompl = completions;
    while (currCompl != nullptr) {
        listOfObjects<std::string>* toDeleteCompl = currCompl;
        currCompl = currCompl->next;
        delete toDeleteCompl;
    }
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

#endif
