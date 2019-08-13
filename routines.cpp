//
//  routines.cpp
//  Word Search
//
//  Created by Jacob Mathai on 3/10/19.
//  Copyright © 2019 Jacob Mathai. All rights reserved.
//

#include "routines.h"

void check_up(vector<vector<char>>& puzzle, int i, const int j, unordered_set<string>& dict, set<match>& output)
{
    string test = "";   // String to test for matches
    for (int k = i; k >= 0 && test.length() <= 45; --k)    // Check for match upward
    {
        test += puzzle[k][j];  // Add each char to test string
        if (test.length() >= 6 && test.length() <= 45)  // Only check for matches when word length is within the proper range
        {
            if (dict.find(test) != dict.end())    // If a match found --> put into set, record coordinate
                output.insert(match(test, "(" + to_string(j) + ", " + to_string(i) + ")", "(" + to_string(j) + ", " + to_string(k) + ")"));
        }
    }
}

void check_down(vector<vector<char>>& puzzle, int i, const int j, unordered_set<string>& dict, set<match>& output)
{
    string test = "";
    for (int k = i; k < m && test.length() <= 45; ++k)    // Check for match down
    {
        test += puzzle[k][j];  // Add each char to test string
        if (test.length() >= 6 && test.length() <= 45) // Words range from 6 to 45 letters
        {
            if (dict.find(test) != dict.end())    // If a match found --> record coordinates, insert into set
                output.insert(match(test, "(" + to_string(j) + ", " + to_string(i) + ")", "(" + to_string(j) + ", " + to_string(k) + ")"));
        }
    }
}

void check_left(vector<vector<char>>& puzzle, const int i, int j, unordered_set<string>& dict, set<match>& output)
{
    string test = "";
    for (int l = j; l >= 0 && test.length() <= 45; --l)    // Check for a match to left
    {
        test += puzzle[i][l];  // Add char to test string
        if (test.length() >= 6 && test.length() <= 45)  // Words range from 6 to 45 letters
        {
            if (dict.find(test) != dict.end())    // If a match found --> record coordinates, insert into set
                output.insert(match(test, "(" + to_string(j) + ", " + to_string(i) + ")", "(" + to_string(l) + ", " + to_string(i) + ")"));
        }
    }
}

void check_right(vector<vector<char>>& puzzle, const int i, int j, unordered_set<string>& dict, set<match>& output)
{
    string test = "";
    for (int l = j; l < n && test.length() <= 45; ++l)    // Check for a match to right
    {
        test += puzzle[i][l];  // Add char to test string
        if (test.length() >= 6 && test.length() <= 45)  // Words range from 6 to 45 letters
        {
            if (dict.find(test) != dict.end())    // If a match found --> record coordinates, insert in set
                output.insert(match(test, "(" + to_string (j) + ", " + to_string(i) + ")", "(" + to_string(l) + ", " + to_string(i) + ")"));
        }
    }
}

void check_lowright_diag(vector<vector<char>>& puzzle, int i, int j, unordered_set<string>& dict, set<match>& output)
{
    string test = "";
    for (int k = i, l = j; k < m && l < n && test.length() <= 45; ++k, ++l) // Check for match to lower right diagonal
    {
        test += puzzle[k][l];  // Add char to test string
        if (test.length() >= 6 && test.length() <= 45) // Words range from 6 to 45 letters
        {
            if (dict.find(test) != dict.end())    // If a match found --> record coordinates, insert in set
                output.insert(match(test, "(" + to_string(j) + ", " + to_string(i) + ")", "(" + to_string(l) + ", " + to_string(k) + ")"));
        }
    }
}

void check_upright_diag(vector<vector<char>>& puzzle, int i, int j, unordered_set<string>& s, set<match>& output)
{
    string test = "";
    for (int k = i, l = j; k >= 0 && l < n && test.length() <= 45; --k, ++l)    // Check for match in upper right diagonal
    {
        test += puzzle[k][l];  // Add char to test string
        if (test.length() >= 6 && test.length() <= 45) // Words range from 6 to 45 letters
        {
            if (s.find(test) != s.end())    // If a match found --> record coordinates, insert in set
                output.insert(match(test, "(" + to_string(j) + ", " + to_string(i) + ")", "(" + to_string(l) + ", " + to_string(k) + ")"));
        }
    }
}

void check_lowleft_diag(vector<vector<char>>& puzzle, int i, int j, unordered_set<string>& s, set<match>& output)
{
    string test = "";
    for (int k = i, l = j; k < m && l >= 0 && test.length() <= 45; ++k, --l)    // Check for match to lower left diagonal
    {
        test += puzzle[k][l];  // Add char to test string
        if (test.length() >= 6 && test.length() <= 45) // Words range from 6 to 45 letters
        {
            if (s.find(test) != s.end())    // If a match found --> record coordinates, insert in set
                output.insert(match(test, "(" + to_string(j) + ", " + to_string(i) + ")", "(" + to_string(l) + ", " + to_string(k) + ")"));
        }
    }
}

