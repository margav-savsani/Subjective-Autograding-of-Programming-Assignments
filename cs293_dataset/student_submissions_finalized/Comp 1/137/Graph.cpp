#ifndef GRAPH_BST_CPP
#define GRAPH_BST_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef GRAPH_BST_H
#include "Graph.h"
#endif

// using namespace std;

BST::BST(){
  root = new TreeNode();
}

BST::BST(TreeNode *root){
  this->root = new TreeNode(root->value,root->left,root->right,root->parent);
}

bool BST::insert(int value){
  if(root->value == 0)
  {
    root->value = value;
    return true;
  }
  else
  {
    if(root->value >= value)
    {
      if(root->left == nullptr)
      {
        root->left = new TreeNode(value);
        root->left->parent = root;
        return true;
      }
      else
      {
        root = root->left;
        bool ins = insert(value);
        root = root->parent;
        return ins;
      }
    }
    else if(root->value<value)
    {
      if(root->right == nullptr)
      {
        root->right = new TreeNode(value);
        root->right->parent = root;
        return true;
      }
      else
      {
        root = root->right;
        bool ins = insert(value);
        root = root->parent;
        return ins;
      }
    }
  }
}

void BST::printBST(const string& prefix, bool isLeft=false)
{
    if( root != nullptr )
    {
        cout << prefix;

        cout << (isLeft ? "|--" : "|__" );

        // print the value of the node
        cout << root->value << endl;
        TreeNode *curr = root;
        root = root->left;
        // enter the next tree level - left and right branch
        printBST( prefix + (isLeft ? "│   " : "    "), true);
        root = curr->right;
        printBST( prefix + (isLeft ? "│   " : "    "), false);
        root = curr;
    }
}

void Graph::DFS(int index,int index_parent, bool visited_once[], bool visited_twice[]){
  static int reccLevel = -1;
  static BST *Tree = nullptr;   //defining a tree variable  to make  the binary tree
  static bool k = false;    //checks if the function is backtraked directlly from a node
  static int t = -1;
  if(reccLevel == -1)
  {
    Tree = new BST();   //initializing the BST
  }
  if(!visited_once[index])    //checking the condition if the node is visited once
  {
    k = false;    
    visited_once[index] = true;   
    Node node = nodes[index];
    Tree->insert(node.value);   //inserting the value of node in the BST
    listOfObjects<int> *a = node.adj;
    while(a != nullptr)
    {
      bool q = false;   //variable to check if the adjacent node is  the node used to come to the current node.
      listOfObjects<int> *p = node.parent;
      while(p != nullptr)
      {
        if(a->object == p->object)    //checking if the node used to come to the current node is present in the parent nodes
        {
          q = true;
          break;
        }
        p = p->next;
      }
      if(!q)
      {
        if(nodes[a->object].parent == nullptr)    //inserting the current node in the parent list of the adjacent node
        {
          nodes[a->object].parent = new listOfObjects<int>(index);
        }
        else
        {
          listOfObjects<int> *np = nodes[a->object].parent;
          bool present = false;
          if(np->object == index)
          {
            present = true;
          }
          while(np->next != nullptr)
          {
            if(np->next->object == index)
            {
              present = true;
            }
            np = np->next;
          }
          if(!present)
          {
            np->next = new listOfObjects<int>(index);
          }
        }
        reccLevel++; 
        DFS(a->object,index,visited_once,visited_twice);    //reccursively calling DFS
        reccLevel--;
      }
      a = a->next;
    }
  }
  else
  {
    if(!visited_twice[index])   //If visited twice
    {
      k = false;
      visited_twice[index] = true;
      Node node = nodes[index];
      Tree->insert(node.value);   //inserting the value if the BST
      listOfObjects<int> *a = node.adj;   //getting the adjacency list
      int m;
      bool r;
      while(a != nullptr)
      {
        listOfObjects<int> *p = node.parent;
        bool q = false;
        while(p != nullptr)
        {
          if(a->object == p->object)     //checking if the node used to come to the current node is present in the parent nodes
          {
            q = true;
            break;
          }
          p = p->next;
        }
        if(!q)
        {
          if(nodes[a->object].parent == nullptr)    //inserting the current node in the parent list of the adjacent node
          {
            nodes[a->object].parent = new listOfObjects<int>(index);
          }
          else
          {
            listOfObjects<int> *np = nodes[a->object].parent;
            bool present = false;
            if(np->object == index)
            {
              present = true;
            }
            while(np->next != nullptr)
            {
              if(np->next->object == index)
              {
                present = true;
              }
              np = np->next;
            }
            if(!present)
            {
              np->next = new listOfObjects<int>(index);
            }
          }
          reccLevel++;
          DFS(a->object,index,visited_once,visited_twice);    //reccursively calling DFS
          reccLevel--;
          if(k)
          {
            if(visited_twice[index])    //if the current node is visited twice
            {
              m = t;
              r = k;
              if(cycle_node == nullptr)
              {
                cycle_node = new listOfObjects<int>(index);   //adding the node to the cycle node list
              }
              else
              {
                bool is_present = false;
                listOfObjects<int> *c = cycle_node;
                while(c != nullptr)
                {
                  if(c->object == index)
                  {
                    is_present = true;
                  }
                  c = c->next;
                }
                c = cycle_node;
                while(c->next != nullptr)
                {
                  c = c->next;
                }
                if(!is_present)
                {
                  c->next = new listOfObjects<int>(index);
                }
              }
            }
          }
        }
        a = a->next;
      }
      t = m;
      k = r;
    }
    else
    {
      k = true;
      t = index;
      return;
    }
  }
  if(reccLevel == -1)
  {
    if(Trees == nullptr)    //inserting the tree in the BST list
    {
      Trees = new listOfObjects<BST *>(Tree);
    }
    else
    {
      listOfObjects<BST *> *Trees_temp = Trees;
      while(Trees_temp->next != nullptr)
      {
        Trees_temp = Trees_temp->next;
      }
      Trees_temp->next = new listOfObjects<BST *>(Tree);
    }
    return;
  }
}

