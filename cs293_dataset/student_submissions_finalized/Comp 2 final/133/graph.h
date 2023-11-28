#include<iostream>
#include<fstream>
using namespace std;

// forward declaration
class Node;                                                   // An implementation of graph vertex 

class list_node {                                             // An implementation of an adjacency_linked_list_node
  public:                                                     
  Node* node;                                                 // Graph vertex
  list_node* next;                                            // pointer to next adjacency_linked_list_node
  list_node(Node* node){this->node = node; next = nullptr;}   // constructor 
};

class adjacency_list{                                         // A linked list which stores the adjacent nodes of a vertex
  public:  
  list_node* adj_nodes = nullptr;                             // head of the linked list
  list_node* tail = nullptr;                                  // tail of the linked list
  adjacency_list(){adj_nodes = nullptr; tail = nullptr;}      // default constructor
  void add(Node* node){                                       // adds a vertex(node) in the list
    if(adj_nodes == nullptr){                                 
      adj_nodes = new list_node(node);
      tail = adj_nodes;
    } else{
      tail->next = new list_node(node);
      tail = tail->next;
    }
  }
  bool is_emp(){return adj_nodes==nullptr;}                   // checks whether the list is empty or not
  bool is_pre(int index);                                     // checks whether a vertex(node) with the given value is present or not  
};

class Node {                                                  // An implementation of a graph vertex
 public:
  int index;
  int value;                                                  // value of the node
  adjacency_list* out_list = new adjacency_list();            // adjcency list of the vertex(node)
  adjacency_list* in_list = new adjacency_list();
  Node(){}  // default constructor
  Node(int value){this->value = value;}  //constructor
  ~Node(){}
  // insert other fields and methods as appropriate
};
 
bool adjacency_list::is_pre(int index){                       // implementation of a member function of the adjacency_list class
  list_node* temp=adj_nodes;
  while(temp != nullptr){
    if(temp->node->index == index) return true;               // return true if a node with the given value is present
    temp = temp->next;
  }
  return false;                                               // else returns false
}

class graph{
  int numNodes;
  Node* nodes;
  ofstream outfile;
  bool** sNodes;
  public:
    graph(int numNodes){
      this->numNodes = numNodes;
      nodes = new Node[numNodes];
      sNodes = new bool*[numNodes];
      for(int i=0;i<numNodes;i++) {
        nodes[i].index = i;
        nodes[i].value = i+1; 
        sNodes[i] = new bool[numNodes];
        for(int j=0;j<numNodes;j++) sNodes[i][j]=0;
      }    
      outfile.open("outGraph.txt");
    }
    void add_edge(int n1,int n2){
      nodes[n1-1].out_list->add(&nodes[n2-1]);
      nodes[n2-1].in_list->add(&nodes[n1-1]);
    }
    void print_sources(){
      outfile<<"Source nodes:";
      for(int i=0;i<numNodes;i++){
        if(nodes[i].in_list->is_emp()) outfile  <<" "<<i+1;
      }
      outfile<<endl;
      outfile<<endl;
    }
    void similar_nodes(int n1, int n2){
      if(nodes[n1-1].in_list->is_emp() && nodes[n2-1].in_list->is_emp()) sNodes[n1-1][n2-1]=1;
    }
    bool check(int i, int j){
      if(sNodes[i][j]) return true;
      if(nodes[i].in_list->is_emp() && nodes[j].in_list->is_emp()) return sNodes[i][j];
      list_node* i_node = nodes[i].in_list->adj_nodes;      
      while(i_node != nullptr){
        bool found=0;
        int p = i_node->node->value-1;        
        list_node* j_list = nodes[j].in_list->adj_nodes;
        while(j_list != nullptr){
          int q = j_list->node->value-1;
          sNodes[p][q] = check(p,q);
          if(sNodes[p][q]){found=1;break;}
          j_list = j_list->next;
        }
        if(!found) return false;
        i_node = i_node->next;
      }
      list_node* j_node = nodes[j].in_list->adj_nodes;
      while(j_node != nullptr){
        bool found = 0;
        int q = j_node->node->value-1;        
        list_node* i_list = nodes[i].in_list->adj_nodes;
        while(i_list != nullptr){
          int p = i_list->node->value-1;
          sNodes[q][p] = check(q,p);
          if(sNodes[q][p]){found = 1;break;}
          i_list = i_list->next;
        }
        if(!found) return false;
        j_node = j_node->next;
      }      
      return true;
    }
    void find_similar_nodes(){
      for(int i=0;i<numNodes;i++) for(int j=0;j<numNodes;j++){
        if(!sNodes[i][j] && nodes[i].in_list->is_pre(j)) if(nodes[i].in_list->adj_nodes->next == nullptr)  sNodes[i][j]=1;
      }
      for(int i=0;i<numNodes;i++) for(int j=0;j<i;j++){
        if(!sNodes[i][j]){          
          sNodes[i][j]=check(i,j);      
          if(!sNodes[j][i]) sNodes[j][i] = sNodes[i][j];    
        }
      }
    }
    void print_similar_nodes(){
      outfile<<"Similar node pairs:";  
      for(int i=0;i<numNodes;i++) for(int j=0;j<numNodes;j++){
        if(sNodes[i][j]) outfile<<" ("<<i+1<<", "<<j+1<<")";
      }    
      outfile<<endl;
      outfile<<endl;
    }
    void collapse(){
      for(int i=0;i<numNodes;i++) for(int j=0;j<numNodes;j++){
        if(sNodes[i][j] && nodes[i].value != nodes[j].value){
          int val = max(nodes[i].value,nodes[j].value);
          int change_val;
          if(val > nodes[i].value) change_val = nodes[i].value;
          else change_val = nodes[j].value;
          for(int k=0;k<numNodes;k++) if(nodes[k].value == change_val) nodes[k].value = val;                           
        }
        sNodes[i][j]=1;
      }
      outfile<<"Collapsed graph:"<<endl;
      outfile<<endl;
      int n=0;
      for(int i=0;i<numNodes;i++) if(nodes[i].value == i+1) n++;
      outfile<<n<<":";
      for(int i=0;i<numNodes;i++) if(nodes[i].value == i+1) outfile<<" "<<i+1;
      outfile<<endl;
      for(int i=0;i<numNodes;i++){
        if(!nodes[i].out_list->is_emp() ){
          int val = nodes[i].value;
          list_node* temp = nodes[i].out_list->adj_nodes;
          while(temp != nullptr ){
            int adj_val = temp->node->value;
            if(adj_val != val && sNodes[val-1][adj_val-1]) {outfile<<val<<" "<<temp->node->value<<endl; sNodes[val-1][adj_val-1]=0;}
            temp = temp->next;
          }
        }
      }
      outfile.close();
    }
    ~graph(){}
};