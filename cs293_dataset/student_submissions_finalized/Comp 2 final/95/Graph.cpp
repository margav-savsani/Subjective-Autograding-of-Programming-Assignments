#ifndef STD_HEADERS_H
#endif
#ifndef GRAPH_BST_H
#include "Graph.h"
#endif
using namespace std;
bool check_exist(vector<int> a,int b){
  for(int i=0;i<a.size();i++){
    if(a[i]==b){
      return true;
    }
  }
  return false;
}
void Graph::add_edges(int a,int b){
      nodes[a-1].adjancy_out.push_back(b);
      nodes[b-1].adjancy_in.push_back(a);
      nodes[b-1].source_node=false;
      nodes[a-1].adjancy.push_back(b);
      nodes[b-1].adjancy.push_back(a);
    }
void Graph::check_similar(){
  for(int i=0;i<numNodes;i++){
    if(nodes[i].adjancy_in.size()==1){
      bool exist=false;
      for(int j=0;j<nodes[i].similar_nodes.size();j++){
        if(nodes[i].similar_nodes[j]==nodes[i].adjancy_in[0]){
          exist=true;
        }
      }
      if(!exist){
        nodes[i].similar_nodes.push_back(nodes[i].adjancy_in[0]);
        nodes[i].undir_sim.push_back(nodes[i].adjancy_in[0]);
        nodes[nodes[i].adjancy_in[0]-1].undir_sim.push_back(i+1);
      }
    }
  }
  for(int i=0;i<numNodes;i++){
    for(int j=0;j<nodes[i].similar_nodes.size();j++){
      if(!(nodes[i].source_node||nodes[j].source_node)){
    bool both_simalar=check_exist(nodes[nodes[i].similar_nodes[j]].similar_nodes,i+1);
    if(both_simalar){
    for(int r=0;r<nodes[i].adjancy_in.size();r++){
      for(int p=0;p<nodes[j].adjancy_in.size();p++){
        if(!check_exist(nodes[nodes[i].adjancy_in[r]-1].similar_nodes,nodes[j].adjancy_in[p])&&!check_exist(nodes[nodes[j].adjancy_in[p]-1].similar_nodes,nodes[i].adjancy_in[r])){
          nodes[nodes[i].adjancy_in[r]].similar_nodes.push_back(nodes[j].adjancy_in[p]);
          nodes[nodes[j].adjancy_in[p]].similar_nodes.push_back(nodes[i].adjancy_in[r]);
          nodes[nodes[i].adjancy_in[r]].undir_sim.push_back(nodes[j].adjancy_in[p]);
          nodes[nodes[j].adjancy_in[p]].undir_sim.push_back(nodes[i].adjancy_in[r]);

        }
        if(!check_exist(nodes[nodes[i].adjancy_in[r]-1].similar_nodes,nodes[j].adjancy_in[p])&&check_exist(nodes[nodes[j].adjancy_in[p]-1].similar_nodes,nodes[i].adjancy_in[r])){
          nodes[nodes[i].adjancy_in[r]].similar_nodes.push_back(nodes[j].adjancy_in[p]);
          nodes[nodes[i].adjancy_in[r]].undir_sim.push_back(nodes[j].adjancy_in[p]);
          nodes[nodes[j].adjancy_in[p]].undir_sim.push_back(nodes[i].adjancy_in[r]);
        }
        if(check_exist(nodes[nodes[i].adjancy_in[r]-1].similar_nodes,nodes[j].adjancy_in[p])&&!check_exist(nodes[nodes[j].adjancy_in[p]-1].similar_nodes,nodes[i].adjancy_in[r])){
           nodes[nodes[j].adjancy_in[p]].similar_nodes.push_back(nodes[i].adjancy_in[r]);
           nodes[nodes[i].adjancy_in[r]].undir_sim.push_back(nodes[j].adjancy_in[p]);
          nodes[nodes[j].adjancy_in[p]].undir_sim.push_back(nodes[i].adjancy_in[r]);
        }
      }
    }
    for(int r=0;r<nodes[i].adjancy_out.size();r++){
      for(int p=0;p<nodes[j].adjancy_in.size();p++){
        if(!check_exist(nodes[nodes[i].adjancy_out[r]-1].similar_nodes,nodes[j].adjancy_in[p])&&!check_exist(nodes[nodes[j].adjancy_in[p]-1].similar_nodes,nodes[i].adjancy_in[r])){
          nodes[nodes[i].adjancy_out[r]].similar_nodes.push_back(nodes[j].adjancy_in[p]);
          nodes[nodes[j].adjancy_in[p]].similar_nodes.push_back(nodes[i].adjancy_out[r]);
          nodes[nodes[i].adjancy_in[r]].undir_sim.push_back(nodes[j].adjancy_in[p]);
          nodes[nodes[j].adjancy_in[p]].undir_sim.push_back(nodes[i].adjancy_in[r]);
        }
        if(!check_exist(nodes[nodes[i].adjancy_out[r]-1].similar_nodes,nodes[j].adjancy_in[p])&&check_exist(nodes[nodes[j].adjancy_in[p]-1].similar_nodes,nodes[i].adjancy_out[r])){
          nodes[nodes[i].adjancy_out[r]].similar_nodes.push_back(nodes[j].adjancy_in[p]);
          nodes[nodes[i].adjancy_in[r]].undir_sim.push_back(nodes[j].adjancy_in[p]);
          nodes[nodes[j].adjancy_in[p]].undir_sim.push_back(nodes[i].adjancy_in[r]);
        }
        if(check_exist(nodes[nodes[i].adjancy_out[r]-1].similar_nodes,nodes[j].adjancy_in[p])&&!check_exist(nodes[nodes[j].adjancy_in[p]-1].similar_nodes,nodes[i].adjancy_out[r])){
           nodes[nodes[j].adjancy_in[p]].similar_nodes.push_back(nodes[i].adjancy_out[r]);
           nodes[nodes[i].adjancy_in[r]].undir_sim.push_back(nodes[j].adjancy_in[p]);
          nodes[nodes[j].adjancy_in[p]].undir_sim.push_back(nodes[i].adjancy_in[r]);
        }
      }
    }
    for(int r=0;r<nodes[i].adjancy_in.size();r++){
      for(int p=0;p<nodes[j].adjancy_in.size();p++){
        if(!check_exist(nodes[nodes[i].adjancy_in[r]-1].similar_nodes,nodes[j].adjancy_in[p])&&!check_exist(nodes[nodes[j].adjancy_in[p]-1].similar_nodes,nodes[i].adjancy_in[r])){
          nodes[nodes[i].adjancy_in[r]].similar_nodes.push_back(nodes[j].adjancy_in[p]);
          nodes[nodes[j].adjancy_in[p]].similar_nodes.push_back(nodes[i].adjancy_in[r]);
          nodes[nodes[i].adjancy_in[r]].undir_sim.push_back(nodes[j].adjancy_in[p]);
          nodes[nodes[j].adjancy_in[p]].undir_sim.push_back(nodes[i].adjancy_in[r]);
        }
        if(!check_exist(nodes[nodes[i].adjancy_in[r]-1].similar_nodes,nodes[j].adjancy_in[p])&&check_exist(nodes[nodes[j].adjancy_in[p]-1].similar_nodes,nodes[i].adjancy_in[r])){
          nodes[nodes[i].adjancy_in[r]].similar_nodes.push_back(nodes[j].adjancy_in[p]);
          nodes[nodes[i].adjancy_in[r]].undir_sim.push_back(nodes[j].adjancy_in[p]);
          nodes[nodes[j].adjancy_in[p]].undir_sim.push_back(nodes[i].adjancy_in[r]);
        }
        if(check_exist(nodes[nodes[i].adjancy_in[r]-1].similar_nodes,nodes[j].adjancy_in[p])&&!check_exist(nodes[nodes[j].adjancy_in[p]-1].similar_nodes,nodes[i].adjancy_in[r])){
           nodes[nodes[j].adjancy_in[p]].similar_nodes.push_back(nodes[i].adjancy_in[r]);
           nodes[nodes[i].adjancy_in[r]].undir_sim.push_back(nodes[j].adjancy_in[p]);
          nodes[nodes[j].adjancy_in[p]].undir_sim.push_back(nodes[i].adjancy_in[r]);
        }
      }
    }
    for(int r=0;r<nodes[i].adjancy_out.size();r++){
      for(int p=0;p<nodes[j].adjancy_out.size();p++){
        if(!check_exist(nodes[nodes[i].adjancy_out[r]-1].similar_nodes,nodes[j].adjancy_out[p])&&!check_exist(nodes[nodes[j].adjancy_out[p]-1].similar_nodes,nodes[i].adjancy_out[r])){
          nodes[nodes[i].adjancy_out[r]].similar_nodes.push_back(nodes[j].adjancy_out[p]);
          nodes[nodes[j].adjancy_out[p]].similar_nodes.push_back(nodes[i].adjancy_out[r]);
          nodes[nodes[i].adjancy_in[r]].undir_sim.push_back(nodes[j].adjancy_in[p]);
          nodes[nodes[j].adjancy_in[p]].undir_sim.push_back(nodes[i].adjancy_in[r]);
        }
        if(!check_exist(nodes[nodes[i].adjancy_out[r]-1].similar_nodes,nodes[j].adjancy_out[p])&&check_exist(nodes[nodes[j].adjancy_out[p]-1].similar_nodes,nodes[i].adjancy_out[r])){
          nodes[nodes[i].adjancy_out[r]].similar_nodes.push_back(nodes[j].adjancy_out[p]);
          nodes[nodes[i].adjancy_in[r]].undir_sim.push_back(nodes[j].adjancy_in[p]);
          nodes[nodes[j].adjancy_in[p]].undir_sim.push_back(nodes[i].adjancy_in[r]);
        }
        if(check_exist(nodes[nodes[i].adjancy_out[r]-1].similar_nodes,nodes[j].adjancy_out[p])&&!check_exist(nodes[nodes[j].adjancy_out[p]-1].similar_nodes,nodes[i].adjancy_out[r])){
           nodes[nodes[j].adjancy_out[p]].similar_nodes.push_back(nodes[i].adjancy_out[r]);
           nodes[nodes[i].adjancy_in[r]].undir_sim.push_back(nodes[j].adjancy_in[p]);
          nodes[nodes[j].adjancy_in[p]].undir_sim.push_back(nodes[i].adjancy_in[r]);
        }
      }
    }
    }}
    }
  }
}
void Graph::print_results(){
  outgraph<<"Source nodes: ";
  for(int i=0;i<numNodes;i++){
    if(nodes[i].source_node){
      outgraph<<i+1<<" ";
    }
  }
  outgraph<<endl;
  outgraph<<"Similar node pairs: ";
  for(int i=0;i<numNodes;i++){
    for(int j=0;j<nodes[i].similar_nodes.size();j++){
      outgraph<<"("<<i+1<<", "<<nodes[i].similar_nodes[j]<<") ";
    }
  }
  outgraph<<endl;
  outgraph<<"Collapsed graph:"<<endl;
  outgraph<<c<<": ";
  for(int i=0;i<coll_gph.size();i++){
    outgraph<<coll_gph[i]<<" ";
  }
  outgraph<<endl;
  for(int i=0;i<coll_gph.size();i++){
    for(int j=0;j<nodes[coll_gph[i]-1].undir_sim.size();j++){
         for(int k=0;k<nodes[nodes[coll_gph[i]-1].undir_sim[j]-1].undir_sim.size();k++){
            if(check_exist(coll_gph,nodes[nodes[coll_gph[i]-1].undir_sim[j]-1].adjancy[k])){
              if(coll_gph[i]!=nodes[nodes[coll_gph[i]-1].undir_sim[j]-1].adjancy[k]){
              outgraph<<coll_gph[i]<<" "<<nodes[nodes[coll_gph[i]-1].undir_sim[j]-1].adjancy[k]<<endl;}
            }
         }
    }
  }
}
void Graph::print_graph(){
  for(int i=0;i<numNodes;i++){
    cout<<i+1<<" :";
    for(int j=0;j<nodes[i].adjancy_in.size();j++){
      cout<<nodes[i].adjancy_in[j]<<"  ";
    }
     for(int j=0;j<nodes[i].adjancy_out.size();j++){
      cout<<nodes[i].adjancy_out[j]<<"  ";
    }
    cout<<endl;
  }
}
int Graph::dfs(int r,int& maximum){
  
  for(int i=0;i<numNodes;i++){
    for(int j=0;j<nodes[i].adjancy.size();j++){
      if(!nodes[nodes[i].adjancy[j]-1].visited){
        nodes[nodes[i].adjancy[j]-1].visited=true;
        maximum=max(dfs(nodes[i].adjancy[j]-1,maximum),maximum);
      }
    }
  }
  maximum=max(r+1,maximum);
  return r+1;
}
void Graph::collapse_graph(){
  Graph *coll_graph=new Graph(numNodes);
  for(int i=0;i<numNodes;i++){
    for(int j=0;j<nodes[i].similar_nodes.size();j++){
      coll_graph->add_edges(i+1,nodes[i].similar_nodes[j]);
    }
  }
  
  for(int i=0;i<numNodes;i++){
    int var=0;
    if(!coll_graph->nodes[i].visited){
      
      int q=coll_graph->dfs(i,var);
      coll_gph.push_back(var);
      c++;
    }
  }
}