void check_upleft_diag(vector<vector<char>>& puzzle, int i, int j, unordered_set<string>& dict, set<match>& output)
{
    string test = "";
    for (int k = i, l = j; k >= 0 && l >= 0 && test.length() <= 45; --k, --l)   // Check for match to upper left diagonal
    {
        test += puzzle[k][l];  // Add char to test string
        if (test.length() >= 6 && test.length() <= 45) // Words range from 6 to 45 letters
        {
            if (dict.find(test) != dict.end())    // If a match found --> record coordinates, insert in set
                output.insert(match(test, "(" + to_string(j) + ", " + to_string(i) + ")", "(" + to_string(l) + ", " + to_string(k) + ")"));
        }
    }
}

void search(vector<vector<char>>& puzzle, unordered_set<string>& dict, set<match>& output)
{
    int i, j;
    for (i = 0; i < m; ++i) // Row
    {
        for (j = 0; j < n; ++j) // Column
        {
            if (j == 0 || j == n - 1 || i == 0 || i == m - 1)   // If point is along an edge of array
            {
                if (j == 0) // If looking at left edge
                {
                    check_right(puzzle, i, j, dict, output);  // Always can check right on left edge
                    if (i >= 5)     // If room for a 6+ letter word to fit above
                    {
                        check_up(puzzle, i, j, dict, output);
                        check_upright_diag(puzzle, i, j, dict, output);
                    }
                    if (m - i - 1 >= 5) // If room for a 6+ letter word to fit under
                    {
                        check_down(puzzle, i, j, dict, output);
                        check_lowright_diag(puzzle, i, j, dict, output);
                    }
                }
                else if (j == n - 1) // If looking at right edge
                {
                    check_left(puzzle, i, j, dict, output);
                    if (i >= 5)  // If room for a 6 letter word to fit above
                    {
                        check_up(puzzle, i, j, dict, output);
                        check_upleft_diag (puzzle, i, j, dict, output);
                    }
                    if (m - i - 1 >= 5) // If room for a 6+ letter word to fit under
                    {
                        check_down(puzzle, i, j, dict, output);
                        check_lowleft_diag (puzzle, i, j, dict, output);
                    }
                }
                else if (i == 0)  // If looking at top edge
                {
                    check_down (puzzle, i, j, dict, output);
                    if (j >= 5)   // If room for a 6 letter word to fit to left
                    {
                        check_left(puzzle, i, j, dict, output);
                        check_lowleft_diag(puzzle, i, j, dict, output);
                    }
                    if (n - j - 1 >= 5) // If room for a 6+ letter word to fit to right
                    {
                        check_right(puzzle, i, j, dict, output);
                        check_lowright_diag(puzzle, i, j, dict, output);
                    }
                }
                else if (i == m - 1) // If looking at bottom edge
                {
                    check_up (puzzle, i, j, dict, output); // Check up
                    if (j >= 5)     // If  room for a 6 letter word to fit left and above
                    {
                        check_left(puzzle, i, j, dict, output);
                        check_upleft_diag(puzzle, i, j, dict, output);
                    }
                    if (n - j - 1 >= 5) // If  room for a 6+ letter word to fit right and above
                    {
                        check_right(puzzle, i, j, dict, output);
                        check_upright_diag(puzzle, i, j, dict, output);
                    }
                }
            }
            else    // Non-edge points
            {
                if (i >= 5) // If room above for word
                {
                    check_up(puzzle, i, j, dict, output);
                    if (j >= 5)     // If room left for word
                    {
                        check_left(puzzle, i, j, dict, output);
                        check_upleft_diag(puzzle, i, j, dict, output);
                    }
                    if (n - j - 1 >= 5)     // If room right and above for word
                    {
                        check_right(puzzle, i, j, dict, output);
                        check_upright_diag(puzzle, i, j, dict, output);
                    }
                }
                if (m - i - 1 >= 5)         // If room below for word
                {
                    check_down(puzzle, i, j, dict, output);
                    if (n - j - 1 >= 5) // If room right and below for word
                    {
                        check_right(puzzle, i, j, dict, output);
                        check_lowright_diag(puzzle, i, j, dict, output);
                    }
                    if (j >= 5)         // If room left and below for word
                    {
                        check_left(puzzle, i, j, dict, output);
                        check_lowleft_diag(puzzle, i, j, dict, output);
                    }
                }
                if (j >= 5)     // If room left for word
                {
                    check_left(puzzle, i, j, dict, output);
                    if (i >= 5)     // If room left and above for word
                    {
                        check_up(puzzle, i, j, dict, output);
                        check_upleft_diag(puzzle, i, j, dict, output);
                    }
                    if (m - i - 1 >= 5) // If room left and below for word
                    {
                        check_down(puzzle, i, j, dict, output);
                        check_lowleft_diag(puzzle, i, j, dict, output);
                    }
                }
                if (n - j - 1 >= 5)     // If room right for word
                {
                    check_right(puzzle, i, j, dict, output);
                    if (i >= 5)     // If room right and above for word
                    {
                        check_up(puzzle, i, j, dict, output);
                        check_upright_diag(puzzle, i, j, dict, output);
                    }
                    if (m - i - 1 >= 5)     // If room right and below for word
                    {
                        check_down(puzzle, i, j, dict, output);
                        check_lowright_diag (puzzle, i, j, dict, output);
                    }
                }
            }
        }
    }
}
