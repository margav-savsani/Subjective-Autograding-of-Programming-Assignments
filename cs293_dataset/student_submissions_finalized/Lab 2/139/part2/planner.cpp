#include "planner.h"
#include <iostream>
#include <cmath>
using namespace std;

Planner::Planner()
{
	N = 64;
	A = new Journey[N];
}

int Planner::hashvalue(Station S)
{
	long long unsigned int hash = 0, p = 33;
	double a = (sqrt(5) - 1) / 2.0;
	long p_degree = 1;
	int n = 0;
	while (S.name[n] != '\0')
	{
		n++;
	}
	for (int i = 0; i < n; ++i)
	{
		hash = (hash + S.name[i] * p_degree);
		p_degree = (p_degree * p);
	}
	int h = (N * ((a * hash) - int(a * hash)));
	return h % N;
}

int Planner::freeIndex(Journey j)
{
	int hash_value = hashvalue(j.station_one);
	for (int i = hash_value; i < N + hash_value; i++)
	{
		if (A[i % N].status == 0)
			return i % N;
	}
	return -1;
}

void Planner::insert(Journey j)
{
	int F = freeIndex(j);
	if (F >= 0)
	{
		cout << "freeIndex: " << F << endl;
		A[F] = j;
		A[F].status = 1;
		return;
	}
	cout << "Can't Insert Train, Size OverFlown" << endl;
}

void Planner::Query_Station(Station s, float time)
{
	bool Found = false;
	int hash_value = hashvalue(s);
	int index = hash_value % N;
	while (A[index % N].status == 1 && index < N + hash_value)
	{
		if ((strcmp(A[index % N].station_one.name, s.name) == 0) && (A[index % N].start_time > time))
		{
			cout << A[index % N].station_one.name << " " << A[index % N].start_time << " " << A[index % N].station_two.name << " " << A[index % N].finish_time << endl;
			if (!Found)
				Found = true;
		}
		index++;
	}
	if (!Found)
		cout << "Sorry, Can't find Trains" << endl;
}

void Planner::Query_Journey(Station s1, float start_time, Station s2)
{
	int hash_value = hashvalue(s1);
	bool intermediate = false;
	int index = hash_value % N;
	Journey j, j_intermediate;
	j.start_time = 9999;
	while (A[index % N].status == 1 && index < N + hash_value)
	{
		if ((strcmp(A[index % N].station_one.name, s1.name) == 0) && A[index % N].start_time > start_time)
		{
			if (j.start_time > A[index % N].start_time && strcmp(A[index % N].station_two.name, s2.name) == 0)
			{
				j = A[index % N];
				intermediate = false;
			}
			else if (j.start_time > A[index % N].start_time)
			{
				int hash_value_intermediate = hashvalue(A[index % N].station_two);
				int index_intermediate = hash_value_intermediate % N;
				while (index_intermediate < N + hash_value_intermediate)
				{
					if (strcmp(A[index_intermediate % N].station_one.name, A[index % N].station_two.name) == 0)
					{
						if (A[index_intermediate % N].start_time >= A[index % N].finish_time && strcmp(A[index_intermediate % N].station_two.name, s2.name) == 0)
						{
							j_intermediate = A[index_intermediate % N];
							intermediate = true;
							j = A[index % N];
						}
					}
					index_intermediate++;
				}
			}
		}
		index++;
	}
	if (j.start_time == 9999)
	{
		cout << "Sorry, Can't find trains" << endl;
		return;
	}
	if (intermediate)
	{
		cout << j.start_time << " " << j_intermediate.station_one.name << " " << j_intermediate.start_time << endl;
		return;
	}
	cout << j.start_time << endl;
}
