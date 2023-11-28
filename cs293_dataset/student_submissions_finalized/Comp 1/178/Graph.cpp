#ifndef GRAPH_BST_CPP
#define GRAPH_BST_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef GRAPH_BST_H
#include "Graph.h"
#endif
using namespace std;
// Add code as appropriate for your implementation
void Graph::Cycle(int vertex,int prev_vertex){
 
  if (color[vertex] == 2) {
        return;
    }
  if(color[vertex] == 1){
    int cur = prev_vertex;
    present[vertex] = 1;
  while(cur != vertex){
    present[cur] = 1;
    cur = par[cur];
    
   
  }
   return ;}
  par[vertex] = prev_vertex;
  color[vertex] = 1;
  for ( int i = 0 ; i<numNodes;i++){
      if(adj[vertex][i]==1&& i != prev_vertex){
        Cycle(i, vertex);}}
        color[vertex] = 2;

}


void Graph::DFS(int vertex,int prev_vertex){
  

  if(nodes[vertex].visited !=2){
    nodes[vertex].visited++;
    tail->tree->insert(nodes[vertex].value);

    for ( int i = 0 ; i<numNodes;i++){
      if(adj[vertex][i]==1&& i != prev_vertex && par[vertex] != i){
         Cycle(i,vertex);
        DFS(i,vertex);
       
      }

    
    }
  }

  return;
}
void Graph::modifiedDFS() {

//cout<<no_connected<<endl; 
for ( int i=0;i<numNodes;i++){
  if (nodes[i].visited == 0){
  no_connected++;
  if(head == NULL){
    head = new TREE() ;
    tail = head;
  }
  else{
    TREE *newtail = new TREE();
    tail->next = newtail;
    tail= newtail;
  }
  
  DFS(nodes[i].value - 1 , nodes[i].value - 1);

  }
}

  return;
}

void Graph::printResults() {
  cout<<"No. of connected components: ";
  cout<<no_connected<<endl;

  int visited2=0;
  
  
  for(int i=0;i<numNodes;i++){

    if(nodes[i].visited==2){
      
      visited2 ++;
    }}
    cout<<"No. of nodes visited once: ";
    cout<<(numNodes-visited2)<<endl;
    cout<<"No. of nodes visited twice: ";
    cout<<visited2 << endl;
    int no_nodes = 0;
  for (int i=0;i<numNodes;i++){
    if(present[i] == 1){
      no_nodes++;
    }
  }
  cout<<"No. of nodes in a cycle: ";
    cout<<no_nodes << endl;
  

  TREE *Tree = head;
  while(Tree!=NULL){
    Tree->tree->printBST("");
    Tree = Tree->next;
  }

  return;
}

BST::BST(){
 root=NULL;}
BST::BST(TreeNode *root){
    this->root=root; 
}

void BST::insert(int data) {
TreeNode *z = new TreeNode(data);
if(root == NULL){
  root = z;
  return;
}
TreeNode *y=NULL;
TreeNode *t =root;
while(t!=NULL){
  if(t->data >= data){
    y=t;
    t=t->left;
  }
  else if (t->data < data){
  y=t;
  t=t->right;
  }
}
if(y->data>=data) y->left = new TreeNode(data);
else y->right = new TreeNode(data);
return ;
}

void BST::printBST(const string& prefix, bool isLeft)   
{
    if( root != nullptr )
    {
        cout << prefix;

        cout << (isLeft ? "|--" : "|__" );

        // print the value of the node
        cout << root->data << endl;
        TreeNode *curr = root;
        root = root->left;
        // enter the next tree level - left and right branch
        printBST( prefix + (isLeft ? "│   " : "    "), true);
        root = curr->right;
        printBST( prefix + (isLeft ? "│   " : "    "), false);
        root = curr;
    }
}
#endif
