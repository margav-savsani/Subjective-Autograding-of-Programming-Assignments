#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

int *Planner::computeHMatrixForKMP(string pattern) {
    int *h = new int[pattern.size() + 1]; // 1-indexed with a zero element
    if (!h) return nullptr;

    h[0] = -1; // to shorten the code and remove a separate if statement, see 213.Week5.kmp
    h[1] = 0;
    for (int i = 2; i <= pattern.length(); i++){
        // in this iteration we will compute h[i].

        int longest = h[i-1];

        // find the prefix of pattern that is also a suffix for p[1] .. p[i]. Note p is actually 0-indexed.
        while(longest >= 0 && toupper(pattern[longest]) != toupper(pattern[i-1])){
            longest = h[longest];
        }
        // h[i] = (longest > -1)? longest + 1: 0;
        h[i] = longest + 1;
    }
    return h;
}

// A simple KMP search for the first occurence of a pattern in a text. Returns the index of the start of the first occurence in the text if found, else -1.
int Planner::KMPMatch(string text, int *h, string pattern) {
    // cout << "hmat\n";
    // cout << "index\t|| h(i)\n";
    // for (int i = 1; i <= pattern.length(); i++) cout << i << "\t|| " << h[i] << endl;

    int index_looking_for = 0; // the index of the pattern that we are currently looking for.
    int start_of_pattern = 0; // the index in the text that the start of the pattern now aligns with

    // O(text) even though there are nested loops.
    while (start_of_pattern <= text.length() - pattern.length()){
        // find index (in pattern) of mismatch/full occurence
        while (index_looking_for < pattern.length() && toupper(text[start_of_pattern + index_looking_for]) == toupper(pattern[index_looking_for]))
            index_looking_for++;

        if (index_looking_for == pattern.length()){ return start_of_pattern; }

        start_of_pattern += index_looking_for - h[index_looking_for]; // \geq 1.
        if (index_looking_for > 0)
            index_looking_for = h[index_looking_for]; // indices before this have already been matched correctly, must check only from h[index_looking_for]. But index = 0 remains 0, does not go to -1.
    }
    return -1;
}

#endif
