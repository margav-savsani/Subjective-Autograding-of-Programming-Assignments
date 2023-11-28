#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <sstream>

using namespace std;

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

class Node
{
public:
  int value;
  bool issrc;
  listOfObjects<Node *> *toadjacencylist;
  listOfObjects<Node *> *fromadjacencylist;
  listOfObjects<Node *> *tailof_toadjlist;
  listOfObjects<Node *> *tailof_fromadjlist;
  Node()
  {
    issrc = true;
    fromadjacencylist = nullptr;
    tailof_fromadjlist = nullptr;
    toadjacencylist = nullptr;
    tailof_toadjlist = nullptr;
  }
  void add_toadjnode(Node *adj)
  {
    if (toadjacencylist == nullptr)
    {
      toadjacencylist = new listOfObjects<Node *>(adj);
      tailof_toadjlist = toadjacencylist;
    }
    else
    {
      tailof_toadjlist->next = new listOfObjects<Node *>(adj);
      tailof_toadjlist = tailof_toadjlist->next;
    }
  }

  void add_fromadjnode(Node *adj)
  {
    if (fromadjacencylist == nullptr)
    {
      fromadjacencylist = new listOfObjects<Node *>(adj);
      tailof_fromadjlist = fromadjacencylist;
    }
    else
    {
      tailof_fromadjlist->next = new listOfObjects<Node *>(adj);
      tailof_fromadjlist = tailof_fromadjlist->next;
    }
    issrc = false;
  }

  // insert other fields and methods as appropriate
};

class Pair
{
public:
  int e1, e2;
  Pair(int a, int b)
  {
    e1 = a;
    e2 = b;
  }
};

class Graph
{
  int numNodes;

  Node *nodes;
  listOfObjects<Pair *> *similarnodes;
  listOfObjects<Pair *> *tailofsimilarnodes;
  fstream graphFile;
  // Add appropriate fields as necessary for your implementation

public:
  Graph(string gFile)
  {
    graphFile.open(gFile, ios::out);

    cin >> numNodes;
    nodes = new Node[numNodes];
    bool *visited, *added;
    visited = new bool[numNodes];
    added = new bool[numNodes];
    similarnodes = tailofsimilarnodes = nullptr;
    for (int i = 0; i < numNodes; i++)
    {
      nodes[i].value = i + 1;
      visited[i] = 0;
      added[i] = 0;
    }

    while (true)
    { // adding edges
      int node1, node2;
      cin >> node1;
      cin >> node2;
      if (node1 == -1)
      {
        break;
      }
      nodes[node1 - 1].add_toadjnode(nodes + node2 - 1);
      nodes[node2 - 1].add_fromadjnode(nodes + node1 - 1);
    }
    while (true)
    { // adding user specified similar nodes
      int node1, node2;
      cin >> node1;
      cin >> node2;
      if (node1 == -1)
      {
        break;
      }
      Pair *p = new Pair(node1, node2);
      if (similarnodes == nullptr)
      {
        similarnodes = new listOfObjects<Pair *>(p);
        tailofsimilarnodes = similarnodes;
      }
      else
      {
        tailofsimilarnodes->next = new listOfObjects<Pair *>(p);
        tailofsimilarnodes = tailofsimilarnodes->next;
      }
    }

    for (int i = 0; i < numNodes; i++)
    {
      if (visited[i] == 0 && nodes[i].issrc)
      {
        visited[i] = 1;
        listOfObjects<int> *head = new listOfObjects<int>(i + 1);
        listOfObjects<int> *tail = head;

        while (head != nullptr)
        {
          listOfObjects<Node *> *children = nodes[head->object - 1].toadjacencylist;
          while (children != nullptr)
          {
            int ind = children->object->value;
            if (!visited[ind])
            {
              visited[ind] = 1;
              tail->next = new listOfObjects<int>(children->object->value);
              tail = tail->next;
              check3rd(children->object->value);
            }
            children = children->next;
          }
          head = head->next;
        }
      }
    }

    listOfObjects<int> *one = nullptr;
    listOfObjects<int> *tailofone = nullptr;

    for (int i = 0; i < numNodes; i++)
    {
      if (nodes[i].issrc)
      {
        listOfObjects<Node *> *children = nodes[i].toadjacencylist;
        while (children != nullptr)
        {
          int val = children->object->value;
          if (!added[val - 1])
          {
            added[val - 1] = 1;
            if (one == nullptr)
            {
              one = new listOfObjects<int>(val);
              tailofone = one;
            }
            else
            {
              tailofone->next = new listOfObjects<int>(val);
              tailofone = tailofone->next;
            }
          }
          children = children->next;
        }
      }
    }
    listOfObjects<int> *a = one;
    realcheck2nd(a);
  }

