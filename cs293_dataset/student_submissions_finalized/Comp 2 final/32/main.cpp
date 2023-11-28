#include <iostream>
#include <fstream>
#include "vector.cpp"

using namespace std;

// To check wheter a node is a source or not
bool is_source(int k, V<int> &source)
{
	int flag = 1;
	for(int i = 0; i < source.size(); i++)
	{
		if(source[i] == k)
		{
			flag = 0;
			break;
		}
	}
	
	if(flag == 1)
		return false;
	
	else
		return true;
}

//Functio to clear a V completely
V<int> clear(V<int> v)
{
 	V<int> v1;
 	return v1;
}

//Function to remove an element from a V
V<int> erase(V<int> v, int pos)
{
	V<int> new_v;
	for(int i = 0; i < v.size(); i++)
	{
		if(i != pos)
			new_v.push_back(v[i]);
	}
	return new_v;
}

//Function to rid a V of duplicates
V<int> remove_duplicates(V<int> v)
{
	int i, j;
	//Sort vector in ascending order
    for (i = 0; i < v.size() - 1; i++)
	{
        for (j = 0; j < v.size() - i - 1; j++)
        {
            if (v[j] > v[j + 1])
            {
            	//Swap elements
            	int temp = v[j];
            	v[j] = v[j + 1];
            	v[j + 1] = temp;
            }
        }
     }
     
     V<int> vv;
     int flag;
   
     for(int i = 0; i < v.size(); i++)
     {
     	flag = 1;
     	for(int j = 0; j < vv.size(); j++)
     	{
     		if(vv[j] == v[i])
     		{
     			flag = 0;
     			break;
     		}
     	}
     	
     	if(flag == 1)
     		vv.push_back(v[i]);
     			
     }
     return vv;
}

//Function to replace elements init with elements fin in a V, starting from index start and ending with index end
V<int> replace(int start, int end, int init, int fin, V<int> v)
{
	for(int i = start; i <= end; i++)
	{
		if(v[i] == init)
			v[i] = fin;
	}
	return v;
}


int main()
{

	ifstream inputfile;
	inputfile.open("graphFile.txt");
	
	int ch;
	int flag = 1;
	int from_val;
	int to_val;
	int flair = 1;
	int num;
	int t = 0;
	int p=0;
	
	V<int> out[100];
	V<int> in[100];
	V<int> similar[100];
	V<int> a;
	V<int> s;
	
	while (1) 
	{
		inputfile >> ch;
			
		//The first number in file is the number of elements			
		if(flag == 1)
		{
		    num = ch;			
			int arr[num];
			
			for(int i = 0; i < num; i++)
			{
				arr[i] = i + 1;
			}			
		}

		//To store similar nodes in the graph			
		if(t == 2)
		{
			s.push_back(ch);
			
			if(s.size() == 2)
			{
				similar[s[0]].push_back(s[1]);
				similar[s[1]].push_back(s[0]);
				//cout<<s[0]<<" "<<s[1]<<"\n";
				s = clear(s);
			}
		}
		
		//If we encounter -1 in file
		if(ch == -1)
		{
			t++;
		}
		
		//Reading edges 
		if(flag == 0 && t <= 1) 
		{	
			//cout<<"ABCD  "<<ch<<"\n";
			//p++;
			//To store edges
			if(flair%3 == 0)
			{
				out[a[0]].push_back(a[1]); // Storing out-edge
				in[a[1]].push_back(a[0]);	//Storing in-edge
				//cout<<a[0]<<" "<<a[1]<<"\n";
				flair++;
				a = clear(a); //Empty the V to store new edge
			}
			
			//First element : element out of which edge goes	
			if(flair%3 == 1)
			{
				a.push_back(ch);
				flair++;
				//cout<<a[0]<<" ";
			}
		
			//Second element : element into which edge goes
	    	else if(flair%3 == 2)
			{
				a.push_back(ch);
				flair++;
				//cout<<a[1]<<"\n";
			}
		}

		//After reading number of elements
		flag = 0;
		
		//Exit if end of file reached
		if (inputfile.eof() || t == 4)
			break;
					
	} 
	
	V<int> source;
	V<int> sink;

	// To store the sources and sinks into V
	for(int i = 1; i <= num; i++)
	{
		if(out[i].size() == 0) // If vetex is a sink, then no out-edge
			sink.push_back(i);
		
		if(in[i].size() == 0) // If vertex is a source, then no in-edge
			source.push_back(i);
	}

	
	// Write the sources to a file
	ofstream output("outgraph.txt");
	output<<"Source nodes : ";
	for(int i = 0; i < source.size(); i++)
	{
		output<<source[i]<<" ";
	}
	
	output<<"\n";
	
	
	
	// To check for similar nodes
	for(int i = 0; i < num; i++)
	{
		int j, k, flag1;
		
		
		//Only one incoming edge
		if(in[i + 1].size() == 1)
		{
			j = in[i + 1][0];
			
			// Store the similar edges
			similar[i + 1].push_back(j);
			similar[j].push_back(i + 1);
		}
		
		

		// Both n1 and n2 are non-source nodes, and for every node m1 that has an edge 
		//to n1, there is a node m2 that has an edge to n2, where m1 and m2 are similar, and vice versa
		for(int l = 0; l < 5; l++)
		{
			int flag = 0;
			//If neither are source-nodes
			if(!is_source(i + 1, source) && !is_source(l + 1, source) && l != i)
			{
				for(int k = 0; k < in[i + 1].size(); k++)
				{
					for(int p = 0; p < similar[k + 1].size(); p++)
					{
						for(int q = 0; q < out[p + 1].size(); q++)
						{
							if(out[p + 1][q] == l + 1)
							{
								flag = 1;
								break;
							}
						}
					}
				}
			}
			//If nodes are found to be similar according to condtions given
			if(flag == 1)
			{
				similar[i + 1].push_back(l + 1);
				similar[l + 1].push_back(i + 1);
			}
			
		}
	}
				 	
		
	V<int> list;
	output<<"Similar node pairs : ";
	//Write the similar nodes to a file
	for(int i = 0; i < num; i++)
	{
		int j = 0;
		//output<< i + 1 << "    ";
		while(j < similar[i + 1].size())
		{
			similar[i + 1] = remove_duplicates(similar[i + 1]);
			output<<"("<<(i+1)<<", "<<similar[i + 1][j]<<") ";
			//Create a list of similar nodes
			list.push_back(i + 1);
			list.push_back(similar[i + 1][j]);
			j++;
		}

	}
					
	//Collapse similar nodes
	for(int i = 0; i < list.size() - 1; i = i+2)
	{
		if(list[i] < list[i + 1])
		{			
			if(i > 0)
			{
				//Replace values of lower nodes with those of higher
				list = replace(0, i , list[i], list[i + 1], list);
			}
		}
		
		else if(list[i] > list[i + 1])
		{
			if(i > 0)
			{
				//Replace values of lower nodes with those of higher
				list = replace(0, i + 1, list[i + 1], list[i], list);
			}
		}
	}
		
	list = remove_duplicates(list);
	for(int i = 0; i < num; i++)
	{
		if(similar[i + 1].size() == 0)
			list.push_back(i + 1);
	}
	list = remove_duplicates(list);
	
	output<<"\nCollapsed Graph :\n";
	output<<list.size()<<" : ";

	//list = remove_duplicates(list);
	for(int i = 0; i < list.size(); i++)
	{
		output<<list[i]<<" ";	
	}		
	output.close();
}
	
	
	
	
		
		
	
	
	

	
	


