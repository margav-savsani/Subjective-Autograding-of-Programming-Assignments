#include <cmath>

using std::string;

const double Fibb = (sqrt(5)-1)/2;

int char_to_int (char a){
    return (int)a;
}

string char_arr_to_string(char c[]){
    int size = sizeof(c)/sizeof(char);
    string st;
    st.resize(size);
    for (int i = 0; i < size; i++){
      st[i] = c[i];
    }
    return st;
}

int string_to_key(int x, string st){
    if(st.length() == 1) return char_to_int(st[0]);
    else {
        string tmp;
        tmp.resize(st.size() - 1);
        for (int i = 0; i < st.length() -1; i++) tmp[i] = str[i+1];
        return char_to_int(st[0]) + x*string_to_key(tmp;)
    }
}

int hash_code_map(string st){
    return string_to_key(17,st);
}

int compression_map(string st){
    double tmp = Fibb*hash_code_map(st);
    return floor(N * (tmp - floor(tmp)));
}

int size_of_dict(){
    int count = 0;
    for (int i = 0; i < N; i++){
        if (A[i].marker == 1) count++;
    }
    return count;
}

int hashValue(char key[]){
    return compression_map(char_arr_to_string(key));
}

int findFreeIndex(char key[]){
    if (size_of_dict() == N) return -1;
    int probe = hashValue(key);
    while (A[probe].marker == 1) probe = (probe + 1) % N;
    return probe;
}

Entry* get(char key[]){
    int probe = hashValue(key);
    while (A[probe] != -1){
        if (A[probe].marker == 0) {probe = (probe + 1) % N; continue;}
        if (A[probe.marker == 1]) {if (strcmp(A[probe].key, char_arr_to_string(key)) == 0) return A + probe; else {probe = (probe + 1) % N; continue;};}
    }
    return NULL;
}

bool put(Entry e){
    if (size_of_dict == N) return false;
    else{
        int probe = compression_map(e.key);
        while (A[probe].marker == 1) probe = (probe + 1) % N;
        A[probe] = e;
        A[probe].marker = 1;
    }
    return true;
}

bool remove(char key[]){
    int probe = hashValue(key);
    while (A[probe].marker != -1){
        if (A[probe].marker == 1){
            if (strcmp(A[probe].key,char_arr_to_string(key)) == 0) {A[probe].marker == 0; return true;}
            else probe = (probe + 1) % N;
        }
        else continue;
    }
    return false;
}

struct Entry{
    string key;
    int marker = -1; // Marker is 1 if this entry is in Dict (occupied), 0 if this was deleted (tombstone), -1 if never added (null).
    int value;
};