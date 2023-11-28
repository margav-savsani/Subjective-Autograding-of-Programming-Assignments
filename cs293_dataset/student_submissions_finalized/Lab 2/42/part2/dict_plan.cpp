#ifndef DICTPLAN_CPP
#define DICTPLAN_CPP

#include "dict_plan.h"
#include "cstring"
#include <cmath>

char s[1] = {'\0'}; 
char t[1] = {(char)2};


int len_str(char key[]){
    int len = 0;
    for (int i=0;key[i] != '\0';i++){
        len+=1;
    }
    return len;
}

mySet::mySet(){
    N = DICT_SIZE;
    len = 0;
}

int mySet::find_next_index(double start, int sindex, int lindex){
    if (this->len == 0) return -1;
    
    if (lindex - sindex == 0){
        if (B[sindex].stime>=start) return sindex;
        else return -1;
    }
    if (lindex - sindex == 1){
        if (B[sindex].stime>=start) return sindex;
        if (B[sindex+1].stime>=start) return sindex+1;
        else return -1;
    }

    int mid = (sindex + lindex)/2;
    if (B[mid].stime > start){
        if (B[mid - 1].stime < start) return mid;
        else return find_next_index(start,sindex,mid - 1);
    }

    else if(B[mid].stime < start) {
        if (B[mid + 1].stime >= start) return (mid+1);
        else return find_next_index(start, mid + 1, lindex);
    }

    else if(B[mid].stime == start){
        int index = 1;
        while (mid - index >= sindex){
            if (B[mid - index].stime != start) return (mid - index + 1);
        }
        return sindex;
    }

    return -1;
    
}

bool mySet::put(Info inf){
    if (len == N) return false;
    int index = find_next_index(inf.stime, 0, this->len - 1);
    if (index == -1) {
        B[len] = inf;
    }
    else{
        for (int i=len-1;i>=index;i--){
            B[i+1] = B[i];
        }
        B[index] = inf;
    }
    len++;
    return true;
}

returnDetails mySet::query_station(char st1[], double start){
    returnDetails r1;
    int index = find_next_index(start,0,len - 1);
    if (index == -1){
        returnDetails nothing;
        nothing.len = 0;
        return nothing;
    }
    r1.len = len - index;
    for (int i=index;i<len;i++){
        r1.details[i - index] = B[i];
    }
    return r1;
}

Dictionary::Dictionary(){
    N = DICT_SIZE;
    for (int i=0;i<N;i++){
        strcpy(A[i].key,s);
    }
}

int Dictionary::hashValue(char key[]){
    int dummy = 0;
    int polyres = 0;
    int len = len_str(key);
    int m = 1000000009;
    int p = 11111;
    for (int i=len-1;i>=0;i--){
        polyres = (((polyres*p)%m) + key[i])%m;
    }
    double a1 = (std::sqrt(5) - 1)/2;
    int val = std::floor(N*(polyres*a1-std::floor(polyres*a1)));
    return val;

}

int Dictionary::findFreeIndex(char key[]){
    int index = hashValue(key);
    for (int j = index;j<DICT_SIZE+index;j++){
        int i = j%DICT_SIZE;
        if (std::strcmp(A[i].key,s) == 0) return i;
        if (std::strcmp(A[i].key,t) == 0) return i;
        if (std::strcmp(A[i].key,key) == 0) return i;
    }
    return -1;    
}

Entry* Dictionary::get(char key[]){
    int index = hashValue(key);
    int i = index;
    while (std::strcmp(A[index%DICT_SIZE].key,s) != 0 && (index - i < DICT_SIZE)){
        if(std::strcmp(A[index%DICT_SIZE].key,key) == 0)
            return &(A[index%DICT_SIZE]);
        index++;
    }
    return nullptr;
}

bool Dictionary::put(char key[], Info inf){
    int index = findFreeIndex(key);
    if (index == -1) return false;
    if (std::strcmp(A[index].key,s) == 0) strcpy(A[index].key,key);
    bool a = A[index].Details.put(inf);
    if (!a) return false;
    return true;
}

bool Dictionary::remove(char key[]){
    int index = hashValue(key);
    int i = index;
    while ((std::strcmp(A[index%DICT_SIZE].key,s) != 0) && (index - i < DICT_SIZE)){
        if(std::strcmp(A[index%DICT_SIZE].key,key) == 0)
            strcpy(A[index%DICT_SIZE].key,t);
            return true;
        index++;
    }
    return false;
}

returnDetails Dictionary::query_station(char st1[], double start){
    int index = findFreeIndex(st1);
    if (index == -1){
        std::cerr<<"The station does not exist"<<std::endl;
        returnDetails no_details;
        no_details.len = -1;
        return no_details;
    }
    if (std::strcmp(A[index].key,s) == 0) {
        std::cerr<<"The station does not exist"<<std::endl;
        returnDetails no_details;
        no_details.len = -1;
        return no_details;
    }
    returnDetails out_details = A[index].Details.query_station(st1,start);
    if (out_details.len == 0){
        std::cerr<<"There are no trains that fit your description"<<std::endl;
    }
    return out_details;
}

Info Dictionary::query_journey(char st1[], double start, char st2[]){
    Info inf;
    returnDetails r1 = query_station(st1,start);
    for (int i=0;i<r1.len;i++){
        char dest[32];
        strcpy(dest,r1.details[i].dest);
        if (strcmp(dest,st2) == 0){
            inf.stime = r1.details[i].stime;
            strcpy(inf.dest,"");
            inf.etime = -1;
            return inf;
        }
        double etime2 = r1.details[i].etime;
        returnDetails r2 = query_station(dest,etime2);
        for (int j=0;j<r2.len;j++){
            if (strcmp(r2.details[j].dest,st2) == 0){
                inf.stime = r1.details[i].stime;
                strcpy(inf.dest,dest);
                inf.etime = r2.details[j].stime;
                return inf;
            }
        }
    }
    std::cerr<<"No such journey exists"<<std::endl;
    inf.stime = -1;
    strcpy(inf.dest,"");
    inf.etime = -1;
    return inf;
}





#endif