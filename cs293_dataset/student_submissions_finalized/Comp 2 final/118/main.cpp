#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char **argv){
	string file="outgraph.txt";
	if (argc == 2) {
		file=argv[1];
  	}
	ofstream out;
	out.open(file);
	if(!out){
		cerr<<"Error in opening file "<<file<<endl;
		exit(1);
	}

	int numnodes, a, b; //To store the values of nodes of a directed edge and the number of nodes in a graph
	cin>>numnodes; //To accept number of nodes

	//A modified form of an Adjacent Matrix to store the graph(First row to store nodes in the graph)(First column to store source nodes)
	bool adjmat[numnodes+1][numnodes+1] {};
	//A matrix to store the similar nodes (First row to store nodes which have exactly 1 parent)
	bool simmat[numnodes+1][numnodes+1] {};
	//checker matrix to store which nodes are yet to be checked for condition 2
	bool checker[numnodes+1][numnodes+1] {};

	//while loop to accept the directed edges
	cin>>a>>b;
	while(a!=-1 && b!=-1){
		adjmat[a][b]=true;
		if(!adjmat[b][0]){
			adjmat[b][0]=true;
			simmat[0][b]=true;
		}
		else{
			simmat[0][b]=false;
		}
		cin>>a>>b;
	}

	//while loop to accept the similar nodes
	cin>>a>>b;
	while(a!=-1 && b!=-1){
		simmat[a][b]=true;
		cin>>a>>b;
	}

	//To print the source nodes and to simultaneously compute similar node according to condition 3
	out<<"Source nodes:";
	for (a=1; a<=numnodes; a++){
		if(!adjmat[a][0]){
			out<<" "<<a;
			checker[a][0]=true;
		}
		else if(simmat[0][a]){
			for(b=1;b<=numnodes;b++){
				if(adjmat[b][a]){
					simmat[a][b]=true;
					break;
				}
			}
			simmat[0][a]=false;
		}
	}
	out<<endl<<endl;

	//Nested for loop to compute similar nodes according to condition 2
	for(a=1;a<=numnodes;a++){
		if(checker[a][0])
			continue;
		for(b=a;b<=numnodes;b++){
			if(checker[a][b])
				continue;
			checker[a][b]=true;
			if(simmat[a][b] && simmat[b][a])
				continue;
			adjmat[0][0]=true; //checker

			//To find the parent nodes (and their count) of a and b
			int len1=0, len2=0, node1[numnodes], node2[numnodes];
			for(int i=1;i<=numnodes;i++){
				if(adjmat[i][a]){
					node1[len1]=i;
					len1++;
				}
				if(adjmat[i][b]){
					node2[len2]=i;
					len2++;
				}
			}

			//To check condition 2
			for(int i=0;i<len1;i++){
				simmat[0][0]=true; //checker
				for(int j=0;j<len2;j++){
					if(simmat[node1[i]][node2[j]]){
						simmat[0][0]=false;
						break;
					}
				}
				if(simmat[0][0]){
					adjmat[0][0]=false;
					break;
				}
			}
			if(!adjmat[0][0])
				continue;
			for(int i=0;i<len2;i++){
				simmat[0][0]=true; //checker
				for(int j=0;j<len1;j++){
					if(simmat[node2[i]][node1[j]]){
						simmat[0][0]=false;
						break;
					}
				}
				if(simmat[0][0]){
					adjmat[0][0]=false;
					break;
				}
			}

			//If a and b are similar by condition 2
			if(adjmat[0][0]){
				simmat[a][b]=true;
				simmat[b][a]=true;

				//To find the children of a and b
				len1=0;
				len2=0;
				for(int i=1;i<=numnodes;i++){
					if(adjmat[a][i]){
						node1[len1]=i;
						len1++;
					}
					if(adjmat[b][i]){
						node2[len2]=i;
						len2++;
					}
				}

				//To find the nodes which may become similar because a and b were similar
				for(int i=0;i<len1;i++){
					for(int j=0;j<len2;j++){
						if(node1[i]<node2[j]){
							checker[node1[i]][node2[j]]=false;
							checker[node1[i]][0]=false;
						}
						else{
							checker[node2[j]][node1[i]]=false;
							checker[node2[j]][0]=false;
						}
					}
				}

				//To change the value of a and b to agian check the nodes which may have become similar
				if(len1>0 && len2>0){
					if(node1[0]<node2[0] && node1[0]<a){
						a=node1[0];
						b=node2[0];
					}
					else if(node2[0]<a){
						a=node2[0];
						b=node1[0];
					}
				}
			}

		}
		checker[a][0]=true;
	}

	//To print the similar nodes
	out<<"Similar node pairs:";
	for(a=1;a<=numnodes;a++){
		for(b=1;b<=numnodes;b++){
			if(simmat[a][b])
				out<<" ("<<a<<", "<<b<<")";
		}
	}
	out<<endl<<endl;

	//To combine the similar nodes
	int len=0, node[numnodes];
	for(a=1;a<=numnodes;a++){
		len=0;
		for(b=1;b<=numnodes;b++){
			if(simmat[a][b] || simmat[b][a]){
				simmat[a][b]=true;
				simmat[b][a]=true;
				node[len]=b;
				len++;
			}
		}
		for(b=0;b<len;b++){
			for(int i=0;i<len;i++){
				simmat[node[i]][node[b]]=true;
				simmat[node[b]][node[i]]=true;
			}
		}
	}

	/*for(a=1;a<=numnodes;a++){
		for(b=1;b<=numnodes;b++)
			cout<<simmat[a][b]<<" ";
		cout<<endl;
	}*/

	/*for(a=1;a<=numnodes;a++){
		for(b=1;b<=numnodes;b++)
			cout<<adjmat[a][b]<<" ";
		cout<<endl;
	}
	cout<<"spacer"<<endl;*/

	for(a=1;a<=numnodes;a++){
		for(b=numnodes;b>a;b--){
			if(simmat[a][b]){
				adjmat[0][a]=true;

				//To combine the forward edges
				for(int i=1;i<=numnodes;i++){
					if(adjmat[a][i])
						adjmat[b][i]=true;
					if(adjmat[i][a])
						adjmat[i][b]=true;
				}
				adjmat[b][b]=false;
				break;
			}
		}
	}

	len=0;
	for(a=1;a<=numnodes;a++){
		if(!adjmat[0][a]){
			node[len]=a;
			len++;
		}
	}

	/*for(a=1;a<=numnodes;a++){
		for(b=1;b<=numnodes;b++)
			cout<<adjmat[a][b]<<" ";
		cout<<endl;
	}*/

	out<<"Collapsed graph:"<<endl<<endl;
	out<<len<<":";
	for(a=0;a<len;a++)
		out<<" "<<node[a];
	out<<endl;
	for(a=0;a<len;a++){
		for(b=0;b<len;b++){
			if(adjmat[node[a]][node[b]])
				out<<node[a]<<" "<<node[b]<<endl;
		}
	}
}