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

//constructor function with the pointer to dictionary as input parameter
Trie::Trie(Dictionary<int> *nameToIndex)
{
  nameDict = nameToIndex;
  root = new TrieNode(); //allocating a memory to the root node of the Trie
  if (root == nullptr)
  {
    cout << "Memory allocation failure." << endl;
    exit(-1);
  }
}

//Destructor function 
Trie::~Trie()
{
  recursiveDelete(root);
}

//Deletes everything below and including the TrieNode given
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

//inserts a given string(wordInName) in the trie and the index of the entire station name corresponding to the dictionary
bool Trie::insert(string wordInName, int indexOfName)
{
  TrieNode *currNode = root; //initialise the currNode to root. This is the pointer that will traverse the trie(adding the required nodes at each step)
  int len = wordInName.length(); //The length that has to be traversed

  for (int i = 0; i < len; i++) // Traversing the trie 
  {
    int index = toupper(wordInName[i]) - 'A'; //This index denotes the character to be added
    if (currNode->branch[index] == nullptr) //If the node is not active already
    {
      currNode->branch[index] = new TrieNode();//Activating the node(just allocating a new memory to this TrieNode indicates that the corresponding character has been activated)
      currNode->numNonNullBranches++; //Trivially the number of branches which are no more null pointer increases by 1
    }
    currNode = currNode->branch[index]; //In any case(whether branch was activated or not) moving the current node to the next step
  }
  //now the current node(currNode) has reached the end point of the Trie where we have to mention that word has been added

  //setting the variable isWord to true to indicate that we have completed the word
  currNode->isWord = true;

  //currNode->indices is the linked list of indices that have to be stored
  listOfObjects<int> *indices = currNode->indices;

  //if the linked list has not been created yet, assign a new memory to it 
  if (currNode->indices == nullptr)
  {
    currNode->indices = new listOfObjects<int>(indexOfName); //assigning a new memory to it with its object being set to the index(of the entire station name corresponding to the dictionary) to be added
  }
  else // if the linked list has been created already earlier
  {
    while (indices->next != nullptr) // traverse to the point where we have to add a new index
    {
      indices = indices->next;
    }
    indices->next = new listOfObjects<int>(indexOfName); // add the index to the linked list
  }

  return true; //returning true after inserting the string in the Trie
}

//deleting a given string(wordInName) from the trie whose entire station name(name) is also given
bool Trie::del(string wordInName, string name)
{ 
  TrieNode *currNode = root;//initialise the currNode to root. This is the pointer that will traverse the trie
  int len = wordInName.length();//The length that has to be traversed

  // Insert your code here
  int dict_index = nameDict->get(name)->value; //The index at which the string(name) is present in the dictionary

  //if the string to be deleted is not present in the trie return true
  if (!isPresent(wordInName))
  {
    return true;
  }

  //traverse the trie and reach the last branch corresponding to the input string
  for (int i = 0; i < len; i++)
  {
    int index = toupper(wordInName[i]) - 'A';
    currNode = currNode->branch[index];
  }
  //currNode has reached the last branch corresponding to the input string

  //currNode->indices denotes the linkedlist(basically the head pointer) of indices corresponding to the last branch
  listOfObjects<int> *indices = currNode->indices;

  //case-1:Number of indices at that branch is more than 1
  //Here we delete just the required index we calculated earlier and the deletion will be complete
  if (indices->next != nullptr)
  {
    listOfObjects<int> *prev = nullptr; //The pointer to the index which preceeds the pointer which has to be removed
    listOfObjects<int> *prevprev = nullptr; //The pointer to the index which preceeds prev
    while (indices->next != nullptr)
    {
      if (indices->object == dict_index) //indices is the pointer which has the index as the one which is to be deleted
      {
        if (prev == nullptr) //special case where we find the index in the first node of the linked list
        {
          currNode->indices = indices->next;
          return true;
        }
        //special case when we find the index at the second node of the linked list
        if(prevprev == nullptr){ 
          currNode->indices = prev;
          currNode->indices->next = nullptr;
          return true;
        }
        //other than special cases
        prevprev->next->next = indices->next; //this pointer manevour basically deletes the pointer containing the required index
        return true;
      }
      //if not found the index yet move forward in the linked list
      prevprev = prev;
      prev = indices; 
      indices = indices->next;
    }
    //we again check once because of the bounday case that the index is at the last node of the linked list
    if (indices->object == dict_index) //indices is the pointer which has the index as the one which is to be deleted
      {
        if (prev == nullptr) //special case where we find the index in the first node of the linked list
        {
          currNode->indices = indices->next;
          return true;
        }
        //other than special case
        if(prevprev == nullptr){
          currNode->indices = prev;
          currNode->indices->next = nullptr;
          return true;
        }
        prevprev->next->next = indices->next; //this pointer manevour basically deletes the pointer containing the required index
        return true;
      }

    return true; // if the index was not found
  }

  //Case 2: number of indices at the last branch is 1 and this branch is a leaf of the Trie.
  if (indices->next == nullptr && indices->object == dict_index && currNode->numNonNullBranches == 0)
  { //flagNode is the last node from the root which has more than one branches while traversing through the path of the string to be deleted
    //flagpoint corresponds to the index of the string(to be deleted) through which we can get the next branch of flagNode in the path of the string to be deleted
    //process to find flagNode starts
    TrieNode *currentNode = root;
    TrieNode *flagNode = root;
    int flagpoint = 0;
    for (int i = 0; i < len; i++)
    {
      int index = toupper(wordInName[i]) - 'A';
      currentNode = currentNode->branch[index];
      if (currentNode->numNonNullBranches > 1)
      {
        flagNode = currentNode;
        flagpoint = i+1;
      }
    }
    
    //flagNode found
    //note that currentNode has reached the last branch point in the path of the string to be deleted

    currentNode->isWord = false;//setting the last branch points isWord variable to false(remember that there was only 1 index for this branch point in this case2)(this is basically a sanity check,not necessary)
    currentNode->indices = nullptr;
    //recursiveDelete(flagNode->branch[toupper(wordInName[flagpoint]) - 'A']); //Deletes everything beyond the flagNode
    flagNode->branch[toupper(wordInName[flagpoint]) - 'A'] = nullptr; //setting the branch next to flagNode to nullptr to complete the deletion
    flagNode->numNonNullBranches--; //reducing the number of null branches of flagnode by 1 due to previous statement

    return true;
  }

  //Case 3: number of indices at the last branch is 1 and this branch is not a leaf of the Trie. 
  else
  { //Simply set the isWord variable to false and indices to null pointer so that nothing is affected structurally in the Trie
    currNode->isWord = false;
    currNode->indices = nullptr;
  }

  return false;
}

