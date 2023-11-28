# include "dictionary.h"
const double Fibonacci = .6180339887;



// Return the hash value (between 0 and N-1) of the given string; assume string is null terminated and of max length 32
template<typename T>
int Dictionary<T>::hashValue(char key[]){
    int size_of_key = 0;
    while (key[size_of_key] != '\0') size_of_key ++;
    int x = 33;
    long long int pow_x = 1;
    long long int result = 0;
    for (int i = 0; i < size_of_key; i++)
    {
        result += pow_x*(int)key[i];
        pow_x = (pow_x * x) % (long long int)(10000000000);
    }
    double temp = result * Fibonacci;
    double fractional_part = temp - (long long int) temp;
    int hash_value = (int)((double)N*fractional_part);
    return hash_value;        
}

// Find the position where given key can be inserted (after resolving hash collision if any); return value between 0 and N-1 if free location present; return -1 if no free location
template<typename T>
int Dictionary<T>::findFreeIndex(char key[]){
    int index = hashValue(key);
    int starting_point = index;
    while (strcmp(A[index].key,"")!= 0)
    {
        index = ++index % N;
        if (index == starting_point)
        {
            return -1;
        }
    }
    return index;
}

// Default constructor
template<typename T>
Dictionary<T>::Dictionary(){
    N = DICT_SIZE;
    A = new Entry<T>[N];
}

// template<typename T>
// Dictionary<T>::~Dictionary(){
//     delete[]A;
// }

// Return the entry corresponding to given key, or NULL if the given key does not exist in the dictionary
template<typename T>
struct Entry<T> *Dictionary<T>::get(char key[]){
    int index = hashValue(key);
    int starting_point = index;
    while (strcmp(A[index].key, key)!= 0)
    {
        index = ++index % N;
        if (index == starting_point || !(strcmp(A[index].key,"")!= 0 && A[index].IS_TUMBSTONE))
        {
            return NULL;
        }
    }
    return &A[index];
}

// Put the given entry in the appropriate location (using hashing) in the dictionary; return true if success, false if failure (array is full)
template<typename T>
bool Dictionary<T>::put(struct Entry<T> e){
    int index = hashValue(e.key);
    int starting_point = index;
    while (strcmp(A[index].key,"")!= 0)
    {
        index = ++index % N;
        if (index == starting_point)
        {
            return false;
        }
    }
    A[index] = e;
    return true;    
}

// Remove the given key; return true if success, false if failure (given key not present)
template<typename T>
bool Dictionary<T>::remove(char key[]){
    int index = hashValue(key);
    while (A[index].IS_TUMBSTONE || strcmp(A[index].key,"")!= 0)
    {
        if (strcmp(A[index].key,key)== 0)
        {
            strcpy(A[index].key,"");
            A[index].value = 0;
            int temp = (index+1)%N;
            if (A[temp].IS_TUMBSTONE or strcmp(A[temp].key,"")!= 0)
            {
                A[index].IS_TUMBSTONE = true;
            }
            else{
                A[index].IS_TUMBSTONE = false;
            }
            return true;
        }
        index = (index+1)%N;
    }
    return false;
}
