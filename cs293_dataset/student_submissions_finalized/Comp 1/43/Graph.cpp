#ifndef GRAPH_BST_CPP
#define GRAPH_BST_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef GRAPH_BST_H
#include "Graph.h"
#endif
//This is the print BST function modified
void printBST(const string& prefix, bool isLeft,TreeNode * r)
{
    if( r != nullptr )
    {
        cout << prefix;

        cout << (isLeft ? "|--" : "|__" );

        // print the value of the node
        cout << r->index << endl;
        // enter the next tree level - left and right branch
        //Recurive call for left branch
        printBST( prefix + (isLeft ? "│   " : "    "), true,r->left);
        //Recursive call for right branch
        printBST( prefix + (isLeft ? "│   " : "    "), false,r->right);
    }
}

//This is the insert function to be implemented
void BST::insert(int value){
  TreeNode *r1 = root;
  //Inserting the root
  if(r1->index == 0){
    r1->index = value;
    return;
  }
  TreeNode* q;
  int s = 0;
  //Going iteratively
  while(r1 != nullptr){
    q = r1;
    if(value > r1->index){
      r1 = r1->right;
      s = 0;
    }
    else{
      r1 = r1->left;
      s = 1;
    }
  }
  //Whether to add left or right
  if(s == 1){
    TreeNode *pi = new TreeNode(value);
    q->left = pi;
    pi->parent = q;
    return;
  }
  else if(s == 0){
    TreeNode *pi = new TreeNode(value);
    q->right = pi;
    pi->parent = q;
    return;
  }
}
// Add code as appropriate for your implementation
//The DFS function which is implemented
void Graph::DFS(int n,BST *r){
    list<int> * adj = adjacent[n];
    //Inserting inside the tree
    r->insert(nodes[n].value);
    //Increasing time by 1
    times[n] = times[n]+1;
    //The adjacency list going iteratively
    while(adj != nullptr){
      if(adj->object == -1){
        adj = adj->next;
        continue;
      }
      int p = adj->object;
      if(times[p] < 2){
        //Deleting the edge so it becomes directed
        adjacent[p]->del(n);
        DFS(p,r);
        //Deleteing the edge when it backtraces
        adjacent[n]->del(p);       
      }
      adj = adj->next;
    }
}
void Graph::modifiedDFS() {
  //To do DFS for the connected components
  for (int i = 0;i< numNodes;i++){
    if(times[i] == 0){
      BST *r = new BST();
      DFS(i,r);
      //Adding the tree to the end of the list
      list<BST *> *q = results;
      while(q->next != nullptr){
        q = q->next;
      }
      q->next = new list<BST *>(r);
    }
  }
}

//This function prints all the results
void Graph::printResults() {
  results = results->next;
  int k = 0;
  //Printing all trees
  while(results != nullptr){
    printBST("",false,results->object->getroot());
    cout<<""<<endl;
    results = results->next;
    k++;
  }
  cout<<"No. of connected components: "<<k<<endl;
  //Calculating how many times the node is visited
  int s2 = 0,s3 = 0,s4 = 0;
  for(int i = 0;i < numNodes;i++){
      if(times[i] == 1){
        s2++;
      }
      if(times[i] == 2){
        s3++;s4++;
      }
  }
  //Printing the results
  cout<<"No. of nodes visited once: "<<s2<<endl;
  cout<<"No. of nodes visited twice: "<<s3<<endl;
  cout<<"No. of nodes that are present in a cycle: "<<s4<<endl;
}

#endif
