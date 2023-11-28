#ifndef GRAPH_BST_CPP
#define GRAPH_BST_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef GRAPH_BST_H
#include "Graph.h"
#endif
BST::BST() { root = NULL; }
BST::BST(TreeNode *root) { this->root = root; }
bool BST::insert(int JourneyCode)
{
  // Adding the first node
  if (root == NULL)
  {
    root = new TreeNode(JourneyCode, NULL, NULL, NULL);
    return true;
  }
  TreeNode *curr = root;
  while (true)
  {
    if (JourneyCode > curr->JourneyCode)
    {
      if (curr->right != NULL)
      {
        curr = curr->right;
      }
      else
      {
        curr->right = new TreeNode(JourneyCode, NULL, NULL, curr);
        break;
      }
    }
    else
    {
      // moving to left if its smaller
      if (curr->left != NULL)
      {
        curr = curr->left;
      }
      else
      {
        curr->left = new TreeNode(JourneyCode, NULL, NULL, curr);
        break;
      }
    }
  }
  return true;
}
void BST::printBST(const string &prefix, bool isLeft = false)
{
  if (root != nullptr)
  {
    cout << prefix;

    cout << (isLeft ? "|--" : "|__");

    // print the value of the node
    cout << '(' << root->JourneyCode << ')' << endl;
    TreeNode *curr = root;
    root = root->left;
    // enter the next tree level - left and right branch
    printBST(prefix + (isLeft ? "│   " : "    "), true);
    root = curr->right;
    printBST(prefix + (isLeft ? "│   " : "    "), false);
    root = curr;
  }
}
// Add code as appropriate for your implementation
void Graph::modifiedDFS()
{
  for (int i = 0; i < numNodes; i++)
  {
    //check if every node is visited or not if not visited atleast once call dfs
    //and add the returned tree into linked list of tree objects
    int *parent = new int[numNodes];
    for (int i = 0; i < numNodes; i++)
    {
      parent[i] = -1;
    }
    if (visited[i] == 0)
    {
      BST *tree = new BST();
      listOfObjects<BST *> *temp =new listOfObjects<BST *>(DFS(i, tree,parent));
      temp->next=alltrees;
      alltrees=temp;
      noc++;
    }
  }
  return;
}

void Graph::printResults()
{
  //printing no of connected components
  cout << "No. of connected components:" << endl;
  cout << noc << endl;
  int count1 = 0;
  int count2 = 0;
  for (int i = 0; i < numNodes; i++)
  {
    if (visited[i] == 1)
    {
      count1++;
    }
    if (visited[i] == 2)
    {
      count2++;
    }
  }
  //printing no of nodes visited once
  cout << "No. of nodes visited once:" << endl;
  cout << count1 << endl;
  //printing no of nodes visited twice
  cout << "No. of nodes visited twice:" << endl;
  cout << count2 << endl;
  //printing no of nodes present in any of the cycle present in the graph
  //the process is done by finding all the bridge edges and removing them from the adjacencylist
  //and checking the degree of every vertex if it is zero then it is an isolated node otherwise it should be present ina cycle
  cout << "No. of nodes that are present in a cycle:" << endl;
  bool *v = new bool[numNodes];
  int *disc = new int[numNodes];
  int *DBE = new int[numNodes];
  int *parent = new int[numNodes];
  for (int i = 0; i < numNodes; i++)
  {
    parent[i] = -1;
    v[i] = false;
  }
  for (int i = 0; i < numNodes; i++)
  {
    if (v[i] == false)
    {
      checkbridge(i, v, disc, DBE, parent);
    }
  }
  for (int i = 0; i < numNodes; i++)
  {
    for (int j = 0; j < numNodes; j++)
    {
      if (bridge[i][j] == 1)
      {
        adjacencylist[i][j] = 0;
      }
    }
  }
  int count3 = 0;
  int i = 0;
  while (i < numNodes)
  {
    int count4 = 0;
    for (int j = 0; j < numNodes; j++)
    {
      if (adjacencylist[i][j] == 1)
        count4++;
    }
    if (count4 > 0)
    {
      count3++;
    }
    i++;
  }
  cout << count3 << endl;
  //printing the trees we showed earlier;
  cout << "TREES" << endl;
  while(alltrees!=nullptr){
    alltrees->object->printBST("");
    alltrees=alltrees->next;
  }
  return;
}

BST *Graph::DFS(int s, BST *tree,int parent[])
{
  //this modified dfs returns the dfs tree from a certain vertex as per the rules given in problem statement
  visited[s]++;
  tree->insert(nodes[s].value);
  for (int i = 0; i < numNodes; i++)
  {
    if (adjacencylist[s][i] == 1)
    {
      if (visited[i] < 2 && parent[s]!=i)
      {
        parent[i]=s;
        DFS(i, tree,parent);
      }
    }
  }
  return tree;
}
void Graph::checkbridge(int u, bool visited[], int disc[], int DBE[], int parent[])
{
  //this functions is used to find weather an edge is bridge edge or not
  //algorithm used is the one discussed in vedio lectures
  //initalize the timer
  //DBE[v]: highest vertex w(i)
  // reachable 0 or more downward edges followed
  // by 0 or 1 up edge and (ii) leading to me or my
  // highest ancestor. (infinity otherwise)
  static int time = 0;
  visited[u] = true;
  disc[u] = time + 1;
  DBE[u] = time + 1;
  time++;
  for (int i = 0; i < numNodes; i++)
  {
    if (adjacencylist[u][i] == 1)
    {
      if (!visited[i])
      {
        parent[i] = u;
        checkbridge(i, visited, disc, DBE, parent);
        DBE[u] = min(DBE[u], DBE[i]);
        if (DBE[i] > disc[u])
        {
          bridge[i][u] = 1;
          bridge[u][i] = 1;
        }
      }
      else if (i != parent[u])
      {
        DBE[u] = min(DBE[u], disc[i]);
      }
    }
  }
}
#endif
