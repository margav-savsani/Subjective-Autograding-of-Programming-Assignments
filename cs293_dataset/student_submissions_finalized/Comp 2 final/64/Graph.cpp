#include "std_headers.h"
#include "graph.h"

//make directed edge between two nodes
void Graph::makeDirectedEdge(int val1, int val2){
  Node* node1 = &nodes[val1-1];
  Node* node2 = &nodes[val2-1];
  if(node1->childAdjacency==nullptr){
    node1->childAdjacency = new listOfObjects<Node*>(node2);
  }else{
    listOfObjects<Node*>* a = node1->childAdjacency;
    while(a->next!=nullptr){
      a=a->next;
    }
    a->next = new listOfObjects<Node*>(node2);
  }
  if(node2->parentAdjacency==nullptr){
    node2->parentAdjacency = new listOfObjects<Node*>(node1);
  }else{
    listOfObjects<Node*>* b = node2->parentAdjacency;
    while(b->next!=nullptr){
      b=b->next;
    }
    b->next = new listOfObjects<Node*>(node1);
  }
  return;
}

void Graph::printChildAdjacencyList(){
  cout<<"CHILD ADJACENCY LIST"<<endl;
  for(int i=0; i<numNodes; i++){
    cout<<i+1<<"==";
    listOfObjects<Node*>* a = nodes[i].childAdjacency;
    while(a!=nullptr){
      cout<<a->object->value<<" ";
      a=a->next;
    }cout<<endl;
  }
}

void Graph::printParentAdjacencyList(){
  cout<<"PARENT ADJACENCY LIST"<<endl;
  for(int i=0; i<numNodes; i++){
    cout<<i+1<<"==";
    listOfObjects<Node*>* a = nodes[i].parentAdjacency;
    while(a!=nullptr){
      cout<<a->object->value<<" ";
      a=a->next;
    }cout<<endl;
  }
}

void Graph::printSimilarList(){
  cout<<"SIMILAR LIST"<<endl;
  for(int i=0; i<numNodes; i++){
    cout<<i+1<<"==";
    listOfObjects<Node*>* a = nodes[i].similar;
    while(a!=nullptr){
      cout<<a->object->value<<" ";
      a=a->next;
    }cout<<endl;
  }
}

void Graph::printSimilar1List(){
  cout<<"SIMILAR LIST"<<endl;
  for(int i=0; i<numNodes; i++){
    cout<<i+1<<"==";
    listOfObjects<Node*>* a = nodes[i].similar1;
    while(a!=nullptr){
      cout<<a->object->value<<" ";
      a=a->next;
    }cout<<endl;
  }
}

//function to find similar nodes according to rule3
void Graph::similarRule3(){
  for(int i=0; i<numNodes; i++){
    listOfObjects<Node*>* parent = nodes[i].parentAdjacency;
    if(parent!=nullptr && parent->next == nullptr){
      if(nodes[i].similar==nullptr){
        nodes[i].similar =  new listOfObjects<Node*>(parent->object);
      }else{
        listOfObjects<Node*>* a = nodes[i].similar;
        while(a->next!=nullptr){
          a=a->next;
        }
        a->next = new listOfObjects<Node*>(parent->object);
      }
    }
  }
}

//function to find similar nodes
bool Graph::isSimilar(int val1, int val2){
  Node* node1 = &nodes[val1-1];
  listOfObjects<Node*>* a = node1->similar;
  if(a==nullptr){
    return false;
  }else{
    while(a!=nullptr){
      if(a->object->value == val2){
        return true;
      }
      a=a->next;
    }
    return false;
  }
}

//calculate length of a linked list
int calLen(listOfObjects<Node*>* abc){
  if(abc==nullptr){
    return 0;
  }else{
    listOfObjects<Node*>* a = abc;
    int count=0;
    while(a!=nullptr){
      a=a->next;
      count++;
    }
    return count;
  }
}

