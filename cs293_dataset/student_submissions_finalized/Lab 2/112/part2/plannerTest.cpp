#include "planner.cpp"
#include <sstream>

int countWords(string cmd)
{
    istringstream iss(cmd);
    string word;
    int count = 0;
    while (iss >> word)
    {
        count++;
    }
    return count;
}

int main(int argc, char **argv)
{
    ifstream inFile(argv[1]);
    ofstream outFile(argv[2]);
    Planner myPlanner;
    while (true)
    {
        string cmd;
        getline(inFile, cmd);
        if (cmd.substr(0, 4) == "EXIT")
        {
            outFile << "ERROR";
            return 0;
        }
        istringstream iss(cmd);
        int nWords = countWords(cmd);
        string word[nWords];
        for (int i = 0; i < nWords; i++)
        {
            iss >> word[i];
        }
        if (word[0] == "ADD")
        {
            myPlanner.add(word[1], stof(word[2]), word[3], stof(word[4]));
        }
        else if (word[0] == "QUERY_STATION")
        {
            myPlanner.qs(word[1], stof(word[2]), outFile);
        }
        else if (word[0] == "QUERY_JOURNEY")
        {
            myPlanner.qj(word[1], stof(word[2]), word[3], outFile);
        }
    }
}