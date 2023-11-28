#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <cstring>
#include <cctype>
using namespace std;
class pair{
  int a;
  int b;
  pair(int a, int b){
    this->a = a;
    this->b = b;
  }
};

// Self implementation of
// the Vector Class in C++
template <typename T>
class vectorClass {
 
    // arr is the integer pointer
    // which stores the address of our vector
    T* arr;
    // capacity is the total storage
    // capacity of the vector
    int capacity;
    // current is the number of elements
    // currently present in the vector
    int current;
 
public:
    // Default constructor to initialise
    // an initial capacity of 1 element and
    // allocating storage using dynamic allocation
    vectorClass()
    {
        arr = new T[1];
        capacity = 1;
        current = 0;
    }
       //destructor to deallocate storage allocated by dynamic allocation
       //to prevent memory leak
    //   ~ vectorClass()
    // {
    //       delete [] arr;
    // }
 
    // Function to add an element at the last
    void push_back(T data)
    {
 
        // if the number of elements is equal to the
        // capacity, that means we don't have space to
        // accommodate more elements. We need to double the
        // capacity
        if (current == capacity) {
            T* temp = new T[2 * capacity];
 
            // copying old array elements to new array
            for (int i = 0; i < capacity; i++) {
                temp[i] = arr[i];
            }
 
            // deleting previous array
            delete[] arr;
            capacity *= 2;
            arr = temp;
        }
 
        // Inserting data
        arr[current] = data;
        current++;
    }
    void remove(int index){
        for(int i = index;i<current;i++){
            arr[i] = arr[i+1];
        }
        current--;
    }
    // function to add element at any index
    void push(T data, int index)
    {
 
        // if index is equal to capacity then this
        // function is same as push defined above
        if (index == capacity)
            push(data);
        else
            arr[index] = data;
    }
 
    // function to extract element at any index
    T get(int index)
    {
 
        // if index is within the range
        if (index < current)
            return arr[index];
    }
 
    // function to delete last element
    void pop() { current--; }
 
    // function to get size of the vector
    int size() { return current; }
 
    // function to get capacity of the vector
    int getcapacity() { return capacity; }
 
    // function to print array elements
    void print()
    {
        for (int i = 0; i < current; i++) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }
};

class Node {
 public:
  int value;
  bool isSource;
  vectorClass<int> toNode;
  vectorClass<int> fromNode;
  vectorClass<int> similar;
  Node(){
    isSource = true;
  }
};

class Graph {
   public:
  int numNodes;
  Node *nodes;
  vectorClass<int> source;
  vectorClass<int> leftSim;
  vectorClass<int> RightSim;
  fstream file;
  Graph(int nNodes, string gfile){
    numNodes = nNodes;
    file.open(gfile);
    nodes = new Node[numNodes];
    if (nodes == nullptr){
      cerr << "Memory allocation failure." << endl;
      exit(-1);
    }
    for (int i = 0; i < numNodes; i++) {
      nodes[i].value = i+1;
    }
  }
  void setsimilar(int a, int b);
  bool similar(int a, int b);
  void insert(int a, int b);
  void sourceNodes();
  void similarNodes();
};



