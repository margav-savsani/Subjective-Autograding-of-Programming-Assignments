#ifndef QUICKSORT_CPP
#define QUICKSORT_CPP

#ifndef STD_HEADERS
#include "std_headers.h"
#endif

#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef DICTIONARY_H
#include "dictionary.h"
#endif

#ifndef CODES_H
#include "codes.h"
#endif

#include <cstdlib>

// less than or equal to comparison for TrainInfoPerStation objects
bool lte(TrainInfoPerStation *a, TrainInfoPerStation *b)
{
	int ia, ib;

	for (int i = 0; i < 7; ++i)
	{
		if (a->daysOfWeek[i])
		{
			ia = i;
		}

		if (b->daysOfWeek[i])
		{
			ib = i;
		}
	}

	if (ia < ib)
		return true;
	else if (ia > ib)
		return false;
	else
	{
		if (a->arrTime <= b->arrTime)
			return true;
		else
			return false;
	}
}

// less than comparison for TrainInfoPerStation objects
bool lt(TrainInfoPerStation *a, TrainInfoPerStation *b)
{
	int ia, ib;

	for (int i = 0; i < 7; ++i)
	{
		if (a->daysOfWeek[i])
		{
			ia = i;
		}

		if (b->daysOfWeek[i])
		{
			ib = i;
		}
	}

	if (ia <= ib)
		return true;
	else if (ia > ib)
		return false;
	else
	{
		if (a->arrTime < b->arrTime)
			return true;
		else
			return false;
	}
}

// Swapping "Values" of 2 nodes of a linked list
// Here I am not swapping the nodes, only values of nodes are being swapped
void swap(listOfObjects<TrainInfoPerStation *> *a, listOfObjects<TrainInfoPerStation *> *b)
{
	TrainInfoPerStation *temp = a->object;
	a->object = b->object;
	b->object = temp;
}

// Function for partitioning the linked list
// This function considers last node of the linked list as a pivot
// It then places pivot into it's correct position and then partitions the nodes around it
listOfObjects<TrainInfoPerStation *> *partition(listOfObjects<TrainInfoPerStation *> *l, listOfObjects<TrainInfoPerStation *> *h)
{
	// set pivot as h element
	TrainInfoPerStation *x = h->object;

	// similar to i = l-1 in an array implementation
	listOfObjects<TrainInfoPerStation *> *i = l->prev;

	// Similar to "for (int j = l; j <= h- 1; j++)"
	for (listOfObjects<TrainInfoPerStation *> *j = l; j != h; j = j->next)
	{
		if (lte(j->object, x))
		{
			// Similar to i++ for array
			i = (i == NULL) ? l : i->next;

			swap(i, j);
		}
	}
	i = (i == NULL) ? l : i->next; // Similar to i++
	swap(i, h);
	return i;
}

