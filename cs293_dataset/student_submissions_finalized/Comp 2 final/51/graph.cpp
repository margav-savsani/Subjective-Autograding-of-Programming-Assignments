#include <iostream>
#include <vector>
using namespace std;
class Node {
 public:
  vector <int> connected;
  vector <int> to_nodes;
  vector <int> from_nodes;
  vector <int> similar;
  int value;
  bool is_similar;
  bool is_source;
  Node(){
    is_similar = false;
    is_source = true;
    to_nodes.resize(0);
    from_nodes.resize(0);
    similar.resize(0);
    connected.resize(0);
      }
  // insert other fields and methods as appropriate
};
class link_list{
  public:
  int node_val;
  link_list * next;
  link_list(){
    node_val =-1;
    next = NULL;
  }
  void get_list(){
    
  }
  link_list* get_free(){
while(next != NULL)
  {return next->get_free();}
  return next;}
};
class Graph {
  vector <int> not_sim;
  int num_node;
  int num_edge;
  Node* nodes;
  
  public:
  Graph(){
    int n;
    cin>>n;
    num_node =n;
    nodes = new Node[n];
    for(int i =0;i<n ;i++){
      nodes[i].value = i+1;
      nodes[i].is_source==true;
    }
    while(true){ 
    int n1,n2;
    cin >> n1 ;
    cin>>n2;
    if( n1 == -1 && n2 == -1){break;}
    nodes[n1-1].connected.push_back(n2);
    nodes[n2-1].connected.push_back(n1);
    nodes[n1-1].to_nodes.push_back(n2) ;
    nodes[n2-1].from_nodes.push_back(n1);
    nodes[n2-1].is_source =false;}
   
    while(true){
    int n1,n2;
    cin >> n1 ;
    cin>>n2;
    if( n1 == -1 && n2 == -1){break;}
    nodes[n1-1].similar.push_back(n2); 
    nodes[n1-1].is_similar = true;
    nodes[n2-1].is_similar = true;
    }
    for(int i=0;i<num_node;i++){
        for(int j=i+1;j<num_node;j++){
          
          check_sim1(i+1,j+1);
        }
    }
    
  }
  void check_similar(){
    for(int i=0;i<num_node;i++){
      if(nodes[i].from_nodes.size() == 1){
        nodes[i].similar.push_back(nodes[i].from_nodes[0]);
        nodes[i].is_similar = true;
        nodes[nodes[i].from_nodes[0]-1].is_similar = true;
      }
    }
  }
  bool check_sim1(int n1,int n2){ 
       
           bool a=false,b=false;
          for(int i=0;i<nodes[n1-1].connected.size();i++){

            if(nodes[nodes[n1-1].connected[i]-1].is_similar){
              int a = nodes[nodes[n1-1].connected[i]-1].similar.size();
              for(int j =0 ;j< nodes[nodes[n1-1].connected[i]-1].similar.size();j++){
                  for(int z =0 ;z<nodes[nodes[nodes[n1-1].connected[i]-1].similar[j]-1].connected.size();z++ ){
                     if(nodes[nodes[nodes[n1-1].connected[i]-1].similar[j]-1].connected[z]==n2 )
                      {
                        a=true;}
                  }
              }
            }
          }
          for(int i=0;i<nodes[n2-1].connected.size();i++){
            if(nodes[nodes[n2-1].connected[i]-1].is_similar){
              int a = nodes[nodes[n2-1].connected[i]-1].similar.size();
              for(int j =0 ;j< nodes[nodes[n2-1].connected[i]-1].similar.size();j++){
                  for(int z =0 ;z<nodes[nodes[nodes[n2-1].connected[i]-1].similar[j]-1].connected.size();z++ ){
                     if(nodes[nodes[nodes[n2-1].connected[i]-1].similar[j]-1].connected[z]==n1 )
                    {
                      b =true;}
                  }
              }
            }
          }
          
          if(a == true && b==true){
                    nodes[n1-1].similar.push_back(nodes[n2-1].value);
                    nodes[n2-1].similar.push_back(nodes[n1-1].value); 
                    nodes[n1-1].is_similar = true;
                    nodes[n2-1].is_similar = true;
                  
          return true;
          }
          
          return false;
        }
      
   
  void print_sources(){
    cout<<"Source nodes:";
    for(int i=0;i<num_node;i++){
        if(nodes[i].is_source){
            cout<<nodes[i].value<< " ";
        }

    }
    cout<<endl;
  }
  void print_similar(){
    cout<<"Similar nodes:";
    for(int i=0;i<num_node;i++){
        int length = nodes[i].similar.size();
        for(int j = 0;j< length;j++){
          cout<< "("<<i+1<<","<<nodes[i].similar[j]<<")";
        }
        }
    cout<<endl;
    }
  void collapsed(){
    int count =0;
    int max = -1;
    cout<<"Collapsed graph:"<<endl;
    for(int i=0;i<num_node;i++){
      if(!nodes[i].is_similar){count++;
      not_sim.push_back(i+1);}
      if(nodes[i].is_similar){
        if(max < i+1){
          max =i+1;
        }
      }
    }
    cout<<count+1<<":";
    cout<<max<<" ";
    int len = not_sim.size();
    for(int i =0;i<len;i++){
      cout<<not_sim[i]<<" ";
    }
    cout<<endl;
    for(int i =0;i<len;i++){
      for(int k=0;k<nodes[not_sim[i]-1].to_nodes.size();k++){
        if(!nodes[nodes[not_sim[i]-1].to_nodes[k]-1].is_similar ||nodes[nodes[not_sim[i]-1].to_nodes[k]-1].value==max-1 ){
          cout<< nodes[not_sim[i]-1].value<<" "<<nodes[nodes[not_sim[i]-1].to_nodes[k]-1].value<<endl;
        }
      }
    }
   
     for(int k=0;k<nodes[max-1].to_nodes.size();k++){
        if(!nodes[nodes[max-1].to_nodes[k]].is_similar ){
          cout<< max<<" "<<nodes[nodes[max-1].to_nodes[k]-1].value<<endl;
        }
      }
  }
  };



