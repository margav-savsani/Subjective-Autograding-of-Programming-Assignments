#ifndef GRAPH_H
#define GRAPH_H

#ifndef STD_HEADERS_H
#include "std_headers.h"
using namespace std;
#endif

template <typename T> class vector{
 private:
	T* a;
	int size;
	int n;

	void grow(){
		if(n>=size){
			size = 2*size;
			T* newa = new T[size];
			for(int i=0; i<n; i++){
				newa[i] = a[i];
			}
			a = newa;
			delete[] newa;
		}
	}
 public:
	vector(){
		size = 10;
		n = 0;
		a = new T[size];
	}

	bool insert(T k){
		if(find(k)) return false;
		grow();
        // dump();
		int p = 0;
		for(int i=0; i<n; i++){
			if(a[i]>=k){
				break;
			}
            p++;
		}
		for(int i=n; i>p; i--){
			a[i] = a[i-1];
		}
		a[p] = k;
		n++;
		return true;
	}

	bool find(T k){
		for(int i=0; i<n; i++){
			if(a[i] == k) return true;
		}
		return false;
	}

	T &operator[](int index){
		return a[index];
	}

	int getSize(){
		return n;
	}

	void dump(){
		for(int i=0; i<n; i++){
			cout << a[i] << " ";
		}
		cout << "\n";
	}

};

class Node {
 public:
	int value;

	// insert other fields and methods as appropriate
	vector<int> outNodes;
	vector<int> inNodes;
	vector<int> similarity;

	bool isSource = 1;
	bool isSink = 1;

	int similarityIndex = -1;

	bool operator>=(Node a){
		return (value >= a.value);
	}
};

class Graph {
	int numNodes;

	Node *nodes;

	// Add appropriate fields as necessary for your implementation
	void updateSimilarityIndex(int a, int b);

 public:
	Graph() {
		// Add appropriate code as necessary for your implementation
	}

	void makeGraph();
			
	~Graph(){
		delete[] nodes;
		// Add appropriate code as necessary for your implementation
	}

	// Add appropriate method declarations as necessary for your implementation
	void sourceNodes();
	void sinkNodes();
	void similarNodes();
	void allNodes();
	bool isSimilar(Node a, Node b);
	void collapse();
	void printSimilarity();
};

#endif