//condition used to find if two nodes are similar
bool Graph::condition(Node* node1, Node* node2){
  listOfObjects<Node*>* parent1 = node1->parentAdjacency;
  while(parent1!=nullptr){
    bool found = false;
    listOfObjects<Node*>* parent2 = node2->parentAdjacency;
    while(parent2!=nullptr){
      if(isSimilar(parent1->object->value, parent2->object->value)){
        found = true;
        break;
      }
      parent2=parent2->next;
    }
    if(!found){
      return false;
    }
    parent1=parent1->next;
  }
  return true;
}

//function to find similar nodes according to rule 2 of the question
void Graph::similarRule2a(){
  listOfObjects<Node*>* srcList1 = sourceNodes;
  while(srcList1!=nullptr){
    // cout<<srcList1->object->value<<"sourcelist1"<<endl;
    listOfObjects<Node*>* srcList2 = sourceNodes;
    while(srcList2!=nullptr){
      // cout<<srcList1->object->value<<",,,"<<srcList2->object->value<<endl;
      listOfObjects<Node*>* child1 = srcList1->object->childAdjacency;
      listOfObjects<Node*>* child2 = srcList2->object->childAdjacency;
      while(child1!=nullptr){
        while(child2!=nullptr){
          if(condition(child1->object, child2->object) && condition(child2->object, child1->object)){
            if(child1->object->similar==nullptr){
              child1->object->similar = new listOfObjects<Node*>(child2->object);
            }else{
              bool found = false;
              listOfObjects<Node*>* abc = child1->object->similar;
              while(abc!=nullptr){
                if(abc->object==child2->object){
                  found = true;
                }
                abc=abc->next;
              }
              if(!found){
                listOfObjects<Node*>* bcd = child1->object->similar;
                while(bcd->next!=nullptr){
                  bcd=bcd->next;
                }
                bcd->next = new listOfObjects<Node*>(child2->object);
              }
            }
          }
          child2=child2->next;
        }
        child1=child1->next;
      }
      srcList2=srcList2->next;
    }
    srcList1=srcList1->next;
  }
}

//function to find similar nodes according to rule 2 of the question
void Graph::similarRule2b(){
  listOfObjects<Node*>* srcList1 = allNodes;
  while(srcList1!=nullptr){
    // cout<<srcList1->object->value<<"sourcelist1"<<endl;
    listOfObjects<Node*>* srcList2 = allNodes;
    while(srcList2!=nullptr){
      // cout<<srcList1->object->value<<",,,"<<srcList2->object->value<<endl;
      listOfObjects<Node*>* child1 = srcList1->object->childAdjacency;
      listOfObjects<Node*>* child2 = srcList2->object->childAdjacency;
      while(child1!=nullptr){
        while(child2!=nullptr){
          if(condition(child1->object, child2->object) && condition(child2->object, child1->object)){
            if(child1->object->similar==nullptr){
              child1->object->similar = new listOfObjects<Node*>(child2->object);
            }else{
              bool found = false;
              listOfObjects<Node*>* abc = child1->object->similar;
              while(abc!=nullptr){
                if(abc->object==child2->object){
                  found = true;
                }
                abc=abc->next;
              }
              if(!found){
                listOfObjects<Node*>* bcd = child1->object->similar;
                while(bcd->next!=nullptr){
                  bcd=bcd->next;
                }
                bcd->next = new listOfObjects<Node*>(child2->object);
              }
            }
          }
          child2=child2->next;
        }
        child1=child1->next;
      }
      srcList2=srcList2->next;
    }
    srcList1=srcList1->next;
  }
}

//function which is executed to call functions
void Graph::similar(){
  similarRule3();
  similarRule2a();
  similarRule2b();
  similarRule2b();
  similarRule2b();
  copySimilar();
  collapse1();
  collapse2();
}

//function to execute the symmetric properties of a node
void Graph::collapse1(){
  for(int i=0; i<numNodes; i++){
    listOfObjects<Node*>* child = nodes[i].similar1;
    while(child!=nullptr){
      Node* node = child->object;
      if(node->similar1==nullptr){
        node->similar1=new listOfObjects<Node*>(&nodes[i]);
      }else{
        bool found = false;
        listOfObjects<Node*>* abc = node->similar1;
        while(abc!=nullptr){
          if(abc->object->value==nodes[i].value){
            found = true;
          }
          abc=abc->next;
        }
        if(!found){
          listOfObjects<Node*>* bcd = node->similar1;
          while(bcd->next!=nullptr){
            bcd=bcd->next;
          }
          bcd->next = new listOfObjects<Node*>(&nodes[i]);
        }
      }
      child=child->next;
    }
  }
}

