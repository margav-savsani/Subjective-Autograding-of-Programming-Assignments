#ifndef GRAPH_BST_H
#define GRAPH_BST_H

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

void split(string str, char seperator, string strings[])
{
  int currIndex = 0, i = 0;
  int startIndex = 0, endIndex = 0;
  while (i <= str.size())
  {
    if (str[i] == seperator || i == str.size())
    {
      endIndex = i;
      string subStr = "";
      subStr.append(str, startIndex, endIndex - startIndex);
      strings[currIndex] = subStr;
      currIndex += 1;
      startIndex = endIndex + 1;
    }
    i++;
  }
}

template <typename T>
class listOfObjects
{
public:
  T object;
  listOfObjects<T> *next;
  listOfObjects<T> *prev;

  // Constructor
  listOfObjects(T initValue)
  {
    object = initValue;
    next = prev = nullptr;
  }

  // Destructor
  ~listOfObjects() { ; }
};

template <typename T>
class listing
{
public:
  T object1;
  T object2;
  listing<T> *next;
  listing<T> *prev;

  // Constructor
  listing(T init1, T init2)
  {
    object1 = init1;
    object2 = init2;
    next = prev = nullptr;
  }

  // Destructor
  ~listing() { ; }
};

class NodeAdjacencyList
{
public:
  listOfObjects<int> *to;
  listOfObjects<int> *from;

  NodeAdjacencyList()
  {
    to = from = nullptr;
  }

  ~NodeAdjacencyList()
  {
    listOfObjects<int> *currStnConnInfo;
    listOfObjects<int> *delStnConnInfo;

    currStnConnInfo = to;
    while (currStnConnInfo != nullptr)
    {
      delStnConnInfo = currStnConnInfo;
      currStnConnInfo = currStnConnInfo->next;
      // delete delStnConnInfo->object;
      delete delStnConnInfo;
    }

    currStnConnInfo = from;
    while (currStnConnInfo != nullptr)
    {
      delStnConnInfo = currStnConnInfo;
      currStnConnInfo = currStnConnInfo->next;
      // delete delStnConnInfo->object;
      delete delStnConnInfo;
    }
  }
};

class Node
{
public:
  int value;
  NodeAdjacencyList *adjacent = new NodeAdjacencyList();
  listOfObjects<int> *similar = nullptr;
  // insert other fields and methods as appropriate
};

class Graph
{
  int numNodes;
  fstream graphFile;

  Node *nodes;
  int *maxi;
  listing<int> *sim = nullptr;
  // Add appropriate fields as necessary for your implementation

public:
  Graph(string gFileName)
  {
    int count = 0;
    int count1 = 0;
    graphFile.open(gFileName);
    if (!graphFile.is_open())
    {
      cerr << "Couldn't open graph file " << gFileName << ". Aborting ..." << endl;
      exit(-1);
    }
    else
    {
      string x;
      while (getline(graphFile, x))
      {
        if (count == 0) //&& count1 == 0)
        {
          numNodes = stoi(x);

          // creating nodes
          nodes = new Node[numNodes];
          maxi = new int[numNodes];
          if (nodes == nullptr)
          {
            cerr << "Memory allocation failure." << endl;
            exit(-1);
          }

          for (int i = 0; i < numNodes; i++)
          {
            nodes[i].value = i + 1;
            maxi[i] = i + 1;
          }
          // creating nodes

          // cout << numNodes << endl;
          count++;
        }
        else if (count1 == 0)
        {
          // cout << "hello" << endl;
          string strings[2];
          char seperator = ' ';
          split(x, seperator, strings);
          int num1 = stoi(strings[0]);
          int num2 = stoi(strings[1]);
          // cout << num1 << " ";
          // cout << num2 << endl;
          if (num1 == -1 && num2 == -1)
          {
            count1++;
            continue;
          }
          if (nodes[num1 - 1].adjacent->to == nullptr)
          {
            nodes[num1 - 1].adjacent->to = new listOfObjects<int>(num2);
          }
          else
          {
            listOfObjects<int> *last = nodes[num1 - 1].adjacent->to;
            while (last->next != nullptr)
              last = last->next;
            last->next = new listOfObjects<int>(num2);
          }
          if (nodes[num2 - 1].adjacent->from == nullptr)
          {
            nodes[num2 - 1].adjacent->from = new listOfObjects<int>(num1);
          }
          else
          {
            listOfObjects<int> *last = nodes[num2 - 1].adjacent->from;
            while (last->next != nullptr)
              last = last->next;
            last->next = new listOfObjects<int>(num1);
          }
          count++;
        }
        else // after the first -1 -1 line
        {
          // cout << "hello1" << endl;
          string strings[2];
          char seperator = ' ';
          split(x, seperator, strings);
          int num1 = stoi(strings[0]);
          int num2 = stoi(strings[1]);
          // cout << num1 << " ";
          // cout << num2 << endl;
          if (num1 == -1 && num2 == -1)
          {
            break;
          }
          else
            add_similar(num1, num2);
        }
      }
      graphFile.close();
      // Add appropriate code as necessary for your implementation
    }
  }
  ~Graph()
  {
    delete[] nodes;
    // Add appropriate code as necessary for your implementation
  }

  // Add appropriate method declarations as necessary for your implementation
  void printsource();
  bool check_similar(int num1, int num2);
  void add_similar(int num1, int num);
  void compute_similar();
  void print_similar();
  void collapse();
};
#endif
