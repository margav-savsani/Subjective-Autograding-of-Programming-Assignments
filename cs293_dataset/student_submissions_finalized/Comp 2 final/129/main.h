#include <iostream>
using namespace std;
#include <string>
#include<fstream>
template <typename T>
class listOfObjects
{
public:
  T object;
  listOfObjects<T> *next;
  listOfObjects<T> *prev;

  // Constructor
  listOfObjects(T initValue)
  {
    object = initValue;
    next = prev = nullptr;
  }

  // Destructor
  ~listOfObjects() { ; }
};

class Node
{
public:
  int value;

  listOfObjects<int> *adjacenthead;
  listOfObjects<int> *adjacenttail;
  listOfObjects<int> * secondadjacenthead;
listOfObjects<int> * secondadjacenttail;
int from_counter ;


  // Node *predecessor;

  Node()
  {
    value = 0;

    adjacenthead = nullptr;
    adjacenttail = nullptr;
    secondadjacenthead = nullptr;
    secondadjacenttail = nullptr;
    from_counter = 0;


  }
  Node(int value)
  {
    this->value = value;

    adjacenthead = nullptr;
    adjacenttail = nullptr;
    secondadjacenthead = nullptr;
    secondadjacenttail = nullptr;
    from_counter = 0;
  }

  // insert other fields and methods as appropriate
};
class similarity{
    public:
    int a;
    int b;
    similarity *next;
    similarity(int x,int y){
        a = x;
        b = y;
        next = nullptr;
    }

};
class Queue_BFS{
    public:
            int x ;
            int level;
            Queue_BFS * next;
            Queue_BFS(){
                x = -1;
                next  = nullptr;
                level = 0;
            }
            Queue_BFS(int a,int l){
                x = a;
                next = nullptr;
                level = l;

            }

};
class level{
    public:
            int index;
            int level1;
            level *next;
            level(){
                index = -1;
                level1 = -1;
                next = nullptr;
            }
            level(int a ,int b){
                index = a;
                level1 = b;
                next = nullptr;
            }

};