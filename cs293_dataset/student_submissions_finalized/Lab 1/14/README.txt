\
---------------------------------------------------------------------------------------Linear Queue------------------------------------------------------------------------------------------------------
	=> tail == head condition is checked to verify if it's empty
	=> to check if queue is full the condition tail - head == N is checked
	=> in grow() function
		-> a new queue is created
		-> elements of old array/queue got copied from head to tail-1
		-> deleting old queue to avoid storage waste
		-> gave the new queue to old queue name
		-> updated head, tail and N 
	=> size() is given by tail-head
	=> In insert function
		-> first it is checked whether the queue is full, if it is full then the queue will be grown and new element gets inserted
		-> if it isn't full but the head is not at 0 which specifies the case when
			-> the queue isn't full but tail is at the end and places at the start of the queue are empty 
		   all elements get shifted to the start and head and tail values get modified
		-> and the element gets inserted
	=> In Delete function
		-> if the queue is empty false is returned
		-> else A[head] is stored in *x 
		-> and all elements get pushed
		-> and true is returned
	
-------------------------------------------------------------------------------------Circular Queue-------------------------------------------------------------------------------------------------------
	=> tail == head condition is checked to verify if it's empty
	=> to check if queue is full the condition tail - head == N-1 is checked because 
		-> tail == head can imply 2 cases here empty or full
  		-> to avoid the possibility of full assuming that queue is full at the moment it's size reaches N-1
  	=> n grow() function
		-> a new queue is created
		-> elements of old array/queue got copied from head to tail-1
		-> deleting old queue to avoid storage waste
		-> gave the new queue to old queue name
		-> updated head, tail and N 
	=> size() is given by (N+tail-head)%N
	=> In insert function
		-> first it is checked whether the queue is full, if it is full then the queue will be grown and new element gets inserted
		-> if it is not full element is inserted at tail and tail gets increased
	=> In Delete function
		-> if the queue is empty false is returned
		-> else A[head] is stored in *x 
		-> and true is returned
----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	
		
