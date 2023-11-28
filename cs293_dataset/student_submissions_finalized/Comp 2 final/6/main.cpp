#include <iostream>
#include <fstream>
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
  listOfObjects<int> *to_list;
  listOfObjects<int> *from_list;
  listOfObjects<int> *similar_list;
  listOfObjects<int> *current_to;
  listOfObjects<int> *current_from;
  listOfObjects<int> *current_sim;

  Node()
  {
    to_list = nullptr;
    from_list = nullptr;
    similar_list = nullptr;
    current_to = nullptr;
    current_from = nullptr;
    current_sim = nullptr;
  }
  Node(int val)
  {
    value = val;
    to_list = nullptr;
    from_list = nullptr;
    similar_list = nullptr;
    current_to = nullptr;
    current_from = nullptr;
    current_sim = nullptr;
  }
  void insert_neighbour_to(int neighbour)
  {
    listOfObjects<int> *newnode = new listOfObjects<int>(neighbour);
    if (to_list == nullptr)
    {
      to_list = newnode;
      current_to = newnode;
    }
    else
    {
      current_to->next = newnode;
      newnode->prev = current_to;
      current_to = newnode;
    }
  }

  void insert_neighbour_from(int neighbour)
  {
    listOfObjects<int> *newnode = new listOfObjects<int>(neighbour);
    if (from_list == nullptr)
    {
      from_list = newnode;
      current_from = newnode;
    }
    else
    {
      current_from->next = newnode;
      newnode->prev = current_from;
      current_from = newnode;
    }
  }

  void insert_similar(int sim)
  {
    listOfObjects<int> *newnode = new listOfObjects<int>(sim);
    if (similar_list == nullptr)
    {
      similar_list = newnode;
      current_sim = newnode;
    }
    else
    {
      current_sim->next = newnode;
      newnode->prev = current_sim;
      current_sim = newnode;
    }
  }
  bool check_similar(int sim)
  {
    listOfObjects<int> *iter_list = similar_list;
    while (iter_list != nullptr)
    {
      if (iter_list->object == sim)
        return true;
      iter_list = iter_list->next;
    }
    return false;
  }
  
};


class Directed_Graph
{
public:

  int numNodes;
  Node* nodes;
  int* collapse_max;

  Directed_Graph(int n)
  {
    numNodes = n;
    nodes = new Node[numNodes+1];
    collapse_max = new int[numNodes+1];
    for (int i = 0; i <= numNodes; i++)
    {
      collapse_max[i] = i;
      nodes[i].value = i;
    }
  }
  
  bool check_similar_graph(int i, int j)
  {
    if(nodes[i].check_similar(j) && nodes[j].check_similar(i))
      return true;
    if(nodes[i].from_list == nullptr || nodes[j].from_list == nullptr)
      return false;

    // rule 2
    listOfObjects<int> *temp_from = nodes[i].from_list;
    while(temp_from != nullptr)
    {
      int m1 = temp_from->object;
      listOfObjects<int> *temp_to = nodes[j].from_list;
      bool present = false;
      while(temp_to != nullptr)
      {
        if(nodes[m1].check_similar(temp_to->object))
        {
          present = true;
          break;
        }
        else
        {
          if(check_similar_graph(m1, temp_to->object))
          {
            present = true;
            break;
          }
        }
        temp_to = temp_to->next;
      }
      if(!present)
        return false;
      temp_from = temp_from->next;
    }

    // for vice-versa
    temp_from = nodes[j].from_list;
    while(temp_from != nullptr)
    {
      int m2 = temp_from->object;
      listOfObjects<int> *temp_to = nodes[i].from_list;
      bool present = false;
      while(temp_to != nullptr)
      {
        if(nodes[m2].check_similar(temp_to->object))
        {
          present = true;
          break;
        }
        else
        {
          if(check_similar_graph(m2, temp_to->object))
          {
            present = true;
            break;
          }
        }
        temp_to = temp_to->next;
      }
      if(!present)
        return false;
      temp_from = temp_from->next;
    }
    return true;
  }
};

