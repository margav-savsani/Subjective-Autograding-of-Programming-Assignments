#include "queue.h"

 template <typename T> bool DynamicQueue<T>:: isEmpty(){
	if(head==tail){
		return true;}
	else{
		return false;}}
 template <typename T> bool DynamicQueue<T>:: isFull(){
 if ((N-head+tail)%N == N-1){
  return true;}
 else{
	return false; }}
 template <typename T> void DynamicQueue<T>:: grow(){
	T*B;
	B=new T[nextSize()];
	

	if (head!=0){
		for(int i=0; i<tail; i++){
			B[i]=A[i];}
		for(int i=0; i<N-head; i++){
			B[head+nextSize()-N+i]=A[head+i];}
		head=head+nextSize()-N;}
	else if (head==0){
		for(int i=0;i<N-1;i++){
			B[i]=A[i];}}
	N=nextSize();
	A=NULL;
	A=B;}


 template <typename T> unsigned int  DynamicQueue<T>:: size(){
	 		 
		return (N-head+tail)%N ;}
 template <typename T>  void DynamicQueue<T>:: QInsert(T x){

	 if(isFull()){
		 grow();
		 A[tail]=x;
		 tail++;}
	 
	 else if(head!=0&&tail==N-1){
		                  A[0]=x;
				                   tail=1;}{
		 A[tail]=x;
		 tail++;}}
 template <typename T> bool DynamicQueue<T>:: QDelete(T *x){
	  if(head==tail){
		 return false;}
 	 else{*x=A[head];
			 head++;
		return true;}}