//Takes in a prefix and returns a linked list of all the matching station names from the dictionary
listOfObjects<string> *Trie::completions(string prefix)
{
  TrieNode *currNode = root;
  int len = prefix.length();
  listOfObjects<string> *currCompletions = new listOfObjects<string>("container"); //This is the container pointer whose next pointer is basically the actual head of the linkedlist of all required staion names

  // Insert your code here
  for (int i = 0; i < len; i++)
  { //traversing throught the trie to reach the last branch point in the path of the prefix
    int index = toupper(prefix[i]) - 'A';
    //special case when the prefix is not present in the Trie
    if (currNode->branch[index] == nullptr)
    {
      return nullptr;
    }
    currNode = currNode->branch[index];
  }
  //note that currNode has reached the last branch point in the path of the prefix

  //This function will update linked list to consist of all strings which comprises the given prefix
  recursiveAddCompletions(currNode, currCompletions);

  return currCompletions->next;
}

// Already written function which updates the linked list to consist of all strings which comprises the given prefix
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

//This function takes in a node pointer(in the Trie) and a linked list and updates it to comprise all words stored in the linkedlist at that branch point
bool Trie::addCompletions(TrieNode *node, listOfObjects<string> *currCompletions)
{
  //move ahead only if that branch point contains any words
  //***And note that currCompletions->next is the head of the linked list comprising of strings
  if (node->isWord == true)
  { //node->indices is the linked list of all the indices corresponding to the dictionary stored at that branch point
    listOfObjects<int> *indices = node->indices;

    //if the linkedlist of strings is empty to start with then add the first station name to it
    if (currCompletions->next == nullptr)
    {
      currCompletions->next = new listOfObjects<string>(nameDict->getKeyAtIndex(indices->object));
    }
    
    listOfObjects<string> *completions = currCompletions->next;
    //reach the point of the linked list of strings where addition of strings should start
    while (completions->next != nullptr)
    {
      completions = completions->next;
    }

    //start inserting the strings until all station names stored at that branch point have been added in the linked list
    while (indices != nullptr)
    {
      string word = nameDict->getKeyAtIndex(indices->object); //get the corresponding string from the index stored at the branch point
      if (!isPresentInCompletions(currCompletions->next, word)) //add only if the string(to be added) is not already present in the linked list of strings
      {
        completions->next = new listOfObjects<string>(word);
        completions = completions->next;
      }
      indices = indices->next;
    }
    return true;
  }
  //if there are no words present at the branch point provided return false
  return false;
}

//checks if a given string is present or not in a given linked list of strings(already present)
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

//Deletes the linked list of strings provided(already present)
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

//checks if a given string is present in the Trie or not(already present)
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