void Planner::Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList)
{
	// A few static variable declarations
	static int K = 4;				// Parameter to be experimented with

	static int recursionLevel = -1; // This can be used to find out at which
									// level of the recursion you are in

	static int N = 0;				// Total number of nodes present in the linked list

	static int start;				// starting index of array of size N/K (will be clear in further lines)
	static int end;					// ending index of array of size N/K (will be clear in further lines)

	static listOfObjects<TrainInfoPerStation *> **arr; 		// To create an array of size N/K

	// Increment recursion level on entering the function
	recursionLevel++;

	if (recursionLevel == 0)
	{
		// To count number of nodes in linked list
		listOfObjects<TrainInfoPerStation *> *ptr = stnInfoList;

		N = 0;

		while (ptr != nullptr)
		{
			N++;
			ptr = ptr->next;
		}

		// Creating an array of size N/K
		// Elements of this array will be pointer pointing to the nodes of linked list
		// Thus Linked list will be divided into N/K parts of K size each
		arr = new listOfObjects<TrainInfoPerStation *> *[N / K];

		ptr = stnInfoList;
		int count = 0;

		// Pointing after every K nodes
		while (ptr != nullptr)
		{
			count++;

			if (count % K == 0)
			{
				arr[count / K - 1] = ptr;
			}

			ptr = ptr->next;
		}
		
		// Setting static variables
		start = 0;
		end = N / K - 1;
	}

	// Put your code for the core of QuicksortSimple here

	// Base cases


	if (stnInfoList == nullptr)
	{
		if (recursionLevel == 0)
		{
			N = 0;
		}
		recursionLevel--;
		return;
	}
	else if (stnInfoList->next == nullptr)
	{
		if (recursionLevel == 0)
		{
			N = 0;
		}

		recursionLevel--;
		return;
	}

	// To store the index of pivot in the K size section
	int index_of_pivot;

	// Pointer to a particular K sized section
	listOfObjects<TrainInfoPerStation *> *pivot_generator;
	
	// None of the pointers in N/K sized array point to this section of linked list
	if (start == -1 || end == -1)
	{
		listOfObjects<TrainInfoPerStation *> *ptr = stnInfoList;

		int count = 0;

		while (ptr != nullptr)
		{
			count++;
			ptr = ptr->next;
		}

		index_of_pivot = rand() % (count) + 1;
		pivot_generator = stnInfoList;
	}
	// At least 1 points to this section
	else
	{	
		// Getting a random pointer to one of the K sized sections
		int index_of_ptr = rand() % (end - start + 1) + start;

		// If pointing to last section
		if (index_of_ptr == end)
		{
			int count = 0;
			listOfObjects<TrainInfoPerStation *> *ptr = arr[index_of_ptr];

			while (ptr != nullptr)
			{
				count++;
				ptr = ptr->next;
			}

			index_of_pivot = rand() % (count) + 1;
			pivot_generator = arr[index_of_ptr];
		}
		// If not the last section
		else
		{	
			index_of_pivot = rand() % (K) + 1;
			pivot_generator = arr[index_of_ptr];
		}
	}

	// Pointer to pivot
	listOfObjects<TrainInfoPerStation *> *pivot = pivot_generator;

	int num = 1;

	while (num != index_of_pivot)
	{
		pivot = pivot->next;
		num++;
	}

	// Pointer to last node of linked list
	listOfObjects<TrainInfoPerStation *> *tail = stnInfoList;

	while (tail->next != nullptr)
	{
		tail = tail->next;
	}

	// Putting pivot as the last node of linked list
	swap(tail, pivot);

	// Partitioning the linked list and storing pointer to pivot
	pivot = partition(stnInfoList, tail);

	// If pivot is single node
	if (pivot->prev == nullptr && pivot->next == nullptr)
	{
		if (recursionLevel == 0)
		{
			N = 0;
		}
		recursionLevel--;
		return;
	}
	// Pivot is the last node
	else if (pivot->next == nullptr && pivot->prev != nullptr)
	{	
		// De-linking the linked list
		pivot->prev->next = nullptr;

		// Getting appropriate start and end 
		int s = -1;
		int e = -1;

		if (start == -1 || end == -1)
		{
			s = -1;
			e = -1;
		}
		else
		{
			for (int i = start; i <= end; ++i)
			{
				if (lt(arr[i]->object, pivot->object))
				{
					s = i;
					break;
				}
			}

			for (int i = start; i <= end; ++i)
			{
				if (lte(pivot->object, arr[i]->object))
				{
					e = i - 1;
					break;
				}
				else if (i == end)
				{
					e = end;
					break;
				}
			}
		}
		start = s;
		end = e;
		Quicksort(stnInfoList);

		// Re-linking the linked list
		pivot->prev->next = pivot;
	}
	// Pivot is the first node
	else if (pivot->prev == nullptr && pivot->next != nullptr)
	{	
		// De-linking the linked list
		pivot->next->prev = nullptr;

		// Getting appropriate start and end
		int s = -1;
		int e = -1;

		if (start == -1 || end == -1)
		{
			s = -1;
			e = -1;
		}
		else
		{
			for (int i = start; i <= end; ++i)
			{
				if (lte(pivot->object, arr[i]->object))
				{
					s = i;
					break;
				}
			}

			e = end;
		}

		start = s;
		end = e;
		Quicksort(pivot->next);

		// Re-linking the linked list
		pivot->next->prev = pivot;
	}
	// Pivot is somewhere in middle
	else
	{	
		// De-linking the linked list
		pivot->prev->next = nullptr;
		pivot->next->prev = nullptr;

		// Getting appropriate start and end for both partitions
		int s1 = -1;
		int e1 = -1;

		int s2 = -1;
		int e2 = -1;

		if (start == -1 || end == -1)
		{
			// do nothing
		}
		else
		{
			for (int i = start; i <= end; ++i)
			{
				if (lt(arr[i]->object, pivot->object))
				{
					s1 = i;
					break;
				}
			}

			for (int i = start; i <= end; ++i)
			{
				if (lte(pivot->object, arr[i]->object))
				{
					e1 = i - 1;
					break;
				}
				else if (i == end)
				{
					e1 = end;
					break;
				}
			}

			for (int i = start; i <= end; ++i)
			{
				if (lte(pivot->object, arr[i]->object))
				{
					s2 = i;
					break;
				}
			}

			e2 = end;
		}
		start = s1;
		end = e1;

		// Recursive call on left partition
		Quicksort(stnInfoList);

		start = s2;
		end = e2;

		// Recursive call on right partition 
		Quicksort(pivot->next);

		// Re-linking the linked list
		pivot->prev->next = pivot;
		pivot->next->prev = pivot;
	}

	// ##########################################################################################################################

	if (recursionLevel == 0)
	{
		N = 0;
	}

	// Decrement recursion level before leaving the function
	recursionLevel--;
	return;


}

