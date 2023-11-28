
        In linearQueue grow function I used nextsize() to find length of the new queue. Then I used a for loop to copy elemnets into the new queue and deleted the old queue.
  In insert() I took 3 cases ,in the case where queue is full I used grow(),In case where tail is N I reaaranged the elements and then added,3rd case is straightforward.
        In circularQueue instead of filling queue upto onlt N-1 elements liked proffesor suggested in the videos ,I filled the queue upto N elemens and made the tail=N 
    only when queue is full.I did this by making tail=N in insert() when queue became full.
