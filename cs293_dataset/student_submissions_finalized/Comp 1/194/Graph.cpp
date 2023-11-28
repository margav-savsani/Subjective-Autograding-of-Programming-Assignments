#ifndef GRAPH_BST_CPP
#define GRAPH_BST_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef GRAPH_BST_H
#include "Graph.h"
#endif

// Add code as appropriate for your implementation

void Graph::recModDFS(int v, BST *b){
  visited[v]++;
  //BST * b = bst;
  // if(bst->next!=nullptr){
  //   while(b->next!=nullptr){
  //     b = b->next;
  //   }
  //   b->next = new BST();
  //   b = b->next;
  // }
  b->insert(v+1);

  Node * temp = &nodes[v];
  while(temp->next!=nullptr){
    //cout<<temp->next->value<<" jk "<<visited[(temp->next->value)-1]<<parent_node[v]<<endl;
    int rep = temp->next->value;
    if(visited[rep-1]<2 && parent_node[v]!=rep ){
      if(visited[(rep)-1]==0){ 
        parent_node[(rep)-1] = v+1;
      }
      //cout<<temp->value<<endl;
      //b->insert((temp->next->value));
      recModDFS((rep)-1,b);
    }


    if(visited[(temp->value)-1]==2){
      // for(int i=0;i<numNodes;i++){
      //   if(inCycle[i]==true){
      //     cout<<i+1<<"inccyckkjjkkjjjjjjjjjjjj"<<endl;
      
      //   }
      // }
      int prev = parent_node[temp->value-1];
      int V = temp->next->value;
      //cout<<temp->value<<" "<<visited[temp->value-1]<<" "<<parent_node[temp->value-1]<<" klaskklaa\n";
      if(parent_node[temp->value-1]==temp->value){ 
        temp = temp->next;
        continue;
      }
      // Node *u =temp;
      // bool c = false;
      // while(u!=nullptr){
      //   if(u->value==V){
      //     c = true;
      //     break;
      //   }
      //   u = u->next;
      // }
      // if(c!=true){
      //   temp = temp->next;
      //   continue;
      // }
      if(temp->next->next == nullptr){
        temp = temp->next;
        continue;
      }
      inCycle[temp->value-1]=true;
      int y;
      //cout<<"saja"<<" "<<prev<<endl;
      if(prev==0){
        temp = temp->next;
        continue;
      }
      for(int j=0;j<numNodes;j++){
          if(prev==nodes[j].value){
            //cout<<1;
            y = nodes[j].value;
            //cout<<y<<endl;
            break;
          }  
      }
      //cout<<"a"<<endl;
      //while(y->parent->value!=0){
      while(prev!=V){ 
        //cout<<"j\n";
        if(parent_node[y-1]==temp->value){
          break;
        }
        if(parent_node[y-1]==0){
          break;
        }
        //cout<<y<<"jksdjksdj"<<endl;
        inCycle[y-1]=true;
        bool a =false;
        //cout<<y-1<<endl;
        for(int j=0;j<numNodes;j++){
          //cout<<j<<" "<<parent_node[y-1]<<" "<<nodes[j].value;
          // for(long long int i=0;i<99999999;i++){
          //   ;
          // }
          //bool a =false;
          if(parent_node[y-1]==nodes[j].value){
            y = nodes[j].value;
            prev = y;
            //cout<<prev<<"sjk";
            a=true;
            break;
          }
        }
        if(a==true){
          //cout<<"uwieiwe"<<endl;
          break;
        }
      }
      //cout<<"1q"<<endl;
    }
    //cout<<"jask"<<endl;
    temp = temp->next;
  }
}

void Graph::modifiedDFS()
{
  //int dfs_stack[2*numNodes];
  //int *visited = new int[numNodes];
  //int end = 0;
  for(int i=0;i<numNodes;i++){
    visited[i]=0;
  }
  BST * b = bst;
  for(int i=0; i<numNodes; i++){
    if(visited[i]==0){
      recModDFS(i,b);
      cnt++;
      b->next = new BST();
      b = b->next;
    }
  }

  return;
}

void Graph::printResults()
{
  cout<<"No. of connected components: "<<cnt<<endl;
  int once = 0;
  int twice = 0;
  for(int i=0;i<numNodes;i++){
    if(visited[i]==1){
      //cout<<i+1<<" once"<<endl;
      once++;
    }
    else if(visited[i]==2){
      twice++;
      //cout<<i+1<<" twice"<<endl;
    }
  }
  cout<<"No. of nodes visited once: "<<once<<endl;
  cout<<"No. of nodes visited twice: "<<twice<<endl;
  //cout<<inCycle<<endl;
  // for(int i=0;i<numNodes;i++){
  //   cout<< parent_node[i]<<"asjk"<<endl;
  // }
  int in=0;
  for(int i=0;i<numNodes;i++){
    if(inCycle[i]==true){
      //cout<<i+1<<"inccyck"<<endl;
      in++;
    }
  }
  cout<<"No. of nodes that are present in a cycle: "<<in<<endl;
  BST * t = bst;
  while(t->next!=nullptr){
    t->printBST("",false);
    t=t->next;
  }
  return;
}

void BST::insert(int val)
{
  if (root == nullptr)
  {
    root = new Node(val);
    return;
  }

  else
  {
    Node *node = root;
    while (true)
    {
      // if (node->value == val && node->times > 1)
      // {
      //     return false;
      // }
      if (node->value <= val)
      {
        if (node->right == nullptr)
        {
          node->right = new Node(val, nullptr, nullptr, node);
          return;
        }
        else
        {
          node = node->right;
          continue;
        }
      }
      else
      {
        if (node->left == nullptr)
        {
          node->left = new Node(val, nullptr, nullptr, node);
          return;
        }
        else
        {
          node = node->left;
          continue;
        }
      }
    }
  }
}

void BST::printBST(const string &prefix, bool isLeft = false)
{
    if (root != nullptr)
    {
        cout << prefix;

        cout << (isLeft ? "|--" : "|__");

        // print the value of the node
        cout << root->value << endl;
        Node *curr = root;
        root = root->left;
        // enter the next tree level - left and right branch
        printBST(prefix + (isLeft ? "│   " : "    "), true);
        root = curr->right;
        printBST(prefix + (isLeft ? "│   " : "    "), false);
        root = curr;
    }
}

#endif

  // cout<<v+1<<"s\n";
  // for(int i=0;i<numNodes;i++){
  //   cout<<parent_node[i]<<" ";
  // }
  // cout<<" parent"<<"\n";
  // for(int i=0;i<numNodes;i++){
  //   cout<<visited[i]<<" ";
  // }
  // cout<<"visited\n";