// Add code as appropriate for your implementation
void Graph::modifiedDFS() {
  listOfObjects<BST *> *Trees_temp = Trees; 
  bool visited_once[numNodes];    //array to store if the nodes are visited once
  bool visited_twice[numNodes];   //array to store if the nodes are visited once
  for(int i = 0; i<numNodes; i++)
  {
    visited_once[i] = false;
    visited_twice[i] = false;
  }
  for(int i = 0; i<numNodes; i++)
  {
    if(!visited_once[i])
    {
      numConnected++;   //incrementing the number of connected components
      DFS(i,-1,visited_once,visited_twice);   //calling DFS
    }
  }
  for(int i = 0; i<numNodes; i++)
  {
    if(visited_twice[i])
    {
      numVisitedTwice++;
    }
    else if(visited_once[i])
    {
      numVisitedOnce++;
    }
  }
  return;
}

void Graph::printResults() {
  cout<<"No. of connected components: "<<numConnected<<endl;
  cout<<"No. of nodes visited once: "<<numVisitedOnce<<endl;
  cout<<"No. of nodes visited twice: "<<numVisitedTwice<<endl;
  listOfObjects<int> *c = cycle_node;
  int numCycleNode = 0;
  while(c != nullptr)
  {
    numCycleNode++;
    cout<<nodes[c->object].value<<" "; 
    c = c->next;
  }
  cout<<endl;
  cout<<"No. of nodes that are present in a cycle: "<<numCycleNode<<endl;
  listOfObjects<BST *> *B = Trees;
  int i = 0;
  while(B != nullptr)
  {
    cout<<"BST "<<i<<": "<<endl;
    B->object->printBST("",false);
    B = B->next;
    i++;
  }
  return;
}

#endif
