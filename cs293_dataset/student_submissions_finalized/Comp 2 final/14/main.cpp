#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

#ifndef GRAPH_BST_CPP
#include "Graph.cpp"
#endif

int main(int argc, char **argv)
{
  Graph *myGraph;
  int num_nodes;
  int n;
  int ds[200], dt[200];
  int sim1[200], sim2[200];

  // cout << "main checkpoint 1" << endl;

  cin >> num_nodes;

  // cout << "got num nodes "  << num_nodes << endl;

  int cnt = 0;
  int num_edges=0;
  while(true)
  {
    // cout << "main checkpoint 2" << endl;
    //take nodes in
    cnt++;
    cin >> n;
    if(n == -1) 
    {
      cin >> n; 
      cnt = 2; //two -1's noted 
      break;
    }
    else
    {
      if(cnt%2 == 1)  ds[num_edges] = n;
      else if(cnt%2 == 0) {dt[num_edges] = n; num_edges++;}
    }
  }

  // cout << "got num edges "  << num_edges << endl;

  int num_sim_pairs = 0;
  cnt=0;

  while(true)
  {
    // cout << "main checkpoint 3" << endl;
    //take similar nodes in
    cin >> n;
    if(n == -1) 
    {
      cin >> n; 
      cnt = 2; //two -1's noted 
      break;
    }
    else
    {
      cnt++;
      if(cnt%2 == 1)  sim1[num_sim_pairs] = n;
      else if(cnt%2 == 0) {sim2[num_sim_pairs] = n; num_sim_pairs++;}
    }
  }

  myGraph = new Graph(num_nodes, num_edges, num_sim_pairs, ds, dt, sim1, sim2);
  // cout << "main checkpoint 4" << endl;

  myGraph->printResults();

  return 0;
}
