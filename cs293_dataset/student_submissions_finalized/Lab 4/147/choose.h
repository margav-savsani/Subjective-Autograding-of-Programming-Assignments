
// The following 4 are functions whose functionality has been hidden.
// You have been provided the compiled .o file (choose.o) for the same
// Link it while compiling your code to use the following functions

// x is the pointer to the array, start is the starting index and finish is the last index, 
// Please ensure start <= finish, start >= 0 and finish <= N-1

#include "journey.h" // changed from journey.cpp
#include <cstdlib>

Journey* choose_one(Journey* x, int start, int finish){
    return x + start;
}
Journey* choose_two(Journey* x, int start, int finish){
    return x + finish;
}
Journey* choose_three(Journey* x, int start, int finish){
    return x + start + rand() % (finish - start);
}
Journey* choose_four(Journey* x, int start, int finish){}