  ~Graph()
  {
    if (graphFile.is_open())
    {
      graphFile.close();
    }
    delete[] nodes;
    // Add appropriate code as necessary for your implementation
  }
  void realcheck2nd(listOfObjects<int> *a)
  {
    while (a->next != nullptr)
    {
      listOfObjects<int> *b = a->next;
      while (b != nullptr)
      {
        if (check2nd(a->object, b->object))
        {
          listOfObjects<int> *x = nullptr;
          listOfObjects<int> *tailofx = nullptr;

          listOfObjects<Node *> *ca = nodes[a->object - 1].toadjacencylist;
          listOfObjects<Node *> *cb = nodes[b->object - 1].toadjacencylist;
          while (ca != nullptr)
          {
            if (x == nullptr)
            {
              x = new listOfObjects<int>(ca->object->value);
              tailofx = x;
            }
            else
            {
              tailofx->next = new listOfObjects<int>(ca->object->value);
              tailofx = tailofx->next;
            }
            ca = ca->next;
          }
          while (cb != nullptr)
          {
            if (x == nullptr)
            {
              x = new listOfObjects<int>(cb->object->value);
              tailofx = x;
            }
            else
            {
              tailofx->next = new listOfObjects<int>(cb->object->value);
              tailofx = tailofx->next;
            }
            cb = cb->next;
          }
          realcheck2nd(x);
        }
        b = b->next;
      }
      a = a->next;
    }
  }
  bool check2nd(int a, int b)
  {
    listOfObjects<Node *> *pa = nodes[a - 1].fromadjacencylist;
    listOfObjects<Node *> *pb = nodes[b - 1].fromadjacencylist;

    while (pa != nullptr)
    {
      bool found = false;

      while (pb != nullptr && !found)
      {
        if (ispair(pa->object->value, pb->object->value))
        {
          found = true;
        }
        pb = pb->next;
      }
      if (!found)
      {
        return false;
      }
      pa = pa->next;
      pb = nodes[b - 1].fromadjacencylist;
    }
    pa = nodes[a - 1].fromadjacencylist;
    pb = nodes[b - 1].fromadjacencylist;
    while (pb != nullptr)
    {
      bool found = false;
      while (pa != nullptr)
      {
        if (ispair(pb->object->value, pa->object->value))
        {
          found = true;
        }
        pa = pa->next;
      }
      if (!found)
      {
        return false;
      }
      pb = pb->next;
      pa = nodes[a - 1].fromadjacencylist;
    }

    Pair *p1 = new Pair(a, b);
    Pair *p2 = new Pair(b, a);
    if (similarnodes == nullptr)
    {
      similarnodes = new listOfObjects<Pair *>(p1);
      tailofsimilarnodes = similarnodes;
      tailofsimilarnodes->next = new listOfObjects<Pair *>(p2);
      tailofsimilarnodes = tailofsimilarnodes->next;
    }
    else
    {
      tailofsimilarnodes->next = new listOfObjects<Pair *>(p1);
      tailofsimilarnodes = tailofsimilarnodes->next;
      tailofsimilarnodes->next = new listOfObjects<Pair *>(p2);
      tailofsimilarnodes = tailofsimilarnodes->next;
    }
    return true;
  }
  bool ispair(int a, int b)
  {
    listOfObjects<Pair *> *list = similarnodes;
    while (list != nullptr)
    {
      if (a == list->object->e1 && b == list->object->e2)
      {
        return true;
      }
      list = list->next;
    }
    return false;
  }
  void check3rd(int c)
  {
    if (nodes[c - 1].fromadjacencylist != nullptr)
    {
      if (nodes[c - 1].fromadjacencylist->next == nullptr)
      {
        Pair *p = new Pair(c, nodes[c - 1].fromadjacencylist->object->value);
        if (similarnodes == nullptr)
        {
          similarnodes = new listOfObjects<Pair *>(p);
          tailofsimilarnodes = similarnodes;
        }
        else
        {
          tailofsimilarnodes->next = new listOfObjects<Pair *>(p);
          tailofsimilarnodes = tailofsimilarnodes->next;
        }
      }
    }
  }
  void printsourcenodes()
  {
    graphFile << "Source nodes:";
    for (int i = 0; i < numNodes; i++)
    {
      if (nodes[i].issrc)
      {
        graphFile << " " << i + 1;
      }
    }
    graphFile << endl
              << endl;
  }
  void printsimilarndoepairs()
  {
    graphFile << "Similar node pairs:";
    if (similarnodes != nullptr)
    {
      listOfObjects<Pair *> *list = similarnodes;
      while (list != nullptr)
      {
        int p1 = list->object->e1, p2 = list->object->e2;
        graphFile << " (" << p1 << ", " << p2 << ")";
        list = list->next;
      }
      graphFile << endl
                << endl;
    }
  }
  void collapse()
  {
    graphFile << "Collapsed graph:\n\n";

    for (int i = 0; i < numNodes; i++)
    {
      int old = nodes[i].value;
      int x = checkinsimilar(old);
      if (x != -1)
      {
        changesimilar(old, x);
        changenodes(old, x);
      }
    }
    int count = 0;
    listOfObjects<int> *colls = nullptr;
    listOfObjects<int> *tailofcolls = nullptr;
    for (int i = 0; i < numNodes; i++)
    {
      if (nodes[i].value == i + 1)
      {
        count++;
        if (colls == nullptr)
        {
          colls = new listOfObjects<int>(i + 1);
          tailofcolls = colls;
        }
        else
        {
          tailofcolls->next = new listOfObjects<int>(i + 1);
          tailofcolls = tailofcolls->next;
        }
      }
    }
    graphFile << count << ":";
    while (colls != nullptr)
    {
      graphFile << " " << colls->object;
      colls = colls->next;
    }
    graphFile << endl;

    listOfObjects<Pair *> *list = nullptr;
    listOfObjects<Pair *> *tailoflist = nullptr;

    for (int i = 0; i < numNodes; i++)
    {
      listOfObjects<Node *> *c = nodes[i].toadjacencylist;
      int par = nodes[i].value;
      while (c != nullptr)
      {
        int val = c->object->value;
        if (par != val)
        {
          Pair *p = new Pair(par, val);
          listOfObjects<Pair *> *clist = list;
          bool found = false;
          while (clist != nullptr)
          {
            if (p->e1 == clist->object->e1 && p->e2 == clist->object->e2)
            {
              found = true;
            }
            clist = clist->next;
          }
          if (!found)
          {
            if (list == nullptr)
            {
              list = new listOfObjects<Pair *>(p);
              tailoflist = list;
            }
            else
            {
              tailoflist->next = new listOfObjects<Pair *>(p);
              tailoflist = tailoflist->next;
            }
          }
        }
        c = c->next;
      }
    }

    while (list != nullptr)
    {
      graphFile << list->object->e1 << " " << list->object->e2 << endl;
      list = list->next;
    }
  }
  void changenodes(int old, int x)
  {
    for (int i = 0; i < numNodes; i++)
    {
      if (nodes[i].value == old)
      {
        nodes[i].value = x;
      }
    }
  }
  void changesimilar(int old, int neww)
  {
    listOfObjects<Pair *> *list = similarnodes;
    while (list != nullptr)
    {
      if (list->object->e1 == old)
      {
        list->object->e1 = neww;
      }
      if (list->object->e2 == old)
      {
        list->object->e2 = neww;
      }
      list = list->next;
    }
  }
  int checkinsimilar(int x)
  {
    listOfObjects<Pair *> *list = similarnodes;
    while (list != nullptr)
    {
      if (list->object->e1 == x)
      {
        if (list->object->e2 > x)
        {
          return list->object->e2;
        }
      }
      if (list->object->e2 == x)
      {
        if (list->object->e1 > x)
        {
          return list->object->e1;
        }
      }
      list = list->next;
    }
    return -1;
  }
};
