#include "dictionary.h"

#include <cmath>

static long double frac(long double x)
{
    return (x - floor(x));
}

// A[i].key[0] == '\0' => empty
// A[i].key[0] == '\a' => tombstone

Dictionary::Dictionary()
    : N(DICT_SIZE), A(new Entry[DICT_SIZE])
{
}

int Dictionary::hashValue(char key[])
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

int Dictionary::findFreeIndex(char key[])
{
    int h = hashValue(key);
    for (int i = h; i != (h + (N - 1)) % N; i = (i + 1) % N) {
        if (A[i].key[0] == '\0' || A[i].key[0] == '\a')
            return i;
    }
    return -1;
}

Entry* Dictionary::get(char key[])
{
    int h = hashValue(key);
    int i = h;
    for (i = h; i != (h + (N - 1)) % N; i = (i + 1) % N) {
        if (A[i].key[0] == '\0')
            break;
        else if (A[i].key[0] == '\a')
            continue;
        int j = 0;
        bool same = true;
        for (j = 0; A[i].key[j] != '\0' && key[j] != '\0'; j++) {
            if (A[i].key[j] != key[j]) {
                same = false;
                break;
            }
        }
        if (!same || A[i].key[j] != key[j]) {
            continue;
        }
        else {
            return (A + i);
        }
    }
    return nullptr;
}

bool Dictionary::put(Entry e)
{
    int i = findFreeIndex(e.key);
    if (i == -1)
        return false;
    A[i] = e;
    return true;
}

bool Dictionary::remove(char key[])
{
    Entry* e_ptr = get(key);
    if (e_ptr == nullptr) {
        return false;
    }
    else {
        e_ptr->key[0] = '\a';
        return true;
    }
}
