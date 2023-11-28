#ifndef GRAPH_BST_CPP
#define GRAPH_BST_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef GRAPH_BST_H
#include "Graph.h"
#endif

  //checks that if any cycle possible between nodes
bool Graph::isCycle(int child,int par){
  while(child!=par){
    if(child==-1)return false;
    child=parent[child];
  }
  return true;
}

//inserts a node corresponding to given value
void BST::insert(int val) {
  BSTNode* newNode=new BSTNode(val);

  if(root==nullptr){                      //root null case
    root=new BSTNode(val);
    return;
  }

  //finds position to insert new node
  BSTNode *node=root,*prev=nullptr;
  while(node!=nullptr){
    prev=node;
    if(node->value>val)node=node->left;
    else node=node->right;
  }

  //inserts new node to BST
  if(prev->value>val){
    prev->left=newNode;
    newNode->parent=prev;
  }
  else{
    prev->right=newNode;
    newNode->parent=prev;
  }
}

//Prints complete Binary search tree
void BST::printBST(const string& prefix, bool isLeft){

  if( root != nullptr )                       //base case of root not null
    {
        cout << prefix;                       //prints prefix

        cout << (isLeft ? "|--" : "|__" );

        // print the value of the node
        cout << root->value << endl;

        //prints left subtree
        BSTNode* curr=root;
        root=curr->left;
        printBST(prefix + (isLeft ? "│   " : "    "), true);

        //prints right subtree
        root=curr->right;
        printBST(prefix + (isLeft ? "│   " : "    "), false);
        root=curr;
    }     
}

//Does the modified form of DFS
void Graph::DFS(int v,BST* tree){

  visited[v]++;                                             //marking node as visited
  tree->insert(nodes[v].value);                             //inserting it's value to BST
  list<Node*>* curr=nodes[v].adjecency;                     //accsessing adjecent nodes

  while(curr!=nullptr){                                     //applying DFS logic
    if(visited[curr->object->value-1]<2){
      
      //updating parent if it's part of true DFS
      if(visited[curr->object->value-1]==0){          
        parent[curr->object->value-1]=v;
        DFS(curr->object->value-1,tree);
      }

      //part when node is again visited
      //backtrack or backfro case
      else if(visited[curr->object->value-1]==1 && parent[v]!=curr->object->value-1){
        //if nodes doesn't have parent child relation
        if(parent[curr->object->value-1]!=v){
          int temp;

          //checking for backtrack case
          if(isCycle(v,curr->object->value-1)){
            temp=v;
            //as case is backtrack means they are in cycle
            //updating their cycle status
            while(temp!=curr->object->value-1){
              
              nodes[temp].isInCycle=true;
              temp=parent[temp];
            }
            nodes[temp].isInCycle=true;
          }

          //checking for backtrack case
          else if(isCycle(curr->object->value-1,v)){
            temp=curr->object->value-1;
            //as case is backtrack means they are in cycle
            //updating their cycle status
            while(temp!=v){
              
              nodes[temp].isInCycle=true;
              temp=parent[temp];
            }
            nodes[temp].isInCycle=true;
          }
        }

        //doing reccursive DFS as we can go to same vertex twice
        DFS(curr->object->value-1,tree);
      }
    }

    //case when the node is raised visited third time
    else{
      //checking for backtrack case
      if(parent[curr->object->value-1]!=v && parent[v]!=curr->object->value-1){
        int temp;
        if(isCycle(v,curr->object->value-1)){
          temp=v;
          //as case is backtrack means they are in cycle
          //updating their cycle status
          while(temp!=curr->object->value-1){
            
            nodes[temp].isInCycle=true;
            temp=parent[temp];
          }
          nodes[temp].isInCycle=true;
        }
        //checking for backtrack case
        else if(isCycle(curr->object->value-1,v)){
          temp=curr->object->value-1;
          //as case is backtrack means they are in cycle
          //updating their cycle status
          while(temp!=v){
            
            nodes[temp].isInCycle=true;
            temp=parent[temp];
          }
          nodes[temp].isInCycle=true;
        }
      }

    }
    curr=curr->next;                                  //going to next node of list
  }
}

// Add code as appropriate for your implementation
//calls DFS on all nodes and creates a tree of values for each connected components
void Graph::modifiedDFS() {
  for(int i=0;i<numNodes;i++){                                //iterates over all nodes 
    //calling DFS on non visited nodes
    if(visited[i]==0){
      BST *tree;                                              //tree to store values of graph nodes
      tree=new BST();
      DFS(i,tree);                                            //doing DFS

      if(BSTlist==nullptr)
        BSTlist=new list(*tree);
      else{
        list<BST>* curr=BSTlist;
        while(curr->next!=nullptr)curr=curr->next;
        curr->next=new list(*tree);
      }
    }
  }
  return;
}

//prints result asked to do
void Graph::printResults() {
  int numConnComp=0,num1Vis=0,num2Vis=0,numInCycle=0;
  list<BST>* curr=BSTlist;

  //finding number of connected components
  while(curr!=nullptr){
    numConnComp++;
    curr=curr->next;
  }
  cout<<"No. of connected components: "<<numConnComp<<endl;

  //finding visited number of nodes
  for(int i=0;i<numNodes;i++){
    if(visited[i]==1)num1Vis++;
    if(visited[i]==2)num2Vis++;
  }
  cout<<"No. of nodes visited once: "<<num1Vis<<endl;
  cout<<"No. of nodes visited twice: "<<num2Vis<<endl;

  //finding number of nodes which are in cycle
  if(numEdges==(numNodes*(numNodes-1))/2)numInCycle=numNodes;
  else{
    for(int i=0;i<numNodes;i++){
      if(nodes[i].isInCycle)numInCycle++;
    }
  }
  cout<<"No. of nodes in cycles: "<<numInCycle<<endl;
  
  //printing BST
  curr=BSTlist;
  int n=1;
  while(curr!=nullptr){
    cout<<"\n";
    cout<<"BST "<<n<<" : "<<endl;
    curr->object.printBST("",false);
    n++;
    curr=curr->next;
  }
  
}

#endif
