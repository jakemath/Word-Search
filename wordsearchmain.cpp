//
//  main.cpp
//  Word Search
//
//  Created by  on 5/31/18.
//  Copyright © 2018  All rights reserved.
//

#include <iostream>

#include <fstream>

#include <string>

#include <unordered_set>

#include <set>

#include <map>

using std::set;

using namespace std;

const int m = 1389;

const int n = 45; // Global puzzle dimensions

struct match
{
    string word;
    string first_coordinate;
    string second_coordinate;
};

bool operator == (const match& m1, const match& m2) // Comparison operator for equivalence
{
    if (m1.word == m2.word && m1.first_coordinate == m2.first_coordinate && m1.second_coordinate == m2.second_coordinate)
        return true;
    return false;
}

bool operator < (const match& m1, const match& m2) { return (m1.word < m2.word); }  // Comparison operator for set ordering

void search (char puzzle [m][n], unordered_set<string>& s, set<match>& output);

void check_up (char puzzle [m][n], int i, int j, unordered_set<string>& s, set<match>& output);    // Helper functions for all 8 directions

void check_down (char puzzle [m][n], int i, int j, unordered_set<string>& s, set<match>& output);    // Use in search function

void check_lowright_diag (char puzzle [m][n], int i, int j, unordered_set<string>& s, set<match>& output);

void check_upright_diag (char puzzle [m][n], int i, int j, unordered_set<string>& s, set<match>& output);

void check_lowleft_diag (char puzzle [m][n], int i, int j, unordered_set<string>& s, set<match>& output);

void check_upleft_diag (char puzzle [m][n], int i, int j, unordered_set<string>& s, set<match>& output);

void check_left (char puzzle [m][n], int i, int j, unordered_set<string>& s, set<match>& output);

void check_right (char puzzle [m][n], int i, int j, unordered_set<string>& s, set<match>& output);

void search (char puzzle [m][n], unordered_set<string>& s, set<match>& output);

int main ()
{
    unordered_set<string> s;    // Write dictionary to unordered set
    string word;
    std::ifstream in;
    in.open ("words.txt");
    while (in >> word)
    {
        if (word.length() > 5)  // Trim any words less than 6 letters from dictionary to make search faster
        {
            s.insert (word);
        }
    }
    in.close();
    std::ifstream p;
    p.open ("puzzle.txt"); // Read puzzle txt file into 2D array
    char puzzle [m][n];
    for (int i = 0; i < m; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            p >> puzzle [i][j];
        }
    }
    p.close();
    set<match> output;
    search (puzzle, s, output);
    cout << endl << "Words found, with corresponding coordinates: " << endl;
    for (set<match>::iterator i = output.begin(); i != output.end(); ++i)   // Iterate through the set
    {
        cout << i -> word << ", from point " << i -> first_coordinate << " to " << i -> second_coordinate << endl;
    }
    cout << endl;
}

