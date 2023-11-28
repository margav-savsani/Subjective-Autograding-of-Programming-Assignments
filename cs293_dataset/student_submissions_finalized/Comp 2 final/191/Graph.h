template<typename T>
class ListNode{
public:
	ListNode<T>* next;
	ListNode<T>* prev;
	T value;
	ListNode(T n);
};

template<typename T>
class List{
public:
	ListNode<T>* start;
	ListNode<T>* end;
	List();
	void insert(T n);
	bool find(T n);
	void deleteFirst();
	T findMax();
	void deleteN(T n);
};

class Node{
public:
	int numOutEdges,numInEdges;
	List<int>* outEdges;
	List<int>* inEdges;
	int val;
	int level;
	List<int>* component;
	bool compCheck;
	Node();
};

class Graph{
public:
	int numberOfNodes;
	Node *node;
	List<int>** levelingSets;
	List<int>** similarNodes; 
	List<int>** eqSimilar;
	int maxLevel;
	List<List<int>*>* comp;
	int totalComp;
	
	Graph(int n); //constructor
	void insertEdge(int num1, int num2);
	void insertSimilarNodes(int num1, int num2);
	void printSourceNodes();
	void printSimilarNodes();
	void check3();
	void check2();
	void minLevel();
	void printLevel();
	void assignLevel();
	void findComp(int i, List<int>* l);
	void findCompMain();
	bool checkSimilarity(int i, int j);
	List<int>* findSource();
};
