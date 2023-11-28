#ifndef GRAPH_BST_CPP
#define GRAPH_BST_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef GRAPH_BST_H
#include "Graph.h"
#endif
int Graph::lca(int x1, int x2){
  int y = predecessor[x1];
  int z = predecessor[x2];
  int temp = y;
  int temp2 = z;
  
  while(temp != -1){
    while(temp2 != -1){
      if(temp == temp2){
        return temp;
      }
      temp2 = predecessor[temp2];
    }
    temp2 = z;
    temp = predecessor[temp];
  }
 }
bool Graph::check_ancestor(int x1, int x2)
{
  int y = predecessor[x2];
  while (y != -1)
  {
    if (y == x1)
    {
      return true;
    }
    y = predecessor[y];
  }
  return false;
}
void Graph::myDFS(Node node, BST *tree)
{
  listOfObjects<int> *x = node.adjacenthead;
  tree->insert(node.value);
  if (visited[node.value - 1] == 0)
  {
    time_arr[node.value - 1] = time1++;
  }

  visited[node.value - 1] = visited[node.value - 1] + 1;

  while (x != nullptr)
  {
    if (visited[x->object] == 0)
    {
      predecessor[x->object] = (node.value - 1);
      myDFS((nodes[x->object]), tree);
    }
    else if (visited[x->object] == 1 && predecessor[node.value - 1] != x->object)
    {
      if (time_arr[x->object] < time_arr[node.value - 1])
      {
        int x1 = node.value - 1;
        if (check_ancestor(x->object, x1))
        {
          while (x1 != x->object)
          {
            // if (x1 == 0)
            // {
            //   // check_wrong = true;
            //   break;
            // }
            incycle[x1] = true;
            x1 = predecessor[x1];
          }
          // if()
          incycle[x1] = true;
        }


      
    }
    myDFS(nodes[x->object], tree);
    }
    else if (visited[x->object] > 1)
    {
      if (predecessor[node.value - 1] != x->object && time_arr[node.value - 1] > time_arr[x->object])
      {
        int x1 = node.value - 1;
        // bool check_wrong = false;
        if (check_ancestor(x->object, x1))
        {
          while (x1 != x->object)
          {
            // if (x1 == 0)
            // {
            //   // check_wrong = true;
            //   break;
            // }
            incycle[x1] = true;
            x1 = predecessor[x1];
          }
          // if()
          incycle[x1] = true;
        }
        else{
          int z = lca(x->object , x1);
          int x2 = x->object;
          while(x1 != z){
            incycle[x1] = true;
            x1 = predecessor[x1];

          }
          while(x2!=z){
            incycle[x2] = true;
            x2 = predecessor[x2];

          }
          incycle[z] = true;
          
        }
      }
    }

    x = x->next;
  }
}

void Graph::modifiedDFS()
{
  Node *y = nodes;
  int i = 0;

  while (i < numNodes)
  {
    if (visited[i] == 0)
    {
      if (head == nullptr)
      {
        head = new BST();
        tail = head;
        myDFS(nodes[i], tail);
        ans1++;
      }
      else
      {
        tail->next = new BST();
        tail = tail->next;
        myDFS(nodes[i], tail);
        ans1++;
      }
    }
    i++;
  }

  return;
}

void Graph::printResults()
{
  cout << "No. of connected components: " << ans1 << endl;
  int y = 0;
  int z = 0;
  int t = 0;
  for (int i = 0; i < numNodes; i++)
  {
    if (incycle[i] == true)
    {
      // cout<<i<<endl;
      y++;
    }
    if (visited[i] == 2)
    {
      z++;
    }
    if (visited[i] == 1)
    {
      t++;
    }

    listOfObjects<int> *x = nodes[i].adjacenthead;
  }
  cout << "No. of nodes visited once: " << t << endl;
  cout << "No. of nodes visited twice: " << z << endl;
  cout << "No. of nodes that are present in a cycle: " << y << endl;
  BST *x = head;
  int c = 1;
  while (x != nullptr)
  {
    cout << "Component " << c << ":-" << endl;
    x->printBST("");
    x = x->next;
    cout << "**********" << endl;
    c++;
  }

  return;
}

#endif