//function to execute transitive properties of a node
void Graph::collapse2(){
  for(int i=0; i<numNodes; i++){
    listOfObjects<Node*>* child = nodes[i].similar1;
    while(child!=nullptr){
      // cout<<nodes[i].value<<" . "<<child->object->value<<endl;
      Node* node = child->object;
      listOfObjects<Node*>* a = node->similar1;
      while(a!=nullptr){
        if(nodes[i].similar1==nullptr){
          nodes[i].similar1 = new listOfObjects<Node*>(a->object);
        }else{
          bool found = false;
          listOfObjects<Node*>* abc = nodes[i].similar1;
          while(abc!=nullptr){
            if(abc->object->value==a->object->value){
              found = true;
            }
            abc=abc->next;
          }
          if(!found){
            listOfObjects<Node*>* bcd = nodes[i].similar1;
            while(bcd->next!=nullptr){
              bcd=bcd->next;
            }
            bcd->next = new listOfObjects<Node*>(a->object);
          }
        }
        a=a->next;
      }
      child=child->next;
    }
  //   listOfObjects<Node*>* newChild = nullptr;
  //   while(child!=nullptr){
  //     if(newChild==nullptr){
  //       newChild=new listOfObjects<Node*>(child->object);
  //     }else{
  //       bool found = false;
  //       listOfObjects<Node*>* abc = newChild;
  //       while(abc!=nullptr){
  //         if(abc->object->value==child->object->value){
  //           found = true;
  //         }
  //         abc=abc->next;
  //       }
  //       if(!found){
  //         listOfObjects<Node*>* bcd = newChild;
  //         while(bcd->next!=nullptr){
  //           bcd=bcd->next;
  //         }
  //         bcd->next = new listOfObjects<Node*>(child->object);
  //       }
  //     }
  //     child=child->next;
  //   }
  //   nodes[i].similar=newChild;
  }
}

//function to copy a array of linked list to another array of linked list
void Graph::copySimilar(){
  for(int i=0; i<numNodes; i++){
    listOfObjects<Node*>* child=nodes[i].similar;
    listOfObjects<Node*>* newChild = nullptr;
    while(child!=nullptr){
      if(newChild==nullptr){
        newChild=new listOfObjects<Node*>(child->object);
      }else{
        bool found = false;
        listOfObjects<Node*>* abc = newChild;
        while(abc!=nullptr){
          if(abc->object->value==child->object->value){
            found = true;
          }
          abc=abc->next;
        }
        if(!found){
          listOfObjects<Node*>* bcd = newChild;
          while(bcd->next!=nullptr){
            bcd=bcd->next;
          }
          bcd->next = new listOfObjects<Node*>(child->object);
        }
      }
      child=child->next;
    }
    nodes[i].similar1=newChild;
  }
}

//function to return if two linked lists are same
bool areListsSame(listOfObjects<Node*>* list1, listOfObjects<Node*>* list2){
  if(list1==nullptr && list2==nullptr){
    return false;
  }
  bool a = (calLen(list1)==calLen(list2));
  if(!a){
    return false;
  }
  while(list1!=nullptr){
    listOfObjects<Node*>* a = list2;
    bool found = false;
    while(a!=nullptr){
      if(list1->object->value == a->object->value){
        found = true;
        break;
      }
      a=a->next;
    }
    if(!found){
      return false;
    }
    list1=list1->next;
  }
  if(a){
    return true;
  }
}

//function to return if a value if present in a linked list
bool isPresentinSimilar(Node* node, listOfObjects<Node*>* list){
  while(list!=nullptr){
    if(list->object->value == node->value){
      return true;
    }
    list=list->next;
  }
  return false;
}


