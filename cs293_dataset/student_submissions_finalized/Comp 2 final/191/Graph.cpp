#include "Graph.h"

template<typename T>
ListNode<T>::ListNode(T n){
	value = n;
	prev = nullptr;
	next = nullptr;
}

template<typename T>
void List<T>::insert(T n){
	if(start == nullptr){
		start = new ListNode<T>(n);
		end = start;
		end->next = nullptr;
	}
	else{
		end->next = new ListNode<T>(n);
		end->next->prev  = end;
		end = end->next;
		end->next = nullptr;
	}
}

template<typename T>
void List<T>::deleteN(T n){
	auto curr = start;
	if(curr->value == n){
		deleteFirst();
	}
	else if(end->value != n){
		curr = curr->next;
		while(curr != nullptr){
			if(curr->value == n){
				curr->prev->next = curr->next;
				curr->next->prev = curr->prev;
				delete curr;
				break;
			}
			curr = curr->next;
		}
	}
	else if(end->value == n){
		end = end->prev;
		delete end;
		end->next = nullptr;
	}	
}

template<typename T>
T List<T>::findMax(){
	if(start == nullptr)
		return T();
	auto curr = start;
	auto max = start->value;
	while(curr!=nullptr){
		if(curr->value > max){
			max = curr->value;
		}
		curr = curr->next;
	}
	return max;
}	

template<typename T>
void List<T>::deleteFirst(){
	if(start == nullptr){
		return;
	}	
	else{
		if(start->next == nullptr){
			delete start;
			start = end = nullptr;
		}
		else{
			start = start -> next;
			delete start->prev;
			start->prev = nullptr;
		}
	}
}

template<typename T>
bool List<T>::find(T n){
	auto curr = start;
	while(curr != nullptr){
		if(curr->value == n)
			return true;
		curr = curr->next;
	}
	return false;
}

template<typename T>
List<T>::List(){
	start = nullptr;
	end = nullptr;
}

Node::Node(){
	inEdges = new List<int>();
	outEdges = new List<int>();
	numInEdges = 0;
	numOutEdges = 0;
	level = -1;
	component = new List<int>;
	compCheck = false;
}

Graph::Graph(int n){
	node = new Node[n];
	numberOfNodes = n;
	for(int i=0;i<n;i++){
		node[i].val = i+1;
	}
	similarNodes = new List<int>*[n];
	eqSimilar = new List<int>*[n];
	for(int i=0;i<n;i++){
		similarNodes[i] = new List<int>();
		eqSimilar[i] = new List<int>();
	}
	comp = new List<List<int>*>;
	totalComp = 0;
}

void Graph::insertEdge(int num1, int num2){
	if(node[num1-1].outEdges->find(num2))
		return;
	node[num1-1].outEdges->insert(num2);
	node[num2-1].inEdges->insert(num1);
	node[num1-1].numOutEdges++;
	node[num2-1].numInEdges++;
}

void Graph::insertSimilarNodes(int num1, int num2){	
	if(similarNodes[num1-1]->find(num2))
		return;
	similarNodes[num1-1]->insert(num2);
	eqSimilar[num1-1]->insert(num2);
	eqSimilar[num2-1]->insert(num1);
}

void Graph::printSourceNodes(){
	auto x = levelingSets[0]->start;
	cout << "Source Nodes : ";
	while(x!=nullptr){
		cout << x->value <<" " ;
		x = x->next;
	}
	cout << endl;
}

void Graph::check3(){
	for(int i = 0;i<numberOfNodes;i++){
		if(node[i].numInEdges == 1){
			insertSimilarNodes(i+1, node[i].inEdges->start->value);
		}
	}
}

