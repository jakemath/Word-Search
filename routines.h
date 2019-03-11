//
//  routines.h
//  Word Search
//
//  Created by Jacob Mathai on 3/10/19.
//  Copyright © 2019 Jacob Mathai. All rights reserved.
//

#ifndef routines_h
#define routines_h

#include <string>
#include <unordered_set>
#include <set>

using std::string;
using std::set;
using std::unordered_set;

const int m = 1389;
const int n = 45; // Global puzzle dimensions (can be adjusted for any m x n puzzle)

struct match    // Struct for word matches which contains the word itself as well as the coordinates the word is found at
{
    string word;
    string first_coordinate;
    string second_coordinate;
    match (string w, string f, string s) : word(w), first_coordinate(f), second_coordinate(s) {}
};

bool operator < (const match& m1, const match& m2) { return (m1.word < m2.word); }

bool operator == (const match& m1, const match& m2);

void search (char puzzle [m][n], unordered_set<string>& s, set<match>& output); // Search function

void check_up (char puzzle [m][n], int i, const int j, unordered_set<string>& s, set<match>& output);    // Helper functions for all 8 directions

void check_down (char puzzle [m][n], int i, const int j, unordered_set<string>& s, set<match>& output);    // Use in search function

void check_left (char puzzle [m][n], const int i, int j, unordered_set<string>& s, set<match>& output);

void check_right (char puzzle [m][n], const int i, int j, unordered_set<string>& s, set<match>& output);

void check_lowright_diag (char puzzle [m][n], int i, int j, unordered_set<string>& s, set<match>& output);

void check_upright_diag (char puzzle [m][n], int i, int j, unordered_set<string>& s, set<match>& output);

void check_lowleft_diag (char puzzle [m][n], int i, int j, unordered_set<string>& s, set<match>& output);

void check_upleft_diag (char puzzle [m][n], int i, int j, unordered_set<string>& s, set<match>& output);

#endif /* routines_h */
