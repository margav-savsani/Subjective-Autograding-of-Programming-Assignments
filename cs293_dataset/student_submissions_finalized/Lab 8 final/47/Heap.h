#ifndef HEAP_H
#define HEAP_H


using namespace std;

template <typename T> class TreeNode {
 public:
  T object;
  TreeNode<T> *left;
  TreeNode<T> *right;
  TreeNode<T> *parent;

  TreeNode(T initObj) {
    object = initObj;
    left = right = parent = nullptr;
  }
  ~TreeNode() {;}
};

template <typename T> class Heap {
  TreeNode<T>* root;
  TreeNode<T>* last_element;
  int n = 0;

 public:
  Heap() {root = nullptr;}
  ~Heap() {;}

  void insert(T obj);
  void delMax();
  T getMax()// changed the function little bit, for taking care of case when root becomes null pointer.
  {
  if ( root == nullptr ) return Review();
  return root->object;
  }
  void printHeap(const string& prefix, bool isleft);
  //  void displayAboveThresh(int thresh);
};
#endif