//collapse node2 into node1 and making parentAdjacency list of node2
//as nullptr
Node* Graph::collapse2nodes(Node* node1, Node* node2){
  listOfObjects<Node*>* a = node1->parentAdjacency;
  listOfObjects<Node*>* b = node2->parentAdjacency;
  while(b!=nullptr){
    if(node1->parentAdjacency==nullptr){
      node1->parentAdjacency=new listOfObjects<Node*>(b->object);
    }else{
      bool found = false;
      listOfObjects<Node*>* abc = node1->parentAdjacency;
      while(abc->next!=nullptr){
        if(abc->object->value==b->object->value){
          found = true;
        }
        abc=abc->next;
      }
      if(!found){
        listOfObjects<Node*>* bcd = node1->parentAdjacency;
        while(bcd->next!=nullptr){
          bcd=bcd->next;
        }
        bcd->next = new listOfObjects<Node*>(b->object);
      }
    }
    b=b->next;
  }
  return node1;
}

//find maximum of all the elements of a linked list
Node* findMax(listOfObjects<Node*>* list){
  if(list==nullptr){
    return nullptr;
  }
  Node* maxNode = list->object;
  while(list!=nullptr){
    if(list->object->value > maxNode->value){
      maxNode = list->object;
    }
    list=list->next;
  }
  return maxNode;
}

//final function to collapse the nodes
void Graph::collapse3(){
  listOfObjects<Node*>* collapsed = new listOfObjects<Node*>(&nodes[0]);
  listOfObjects<Node*>* s = nodes[0].similar1;
  for(int i=1; i<numNodes; i++){
    listOfObjects<Node*>* t = nodes[i].similar1;
    if(!areListsSame(s,t)){
      bool found = false;
      listOfObjects<Node*>* a = collapsed;
      while(a!=nullptr){
        if(areListsSame(a->object->similar1, t)){
          found=true;
        }
        a=a->next;
      }
      if(!found){
        a=collapsed;
        while(a->next!=nullptr){
          a=a->next;
        }
        a->next = new listOfObjects<Node*>(&nodes[i]);
      }
    }
  }
  listOfObjects<Node*>* k = collapsed;
  // listOfObjects<Node*>* m = collapsed;
  // cout<<calLen(collapsed)<<endl;
  // while(m!=nullptr){
  //   cout<<m->object->value<<endl;
  //   m=m->next;
  // }
  Node* finalGraph[calLen(collapsed)];
  int i=0;
  while(k!=nullptr){
    Node* node = k->object;
    listOfObjects<Node*>* l = k->object->similar1;
    if(l==nullptr){
      finalGraph[i]=node;
      i++;
    }else{
      Node* finalnode = findMax(l);
      while(l!=nullptr){
        if(finalnode->value!=l->object->value){
          finalnode = collapse2nodes(finalnode, l->object);
        }
        l=l->next;
      }
      finalGraph[i]=finalnode;
      i++;
    }
    k=k->next;
  }

  cout<<"Collapsed graph: "<<endl;
  cout<<calLen(collapsed)<<": ";
  for(int i=0; i<calLen(collapsed); i++){
    cout<<finalGraph[i]->value<<" ";
  }cout<<endl;
  for(int i=0; i<calLen(collapsed); i++){
    listOfObjects<Node*>* p = finalGraph[i]->parentAdjacency;
    // cout<<finalGraph[i]->value<<"==";
    while(p!=nullptr){
      // cout<<p->object->value<<" ";
      for(int j=0; j<calLen(collapsed); j++){
        if(p->object->value==finalGraph[j]->value){
          cout<<p->object->value<<" "<<finalGraph[i]->value<<endl;
        }
      }
      p=p->next;
    }
  }
}
//function to print results
void Graph::printResults(){
  // fstream file("output.txt");
  cout<<"Source Nodes: ";
  listOfObjects<Node*>* src = sourceNodes;
  while(src!=nullptr){
      cout<<src->object->value<<" ";
      src =src->next;
  }cout<<endl;

  cout<<"Similar Node Pairs: ";
  for(int i=0; i<numNodes; i++){
    if(nodes[i].similar==nullptr){
      continue;
    }else{
      listOfObjects<Node*>* a = nodes[i].similar;
      while(a!=nullptr){
        cout<<"("<<nodes[i].value<<", "<<a->object->value<<") ";
        a=a->next;
      }
    }
  }
  cout<<endl;
  collapse3();
}