bool Graph::checkSimilarity(int i, int j){
	auto curr1 = node[i].inEdges->start;
	auto curr2 = node[j].inEdges->start;
	bool solution = true;
	if(similarNodes[i]->find(j+1) && similarNodes[j]->find(i+1))
		return false ;
	while(curr1 != nullptr){
		curr2 = node[j].inEdges->start;
		while(true){
			if(similarNodes[curr1->value-1]->find(curr2->value)){
				solution = true;
				break;
			}
			curr2 = curr2->next;
			if(curr2 == nullptr){
				solution = false;
				break;
			}	
		}
		if(!solution)break;
		curr1 = curr1->next;
	}
	
	if(!solution){
		return false;
	}
	
	curr1 = node[i].inEdges->start;
	curr2 = node[j].inEdges->start;
	
	while(curr2 != nullptr){
		curr1 = node[i].inEdges->start;
		while(true){
			if(similarNodes[curr2->value-1]->find(curr1->value)){
				solution = true;
				break;
			}
			curr1 = curr1->next;
			if(curr1 == nullptr){
				solution = false;
				break;
			}	
		}
		if(!solution)return false;
		curr2 = curr2->next;
	}
	
	if(solution){
		insertSimilarNodes(i+1,j+1);
		insertSimilarNodes(j+1, i+1);
		return true;
	}
	else{
		return false;
	}
}

void Graph::check2(){
	bool sol = false;
	do{
		sol = false;
		for(int i=0;i<numberOfNodes;i++){
			for(int j=0;j<numberOfNodes;j++){
				if(node[i].level != node[j].level)
					continue;
				if(node[i].numInEdges == 0){	
					break;
				}
				if(node[j].numInEdges == 0){
					continue;
				}
				sol = checkSimilarity(i, j);
				
			}
			if(sol)
				break;
		}
	}while(sol);
}

List<int>* Graph::findSource(){
	int i;
	List<int>* x = new List<int>;
	for (i=0;i<numberOfNodes;i++){
		if(node[i].numInEdges == 0){
			x->insert(i+1);
			node[i].level = 0;
		}
	}
	return x;
}

void Graph::minLevel(){
	auto x = findSource();
	auto y = x->start;
	while(y!=nullptr){
		int index = y->value-1;
		auto curr = node[index].outEdges->start;
		while(curr!=nullptr){
			if(node[curr->value-1].level==-1){
				node[curr->value-1].level = node[index].level+1;
				maxLevel = node[curr->value-1].level;
			}
			x->insert(curr->value);
			curr = curr->next;
		}
		x->deleteFirst();
		y = x->start;
	}	
}

void Graph::printSimilarNodes(){
	cout << "Similar Node Pairs : ";
	for(int i=0;i<numberOfNodes;i++){
		auto curr = similarNodes[i]->start;
		while(curr!=nullptr){
			cout << "("<<i+1<<","<<curr->value<<") ";
			curr = curr->next;
		}
	}
	cout << endl;
}

void Graph::assignLevel(){
	levelingSets = new List<int>*[maxLevel+1];
	for(int i=0;i<maxLevel+1;i++){
		levelingSets[i] = new List<int>;
	}
	for(int i=0;i<numberOfNodes;i++){
		levelingSets[node[i].level]->insert(i+1);
	}
}

void Graph::findComp(int i, List<int>* l){
	if(node[i].compCheck)
		return;
	node[i].compCheck = true;
	auto curr = eqSimilar[i]->start;
	l->insert(i+1);
	node[i].component = l;
	while(curr != nullptr){
		findComp(curr->value-1, l);
		curr = curr->next;
	}
}

void Graph::findCompMain(){
	for(int i=0;i<numberOfNodes;i++){
		if(node[i].compCheck)
			continue;
		auto l = new List<int>;
		findComp(i, l);
		comp->insert(l);
	}
	for(int i=0;i<numberOfNodes;i++){
		node[i].compCheck = false;
	}
	
	auto curr1 = comp->start;
	while(curr1!=nullptr){
		auto curr2 = curr1->value;
		int n = curr2->findMax();
		curr2->deleteN(n);
		curr2->insert(n);
		curr1 = curr1->next;
		totalComp++;
	}	
}

void Graph::printLevel(){
	for(int i=0;i<4;i++){
		auto c = eqSimilar[i]->start;
		while(c!=nullptr){
			cout << c->value << " ";
			c = c->next;
		}
		cout << endl;
	}
}