int main()
{
  int num;
  cin >> num;
  Directed_Graph graph(num);
  int n1, n2;

  while (true)
  { 
    // node and edge reading
    cin >> n1; 
    cin >> n2;
    if (n1 == -1 && n2 == -1)
      break;
    graph.nodes[n1].insert_neighbour_to(n2);
    graph.nodes[n2].insert_neighbour_from(n1);

  }

  while (true)
  { 
    // rule 1
    cin >> n1;
    cin >> n2;
    if (n1 == -1 && n2 == -1)
      break;
    if(graph.nodes[n1].from_list == nullptr && graph.nodes[n2].from_list == nullptr)
      graph.nodes[n1].insert_similar(n2);
  }

  for (int i = 1; i<= num; i++)
  {
     // rule 3
    listOfObjects<int> *temp = graph.nodes[i].from_list;
    if(temp == nullptr)
      continue;
    if(temp->next == nullptr)
      graph.nodes[i].insert_similar(temp->object);
  }

  for (int i = 1; i <=num; i++)
  {
    for (int j = 1; j <=i; j++)
    {
      if(graph.check_similar_graph(i, j))
      {
        if(i == j)
          if(!graph.nodes[i].check_similar(i))
            graph.nodes[i].insert_similar(i);
        else
        {
          if(!graph.nodes[i].check_similar(j)) 
            graph.nodes[i].insert_similar(j);
          if(!graph.nodes[j].check_similar(i))
            graph.nodes[j].insert_similar(i);
        }
      }
    }
  }

  ofstream info;
  info.open ("outgraph.txt");
  info << "Source nodes: ";
  for (int i = 1; i <=num; i++)
    if (graph.nodes[i].from_list == nullptr)
      info << i  << " ";

  info << endl;
  info << endl;
  info << "Similar node pairs: ";

  for (int i = 1; i <=num; i++)
    for (int j = 1; j <=num; j++)
      if (graph.nodes[i].check_similar(j))
      {
        if(graph.collapse_max[i] < graph.collapse_max[j])
        {
          int prev_max = graph.collapse_max[i];
          for (int k = 1; k <=num; k++)
            if(graph.collapse_max[k] == prev_max)
              graph.collapse_max[k] = graph.collapse_max[j];
        }
        else if(graph.collapse_max[i] > graph.collapse_max[j])
        {
          int prev_max = graph.collapse_max[j];
          for (int k = 1; k <=num; k++)
            if(graph.collapse_max[k] == prev_max)
              graph.collapse_max[k] = graph.collapse_max[i];
        }
        info << "(" << i << "," << j  << ") ";
      }

  info << endl;
  info << endl;
  int max_elem = 0;

  for(int i=1; i<=num; i++)
    if(graph.collapse_max[i] == i)
      max_elem++;


  bool g[num+1][num+1];
  for(int i=0; i<=num; i++)
    for(int j=0; j<=num; j++)
      g[i][j] = false;

  info << "Collapsed Graph: "<<endl;
  info << max_elem <<": ";
  for(int i=1; i<=num; i++)
    if(graph.collapse_max[i] == i)
      info<<i<<" ";
  info<<endl;

  for(int i = 1; i<=num; i++)
  {
    int grp_rep = graph.collapse_max[i];
    listOfObjects<int> *temp = graph.nodes[i].to_list;
    while(temp != nullptr)
    {
      if(graph.collapse_max[temp->object] == grp_rep)
      {
        temp = temp->next;
        continue;
      }
      else
        g[grp_rep][graph.collapse_max[temp->object]] = true;
      temp = temp->next;
    }

  }
  for(int i = 1; i<=num; i++)
    for(int j=1; j<=num; j++)
      if(g[i][j])
        info<<i<<" "<<j<<endl;

  info.close();
}