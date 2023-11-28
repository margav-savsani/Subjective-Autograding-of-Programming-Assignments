#include "dictionary.cpp"

void handler(Dictionary &dictionary)
{
    while (true)
    {
        char input[32];
        cin >> input;
        if (strcmp(input, "EXIT") == 0)  //exiting loop
        {
            break;
        }
        else if (strcmp(input, "ADD") == 0)  //adding
        {
            // string s1,s2;
            // float t1,t2;
            Entry J1;
            cin >> J1.station1 >> J1.starttime >> J1.station2 >> J1.finishtime;
            dictionary.put(J1);
        }
        else if (strcmp(input, "QUERY_STATION") == 0)  //queries for station
        {
            char s1[32];
            float t1;
            cin >> s1;
            cin >> t1;
            Entry *entry = dictionary.get(s1);
            if (entry == NULL)
                cout << "ERROR" << endl;
            
            else if (entry != NULL)
                dictionary.print(s1, t1);  //lists the trains
        }

        else if (strcmp(input, "QUERY_JOURNEY") == 0)
        {
            char s1[32], s2[32];
            float t1;
            cin >> s1 >> t1 >> s2;
            Entry *entry = dictionary.findpath(s1, s2, t1);
            if (entry == NULL)
                cout << "ERROR" << endl;
        }
    }
}
void interactive()
{
    cout << "Welcome to Train handling system \n";
    cout << "";
    Dictionary dictionary;
    handler(dictionary);
}

int main()
{
    interactive();  //interactive
}


