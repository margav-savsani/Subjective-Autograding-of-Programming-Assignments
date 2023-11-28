#include <cmath>
#include<string.h>
#include "dictionary.h"
using namespace std;

int polyvalue(char key[])
{
	if (key[0] == '\0')
		return 0;
	else
		return (key[0] + 33 * polyvalue(&key[1])) % DICT_SIZE;
}

Dictionary::Dictionary()
{
	N = DICT_SIZE;
	A = new Entry[N];
}

int Dictionary::hashValue(char key[])
// Return the hash value (between 0 and N-1) of the given string; assume string is null terminated and of max length 32
{
	int polykey = polyvalue(&key[0]);
	double a = (polykey * (sqrt(5) - 1) / 2);
	return int(DICT_SIZE * (a - int(a)));
}

int Dictionary::findFreeIndex(char key[])
{
	int h = hashValue(key);
	for (int i = 0; i < N; i++)
	{
		int a = (h + i) % DICT_SIZE;
		if (!(A[a]).occupied)
			return a;
	}
	return -1;
}



Entry *Dictionary::get(char key[])
{
	int h = hashValue(key);
	for (int i = 0; i < N; i++)
	{
		int a = (h + i) % DICT_SIZE;
		if (A[a].occupied)
			if (!strcmp(A[a].key, key))
				return &A[a];
		else if (!A[a].tombstone) continue;
		else break;
	}
	return NULL;
}

bool Dictionary::put(struct Entry e)
{
	int a = findFreeIndex(e.key);
	if (a == -1)
		return false;
	else
	{
		e.occupied = true;
		e.tombstone = true;
		A[a] = e;
		return true;
	}
}

bool Dictionary::remove(char key[])
{
	Entry *h = get(key);
	if (h == NULL)
		return false;
	else
	{
		h->occupied = false;
	}
	return true;
}
