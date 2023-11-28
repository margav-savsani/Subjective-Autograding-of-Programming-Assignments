#ifndef DICTIONARY_TPP_HPP
#define DICTIONARY_TPP_HPP

#define NDEBUG

// size of key (including '\0')
#ifndef CHAR_ARRAY_SIZE
    #define CHAR_ARRAY_SIZE 32
#endif

#include <iostream>
#include <cmath>
#include <cstring>

template <typename T>
class Dictionary {
  private:
    // keys[i][0] == '\0' => empty
    // keys[i][0] == '\a' => tombstone
    
    static long double frac(long double x);
    
    unsigned int const N; // size of arrays
    char** keys; // Array of keys (char[CHAR_ARRAY_SIZE]s)
    T* values; // Array of values

  public:
    // Constructor and destructor
    Dictionary(unsigned int DICT_SIZE = 64);
    ~Dictionary();

    int hashValue(char const key[]);
    int findFreeIndex(char const key[]);
    int getIndex(char const key[]);

    bool put(char const key[], T value);
    T* get(char const key[]);
    bool remove(char const key[]);
};

template <typename T>
long double Dictionary<T>::frac(long double x)
{
    return (x - floor(x));
}

template <typename T>
Dictionary<T>::Dictionary(unsigned int DICT_SIZE)
    : N(DICT_SIZE), keys(new char*[DICT_SIZE]), values(new T[DICT_SIZE])
{
    for (int i = 0; i < N; i++) {
        keys[i] = new char[CHAR_ARRAY_SIZE];
        keys[i][0] = '\0';
    }
}

template <typename T>
Dictionary<T>::~Dictionary()
{
    for (int i = 0; i < N; i++) {
        delete[] keys[i];
    }
    delete[] keys;
    delete[] values;
}

// Return the hash value (between 0 and N-1) of the given string; assume string is null terminated and of max length CHAR_ARRAY_SIZE including '\0')
template <typename T>
int Dictionary<T>::hashValue(char const key[])
{
    int p = 31;
    long double phi = 0.5 * (sqrt(5) - 1);
    long double k = frac(phi * key[0]);
    for (int i = 1; key[i] != '\0'; i++) {
        k *= p;
        k += phi * key[i];
        k = frac(k);
    }

    return floor(N * k);
}

// Find the position where given key can be inserted (after resolving hash collision if any); return value between 0 and N-1 if free location present; return -1 if no free location
template <typename T>
int Dictionary<T>::findFreeIndex(char const key[])
{
    if (strlen(key) >= CHAR_ARRAY_SIZE) {
        throw -1;
    }

    int h = hashValue(key);
    for (int i = h; i != (h + (N - 1)) % N; i = (i + 1) % N) {
        if (keys[i][0] == '\0' || keys[i][0] == '\a')
            return i;
    }
    return -1;
}

// Return the index corresponding to given key, or -1 if the given key does not exist in the dictionary
template <typename T>
int Dictionary<T>::getIndex(char const key[])
{
    if (strlen(key) >= CHAR_ARRAY_SIZE) {
        throw -1;
    }

    int i = hashValue(key);
    for (; i != (hashValue(key) + (N - 1)) % N; i = (i + 1) % N) {
        if (keys[i][0] == '\0')
            break;
        else if (keys[i][0] == '\a')
            continue;
        int j = 0;
        bool same = (strcmp(keys[i], key) == 0);
        if (strcmp(keys[i], key) != 0) {
            continue;
        }
        else {
            return i;
        }
    }
    return -1;
}

// Put the given key-value pair in the appropriate location (using hashing) in the dictionary; return true if success, false if failure (array is full)
template <typename T>
bool Dictionary<T>::put(char const key[], T value)
{
    if (strlen(key) >= CHAR_ARRAY_SIZE) {
        throw -1;
    }

    int i = findFreeIndex(key);
#ifndef NDEBUG
    std::cout << "Hash value: " << hashValue(key) << '\n';
    std::cout << "Free index: " << i << '\n';
#endif
    if (i == -1)
        return false;
    int j = 0;
    strcpy(keys[i], key);
    values[i] = value;
    return true;
}

// Find the key, if found return pointer for corresponsing value, else return nullptr
template <typename T>
T* Dictionary<T>::get(char const key[])
{
    int i = getIndex(key);
    if (i == -1) {
        return nullptr;
    }
    else {
        return (values + i);
    }
}

// Remove the given key; return true if success, false if failure (given key not present)
template <typename T>
bool Dictionary<T>::remove(char const key[])
{
    int i = getIndex(key);
    if (i == -1) {
        return false;
    }
    else {
        keys[i][0] = '\a';
        return true;
    }
}

#endif
