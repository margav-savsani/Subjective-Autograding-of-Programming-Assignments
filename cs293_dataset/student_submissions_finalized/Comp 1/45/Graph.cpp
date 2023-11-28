#ifndef GRAPH_BST_CPP
#define GRAPH_BST_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef GRAPH_BST_H
#include "Graph.h"
#endif


BST::BST(){
  root = NULL;  
}
BST::BST(TreeNode *root){
  this->root=root; 
}

void BST::insert(int value) {
  if(root == NULL){
    root = new TreeNode(value,nullptr,nullptr,nullptr);
  }
  TreeNode *curr = root;
    while(true){
        // curr->sizeOfTree++; // incrementing Size of subtree which is rooted at this node

        // Moving to the right, if price is greater
        if(value > curr->value){
            if(curr->right!=NULL){
                curr = curr->right;
            }else{
                curr->right = new TreeNode(value,NULL,NULL,curr);
                break;
                
            }
        }else{
            // moving to left if its smaller
            if(curr->left!=NULL){
                curr = curr->left;
            }else{
                curr->left = new TreeNode(value,NULL,NULL,curr);
                break;
                
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
        cout << '('<< root->value<<')' << endl;
        TreeNode *curr = root;
        root = root->left;
        // enter the next tree level - left and right branch
        printBST( prefix + (isLeft ? "│   " : "    "), true);
        root = curr->right;
        printBST( prefix + (isLeft ? "│   " : "    "), false);
        root = curr;
    }
}

void Graph::DFS(Node n,Node p,BST* b){

  nodes[n.value-1].visited_count++;
  
  b->insert(n.value);
  // cout<<"val = "<<n.value <<endl;
  listOfObjects<Node>* tmp = n.adj;
  
  while(tmp!=nullptr){
    // cout <<"kkk"<<endl;
    int adjval = tmp->object.value;

    if(adjval!=p.value){
      // cout <<"hi = "<< adjval<<endl;
      if(nodes[adjval-1].visited_count<2){
        DFS(nodes[adjval-1],n,b);
      }
    }

    tmp=tmp->prev;
  }
  // return b;
}

// Add code as appropriate for your implementation
void Graph::modifiedDFS() {
  // for(int i=0;i<numNodes;i++){
  //   cout<<nodes[i].visited_count<<endl;
  // }

  // cout<<"-------"<<endl;

  for(int i=0;i<numNodes;i++){
    if(nodes[i].visited_count==0){

      connected_comps++;

      BST* b = new BST();
      DFS(nodes[i],Node(0),b);
      if(bstlist==nullptr){
        bstlist = new listOfObjects<BST*> (b);
      }
      else {
        bstlist->next = new listOfObjects<BST*> (b);
        bstlist->next->prev = bstlist;
        bstlist = bstlist->next;
      }
    }
  }
  // cout<<numNodes<<endl;
  // for(int i=0;i<numNodes;i++){
  //   cout<<nodes[i].visited_count<<endl;
  // }
  return;
}

void Graph::printResults() {
  int visited_once=0;
  int visited_twice=0;

  for(int i=0;i<numNodes;i++){
    if(nodes[i].visited_count==1){
      visited_once++;
    }
    else if(nodes[i].visited_count==2){
      visited_twice++;
    }
  }

  cout<<"No. of connected components:"<<connected_comps<<endl;
  cout<<"No. of nodes visited once:"<<visited_once<<endl;
  cout<<"No. of nodes visited twice:"<<visited_twice<<endl;
  cout<<"No. of nodes that are present in a cycle:"<<0<<endl;
  listOfObjects<BST*>*tmp=bstlist;
  // if(tmp==nullptr){ cout<<"Hi5"<<endl;}
  while(tmp!=nullptr){
    //  cout<<"Hi4"<<endl;
    tmp->object->printBST("");
    tmp=tmp->prev;
  }

  return;
}

#endif
