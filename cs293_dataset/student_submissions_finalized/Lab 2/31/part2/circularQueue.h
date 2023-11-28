#include "planner.h"

bool DynamicQueue::isEmpty(){
	return (head==0 && tail==0);
}

bool DynamicQueue::isFull(){
	return (size()==N);
}


unsigned int DynamicQueue::size(){
	if(tail>head || (tail==0 && head==0))
		return (tail-head);	//circulation didnt happen(i.e same as linear-queue)
	else 
		return(N-head+tail); //circulation happened
}

bool DynamicQueue::QDelete(Journey *x){
	if(isEmpty())  //if empty, return false
		return false;
	*x = A[head];
	if(size()==1){
		head=0;
		tail=0;
	}
	else head++;
	return true;
}

void DynamicQueue::QInsert(Journey x){ //Insert Journey in the queue
	if(tail==N && !isFull()){ //if tail is at the end, but we have some space at the start of the array, then start filling that space, by making tail=0
		tail=0;		// this makes tail<head, unlike linear-queue
	}
	else if(isFull()){ //if isFull, then grow the array
		this->grow();
	}
	if(tail==0 && head==0){
		A[0]=x;
	}
	int i=head;
	bool p=false;
	while( i!=tail){       
		if(A[i].start>x.start){ //Insert at the suitable location so that the queue is increasing
			p=true;				//Insert and sort at the same time
			int j=tail;
			while(j>i){
				A[j]=A[j-1];
				j= (j-1+N)%N;
			}
			A[i]=x;
			break;
		}
		i = (i+1)%N;
	}

	if(p==false)
		A[tail]=x;
	tail++;

}

void DynamicQueue::grow(){
	if(head<tail){	//general case(i.e same as linearQueue)
		Journey *B = new Journey [nextSize()];	
		for(int i=0; i<N; i++){	// copy all the elements from A(initial array) to B(new array with increased size) index-wise
			B[i]=A[i];
		}
	 	 delete[] A; //deallocate memory of initial array(i.e where A is pointing to)
		A = B;		// Now, point A(initial array) to the new array(B)
		N = nextSize();
	}

	else {		// if circulation happened
		Journey *B = new Journey [nextSize()];
		int j=0;
		for(int i=head; i<N; i++){ //first copy elements one by one, from head to end of array, to B(new array pointer)  
			B[j]=A[i];
			j++;
		}
		for(int i=0; i<head; i++){// next copy elements one by one from index '0' to 'head-1', to B(new array) continuing the already existing elements
			B[j]=A[i];
			j++;
		}
		 delete[] A;//deallocate memory 
		A=B;	// A points to new array now
		head = 0;
		tail = N;
		N = nextSize();
	}
}

