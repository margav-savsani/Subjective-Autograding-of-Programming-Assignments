
#include<iostream>
using namespace std;
#include<string>
#include "dictionary.cpp"
#include<vector>
#include<fstream>
#include<sstream>
int main(){
    Dictionary dict;
    string line;
    string word;
    
    ifstream inFile("input3.txt");
    
    //create/use a vector instead of builit in array 
    vector<vector<string> > vec;

    while (getline(inFile, line, '\n'))
    {
        // create a temporary vector that will contain all the columns
        vector<string> tempVec;

        istringstream ss(line);

        // read word by word(or int by int)
        while (ss >> word)
        {
            // cout<<"word:"<<word<<endl;
            // add the word to the temporary vector
            tempVec.push_back(word);
        }
        // now all the words from the current line has been added to the temporary vector
        vec.__emplace_back(tempVec);
    }
    for(int i=0;i<vec.size();i++){
        if(vec[i][0]=="ADD") dict.add(vec[i][1],stof(vec[i][2]),vec[i][3],stof(vec[i][4]));
        else if(vec[i][0]=="QUERY_STATION") dict.station(vec[i][1],stof(vec[i][2]));
        else if(vec[i][0]=="QUERY_JOURNEY") dict.journey(vec[i][1],stof(vec[i][2]),vec[i][3]);
        else break;
    }
}