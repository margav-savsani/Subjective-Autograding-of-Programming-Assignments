#include <iostream>
#include "queue.h"
using namespace std;

 bool DynamicQueue<int>::isFull(){
  if(tail=N) return true;
  else return false;
 }
 bool isEmpty(){
  if(head==0)return true;
  else return false;
 }
 void grow(){
  if(N<nextSize()){
  N=N+1;}
 } 
 unsigned int size(){
  return N;
 } 
 void QInsert(T x){
  if(isFull()){
  cout << endl<< "Queue is full!!";}
  else if(head == 0) {
  unsigned int i;
  cin>>i;
  if(i < N){
  head = i;}}
  else{
  tail++;
  if(tail > N){
  grow();}
  myqueue[tail] = x;
  cout << x << " ";
  }
 }
 bool QDelete(T *x){
  if(isEmpty()){
   return false; } 
  else { x = myqueue[head]; if(head >= tail){      //only one element in queue
   head = tail= 0 ;}
   else {
   front++;} 
   return true;
  }
 }
}  
int main()
{
  DynamicQueue<int>& myq;
  myq.QDelete();
  myq.QInsert(&10);
  myq.QInsert(&20);
  myq.QInsert(&30);
  myq.size;
}  
#include <stdexcept>
#include <cstdlib>
#include <chrono>
#include "queue.h"

using namespace std;
using namespace std::chrono;

bool isFull(){
 if(tail=N) return true;
 else return false;
}
bool isEmpty(){
 if(head==0)return true;
 else return false;
}
void grow(){
 if(N<nextSize()){
 N=N+1;}
} 
unsigned int size(){
 return N;
} 
void QInsert(T x){
 if(isFull()){
 cout << endl<< "Queue is full!!";}
 else if(head == 0) {
 unsigned int i;
 cin>>i;
 if(i < N){
 head = i;}}
 else{
 tail++;
 if(tail > N){
 grow();}
 myqueue[tail] = x;
 cout << x << " ";
 }
}
bool QDelete(T *x){
 if(isEmpty()){
  return false; } 
 else { x = myqueue[head]; if(head >= tail){      //only one element in queue
  head = tail= 0 ;}
  else {
  front++;} 
  return true;
 }
} 
int main()
{
  DynamicQueue myq;
  myq.QDelete();
  myq.QInsert(&10);
  myq.QInsert(&20);
  myq.QInsert(&30);
  myq.size;
}