// Commented out implementation of QuicksortSimple

void Planner::QuicksortSimple(listOfObjects<TrainInfoPerStation *> *stnInfoList, int bruh1, int bruh2)
{
	// // A few static variable declarations
	// static int K = 4;				// Parameter to be experimented with
	// static int recursionLevel = -1; // This can be used to find out at which
	// 								// level of the recursion you are in
	// static int N = 0;

	// static int start;
	// static int end;

	// static listOfObjects<TrainInfoPerStation *> **arr;

	// // Increment recursion level on entering the function
	// recursionLevel++;

	// // If you need to set up additional storage (upto n/K TrainInfoPerStation
	// // elements), it's ok to do it *once* using static variables/array.
	// // Using the static recursionLevel, you can ensure that the storage
	// // allocation is done only the first time Quicksort is called, and not
	// // in every recursive call.
	// //
	// // Note that if you allocate space for upto n/K TrainInfoPerStation in
	// // each recursive call, you will end up using much more than n/K space
	// // overall.  So you MUST NOT allocate space in each recursive call.
	// //
	// // A variable/array defined using static is not created afresh in
	// // each recursive call.  Instead, a single copy of it is maintained
	// // across all recursions.

	// if (recursionLevel == 0)
	// {
	// 	// Allocate additional space for upto n/K TrainInfoPerStation objects
	// 	// if needed.
	// 	// Do other things that you may want to do only at the beginning
	// 	// as a pre-processing step.
	// 	listOfObjects<TrainInfoPerStation *> *ptr = stnInfoList;

	// 	while (ptr != nullptr)
	// 	{
	// 		N++;
	// 		ptr = ptr->next;
	// 	}

	// 	arr = new listOfObjects<TrainInfoPerStation *> *[N / K];

	// 	ptr = stnInfoList;
	// 	int count = 0;

	// 	while (ptr != nullptr)
	// 	{
	// 		count++;

	// 		if (count % K == 0)
	// 		{
	// 			arr[count / K - 1] = ptr;
	// 		}

	// 		ptr = ptr->next;
	// 	}

	// 	start = 0;
	// 	end = N / K - 1;

	// 	for (int i = 0; i < N / K; ++i)
	// 	{
	// 		cout << arr[i] << endl;
	// 	}
	// }

	// // Put your code for the core of QuicksortSimple here

	// // ##########################################################################################################################

	// if (stnInfoList == nullptr)
	// {
	// 	if (recursionLevel == 0)
	// 	{
	// 		N = 0;
	// 	}
	// 	recursionLevel--;
	// 	return;
	// }
	// else if (stnInfoList->next == nullptr)
	// {
	// 	if (recursionLevel == 0)
	// 	{
	// 		N = 0;
	// 	}

	// 	recursionLevel--;
	// 	return;
	// }

	// int index_of_pivot;
	// listOfObjects<TrainInfoPerStation *> *pivot_generator;

	// if (start == -1 || end == -1)
	// {
	// 	listOfObjects<TrainInfoPerStation *> *ptr = stnInfoList;

	// 	int count = 0;

	// 	while (ptr != nullptr)
	// 	{
	// 		count++;
	// 		ptr = ptr->next;
	// 	}

	// 	index_of_pivot = rand() % (count) + 1;
	// 	pivot_generator = stnInfoList;
	// }
	// else
	// {
	// 	int index_of_ptr = rand() % (end - start + 1) + start;

	// 	if (index_of_ptr == end)
	// 	{
	// 		int count = 0;
	// 		listOfObjects<TrainInfoPerStation *> *ptr = arr[index_of_ptr];

	// 		while (ptr != nullptr)
	// 		{
	// 			count++;
	// 			ptr = ptr->next;
	// 		}

	// 		index_of_pivot = rand() % (count) + 1;
	// 		pivot_generator = arr[index_of_ptr];
	// 	}
	// 	else
	// 	{
	// 		index_of_pivot = rand() * (K) + 1;
	// 		pivot_generator = arr[index_of_ptr];
	// 	}
	// }

	// listOfObjects<TrainInfoPerStation *> *pivot = pivot_generator;

	// int num = 1;

	// while (num != index_of_pivot)
	// {
	// 	pivot = pivot->next;
	// 	num++;
	// }

	// listOfObjects<TrainInfoPerStation *> *tail = stnInfoList;

	// while (tail->next != nullptr)
	// {
	// 	tail = tail->next;
	// }

	// swap(tail, pivot);

	// pivot = partition(stnInfoList, tail);

	// if (pivot->prev == nullptr && pivot->next == nullptr)
	// {
	// 	if (recursionLevel == 0)
	// 	{
	// 		N = 0;
	// 	}
	// 	recursionLevel--;
	// 	return;
	// }
	// else if (pivot->next == nullptr && pivot->prev != nullptr)
	// {
	// 	pivot->prev->next = nullptr;

	// 	int s = -1;
	// 	int e = -1;

	// 	if (start == -1 || end == -1)
	// 	{
	// 		s = -1;
	// 		e = -1;
	// 	}
	// 	else
	// 	{
	// 		for (int i = start; i <= end; ++i)
	// 		{
	// 			if (lt(arr[i]->object, pivot->object))
	// 			{
	// 				s = i;
	// 				break;
	// 			}
	// 		}

	// 		for (int i = start; i <= end; ++i)
	// 		{
	// 			if (lte(pivot->object, arr[i]->object))
	// 			{
	// 				e = i - 1;
	// 				break;
	// 			}
	// 			else if (i == end)
	// 			{
	// 				e = end;
	// 				break;
	// 			}
	// 		}
	// 	}
	// 	start = s;
	// 	end = e;
	// 	QuicksortSimple(stnInfoList, s, e);

	// 	pivot->prev->next = pivot;
	// }
	// else if (pivot->prev == nullptr && pivot->next != nullptr)
	// {
	// 	pivot->next->prev = nullptr;

	// 	int s = -1;
	// 	int e = -1;

	// 	if (start == -1 || end == -1)
	// 	{
	// 		s = -1;
	// 		e = -1;
	// 	}
	// 	else
	// 	{
	// 		for (int i = start; i <= end; ++i)
	// 		{
	// 			if (lte(pivot->object, arr[i]->object))
	// 			{
	// 				s = i;
	// 				break;
	// 			}
	// 		}

	// 		e = end;
	// 	}

	// 	start = s;
	// 	end = e;
	// 	QuicksortSimple(pivot->next, s, e);

	// 	pivot->next->prev = pivot;
	// }
	// else
	// {
	// 	pivot->prev->next = nullptr;
	// 	pivot->next->prev = nullptr;

	// 	int s1 = -1;
	// 	int e1 = -1;

	// 	int s2 = -1;
	// 	int e2 = -1;

	// 	if (start == -1 || end == -1)
	// 	{
	// 	}
	// 	else
	// 	{
	// 		for (int i = start; i <= end; ++i)
	// 		{
	// 			if (lt(arr[i]->object, pivot->object))
	// 			{
	// 				s1 = i;
	// 				break;
	// 			}
	// 		}

	// 		for (int i = start; i <= end; ++i)
	// 		{
	// 			if (lte(pivot->object, arr[i]->object))
	// 			{
	// 				e1 = i - 1;
	// 				break;
	// 			}
	// 			else if (i == end)
	// 			{
	// 				e1 = end;
	// 				break;
	// 			}
	// 		}

	// 		for (int i = start; i <= end; ++i)
	// 		{
	// 			if (lte(pivot->object, arr[i]->object))
	// 			{
	// 				s2 = i;
	// 				break;
	// 			}
	// 		}

	// 		e2 = end;
	// 	}
	// 	start = s1;
	// 	end = e1;
	// 	QuicksortSimple(stnInfoList, s1, e1);

	// 	start = s2;
	// 	end = e2;
	// 	QuicksortSimple(pivot->next, s2, e2);

	// 	pivot->prev->next = pivot;
	// 	pivot->next->prev = pivot;
	// }

	// // ##########################################################################################################################

	// if (recursionLevel == 0)
	// {
	// 	N = 0;
	// }

	// // Decrement recursion level before leaving the function
	// recursionLevel--;
	// return;
}

#endif
