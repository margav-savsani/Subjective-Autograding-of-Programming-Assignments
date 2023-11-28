#include<iostream>
#include<fstream>
using namespace std;


template <typename T> class list {
 public:
  T object;
  list<T> *next;
  list<T> * prev;
  // Constructor
  list(T initValue) {object = initValue; next = nullptr;}

};
class Node{
  public:
    list<Node> * repnode = nullptr;
    int value = -1; //value of the node, -1 for checking errors related to uninitialized node
    list<int> * outEdges = nullptr;  //list of values of nodes, this node has edges to
    list<int> * outEdgesTail = nullptr; //tail pointer of outEdges
    list<int> * inEdges = nullptr; //list of values of nodes, this node has edge from
    list<int> * inEdgesTail = nullptr; //tail pointer of inEdges
    list<int> * similarTo = nullptr; //list of values of nodes, this node is similar to
    list<int> * similarToTail = nullptr; //tail pointer of similarTo

    bool isAdjTo(int n){
      list<int>* curr = outEdges;
      if (curr==nullptr) return false;
      while(curr!=nullptr){
        if(curr->object == n) return true;
        curr = curr->next;
      }
      return false;
    }

    void addAdjTo(int n){
      if (isAdjTo(n)){
        return;
      }

      if(outEdges==nullptr){
        outEdges = new list<int>(n);
        outEdgesTail = outEdges;
        return;
      }
      outEdgesTail->next = new list<int>(n);
      outEdgesTail->next->prev = outEdgesTail;
      outEdgesTail = outEdgesTail->next;
    }

    bool isAdjFrom(int n){
      list<int>* curr = inEdges;
      if (curr==nullptr) return false;
      while(curr!=nullptr){
        if(curr->object == n) return true;
        curr = curr->next;
      }
      return false;
    }

    void addAdjFrom(int n){
      if (isAdjFrom(n)){
        return;
      }

      if(inEdges==nullptr){
        inEdges = new list<int>(n);
        inEdgesTail = inEdges;
        return;
      }
      inEdgesTail->next = new list<int>(n);
      inEdgesTail->next->prev = inEdgesTail;
      inEdgesTail = inEdgesTail->next;
    }

    bool isSimilar(int n){
      list<int>* curr = similarTo;
      if (curr==nullptr) return false;
      while(curr!=nullptr){
        if(curr->object == n) return true;
        curr = curr->next;
      }
      return false;
    }
    void addSimilar(int n){
      if (isSimilar(n)){
        return;
      }

      if(similarTo==nullptr){
        similarTo = new list<int>(n);
        similarToTail = similarTo;
        return;
      }
      similarToTail->next = new list<int>(n);
      similarToTail->next->prev = similarToTail;
      similarToTail = similarToTail->next;
    }
};

class DAG{
  public:
  ofstream f;
  Node* nodes = nullptr;
  int numNodes = 0;
  DAG(int nNodes){
    f.open("outgraph.txt");
    numNodes = nNodes;
    nodes = new Node[numNodes];
    for(int i=1; i<=numNodes; i++){ //now all nodes are added and defined correctly, nodes[i] = i+1
      nodes[i-1].value = i;
    }

    //reading the edges
    int n1, n2;
    while(cin>>n1>>n2){
      if((n1==-1) && (n2==-1)){ //break to adding similar edges
        break;
      } 
      if((n1 > numNodes) || (n2 > numNodes) || (n1<=0) || (n2<=0)){ //nodes out of bounds
        cerr<<"Error : Nodes out of range"<<endl;
        return;
      }

      nodes[n1-1].addAdjTo(n2); //add this to edgesTo list of n1
      nodes[n2-1].addAdjFrom(n1); //add this to edgesFrom list of n2
    }
    
    //reading the similar source nodes
    while(cin>>n1>>n2){
      if((n1==-1) && (n2==-1)){ //done adding similarity
        break;
      }
      if((n1 > numNodes) || (n2 > numNodes) || (n1<=0) || (n2<=0)){ //nodes out of bounds
        cerr<<"Error : Nodes out of range"<<endl;
        return;
      }
      if( (nodes[n1-1].inEdges!=nullptr) || (nodes[n2-1].inEdges!=nullptr) ){
        cerr<<"Error : Nodes are not Source Nodes"<<endl;
      }
      nodes[n1-1].addSimilar(n2);
      // nodes[n2-1].addSimilar(n1);
    }

    //Now we should identify all the similarity relations
    //case 1 : similarity implied by single edge incoming 
    for (int i=0; i<numNodes; i++){
      if((nodes[i].inEdges!=nullptr) && (nodes[i].inEdges==nodes[i].inEdgesTail)){ //if this node has exactly one incoming edge
        int v= nodes[i].inEdges->object;
        nodes[i].addSimilar(v);
        // nodes[v-1].addSimilar(i+1);
      }
    }
    //case 2 : similarity due to similar parents
    while(true){
      bool doessomethingchange = false;  
      for(int i=0; i<(numNodes-1); i++){
        for(int j=i; j<numNodes; j++){
          if(! nodes[i].isSimilar(j+1)){ //if these two nodes aren't already similar, 
                                        //we check if they are similar bcoz of their parents
            if((nodes[i].inEdges==nullptr) || (nodes[j].inEdges==nullptr)){ //both should be source nodes
              continue;
            }
            //nodes which have edge towards nodes[i]
            list<int>* curr = nodes[i].inEdges;
            bool aresimilar= true;
            while(curr!=nullptr){
              bool issimilar=false;
              //this should have atleast one similar node in inEdges of nodes[j]
              list<int>* l = nodes[j].inEdges;
              while(l!=nullptr){
                if(nodes[curr->object-1].isSimilar(l->object)) {
                  issimilar=true;
                  break;
                }
                l=l->next;
              }
              //now if this node doesn't have a similar node in nodes[j].inEdges, j and i aren't similar nodes
              if(!issimilar){
                aresimilar = false;
                break;
              }
              curr=curr->next;
            }

            //nodes which have edge towards nodes[j]
            curr = nodes[j].inEdges;
            while(curr!=nullptr){
              bool issimilar=false;
              //this should have atleast one similar node in inEdges of nodes[j]
              list<int>* l = nodes[i].inEdges;
              while(l!=nullptr){
                if(nodes[curr->object-1].isSimilar(l->object)) {
                  issimilar=true;
                  break;
                }
                l=l->next;
              }
              //now if this node doesn't have a similar node in nodes[j].inEdges, j and i aren't similar nodes
              if(!issimilar){
                aresimilar = false;
                break;
              }
              curr=curr->next;
            }
            if(!aresimilar) continue; //if some parent disagrees and sets issimilar to false, which causes aresimilar to false
            else{ //this means all parents agreed and these two nodes are similar
              nodes[i].addSimilar(j+1);
              nodes[j].addSimilar(i+1);
              doessomethingchange = true;
            }
          }
        }
      }
      if(!doessomethingchange) break;
    }
  }