void search (char puzzle [m][n], unordered_set<string>& s, set<match>& output)
{
    int i, j;
    for (i = 0; i < m; ++i) // Row
    {
        for (j = 0; j < n; ++j) // Column
        {
            if (j == 0 || j == n - 1 || i == 0 || i == m - 1)
            {
                if (j == 0) // If looking at left edge
                {
                    check_right (puzzle, i, j, s, output);  // Always can check right on left edge
                    if (i >= 5)     // If there's enough room for a 6 letter word to fit above
                    {
                        check_up (puzzle, i, j, s, output);
                    }
                    if (m - i - 1 >= 5) // If there's enough room for a 6+ letter word to fit under
                    {
                        check_down (puzzle, i, j, s, output);
                    }
                    if (i >= 5 && n >= 6)     // If there's enough room for a 6+ letter in the upper right diagonal direction
                    {
                        check_upright_diag (puzzle, i, j, s, output);
                    }
                    if (m - i - 1 >= 5 && n >= 6)        // If there's enough room for a 6+ letter in the lower right diagonal direction
                    {
                        check_lowright_diag (puzzle, i, j, s, output);
                    }
                }
                else if (j == n - 1)     // If looking at right edge
                {
                    check_left(puzzle, i, j, s, output);
                    if (i >= 5)     // If there's enough room for a 6 letter word to fit above
                    {
                        check_up (puzzle, i, j, s, output);
                        check_upleft_diag (puzzle, i, j, s, output);
                    }
                    if (m - i - 1 >= 5) // If there's enough room for a 6+ letter word to fit under
                    {
                        check_down (puzzle, i, j, s, output);
                        check_lowleft_diag (puzzle, i, j, s, output);
                    }
                }
                else if (i == 0)     // If looking along top edge
                {
                    check_down (puzzle, i, j, s, output);
                    if (j >= 5)     // If there's enough room for a 6 letter word to fit to left
                    {
                        check_left (puzzle, i, j, s, output);
                        check_lowleft_diag(puzzle, i, j, s, output);
                    }
                    if (n - j - 1 >= 5) // If there's enough room for a 6+ letter word to fit to right
                    {
                        check_right (puzzle, i, j, s, output);
                        check_lowright_diag(puzzle, i, j, s, output);
                    }
                }
                else if (i == m - 1) // If looking at bottom edge
                {
                    check_up (puzzle, i, j, s, output); // Check up
                    if (j >= 5)     // If there's enough room for a 6 letter word to fit left and above
                    {
                        check_left (puzzle, i, j, s, output);
                        check_upleft_diag(puzzle, i, j, s, output);
                    }
                    if (n - j - 1 >= 5) // If there's enough room for a 6+ letter word to fit right and above
                    {
                        check_right (puzzle, i, j, s, output);
                        check_upright_diag(puzzle, i, j, s, output);
                    }
                }
            }
            else    // Non-edge points
            {
                if (i >= 5) // If room above for word
                {
                    check_up (puzzle, i, j, s, output);
                    if (j >= 5)     // If room left for word
                    {
                        check_left (puzzle, i, j, s, output);
                        check_upleft_diag(puzzle, i, j, s, output);
                    }
                    if (n - j - 1 >= 5)     // If room right and above for word
                    {
                        check_right (puzzle, i, j, s, output);
                        check_upright_diag(puzzle, i, j, s, output);
                    }
                }
                if (m - i - 1 >= 5)         // If room below for word
                {
                    check_down (puzzle, i, j, s, output);
                    if (n - j - 1 >= 5) // If room right and below for word
                    {
                        check_right (puzzle, i, j, s, output);
                        check_lowright_diag (puzzle, i, j, s, output);
                    }
                    if (j >= 5)         // If room left and below for word
                    {
                        check_left (puzzle, i, j, s, output);
                        check_lowleft_diag(puzzle, i, j, s, output);
                    }
                }
                if (j >= 5)     // If room left for word
                {
                    check_left (puzzle, i, j, s, output);
                    if (i >= 5)     // If room left and above for word
                    {
                        check_up (puzzle, i, j, s, output);
                        check_upleft_diag(puzzle, i, j, s, output);
                    }
                    if (m - i - 1 >= 5) // If room left and below for word
                    {
                        check_down (puzzle, i, j, s, output);
                        check_lowleft_diag(puzzle, i, j, s, output);
                    }
                }
                if (n - j - 1 >= 5)     // If room right for word
                {
                    check_right (puzzle, i, j, s, output);
                    if (i >= 5)     // If room right and above for word
                    {
                        check_up (puzzle, i, j, s, output);
                        check_upright_diag(puzzle, i, j, s, output);
                    }
                    if (m - i - 1 >= 5)     // If room right and below for word
                    {
                        check_down (puzzle, i, j, s, output);
                        check_lowright_diag (puzzle, i, j, s, output);
                    }
                }
            }
        }
    }
}

// Helper functions for each direction to check
void check_up (char puzzle [m][n], int i, int j, unordered_set<string>& s, set<match>& output)
{
    string test = "";
    for (int k = i; k >= 0 && test.length() <= 45; --k)    // Check for a match in vertical (reverse) direction up to edge
    {
        test += puzzle [k][j];  // Add char to test string
        if (test.length() >= 6 && test.length() <= 45)  // Max length of word in dictionary is 45
        {
            if (s.find(test) != s.end())    // If a match found --> put into set
            {
                match m;
                m.word = test;
                m.first_coordinate = "(" + std::to_string (i) + ", " + std::to_string (j) + ")";
                m.second_coordinate = "(" + std::to_string (k) + ", " + std::to_string (j) + ")";
                output.insert (m);
            }
        }
    }
}

void check_down (char puzzle [m][n], int i, int j, unordered_set<string>& s, set<match>& output)
{
    string test = "";
    for (int k = i; k < m && test.length() <= 45; ++k)    // Check for a match in vertical (reverse) direction up to edge
    {
        test += puzzle [k][j];  // Add char to test string
        if (test.length() >= 6 && test.length() <= 45) // Max length of word in dictionary is 45
        {
            if (s.find(test) != s.end())    // If a match found --> insert into set
            {
                match m;
                m.word = test;
                m.first_coordinate = "(" + std::to_string (i) + ", " + std::to_string (j) + ")";
                m.second_coordinate = "(" + std::to_string (k) + ", " + std::to_string (j) + ")";
                output.insert (m);
            }
        }
    }
}

