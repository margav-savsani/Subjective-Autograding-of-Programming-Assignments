#ifndef GRAPH_BST_CPP
#define GRAPH_BST_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef GRAPH_BST_H
#include "Graph.h"
#endif

// Add code as appropriate for your implementation
void Graph::DFS(Node node, int value)
{
  if (value == -1)
  {
    // cout<<"call at root node"<<endl;
    int ind = node.value - 1;
    if (visited[ind] == 2)
    {
      // cout<<"visited twice index: "<<ind<<endl;
      return;
    }
    else
    {
      // cout<<"not visited twice index: "<<ind<<endl;
      visited[ind]++;

      if (stack == nullptr)
      {
        stack = new listOfObjects(node.value);
        //cout<<"inserted into stack: "<<node.value<<endl;
      }

      if (tree == nullptr)
      {
        TreeNode *curr_node = new TreeNode(node.value);
        tree = new BST(curr_node);
      }
      else
      {
        tree->insert(node.value);
      }

      listOfObjects<Node> *list = node.adjacency;
      while (list != nullptr)
      {
        DFS(list->object, node.value);
        list = list->next;
      }


      { // deleting number from the stack when backtracking i.e returning
        if (stack->next == nullptr)
        {
          stack = nullptr;
        }
        else
        {
          listOfObjects<int> *last = stack;
          while (last->next->next != nullptr) // we are going till last element
          {
            last = last->next;
          }
          last->next = nullptr;
        }
      }
      //cout<<(stack==nullptr)<<endl;


      tree->print();
      cout << "***************" << endl;
      tree = nullptr;
      return;
    }
  }
  else
  {
    // cout<<"call at child node"<<endl;
    int ind = node.value - 1;
    if (visited[ind] == 2)
    {
      // cout<<"visited twice index: "<<ind<<endl;
      return;
    }
    else
    { 
      //cout<<"hi"<<endl;
      // cout<<"not visited twice index: "<<ind<<endl;
      visited[ind]++;


      { 
        //cout<<"hi1"<<endl;
        listOfObjects<int> *last = stack;
        //cout<<last->object<<endl;;
        while (last->next != nullptr)
        {
          last = last->next;
        }
        last->next = new listOfObjects(node.value);
        //cout<<"inserted into stack: "<<node.value<<endl;
        last = stack;
        listOfObjects<int> *repeat = nullptr;
        while (last->next->next != nullptr)
        { 
          //cout<<"elements in stack: "<<last->object<<endl;
          if (last->object == node.value)
          { 
            //cout<<"hello"<<endl;
            repeat = last;
            //cout<<repeat->object<<endl;
            break;
          }
          last=last->next;
        }
        //cout<<"hi"<<endl;
        //cout<<(repeat==nullptr)<<endl;
        if (repeat != nullptr) // cycle found
        { 
          //cout<<"hello"<<endl;
          while (repeat->next->object!= node.value)
          { 
            cout<<"hmm"<<endl;
            node_cycle++;
            repeat=repeat->next;
          }
        }
        //cout<<"hi2"<<endl;
      }


      tree->insert(node.value);
      listOfObjects<Node> *list = node.adjacency;
      while (list != nullptr)
      {
        if (list->object.value != value) // should not reach again to the parent node
        {
          DFS(list->object, node.value);
        }
        list = list->next;
      }
      { // deleting number from the stack when backtracking i.e returning
      //cout<<"hi1"<<endl;
        if(stack==nullptr)
         return;
        else if (stack->next == nullptr)
        { 
          //cout<<"if"<<endl;
          stack = nullptr;
        }
        else
        { 
          //cout<<"else1"<<endl;
          listOfObjects<int> *last = stack;
          while (last->next->next != nullptr) // we are going till last element
          {
            last = last->next;
          }
          //delete last->next;
          last->next = nullptr;
          //cout<<"else2"<<endl;
        }
        //cout<<"hi2"<<endl;
      }
      return;
    }
  }
  // cout<<"hi2"<<endl;
  // return;
}

void Graph::modifiedDFS()
{
  while (true)
  {
    // cout<<"hi1"<<endl;
    bool all_visit = true;
    int ind_node;
    for (int i = 0; i < numNodes; i++)
    {
      if (visited[i] == 0)
      {
        all_visit = false;
        ind_node = i;
        // cout<<"not visited index: "<<i<<endl;
        ind_com++; // every time we get a non visited node after every DFS we get a independent component.
        break;
      }
    }
    if (all_visit == true)
    {
      // cout<<"all visited"<<endl;
      break;
    }
    else
    {
      DFS(nodes[ind_node], -1);
    }
  }
  return;
}

void Graph::printResults()
{
  cout << "number of independent components: " << ind_com << endl;
  int once_count = 0;
  for (int i = 0; i < numNodes; i++)
  {
    if (visited[i] == 1)
      once_count++;
  }
  int twice_count = 0;
  for (int i = 0; i < numNodes; i++)
  {
    if (visited[i] == 2)
    {
      twice_count++;
    }
  }
  cout << "number of vertices visited once: " << once_count << endl;
  cout << "number of vertices visited twice: " << twice_count << endl;
  cout << "number of nodes in a cycle: " << node_cycle << endl;
  // tree->print();
  for (int i = 0; i < numNodes; i++) // printing the
  {
    if (i == numNodes - 1)
      cout << visited[i] << endl;
    else
      cout << visited[i] << " ";
  }
  return;
}

#endif
