#include "dictionary.h"
#include <cmath>
using namespace std;
Dictionary::Dictionary(){
    N = 64; // size of array
    A = new Entry[N];
    for(int i=0; i<N; i++){
        A[i].key=NULL; // initializing every key to NULL
    }
}

int Dictionary::hashValue(char key[]){
    if(key == NULL) return -1;

    double euler=(sqrt(5)-1)/2; // used in fibonacci hashing

    int i=0, prehash=0; // defining variables for polynomial accumulation
    int factor=1;
    while(key[i]!='\0'){
        prehash += ((key[i])*factor) % 379931; // modulo division by large prime number,
        factor = (factor*41) % 379931;         // to avoid overflow
        i++;
    }
    float fibhash = prehash*euler - floor(prehash*euler); // fibonacci hashing
    fibhash = floor(fibhash*DICT_SIZE);
    int hash = fibhash;
    return hash;
}

int Dictionary::findFreeIndex(char key[]){
    if(strcmp(key,"tombstone") == 0){ // banning use of "tombstone" as a key
        cout << "ERROR: \"tombsone\" is a keyword, cannot use it as a key" << endl;
        return -1;
    }
    int hash = hashValue(key);
    int index = hash;
    while( A[index].key != NULL && strcmp(A[index].key, "tombstone")){ // both null pointers and tombstones denote free indices
        index = (index+1)%DICT_SIZE; 
        if(index == hash) return -1; // if index looped back to original position, array is full
    }
    return index;
}

struct Entry *Dictionary::get(char key[]){
    if(strcmp(key,"tombstone") == 0){ // banning use of "tombstone" as a key
        cout << "ERROR: \"tombsone\" is a keyword, cannot use it as a key" << endl;
        return NULL;
    }
    int hash = hashValue(key);
    int index = hash;
    while(A[index].key != NULL){
        if(strcmp(A[index].key, key) == 0){ // comparing key with each entry's key
            return A+index;
        }
        index = (index+1)%DICT_SIZE;
        if(index == hash) break; // dictionary full, key not found     
    }
    return NULL;
}

bool Dictionary::put(struct Entry &e){
    int index = findFreeIndex(e.key);
    if(index == -1) return 0;
    A[index].key = new char[30];
    strcpy(A[index].key, e.key);
    A[index].value = e.value; // inserting new entry at first valid index (can be tombstone or null entry)
    return 1;
}

bool Dictionary::remove(char key[]){
    struct Entry *e = get(key);
    if (e == NULL) return 0;
    strcpy(e->key,"tombstone"); // removing entry by changing key to "tombstone", dummy value used to denote tombstone
    return 1;
}

void Dictionary::getall(char key[], Journey *result, int &num_results, float start){
    if(strcmp(key,"tombstone") == 0){ // banning use of "tombstone" as a key
        cout << "ERROR: \"tombsone\" is a keyword, cannot use it as a key" << endl;
        return;
    }
    int hash = hashValue(key);
    int index = hash;
    while(A[index].key != NULL){
        if(strcmp(A[index].key, key) == 0 && A[index].value.start >= start){ // comparing key with each entry's key
            result[num_results] = (A+index)->value;
            num_results++;
        }
        index = (index+1)%DICT_SIZE;
        if(index == hash) break; // dictionary full, key not found     
    }
}

void Dictionary::FastestNonStop(char station1[], char station2[], float start, Journey *result, int &num_results, float &fastest){
    char mykey[30];
    strcpy(mykey, station1);
    int hash = hashValue(station1);
    if(hash == -1) return; // useful when processing null pointer
    int index = hash;
    int count = 0;
    while(A[index].key != NULL){
        if(strcmp(A[index].key, mykey) == 0 && A[index].value.start >= start                  // comparing all relevant fields 
        && strcmp(A[index].value.station2, station2) == 0 && A[index].value.start < fastest){ // of query and dictionary element
            result[0] = (A+index)->value; // stores value in result
            if(count == 0){
                num_results++; // increment number of results
                count = 1;
            }
            fastest = A[index].value.start; // update fastest possible journey time
        }
        index = (index+1)%DICT_SIZE; // moving to next possible index
        if(index == hash) break; // dictionary full, key not found
    }
}

void Dictionary::FastestOneStop(char station1[], char station2[], float start, Journey *result, int &num_results, float &fastest){
    FastestNonStop(station1, station2, start, result, num_results, fastest); // tries to find the fastest nonstop journey
    Journey *all_trains = new Journey[64];
    int num_all_trains=0;
    getall(station1, all_trains, num_all_trains, start); // store all trains leaving station1
    for(int i=0; i<num_all_trains; i++){
        Journey current_train = all_trains[i];
        if(current_train.start < fastest){ // to reduce unnecessary computation
            float fastest2 = 9999;

            // tries to find a direct train from the stop to the destination, if yes stores it in the result
            FastestNonStop(current_train.station2, station2, current_train.finish, result+1, num_results, fastest2);

            if(fastest2 != 9999){ // updates input variables if a faster one stop journey is possible
                fastest = current_train.start;
                result[0] = current_train;
                num_results = 2;
            }
        }
    }
    delete[] all_trains;
    return;
}