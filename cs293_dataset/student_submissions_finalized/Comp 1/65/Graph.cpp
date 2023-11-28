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
void Graph::loopDFS(Node *n, Node *pn, BST *tree){
    if(n->visit1==0){
      n->visit1++;

    }
    else if(n->visit1==1){
      n->visit2++;
    }

    tree->insert(n->value);
    int nNodes = numNodes;
    for(int i=0;i<nNodes;i++){
      if(n->adjacency[i]>0){
        if((nodes[i].visit1+nodes[i].visit2) < 2){
          n->adjacency[i]=0;
          loopDFS(&nodes[i],n,tree);
        }
      }
    }
}

// Add code as appropriate for your implementation

void Graph::modifiedDFS()
{
    int nNodes = numNodes;
    int p=0;
    for(int i=0;i<nNodes;i++){
      if(checkadjacency(nodes[i].adj,nodes[i].adjacency)){
        if(nodes[i].visit1 + nodes[i].visit2 < 2){
          loopDFS(&nodes[i],nullptr,Treelist[p]);
          p++;
          connected++;
        }
      }
    }
} 

bool Graph::checkadjacency(int *adjacency,int *adj){
  int n1 = sizeof(adjacency);
  int n2 = sizeof(adj);

  if(n1!=n2){
    return false;
  }
  else{
    for(int i=0;i<n1;i++){
      if(adjacency[i]!=adj[i]){
        return false;
      }
    }
  }
  return true;
}

// bool Cycle(Node *node, int val){

//     node->cvisit=1;
//     for(int i=0;i<sizeof(node->adjacency);i++){
//       if(node->adjacency>0){
//         if(!(nodes[i]->cvisit)){
//           Cycle(nodes[i],val)
//         }
//         else{

//         }
//       }
//     }

    

//     return false;
// }


void Graph::printResults() {
  int oncevisit=0;
  int twicevisit=0;
  int cyclic_nodes =0;
  for(int i=0;i<numNodes;i++){
    if(nodes[i].visit2 > 0){
      twicevisit++;
    }
    else if(nodes[i].visit1 >0 && nodes[i].visit2==0){
      oncevisit++;
    }
  }
  cout << "No. of connected components:"<<connected<<endl;
  cout << "No. of nodes visited once:"<<oncevisit<<endl;
  cout << "No. of nodes visited twice:" << twicevisit <<endl;
  cout << "No. of nodes that are present in a cycle:" <<cyclic_nodes<<endl;   
  int i=0;
  while(Treelist[i]->checkroot()){
    Treelist[i]->printBST("");
    i++;
  }
}

bool BST::checkroot(){
    if(this->root==nullptr){
      return false;
    }
    return true;
  
}

void BST::printBST(const string& prefix, bool isLeft)
{
    if( this->root != nullptr )
    {
        cout << prefix;

        cout << (isLeft ? "|--" : "|__" );

        // print the value of the node
        cout << this->root->value << endl;
        TreeNode *curr = this->root;
        this->root = this->root->left;
        // enter the next tree level - left and right branch
        printBST( prefix + (isLeft ? "│   " : "    "), true);
        this->root = curr->right;
        printBST( prefix + (isLeft ? "│   " : "    "), false);
        this->root = curr;
    }
}

#endif
