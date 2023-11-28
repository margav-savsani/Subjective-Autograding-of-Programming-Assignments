#include<iostream>
using namespace std;
template <typename T> class listOfObjects {
 public:
  T object;
  listOfObjects<T> *next;
  listOfObjects<T> *prev;
  
  // Constructor
  listOfObjects(T initValue) {object = initValue; next = prev = nullptr;}
  
  // Destructor
  ~listOfObjects() {;}
};
class Node{
    public:
        int value;
        int inDegree;
        int outDegree;
        int depTime;
        int cNumber;
        listOfObjects<Node> *parents;
        // bool isSource = false;
        Node(int value = -1){
            this->value = value;
            inDegree = 0;
            outDegree = 0;
            depTime = -1;
            parents = nullptr;
        }
};
class Graph{
    public:
        int num_nodes;
        int** adjMatrix;
        int** collapsedadjMatrix;
        int *arrTime;
        int *depTime;
        bool *visited;
        bool *visitedCopy;
        Node *nodes;
        int numSourceNodes;
        int** similarityRelation;
        int *components;
        listOfObjects<Node> *SourceNodes;
        int time;
        Graph(int num_nodes){
            this->num_nodes = num_nodes;
            adjMatrix = new int*[num_nodes];
            similarityRelation = new int*[num_nodes];
            arrTime = new int[num_nodes];
            depTime = new int[num_nodes];
            visited = new bool[num_nodes];
            visitedCopy = new bool[num_nodes];
            collapsedadjMatrix = new int*[num_nodes];
            components = new int[num_nodes];
            time = 0;
            for(int i = 0; i<num_nodes; i++){
                adjMatrix[i] = new int[num_nodes];
                similarityRelation[i] = new int[num_nodes];
                collapsedadjMatrix[i] = new int[num_nodes];
                for(int j = 0; j < num_nodes; j++){
                    adjMatrix[i][j] = 0;
                    similarityRelation[i][j] = 0;
                    collapsedadjMatrix[i][j] = 0;
                }
                arrTime[i] = -1;
                depTime[i] = -1;
                visited[i] = 0;
                visitedCopy[i] = 0;
                components[i] = -1;
            }
            nodes = new Node[num_nodes];
            numSourceNodes = 0;
            SourceNodes = nullptr;

        }
        void DFS(int v){
            visited[v] = 1;
            arrTime[v] = time++;
            for(int i = 0; i<num_nodes; i++){
                if(adjMatrix[v][i] == 1 && visited[i]==0){
                    DFS(i);
                }
            }
            nodes[v].depTime = time;
            depTime[v] = time++;
        }
        void printsimilarityMatrix(){
            for(int i = 0; i<num_nodes; i++){
                for(int j=0; j<num_nodes; j++){
                    cout<<similarityRelation[i][j]<<" ";
                }
                cout<<endl;
            }
        }
        void DFSFindComponent(int v, int &var){
            visited[v] = 1;
            // arrTime[v] = time++;
            var = max(var, v);
            for(int i = 0; i<num_nodes; i++){
                if(similarityRelation[v][i] == 1 && visited[i]==0){
                    var = max(var, i);
                    DFSFindComponent(i,var);
                }
            }
            // nodes[v].depTime = time;
            // depTime[v] = time++;
        }
        void DFSAssignComponent(int v, int &var){
            visitedCopy[v] = 1;
            // arrTime[v] = time++;
            // var = max(var, v);
            components[v] = var;
            for(int i = 0; i<num_nodes; i++){
                if(similarityRelation[v][i] == 1 && visitedCopy[i]==0){
                    // var = max(var, i);
                    components[i] = var;
                    DFSAssignComponent(i,var);
                }
            }
            // nodes[v].depTime = time;
            // depTime[v] = time++;
        }
};