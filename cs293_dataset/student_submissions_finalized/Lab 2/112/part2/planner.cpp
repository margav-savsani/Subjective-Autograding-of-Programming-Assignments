#include "planner.h"
#include <cmath>
using namespace std;

Planner::Planner()
{
    N = DICT_SIZE;
    A = new struct Entry[N];
}

int Planner::hashValue(char key[])
{
    int x = 3;                // value of x in polynomial accumulartion
    long long integerKey = 0; // stringkey converted to int key

    for (int i = 0; key[i] != '\0'; i++)
    {
        integerKey = (integerKey * x) + key[i];
    }

    long double phi = (sqrt(5) - 1) / 2; // conjugat of golden ratio
    long double kA = integerKey * phi;
    long double intPart;
    double fracPart = modf(kA, &intPart);

    double floorMe = N * fracPart; // floor this number to get final hash

    modf(floorMe, &intPart);

    return round(intPart);
}

int Planner::findIndex(char key[])
{
    int initialHashValue = hashValue(key);
    int index = initialHashValue;

    while ((strcmp(key, A[index].S1) != 0) && (A[index].is_filled == true))
    {
        index = (index + 1) % N;
        if (index == initialHashValue)
        {
            return -1;
        }
    }
    return index;
}

int Planner::getIndex(char key[])
{
    int index = findIndex(key);
    if (A[index].is_filled)
    {
        return index;
    }
    else
    {
        return -1;
    }
}

void Planner::add(string str1, float dT, string str2, float aT) // dT stands for departure time and aT for arrival time
{
    char S1[32], S2[32];
    for (int i = 0; i < str1.length(); i++)
    {
        S1[i] = str1[i];
    }
    S1[str1.length()] = '\0';
    for (int i = 0; i < str2.length(); i++)
    {
        S2[i] = str2[i];
    }
    S2[str2.length()] = '\0';
    int entryIndex = findIndex(S1);
    if (!A[entryIndex].is_filled)
    {
        for (int i = 0; i < 32; i++)
        {
            A[entryIndex].S1[i] = S1[i];
        }
    }
    threeTuple addMe;
    addMe.departureTime = dT;
    addMe.arrivalTime = aT;
    for (int i = 0; i < 32; i++)
    {
        addMe.S2[i] = S2[i];
    }
    A[entryIndex].put(addMe, 0, A[entryIndex].length);

    A[entryIndex].is_filled = true;
    A[entryIndex].length += 1;
}

void Planner::qs(string str1, float dT, ofstream &outFile) // dT stands for departure time and aT for arrival time
{
    char S1[32];
    for (int i = 0; i < str1.length(); i++)
    {
        S1[i] = str1[i];
    }
    S1[str1.length()] = '\0';
    int index = getIndex(S1);
    if (index == -1)
    {
        outFile << "No station called " << str1 << endl;
        return;
    }
    int dTIndex = A[index].find(dT, 0, A[index].length);
    for (int i = dTIndex; i < A[index].length; i++)
    {
        outFile << A[index].fsf[i].departureTime << ' ' << A[index].fsf[i].S2 << endl;
    }
}

void Planner::qj(string str1, float dT, string str2, ofstream &outFile) // dT stands for departure time and aT for arrival time
{
    char S1[32], S2[32];
    for (int i = 0; i < str1.length(); i++)
    {
        S1[i] = str1[i];
    }
    S1[str1.length()] = '\0';
    for (int i = 0; i < str2.length(); i++)
    {
        S2[i] = str2[i];
    }
    S2[str2.length()] = '\0';

    float directTimes[DICT_SIZE]; // contains the departure times of all direct journeys from S1 to S2
    int nDirectJourneys = 0;      // number of direct journeys possible
    int S1Index = getIndex(S1);
    if (S1Index == -1)
    {
        outFile << "No paths exist" << endl;
        return;
    }
    for (int i = 0; i < A[S1Index].length; i++)
    {
        if ((strcmp(A[S1Index].fsf[i].S2, S2) == 0) && A[S1Index].fsf[i].departureTime >= dT)
        {
            directTimes[nDirectJourneys] = A[S1Index].fsf[i].departureTime;
            nDirectJourneys++;
        }
    }
    threeTuple indirectJourneys[DICT_SIZE];
    int ninDirectJourneys = 0; // number of indirect journeys possible
    for (int i = 0; i < A[S1Index].length; i++)
    {
        if (A[S1Index].fsf[i].departureTime < dT)
            continue;
        int S2Index = getIndex(A[S1Index].fsf[i].S2);
        if (S2Index == -1)
        {
            continue;
        }
        for (int j = 0; j < A[S2Index].length; j++)
        {
            if ((strcmp(A[S2Index].fsf[j].S2, S2) == 0) && A[S2Index].fsf[j].departureTime >= A[S1Index].fsf[i].arrivalTime) // also making sure he isnt present in 2 trains at once
            {
                indirectJourneys[ninDirectJourneys].departureTime = A[S1Index].fsf[i].departureTime;
                indirectJourneys[ninDirectJourneys].arrivalTime = A[S2Index].fsf[j].departureTime;
                for (int k = 0; k < 32; k++)
                {
                    indirectJourneys[ninDirectJourneys].S2[k] = A[S1Index].fsf[i].S2[k];
                }
                ninDirectJourneys++;
            }
        }
    }

    if (nDirectJourneys == 0 && ninDirectJourneys == 0)
    {
        outFile << "No paths exist" << endl;
        return;
    }
    int minimumDirectDepartureIndex = 0;
    if (nDirectJourneys != 0)
    {
        for (int i = 0; i < nDirectJourneys; i++)
        {
            if (directTimes[i] < directTimes[minimumDirectDepartureIndex])
            {
                minimumDirectDepartureIndex = i;
            }
        }
    }
    int minimumIndirectDepartureIndex = 0;
    if (ninDirectJourneys != 0)
    {
        for (int i = 0; i < ninDirectJourneys; i++)
        {
            if (indirectJourneys[i].departureTime < indirectJourneys[minimumIndirectDepartureIndex].departureTime)
            {
                minimumIndirectDepartureIndex = i;
            }
        }
    }
    if (nDirectJourneys == 0)
    {
        outFile << indirectJourneys[minimumIndirectDepartureIndex].departureTime << ' ' << indirectJourneys[minimumIndirectDepartureIndex].S2 << ' ' << indirectJourneys[minimumIndirectDepartureIndex].arrivalTime << endl;
        return;
    }
    if (ninDirectJourneys == 0)
    {
        outFile << directTimes[minimumDirectDepartureIndex] << endl;
        return;
    }
    if (indirectJourneys[minimumIndirectDepartureIndex].departureTime < directTimes[minimumDirectDepartureIndex])
    {
        outFile << indirectJourneys[minimumIndirectDepartureIndex].departureTime << ' ' << indirectJourneys[minimumIndirectDepartureIndex].S2 << ' ' << indirectJourneys[minimumIndirectDepartureIndex].arrivalTime << endl;
        return;
    }
    else
    {
        outFile << directTimes[minimumDirectDepartureIndex] << endl;
        return;
    }
}