void check_left (char puzzle [m][n], int i, int j, unordered_set<string>& s, set<match>& output)
{
    string test = "";
    for (int l = j; l >= 0 && test.length() <= 45; --l)    // Check for a match in vertical (reverse) direction up to edge
    {
        test += puzzle [i][l];  // Add char to test string
        if (test.length() >= 6 && test.length() <= 45)  // Max length of word in dictionary is 45
        {
            if (s.find(test) != s.end())    // If a match found --> insert into set
            {
                match m;
                m.word = test;
                m.first_coordinate = "(" + std::to_string (i) + ", " + std::to_string (j) + ")";
                m.second_coordinate = "(" + std::to_string (i) + ", " + std::to_string (l) + ")";
                output.insert (m);
            }
        }
    }
}

void check_right (char puzzle [m][n], int i, int j, unordered_set<string>& s, set<match>& output)
{
    string test = "";
    for (int l = j; l < n && test.length() <= 45; ++l)    // Check for a match in vertical (reverse) direction up to edge
    {
        test += puzzle [i][l];  // Add char to test string
        if (test.length() >= 6 && test.length() <= 45)  // Max length of word in dictionary is 45
        {
            if (s.find(test) != s.end())    // If a match found --> print the coordinate range
            {
                match m;
                m.word = test;
                m.first_coordinate = "(" + std::to_string (i) + ", " + std::to_string (j) + ")";
                m.second_coordinate = "(" + std::to_string (i) + ", " + std::to_string (l) + ")";
                output.insert (m);
            }
        }
    }
}

void check_lowright_diag (char puzzle [m][n], int i, int j, unordered_set<string>& s, set<match>& output)
{
    string test = "";
    int k = i, l = j;
    while (k < m && l < n && test.length() <= 45)     // Use while loop to increment l and decrement k co-iteratively
    {
        test += puzzle [k][l];  // Add char to test string
        if (test.length() >= 6 && test.length() <= 45) // Max length of word in dictionary is 45
        {
            if (s.find(test) != s.end())    // If a match found --> print the word and coordinate range, break loop
            {
                match m;
                m.word = test;
                m.first_coordinate = "(" + std::to_string (i) + ", " + std::to_string (j) + ")";
                m.second_coordinate = "(" + std::to_string (k) + ", " + std::to_string (l) + ")";
                output.insert (m);
            }
        }
        ++k;
        ++l;
    }
}

void check_upright_diag (char puzzle [m][n], int i, int j, unordered_set<string>& s, set<match>& output)
{
    string test = "";
    int k = i, l = j;
    while (k >= 0 && l < n && test.length() <= 45)     // Use while loop to increment l and decrement k co-iteratively
    {
        test += puzzle [k][l];  // Add char to test string
        if (test.length() >= 6 && test.length() <= 45) // Max length of word in dictionary is 45
        {
            if (s.find(test) != s.end())    // If a match found --> print the word and coordinate range, break loop
            {
                match m;
                m.word = test;
                m.first_coordinate = "(" + std::to_string (i) + ", " + std::to_string (j) + ")";
                m.second_coordinate = "(" + std::to_string (k) + ", " + std::to_string (l) + ")";
                output.insert (m);
            }
        }
        --k;
        ++l;
    }
}

void check_lowleft_diag (char puzzle [m][n], int i, int j, unordered_set<string>& s, set<match>& output)
{
    string test = "";
    int k = i, l = j;
    while (k < m && l >= 0 && test.length() <= 45)     // Use while loop to increment l and decrement k co-iteratively
    {                                                             // for traversing diagonally
        test += puzzle [k][l];  // Add char to test string
        if (test.length() >= 6 && test.length() <= 45) // Max length of word in dictionary is 45
        {
            if (s.find(test) != s.end())    // If a match found --> print the word and coordinate range, break loop
            {
                match m;
                m.word = test;
                m.first_coordinate = "(" + std::to_string (i) + ", " + std::to_string (j) + ")";
                m.second_coordinate = "(" + std::to_string (k) + ", " + std::to_string (l) + ")";
                output.insert (m);
            }
        }
        ++k;
        --l;
    }
}

void check_upleft_diag (char puzzle [m][n], int i, int j, unordered_set<string>& s, set<match>& output)
{
    string test = "";
    int k = i, l = j;
    while (k >= 0 && l >= 0 && test.length() <= 45)     // Use while loop to increment l and decrement k co-iteratively
    {
        test += puzzle [k][l];  // Add char to test string
        if (test.length() >= 6 && test.length() <= 45) // Max length of word in dictionary is 45
        {
            if (s.find(test) != s.end())    // If a match found --> print the word and coordinate range, break loop
            {
                match m;
                m.word = test;
                m.first_coordinate = "(" + std::to_string (i) + ", " + std::to_string (j) + ")";
                m.second_coordinate = "(" + std::to_string (k) + ", " + std::to_string (l) + ")";
                output.insert (m);
            }
        }
        --k;
        --l;
    }
}


