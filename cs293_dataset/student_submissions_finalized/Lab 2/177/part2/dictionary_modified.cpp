#include <cmath>
#include "dictionary_modified.h"
#include <string>
const double Fibb = 0.61803;

// Start of helper functions

int char_to_int (char a){ // To convert a char to its ASCII value
    return (int)a;
}

int string_to_key(int x, std::string st){ // A recursive function for polynomial accumulation, with user-defined value for the polynomial variable
    if(st.length() == 1) return char_to_int(st[0]);
    else {
        std::string tmp;
        tmp.resize(st.size() - 1);
        for (int i = 0; i < st.length() -1; i++) tmp[i] = st[i+1];
        return char_to_int(st[0]) + x*string_to_key(x, tmp)%100000; // This remainder was taken as digits of higher power have no effect due to multiplication with a double with only 5 significant digits after decimal
    }
}

int hash_code_map(std::string st){ // Just string_to_key, the variable is set to 31
    return string_to_key(57637,st);
}

int compression_map(std::string st){ // Compresses the key obtained from a string to an integer within the size of the table
    double tmp = Fibb*hash_code_map(st);
    return floor(DICT_SIZE * (tmp - floor(tmp)));
}

template <typename T> int size_of_dict(Entry<T>* A){ // A very specific function, only to be used within Dictionary functions
    int count = 0;
    for (int i = 0; i < DICT_SIZE; i++){
        if (A[i].marker == 1) count++;
    }
    return count;
}

bool string_compare(std::string st1, std::string st2){ // Compares two strings for equality
    if (st1.length() != st2.length()) return false;
    else {
        for (int i = 0; i < st1.length(); i++){
            if (st1[i] != st2[i]) return false;
        }
    }
    return true;
}

// End of helper functions

// Definitions of functions declared in header file

template <typename T> Dictionary<T>::Dictionary(){
    N = DICT_SIZE;
    A = new Entry<T>;
}

template <typename T> int Dictionary<T>::hashValue(std::string key){
    return compression_map(key);
}

template <typename T> int Dictionary<T>::findFreeIndex(std::string key){
    if (size_of_dict<T>(A) == DICT_SIZE) return -1;
    int probe = hashValue(key);
    while (A[probe].marker == 1) probe = (probe + 1) % N;
    return probe;
}

template <typename T> Entry<T>* Dictionary<T>::get(std::string key){
    int probe = hashValue(key);
    while (A[probe].marker != -1){
        if (A[probe].marker == 1) {if (string_compare(A[probe].key, key)) return A + probe;}
        probe = (probe + 1) % DICT_SIZE;
        if (probe == hashValue(key)) break; // No element found, we reached starting point again. Break. 
    }
    return NULL;
}

template <typename T> bool Dictionary<T>::put(Entry<T> e){
    if (size_of_dict<T>(A) == DICT_SIZE) return false;
    else{
        int probe = hashValue(e.key);
        while (A[probe].marker == 1) probe = (probe + 1) % N;
        A[probe] = e;
        A[probe].marker = 1;
    }
    return true;
}

template <typename T> bool Dictionary<T>::remove(std::string key){
    int probe = hashValue(key);
    while (A[probe].marker != -1){
        if (A[probe].marker == 1){
            if (string_compare(A[probe].key,key)) {A[probe].marker = 0; return true;}
            else probe = (probe + 1) % N;
        }
        if (probe == hashValue(key)) break;
    }
    return false;
}