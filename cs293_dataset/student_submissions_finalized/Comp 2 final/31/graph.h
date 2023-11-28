#include <iostream>
using namespace std;
template <typename T> class listOfObjects {
 public:
  T object;
  listOfObjects<T> *next;
  listOfObjects<T> *prev;
  
  // Constructor
  listOfObjects(T initValue) {object = initValue; next = prev = NULL;}
  
  // Destructor
  ~listOfObjects() {;}
  void addnext(T val){
  	next = new listOfObjects<T>(val);
  }
};

class adjacency{
public:
	listOfObjects<int> *toNodes;
	listOfObjects<int> *fromNodes;
};

class Graph{
	int numNodes;
	int numEdges;
	int** similarity;
	int* visited;
	int* NodeExchange;
	bool** printed;
	adjacency* adjList;
	ofstream file;

public:
	Graph(int n){
		file.open("outgraph.txt");
		numNodes = n;
		similarity = new int*[n];
		printed = new bool*[n];
		visited = new int[n];
		NodeExchange = new int[n];
		for(int i=0; i<n; i++){
			similarity[i] = new int[n];
			printed[i] = new bool[n];
			visited[i] = 0;
			NodeExchange[i] = i;
			for(int j=0; j<n; j++){
				similarity[i][j] = 0;
				printed[i][j] = 0;
			}
		}
		adjList = new adjacency[n];
	}
	void addEdge(int a, int b){
		if(adjList[a-1].toNodes==NULL){
			adjList[a-1].toNodes = new listOfObjects<int>(b-1);
		}
		else {
			listOfObjects<int> *list = adjList[a-1].toNodes;
			while(list->next!= NULL){
				list = list->next;
			}
			list->next = new listOfObjects<int> (b-1);
		}
		if(adjList[b-1].fromNodes==NULL){
			adjList[b-1].fromNodes = new listOfObjects<int>(a-1);
		}
		else {
			listOfObjects<int> *list = adjList[b-1].fromNodes;
			while(list->next!= NULL){
				list = list->next;
			}
			list->next = new listOfObjects<int> (a-1);
		}
	}
	void printGraph(){
		for(int i=0; i<numNodes; i++){
			if(true){
				listOfObjects<int>* l = adjList[i].toNodes;
				while(l!=NULL){
					if(printed[NodeExchange[i]][l->object]==false && NodeExchange[i]!=l->object){
						file << NodeExchange[i]+1 << " " << l->object+1 << endl;
						printed[NodeExchange[i]][l->object]=true;
					}
					l = l->next;
				}
				listOfObjects<int>* l2 = adjList[i].fromNodes;
				while(l2!=NULL){
					if(printed[l2->object][NodeExchange[i]]==false && NodeExchange[i]!=l2->object){
						file << l2->object+1 << " " << NodeExchange[i]+1 << endl;
						printed[l2->object][NodeExchange[i]]=true;
					}
					l2 = l2->next;
				}
			}
		}
	}
	void checksim(int a, int b){
		if(similarity[a-1][b-1]==1 || similarity[a-1][b-1]==-1){}
		else{
			if(adjList[a-1].fromNodes==NULL && adjList[b-1].fromNodes==NULL){
				similarity[a-1][b-1]=1;
			}
			else{
				similarity[a-1][b-1]=0;
			}
		}
	}
	void checksimcase3(){
		for(int i=0; i<numNodes; i++){
			listOfObjects<int> *list = adjList[i].fromNodes;
			if(list==NULL){
				continue;
			}
			else if(list->next==NULL){
				similarity[i][list->object] = 1;
			}
		}
	}
	int checksimcase2(int a, int b){
		if(similarity[a][b]!=0){
			return similarity[a][b];
		}
		else if(adjList[a].fromNodes==NULL || adjList[b].fromNodes==NULL){
			 similarity[a][b] = -1;
			 return -1;
		}
		else{
			listOfObjects<int>* lista = adjList[a].fromNodes;
			listOfObjects<int>* listb;
			while(lista!=NULL){
				bool p = false;
				listb = adjList[b].fromNodes;
				while(listb!=NULL){
					if(checksimcase2(lista->object,listb->object)==1){
						p = true;
						break;
					}
					listb = listb->next;
				}
				if(!p){
					similarity[a][b]=-1;
					return -1;
				}
				lista = lista->next;
			}
			lista = adjList[a].fromNodes;
			while(listb!=NULL){
				bool p = false;
				lista = adjList[a].fromNodes;
				while(lista!=NULL){
					if(checksimcase2(listb->object,lista->object)==1){
						p = true;
						break;
					}
					lista = lista->next;
				}
				if(!p){
					similarity[a][b]=-1;
					return -1;
				}
				listb = listb->next;
			}
			similarity[a][b]=1;
			similarity[b][a]=1;
			return 1;
		}
	}
	void case2(){
		for(int i=0; i<numNodes; i++){
			for(int j=i+1; j<numNodes; j++){
				checksimcase2(i,j);
			}
		}
	}
	void printSimilarNodes(){
		file << "Similar node pairs: ";
		for(int i=0; i<numNodes; i++){
			for(int j=0; j<numNodes; j++){
				if(similarity[i][j]==1){
					file << " (" << i+1 << ", " << j+1 << ")";
				}
			}
		}
		file << endl;
		file<< endl;
	}
	bool addtolist( listOfObjects<int> *list,int value){
		while(list->next!=NULL){
			if(list->object==value){
				return false;
			}
			list = list->next;
		}
		list->addnext(value);
		return true;
	}
	int getmax(listOfObjects<int>* list){
		int max=-1;
		listOfObjects<int>* l = list;
		while(list!=NULL){
			if(list->object>max){
				max = list->object;
			}
			list = list->next;
		}
		while(l!=NULL){
			NodeExchange[l->object] = max;
			l = l->next;
		}
		return max;
	}
	void doDFS(int a, listOfObjects<int> *list){
		this->visited[a] = 1;
		addtolist(list,a);
		for(int j=0; j<numNodes; j++){
			if(similarity[a][j]==1 && this->visited[j]!=1){
				doDFS(j,list);
			}
			else if(similarity[j][a]==1 && this->visited[j]!=1){
				doDFS(j,list);
			}
		}
	}
	void collapse(){
		for(int i=0; i<numNodes; i++){
			if(true){
				listOfObjects<int>* fromlist = adjList[i].fromNodes;
				while(fromlist!=NULL){
					fromlist->object = NodeExchange[fromlist->object];
					fromlist = fromlist->next;
				}
				listOfObjects<int>* tolist = adjList[i].toNodes;
				while(tolist!=NULL){
					tolist->object = NodeExchange[tolist->object];
					tolist = tolist->next;
				}

			}
		}
	}
	void connComp(){
		file << "Collapsed graph: " << endl << endl;
		listOfObjects<int>* finalnodes = new listOfObjects<int>(-1);
		for(int i=0; i<numNodes; i++){
			if(this->visited[i]==0){
				listOfObjects<int>* list = new listOfObjects<int>(-1);
				doDFS(i,list);
				int max = getmax(list);
				addtolist(finalnodes,max+1);
			}
		}
		listOfObjects<int>* len = finalnodes;
		int i=0;
		while(len!=NULL){
			i++;
			len = len->next;
		}
		file << i-1 << ": ";
		printlist(finalnodes->next);
		collapse();

	}
	void printlist(listOfObjects<int> *l){
		while(l!=NULL){
			file << l->object << " ";
			l = l->next;
		}
		file << endl;
	}
	void printsourceNodes(){
		file << "Source Nodes: ";
		listOfObjects<int> *sNodes = new listOfObjects<int>(-1);
		for(int i=0; i<numNodes; i++){
			listOfObjects<int>* list = adjList[i].fromNodes;
			if(list==NULL){
				addtolist(sNodes,i+1);
			}
		}
		printlist(sNodes->next);
		file << endl;
	}
};