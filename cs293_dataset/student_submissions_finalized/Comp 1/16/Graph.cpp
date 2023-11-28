#ifndef GRAPH_BST_CPP
#define GRAPH_BST_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef GRAPH_BST_H
#include "Graph.h"
#endif

// Function  added to assist me in building the stack of DFS
void Graph::myDFS(int parent, int curr, BST &tree)
{
  // Don't visit the node if already visited twice
  if (visited[curr] == 2)
  {
    return;
  }

  // Dont visit the node if there already exists a route from child to parent
  else if (parent != -1 && (nodes[parent].p1 == curr || nodes[parent].p2 == curr))
  {
    return;
  }

  // Insert into BST the current element
  tree.insert(curr + 1);

  // Add into the stack list that stores path of the current search
  // if and else are only to handle the case of initially empty stack list
  if (stk == nullptr)
  {
    stk = new stackss(curr);
  }
  else
  {
    stackss *temp = new stackss(curr);
    temp->prev = stk;
    stk->next = temp;
    stk = temp;
  }

  // Marking as present in some connected component
  conn_comp[curr] = 0;

  // Marking as visited
  visited[curr]++;

  // Marking the number of presence in the stackss
  nodes[curr].in_stack++;

  // Checking if element is in cycle or not
  if (nodes[curr].in_stack == 2)
  {
    // Marks all the element in cycle are true
    stackss *iter = stk->prev;
    cycle[curr] = 1;
    while (iter == nullptr || iter->idx == curr)
    {
      cycle[iter->idx] = 1;
      iter = iter->prev;
    }
  }

  // Setting the parent
  if (nodes[curr].p1 == -1)
  {
    nodes[curr].p1 = parent;
  }
  else
  {
    nodes[curr].p2 = parent;
  }

  // Now lets iterate over adjacent elements of the current node
  adj_node *iter = nodes[curr].adjs;
  while (iter != nullptr)
  {
    myDFS(curr, iter->idx_val, tree);
    iter = iter->next;
  }

  // Removing from the stackss hence reducing the in_stack count
  nodes[curr].in_stack--;
  if (stk->prev == nullptr)
  {
    stk = nullptr;
  }
  else
  {
    stk = stk->prev;
  }
}

// Add code as appropriate for your implementation
void Graph::modifiedDFS()
{
  // Index from which the DFS is to be called from
  int to_start = 0;

  // This loop is to call the function on every connected component
  while (to_start < numNodes)
  {
    if (treesstart == nullptr)
    {
      treesstart = new listofBST();
      treesend = treesstart;
    }
    else
    {
      listofBST *temp = new listofBST();
      treesend->next = temp;
      temp->prev = treesend;
      treesend = temp;
    }
    connected++;
    // Individual connected components would be handled here

    // Updating everything for this connected component
    myDFS(-1, to_start, *treesend->elem);

    // Update to_start as following
    to_start++;
    while (to_start < numNodes)
    {
      if (conn_comp[to_start] == -1)
      {
        break;
      }
      to_start++;
    }
  }
  return;
}

// This function is used to print the results obtained using modified DFS function
void Graph::printResults()
{
  cout << "No. of connected components: " << connected << endl;

  int once = 0, twice = 0, count_cycle = 0;
  // Assimilating the data
  for (int i = 0; i < numNodes; i++)
  {
    if (visited[i] == 1)
    {
      once++;
    }
    else
    {
      twice++;
    }

    if (cycle[i])
    {
      count_cycle++;
    }
  }
  // Printing out the data
  cout << "No. of nodes visited once: " << once << endl;
  cout << "No. of nodes visited twice: " << twice << endl;
  cout << "No. of nodes that are present in a cycle: " << count_cycle << endl;

  // Also need to print the BST
  cout << endl;
  cout << "The trees are as following: " << endl;
  cout << endl;

  int i = 1;
  listofBST *temp = treesstart;
  while (temp != nullptr)
  {
    cout << "BST of connected component : " << i << endl;
    temp->elem->printBST("", false);
    temp = temp->next;
    cout << endl;
    i = i + 1;
  }
  return;
}

#endif
