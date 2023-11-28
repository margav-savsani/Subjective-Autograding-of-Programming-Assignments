#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#define GREY = 0
#define BLACK = -1
#define WHITE = 1

using namespace std;

void Planner::printDirectJourneys(string srcStnName, string destStnName)
{

  // insert your code here
  
  cout << "This function is to be implemented by you." << endl;



  return;
}

template <typename T>
class AdjacenyList{
	listOfObject<T> *node;
	listOfObject<T> *adjacent;
	int number = 0;
	
	AdjacenyList(){
		node = nullptr;
		adjacent = nullptr;
	}
	
	void BFS(T source){
		color_node_black(source);
		iterate(source.adjacent);
		iterate2(source.adjacent);
	}
	
	void color_node_black(T node){
		node.change_color(BLACK);
	}
	
	void color_node_white(T node){
		node.change_color(WHITE);
	}
	
	void color_node_gray(T node){
		node.change_color(GREY);
	}
	
	void iterate(T adjacent){
		number ++; 
		auto ptr = adjacent;
		while(ptr != nullptr){
			color_node_black(grey);
			ptr->number = number;
		}
	}
	
	void iterate2(T adjacent){
		auto ptr = adjacent;
		while(ptr != nullptr){
			iterate(ptr->adjacent);
		}
	}
};

class GraphNode{
	int object;
	int color;
	int number;
	listOfObject<GraphNode*> adjacent;
	
	change_color(int color){
		this->color = color;
	}
};


#endif
