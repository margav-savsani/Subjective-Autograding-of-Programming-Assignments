#include <bits/stdc++.h>

using namespace std;

class DynamicArray {
private:
    int capacity;  // Max capacity of the array
    int num_ele;  // Number of elements in the array
    int* arr;  // The array

    // Double the capacity of the array
    void grow() {
        int* new_arr = new int[2*capacity];
        memcpy(new_arr, arr, sizeof(int)*capacity);
        delete[] arr;
        arr = new_arr;
        capacity = 2*capacity;
    }

public:
    DynamicArray(int ini_sz=10) {
        arr = new int[ini_sz];
        num_ele = 0;
        capacity = ini_sz;
    }

    // Find k in array
    bool find(int k) {
        bool found { false };
        for (int i=0; i<num_ele; i++) found |= (arr[i] == k);
        return found;
    }

    // Returns the number of elements in the array
    int size() {
        return num_ele;
    }

    // Get the element at index idx
    int get(int idx) {
        return (idx > -1 && idx < num_ele ? arr[idx]:-1);
    }

    // Set the element at index idx to k
    void set(int idx, int k) {
        if (idx > -1 && idx < num_ele) arr[idx] = k;
    }

    // Add element k to the back of the array
    void add(int k) {
        if (num_ele == capacity) grow();
        arr[num_ele++] = k;
    }
};