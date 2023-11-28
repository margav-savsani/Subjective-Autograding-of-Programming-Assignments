#include "journey.cpp"
#include "choose.h"

int array_quicksort(Journey* arr, int low, int high, int choice) {

    Journey* cur_pivot;
    if(choice==1) {
        cur_pivot=choose_one(arr, low, high);
    }
    if(choice==2) {
        cur_pivot=choose_two(arr, low, high);
    }
    if(choice==3) {
        cur_pivot=choose_three(arr, low, high);
    }
    if(choice==4) {
        cur_pivot=choose_four(arr, low, high);
    }

    if(low<high) {
        int cur_price=cur_pivot->getPrice();

        int left_index=low;
        int right_index=high;

        while(left_index<right_index) {
            while(cur_price>=arr[left_index].getPrice()) {
                left_index+=1;
            }
            while(cur_price<=arr[right_index].getPrice()) {
                right_index-=1;
            }
            if(right_index>left_index) {
                Journey temp=arr[right_index];
                arr[right_index]=arr[left_index];
                arr[left_index]=arr[right_index];
            }
        }

        Journey temp=*cur_pivot;
        *cur_pivot=arr[right_index];
        arr[right_index]=temp;
    }

    array_quicksort(arr, low, cur_pivot->getPrice()-1, choice);
    array_quicksort(arr, cur_pivot->getPrice()+1, high, choice);

}