  void Collapse(){
    list<Node> * collapsed_nodes = new list<Node>(*(new Node));
    collapsed_nodes->object.value =1;
    int numCollapsedNodes=0;
    list<Node> * tail_cnodes = collapsed_nodes;
    bool visited[numNodes];
    for (int i=0; i<numNodes; i++){
      visited[i] = false;
    } 
    for(int i=0; i<numNodes; i++){
      if(visited[i]) continue; //if the node has been visited
      visited[i] = true;
      numCollapsedNodes++;
      //we should implement a bfs here from the node that has not been visited yet
      list<int> * queue = new list<int>(i); //queue contains index of vertex to be checked
      list<int> * tailqueue = queue;
      while(queue!=nullptr){
        //working with nodes[i]
        if (tail_cnodes->object.value < (queue->object +1)){
          tail_cnodes->object.value = queue->object + 1;
        }
        nodes[queue->object].repnode = tail_cnodes;
        tail_cnodes->object.addSimilar(queue->object+1);
        //adding all the adjacent nodes into this queue
        list<int> * curr = nodes[queue->object].similarTo;
        while(curr!=nullptr){
          if(!visited[curr->object-1]){
            visited[curr->object-1] = true;
            tailqueue->next = new list<int>(curr->object-1);
            tailqueue = tailqueue->next;
          }
          curr = curr->next;
        }
        queue = queue->next;
      }
      tail_cnodes->next = new list<Node>(*(new Node));
      tail_cnodes->next->object.value = -1;
      tail_cnodes = tail_cnodes->next;
    }
    f<<endl;
    f << "Collapsed graph:"<<endl<<endl;
    f<<numCollapsedNodes<<":";
    //adding all the edges 
    //current collapsed node in the list of collapsed nodes
    list<Node> * curr_cnode = collapsed_nodes;
    //for every collapsed node
    while((curr_cnode!=nullptr) && (curr_cnode!=tail_cnodes)){ //because last node is reduntant and has value = -1 in it
      f<<" "<<curr_cnode->object.value;
      list<int> * currnode = curr_cnode->object.similarTo;
      //for every participant node of the collapsed node
      //{participant nodes are stored in the similarTo list of each Node in collapsed_nodes}
      while(currnode!=nullptr){
        //for every edge of this participating node
        list<int>* currAdj = nodes[currnode->object -1].outEdges;
        while(currAdj!=nullptr){
          curr_cnode->object.addAdjTo(nodes[currAdj->object-1].repnode->object.value);
          currAdj = currAdj->next;
        }
        currAdj = nodes[currnode->object].inEdges;
        while(currAdj!=nullptr){
          curr_cnode->object.addAdjFrom(nodes[currAdj->object-1].repnode->object.value);
          currAdj = currAdj->next;
        }
        currnode = currnode->next;
      }
      curr_cnode = curr_cnode->next;
    }
    f<<endl;
    //printing every edge
    list<Node> * curr= collapsed_nodes;
    while((curr!=nullptr) && (curr!=tail_cnodes)){
      list<int> * curredge = curr->object.outEdges;
      while(curredge !=nullptr){
        f<<curr->object.value<<" "<<curredge->object<<endl;
        curredge = curredge->next;
      }
      curr = curr->next;
    }
  }

  void printSimilar(){
    f<<"Similar node pairs:";
    for (int i=0; i<numNodes; i++){
      list<int> * curr = nodes[i].similarTo;
      while(curr!=nullptr){
        f<<" ("<<i+1<<", "<<curr->object<<")";
        curr = curr->next;
      }
    }
    f<<endl;
  }

  void printSources(){
    f<<"Source Nodes:";
    for(int i=0; i<numNodes; i++){
      if(nodes[i].inEdges==nullptr){
        f<<" "<<nodes[i].value;
      }
    }
    f<<endl<<endl;
  }
};