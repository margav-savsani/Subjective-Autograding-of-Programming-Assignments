#ifndef GRAPH_BST_CPP
#define GRAPH_BST_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef GRAPH_BST_H
#include "Graph.h"
#endif

bool Graph::find(int n1,int n2)
{
    for(int j=0; j<num_sims[n1]; j++)
    {
        if(n2 == sim_list[n1][j]) return true;
    }
    return false;
}

void Graph::collapsefn()
{
    // modify the similarity list 
    // and replace everything with greatest number in sims

    //symmetric
    int n2;
    for(int n1=1; n1<numNodes+1; n1++)
    {
        for(int j=0; j<num_sims[n1]; j++)
        {
            n2 = sim_list[n1][j];
            if(!find(n2, n1)) 
            {
                sim_list[n2][num_sims[n2]] = n1;
                num_sims[n2]++;
            }
        }
    } 

    //transitive
    for(int n1=1; n1<numNodes+1; n1++)
    {
        for(int i1=0; i1<num_sims[n1]; n1++)
        {
            //checking each and every pair if same leave if not add
            // for an i and j take all elems in sim list of i if they are in j leave
            // if not there add same vice versa
            int n2 = sim_list[n1][i1];
            for(int j=0; j<num_sims[n2];j++)
            {
                if(!find(n1, sim_list[n2][j]))
                {
                    sim_list[n1][num_sims[n1]] = sim_list[n2][j];
                    num_sims[n1]++;
                }
            }
        }
    }

    // printsimilar();

    //construct collapsed array
    for(int i=1; i<numNodes+1; i++)
    {
        int max = i;
        for(int j=0; j<num_sims[i]; j++)
        {
            if(max < sim_list[i][j]) max = sim_list[i][j];
        }
        collapsed[i] = max;
        // cout << "collapsed " << i << " " << collapsed[i] << endl;
    }

}

// Add code as appropriate for your implementation
bool Graph::point2(int n1, int n2)
{
    //base cases
    for(int i=0; i<num_sims[n1]; i++)
    {
        if(sim_list[n1][i] == n2) return true; //aldready similar
    }
    if(num_parents[n1] == 0 || num_parents[n2] == 0) return false;

    //recursively check for all parents
    for(int i=0; i<num_parents[n1]; i++)
    {
        bool found_map = false;
        for(int j=0; j<num_parents[n2]; j++)
        {
            if(point2(par_list[n1][i], par_list[n2][j]) == true) found_map = true;
        }
        if(found_map == false) return false;
    }
    //vice versa
    for(int i=0; i<num_parents[n2]; i++)
    {
        bool found_map = false;
        for(int j=0; j<num_parents[n1]; j++)
        {
            if(point2(par_list[n2][i], par_list[n1][j]) == true) found_map = true;
        }
        if(found_map == false) return false;
    }
    //came out means all found_maps are true  
    sim_list[n1][num_sims[n1]] = n2;
    num_sims[n1]++; 
    return true;
}


void Graph::task1()
{
    for(int i=0;i<numNodes;i++)
    {
        bool isthere = false;
        for(int j=0;j<numEdges;j++)
        {
            if(i+1 == tarnodes[j]) isthere = true;
        }
        if(!isthere) 
        {
            srcnodes[num_src_nodes] = i+1;
            num_src_nodes++;
        }
    }
}

void Graph::similarity()
{
    task1();

    // cout << "similarity function checkpoint" << endl;
    // get data into required format
    for(int i=0; i<numSimPairs; i++)
    {
        sim_list[sim1src[i]][num_sims[i+1]] = sim2src[i];
        num_sims[i+1]++;
    }

    //point 1
    //remove all those are against point 1
    for(int i=0; i<numNodes; i++)
    {
        bool n1_is_src = false;
        for(int k=0;k<num_src_nodes;k++)
        {
            if(srcnodes[k] == i+1) n1_is_src = true;
        }
        for(int j=0;j<num_sims[i];i++)
        {
            bool n2_is_src = false;
            for(int k=0;k<num_src_nodes;k++)
            {
                if(srcnodes[k] == sim_list[i][j]) n2_is_src = true;
            }
            if(n1_is_src == false && n2_is_src== false) sim_list[i][j] = 0;
        }
    }

    //point 3
    // if n1 has single parent n2 then then n1, n2 similar
    for(int i=1; i<numNodes+1; i++)
    {
        if(num_parents[i] == 1)
        {
            sim_list[i][num_sims[i]] = par_list[i][num_parents[i]-1]; 
            num_sims[i]++;
        }
    }

    //point 2
    // check parents of every pair
    for(int i=1; i<numNodes+1; i++)
    {
        for(int j=1; j<numNodes+1; j++)
        {
            // cout<< "doing" << endl;
            point2(i, j);
            // cout << i << " " << j << " " << point2(i, j) << endl;
        }
    }
}

void Graph::printResults() 
{
    task1();
    ofstream o;
    o.open("outgraph.txt");
    if( !o ) { // file couldn't be opened
      cerr << "Error: file could not be opened" << endl;
      exit(1);
    }

    //print source node
    o << "Source nodes: ";
    for(int i=0;i<num_src_nodes/2 -1;i++)
    {
        o << srcnodes[i] << " ";
    }
    o << srcnodes[num_src_nodes-1] << endl;
    o << endl;

    //similarity
    o << "Similar node pairs:";
    for(int i=1; i<numNodes+1; i++)
    { 
      for(int j=0;j<num_sims[i]; j++)
      {
        if(sim_list[i][j]!=0) 
            o << " (" << i << ", " << sim_list[i][j] << ")";
      }
    }
    o << endl;
    o << endl;

    //print collapsed
    collapsefn();
    collapsefn();
    collapsefn();

    for(int i=1; i<numNodes+1; i++)
    {
        bool found1 = false;
        for(int j=1;j<numNodes+1;j++)
        {
            if(collapsed[j] == i) 
            {
                found1 = true;
                grps[num_grps+1] = i;
                num_grps++;  
                break;
            }
        }
    }
    o << "Collapsed graph:\n" << endl;
    o << num_grps << ":";
    for(int i=1;i<num_grps+1;i++)
    {
        o << " " << grps[i];    
    }
    o << endl;

    int num_results=0;
    for(int i=0;i<numEdges;i++)
    {
        int n1 = desrcnodes[i];
        int n2 = tarnodes[i];
        int results1[100];
        int results2[100];
        
        

        if(collapsed[n1] != collapsed[n2])
        {
            bool found3 = false;
            for(int j=0; j<num_results; j++)
            {
                // cout << results1[j] << " " << collapsed[n1] << " " << results2[j]  << " " << collapsed[n2] << " " << num_results << endl;
                if(results1[j] == collapsed[n1] &&  results2[j] == collapsed[n2]) 
                {
                    found3 = true;
                }
                // cout << found3 << endl;
            }
            if(found3 == false)
            {
                results1[num_results] = collapsed[n1] ;
                results2[num_results] = collapsed[n2] ;        
                o << results1[num_results] << " " << results2[num_results] << endl;
                num_results++;
            }
            
        }
    }


    o.close();

}
#endif
