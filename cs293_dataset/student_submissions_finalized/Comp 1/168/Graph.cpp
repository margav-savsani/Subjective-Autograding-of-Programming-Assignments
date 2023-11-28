#ifndef GRAPH_BST_CPP
#define GRAPH_BST_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef GRAPH_BST_H
#include "Graph.h"
#endif

// Add code as appropriate for your implementation
void Graph::modifiedDFS() { 
  for(int i=0;i<numNodes;i++){
    if(nodes[i].numOfVisits==0){    //carries out the DFS for each new component
      tree=new BST();   //creates a BST
      nodes[i].prevNode=nullptr;
      modifiedDFSfromNode(i);   
      tree->printBST("",false);     //printing the BST for each component
      cout<<endl<<endl;
      numComponents++;    //increasing the number of components
    }
  }
}

void Graph::modifiedDFSfromNode(int n){
  // checking if the entered node is already in the path (implies a cycle)
  auto tempPath=path;
  listOfObjects<int>* tempNode=nullptr;
  if(tempPath){
    if(tempPath->object==n){
      tempNode=tempPath;
    }
    while(tempPath->next){
      tempPath=tempPath->next;
      if(tempPath->object==n){
        tempNode=tempPath;
      }
    }
    if(tempNode){
      while(tempNode->next){
        isCycle[tempNode->object]=true;     //indicating that the corresponding nodes belong to a cycle
        tempNode=tempNode->next;
      }
      isCycle[tempNode->object]=true;
    }
  }
  // Adding the entered node to the path.
  // cout<<n+1<<endl;
  if(path){
    // cout<<"a"<<endl;
    auto temp = path;
    while(temp->next){
      // cout<<temp->object+1<<" ";
      temp=temp->next;
    }
    // cout<<temp->object+1<<" ";
    temp->next=new listOfObjects<int>(n);
    // cout<<temp->next->object+1<<endl;
    temp->next->prev=temp;
  }
  else{
    path=new listOfObjects<int>(n);
    // cout<<path->object<<endl;
  }
  nodes[n].numOfVisits++;
  tree->insert(n+1);
  listOfObjects<int>* temp=nodes[n].adjacencyList;
  while(temp){    //temp represents each node in the adjacency list of the node
    bool notParent=true;
    auto tempo = nodes[n].prevNode;
    while(tempo){     //checks if the temp node is a parent of the node we are currently at
      if(temp->object == tempo->object){
        notParent=false;
        break;
      }
      tempo=tempo->next;
    }

    if(nodes[temp->object].numOfVisits<2 && notParent){
      // cout<<temp->object+1<<" "<<nodes[temp->object].numOfVisits<<endl;
      //Updating the information on parent nodes (prevNode) of each visited node.
      if(nodes[temp->object].prevNode){
        auto tempo = nodes[temp->object].prevNode;
        while(tempo->next){
          tempo=tempo->next;
        }
        tempo->next=new listOfObjects<int>(n);
        tempo->next->prev=tempo;
      }
      else{
        nodes[temp->object].prevNode=new listOfObjects<int>(n);
      }
      // cout<<"Entering "<<temp->object+1<<endl;
      modifiedDFSfromNode(temp->object);    //calls the modified DFS for the new node recursively

      //deleting the node from the path now that we are done processing it
      auto temp1=path;
      while(temp1->next){
        temp1=temp1->next;
      }
      // cout<<temp->object+1<<"Deleting"<<temp1->object+1<<endl;
      temp1=temp1->prev;
      temp1->next=nullptr;
      //stop
    }
    //moving to the next node in the adjacency list
    temp=temp->next;
  }
}

void Graph::printResults() {
  int numOnce=0;
  int numTwice=0;
  int numCycle=0;

  for(int i=0;i<numNodes;i++){
    if(nodes[i].numOfVisits==1){
      numOnce++;    //finding the number of nodes which have only been visited once
    }
    else if(nodes[i].numOfVisits==2){
      numTwice++;   //finding the number of nodes which have been visited twice.
    }
    if(isCycle[i]){
      numCycle++;    //finding the number of nodes in a cycle.
    }
  }

  //printing the information
  cout<<"Number of Connected Components: "<<numComponents<<endl;
  cout<<"Number of nodes visited once: "<<numOnce<<endl;
  cout<<"Number of nodes visited twice: "<<numTwice<<endl;
  cout<<"Number of nodes present in a cycle: "<<numCycle<<endl;
}

bool BST::insert(int value){
    TreeNode nodeInsert(value);

    if(!root){
        root=new TreeNode(nodeInsert);
        root->parent=nullptr;
        return true;
    }

    TreeNode* parentIns=nullptr;
    TreeNode* temp=root;

    while(temp){
        parentIns=temp;
        if(nodeInsert.value>=temp->value){
            temp=temp->right;
        }
        else{
            temp=temp->left;
        }
    }

    if (parentIns->value>nodeInsert.value){
        nodeInsert.parent=parentIns;
        parentIns->left=new TreeNode(nodeInsert);
    }
    else{
        nodeInsert.parent=parentIns;
        parentIns->right=new TreeNode(nodeInsert);
    }
    return true;
}

void BST::printBST(const string& prefix, bool isLeft)
{
  if( root != nullptr )   {
    cout << prefix;
    
    cout << (isLeft ? "|--" : "|__" );
    
    // print the value of the node
    cout<<root->value;
    cout << endl;
    TreeNode *curr = root;
    root = root->left;
    // enter the next tree level - left and right branch
    printBST(prefix + (isLeft ? "│   " : "    "), true);
    root = curr->right;
    printBST(prefix + (isLeft ? "│   " : "    "), false);
    root = curr;
  }
}

#endif
