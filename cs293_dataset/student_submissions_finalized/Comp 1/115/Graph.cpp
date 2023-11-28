#ifndef GRAPH_BST_CPP
#define GRAPH_BST_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef GRAPH_BST_H
#include "Graph.h"
#endif
using namespace std;
void Graph::modifiedDFS()
{
	//cout << "printing data"<<endl;
	//for (int i=0;i<numNodes;i++)
	//{
	//	cout<<"adjacent nodes for "<<i+1<<endl;
	//	for(int j=0;j<nodes[i].size;j++)
	//	{
	//		cout<<nodes[i].adjacent_Nodes[j]+1<<" ";
	//	}
	//	cout<<""<<endl;
	//}
	bool completed=false;
	int start=0;// this can be initialised using any value between 0 and N-1, but for simplifying things I took it as 0
	while (!completed)//calling using while loop because there can be many connected components
	{
		size_of_stack=0;
		modifiedDFS_Basic(start,-1);
		//cout<<"one BFS completed"<<endl;
		for(int i=start;i<numNodes;i++)
		{
			if(freq[i]==0)
			{
				start=i;
				completed=false;
				break;
			}
			if(i==numNodes-1)// if every value is more than 0, it means every node is visited once
			{
				completed=true;
			}
		}
		no_BST++;
	}
	return;
}

void Graph::modifiedDFS_Basic(int start,int parent)
{
	//cout<<"----------------------"<<endl;
	//cout<<"printing cycle nodes"<<endl;
	//for(int i=0;i<numNodes;i++)
	//{
	//	cout<<Nodes_in_cycle[i]<<" ";
	//}
	//cout<<""<<endl;
	//cout<<"called modifiedDFS_Basic with start="<<start+1<<", parent="<<parent+1<<endl;
	//cout<<"printing directions"<<endl;
	//for(int i=0;i<numNodes*numNodes;i++)
	//{
	//	cout << directions[i]<<" ";
	//}
	//cout<<""<<endl;
	int* adjacency=nodes[start].adjacent_Nodes;
	int size=nodes[start].size;
	freq[start]++;
	BST_Trees[no_BST].add(start+1);
	int curr_index;
	stack[size_of_stack]=start;// adding into the stack
	size_of_stack++;
	//cout<<"printing stack"<<endl;
	//for(int i=0;i<size_of_stack;i++)
	//{
	//	cout<<stack[i]+1<<" ";
	//}
	//cout<<endl;
	if(size==0)
	{
		size_of_stack--;
	}
	for(int i=0;i<size;i++)
	{
		//cout<<"start of for loop "<<i<<endl;

		curr_index=adjacency[i];//curr_index will be added to the stack in the next recursive call
		if(freq[curr_index]==2)// stopping at a point if it is already visited twice
		{
			//cout<<"$1 "<<curr_index+1<<endl;
			continue;
		}
		if(curr_index==parent)
		{
			//cout<<"$3 "<<curr_index+1<<endl;
			continue;
		}
		if(directions[start*(numNodes)+curr_index]==1)//if it is one, we should not go along this direction
		{
			//cout<<"$2 "<<curr_index+1<<endl;
			continue;
		}
		bool found=false;
		for(int i=0;i<size_of_stack;i++)// this is for calculating whether a cycle is formed or not
		{
			if(i==0)
			{
				found=false;
			}
			if(stack[i]==curr_index)
			{
				found=true;// found in the stack, this is the use of stack, to find the so called back-edges in DFS
			}
			if(found)
			{
				Nodes_in_cycle[stack[i]]=true;// I am not adding directly into no of nodes which are in cycle, because a node can be there in many cycles
			}

		}
		//if(parent!=-1)
		//{
		directions[curr_index*(numNodes)+start]=1;// we should not move in this direction, because already one time we have moved along this direction
		//}
		modifiedDFS_Basic(curr_index,start);// aftering moving though an edge, recursive call is made
		size_of_stack--;
		//cout<<"Backtracing to " << start+1<<endl;
	}
	return;
}

void Graph::printResults()
{	
	cout << "No. of connected components: "<<no_BST<<endl;
	int a=0;
	int b=0;
	int c=0;
	for(int i=0;i<numNodes;i++)
	{
        //no node should have frequency 0.
		if(freq[i]==1)// frequency will be one if it is visited only once, note: backtracking won't be counted in the frequency
		{
			a++;
		}
		if(freq[i]==2)// frequency will be two if it is visited twice, note: backtracking won't be counted in the frequency
		{
			b++;
		}
		if(Nodes_in_cycle[i])// traversing through bool array 
		{
			c++;
		}
	}
	cout << "No. of nodes visited once: "<<a<<endl;
	cout << "No. of nodes visited twice: "<<b<<endl;
	cout << "No. of nodes that are present in a cycle: "<<c<<endl;
	for(int i=0;i<no_BST;i++)
	{
		BST_Trees[i].printBST("");
	}
	return;
}

#endif