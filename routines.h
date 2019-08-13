//
//  routines.h
//  Word Search
//
//  Created by Jacob Mathai on 3/10/19.
//  Copyright © 2019 Jacob Mathai. All rights reserved.
//

#ifndef routines_h
#define routines_h

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_set>
#include <set>

using std::cout;
using std::endl;
using std::vector;
using std::string;
using std::to_string;
using std::set;
using std::unordered_set;

const int m = 1389;
const int n = 45; // Global puzzle dimensions (can be adjusted for any m x n puzzle)

// Struct for word matches containing start and end coordinates
class match
{
public:
    match(string w, string f, string s) : word(w), start(f), end(s) {}
    string get_word() const { return word; }
    string get_start() const { return start; }
    string get_end() const { return end; }
    bool operator < (const match& m) const { return (word < m.word); }
    bool operator == (const match& m) const { return word == m.word && start == m.start && end == m.end; }
private:
    string word;
    string start;
    string end;
};

// Function to solve puzzle
void search(vector<vector<char>>& puzzle, unordered_set<string>& dict, set<match>& output);

// Directional search functions
void check_up(vector<vector<char>>& puzzle, int i, const int j, unordered_set<string>& dict, set<match>& output);
void check_down(vector<vector<char>>& puzzle, int i, const int j, unordered_set<string>& dict, set<match>& output);
void check_left(vector<vector<char>>& puzzle, const int i, int j, unordered_set<string>& dict, set<match>& output);
void check_right(vector<vector<char>>& puzzle, const int i, int j, unordered_set<string>& dict, set<match>& output);
void check_lowright_diag(vector<vector<char>>& puzzle, int i, int j, unordered_set<string>& dict, set<match>& output);
void check_upright_diag(vector<vector<char>>& puzzle, int i, int j, unordered_set<string>& dict, set<match>& output);
void check_lowleft_diag(vector<vector<char>>& puzzle, int i, int j, unordered_set<string>& dict, set<match>& output);
void check_upleft_diag(vector<vector<char>>& puzzle, int i, int j, unordered_set<string>& dict, set<match>& output);

#endif /* routines_h */
