#ifndef HEAP_H
#define HEAP_H

#ifndef STD_HEADERS
#include "std_headers.h"
#endif

using namespace std;

template<class T>
struct listNode{
  T obj;
  listNode* next;
  listNode* prev;
  

  listNode(T obj){
    this->obj = obj;
  }


};

template<class T>
struct LinkedList{
  listNode<T> * head;
  listNode<T> * tail;
  int length;
  

  LinkedList(){
    this->head = nullptr;
    this->tail = nullptr;
    this->length = 0;
  }

  void insert(listNode<T> * newNode){
    if (head == nullptr){
      head = tail = newNode;
      length++;
    } else {
      tail->next = newNode;
      newNode->prev = tail;
      tail = newNode; 
      length++;
    }
  }


};

template <typename T> class TreeNode {
 public:
  T object;
  TreeNode<T> *left;
  TreeNode<T> *right;
  TreeNode<T> *parent;

  //additional attributes defined for validating heap.
  int level;
  int numNodes;

  TreeNode(T initObj) {
    object = initObj;
    left = right = parent = nullptr;
    level = 1;
    numNodes = 1;
  }
  ~TreeNode(){;};
};

template <typename T> class Heap {
  TreeNode<T>* root;

 public:
  Heap() {root = nullptr;}
  ~Heap();

  void insert(T obj);
  T delMax();
  T getMax() {return root->object;}
  void printHeap(TreeNode<T> *node);
  //  void displayAboveThresh(int thresh);
};
#endif

