#include <cmath>
#include "dictionary.h"

int Dictionary::hashValue(char key[])
{
	int r;
	float a = (sqrt(5) - 1) / 2;
	float t = (sqrt(5) + 1) / 2;
	for (r = 0; r < 32; r++)
	{
		if (key[r] == '\0')
		{
			break;
		}
	}

	float v = 0;
	for (int i = r; i >= 1; i--)
	{

		v = ((int)key[i - 1] + v * 3 * t) * a;
		int v1 = v;
		v = v - v1;
	}

	int v2 = 64 * v;

	return v2; // Return the hash value (between 0 and N-1) of the given string; assume string is null terminated and of max length 32
}
Dictionary::Dictionary()
{
	N = 64; // Default constructor
	A = new Entry[64];
	for (int i = 0; i < 64; i++)
		A[i].ts = 'N';
}

int Dictionary::findFreeIndex(char key[])
{
	int h = hashValue(key);
	for (int i = h; i < 64; i++)
	{
		if (A[i].ts == 'T' || A[i].ts == 'N')
		{
			return i;
		}
	}
	for (int v = 0; v < h; v++)
	{
		if (A[v].ts == 'T' || A[v].ts == 'N')
		{
			return v;
		}
		if (v == h)
		{
			return -1;
		}
	} //  the position where given key can be inserted (after resolving hash collision if any); return value between 0 and N-1 if free location present; return -1 if no free location
}

bool Dictionary::put(struct Entry e)
{

	int f = findFreeIndex(e.key);
	if (f == -1)
	{
		return false;
	}
	for (int k = 0; k < 32; k++)
	{
		A[f].key[k] = e.key[k];
	}
	A[f].value = e.value;
	A[f].ts = 'F';
	return true; // Put the given entry in the appropriate location (using hashing) in the dictionary; return true if success, false if failure (array is full)
}
Entry *Dictionary::get(char key[])
{
	int h = hashValue(key);
	int i;
	while (A[h].ts != 'N')
	{
		for (int w = 0; w < 32; w++)
		{
			if (A[h].key[w] != key[w])
			{
				break;
			}
			if (A[h].key[w] == key[w])
			{
				if (key[w] != '\0')
				{
					continue;
				}
				else
				{
					return &A[h];
				}
			}
			h = (h + 1) % 64;
		}
		if (h == hashValue(key))
		{
			return NULL;
		}
	}

	return NULL; // Return the entry corresponding to given key, or NULL if the given key does not exist in the dictionary
}
bool Dictionary::remove(char key[])
{
	Entry *E;
	E = get(key);
	int i;
	for (i = 0; i < 64; i++)
	{
		if (E == &A[i])
		{
			for (int u = 0; u < 32; u++)
			{
				A[i].key[u] = 0;
			}
			A[i].ts = 'T';
			return true;
		}
	}
	if (i == 64)
	{
		return false; // Remove the given key; return true if success, false if failure (given key not present)
	}
}
