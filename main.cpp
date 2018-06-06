//
//  main.cpp
//  Word Search
//
//  Created by Jacob Mathai on 5/31/18.
//  Copyright © 2018 Jacob Mathai. All rights reserved.
//

#include <iostream>

#include <fstream>

#include <unordered_set>

#include <set>

using namespace std;

const int m = 1389;

const int n = 45; // Global puzzle dimensions (can be adjusted for any m x n puzzle)

struct match    // Struct for word matches which contains the word itself as well as the coordinates the word is found at
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

void search (char puzzle [m][n], unordered_set<string>& s, set<match>& output); // Search function

void check_up (char puzzle [m][n], int i, int j, unordered_set<string>& s, set<match>& output);    // Helper functions for all 8 directions

void check_down (char puzzle [m][n], int i, int j, unordered_set<string>& s, set<match>& output);    // Use in search function

void check_left (char puzzle [m][n], int i, int j, unordered_set<string>& s, set<match>& output);

void check_right (char puzzle [m][n], int i, int j, unordered_set<string>& s, set<match>& output);

void check_lowright_diag (char puzzle [m][n], int i, int j, unordered_set<string>& s, set<match>& output);

void check_upright_diag (char puzzle [m][n], int i, int j, unordered_set<string>& s, set<match>& output);

void check_lowleft_diag (char puzzle [m][n], int i, int j, unordered_set<string>& s, set<match>& output);

void check_upleft_diag (char puzzle [m][n], int i, int j, unordered_set<string>& s, set<match>& output);

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

    set<match> output;  // Store matches in a set to sort alphabetically
    search (puzzle, s, output);
    cout << "Words found, with corresponding coordinates: " << endl;
    for (set<match>::iterator i = output.begin(); i != output.end(); ++i)   // Iterate through the set
    {
        cout << i -> word << ", from point " << i -> first_coordinate << " to point " << i -> second_coordinate << endl;
    }
    cout << output.size() << " words." << endl;
}

void search (char puzzle [m][n], unordered_set<string>& s, set<match>& output)
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
                    check_right (puzzle, i, j, s, output);  // Always can check right on left edge
                    if (i >= 5)     // If there's enough room for a 6+ letter word to fit above
                    {
                        check_up (puzzle, i, j, s, output);
                        check_upright_diag (puzzle, i, j, s, output);
                    }
                    if (m - i - 1 >= 5) // If there's enough room for a 6+ letter word to fit under
                    {
                        check_down (puzzle, i, j, s, output);
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
    string test = "";   // String to test for matches
    for (int k = i; k >= 0 && test.length() <= 45; --k)    // Check for match upward
    {
        test += puzzle [k][j];  // Add each char to test string
        if (test.length() >= 6 && test.length() <= 45)  // Only check for matches when word length is within the proper range
        {
            if (s.find (test) != s.end())    // If a match found --> put into set, record coordinate
            {
                match m;
                m.word = test;
                m.first_coordinate = "(" + std::to_string (j) + ", " + std::to_string (i) + ")";
                m.second_coordinate = "(" + std::to_string (j) + ", " + std::to_string (k) + ")";
                output.insert (m);
            }
        }
    }
}

void check_down (char puzzle [m][n], int i, int j, unordered_set<string>& s, set<match>& output)
{
    string test = "";
    for (int k = i; k < m && test.length() <= 45; ++k)    // Check for match downward
    {
        test += puzzle [k][j];  // Add each char to test string
        if (test.length() >= 6 && test.length() <= 45) // Only check for matches when word length is within the proper range
        {
            if (s.find(test) != s.end())    // If a match found --> insert into set
            {
                match m;
                m.word = test;
                m.first_coordinate = "(" + std::to_string (j) + ", " + std::to_string (i) + ")";
                m.second_coordinate = "(" + std::to_string (j) + ", " + std::to_string (k) + ")";
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
                m.first_coordinate = "(" + std::to_string (j) + ", " + std::to_string (i) + ")";
                m.second_coordinate = "(" + std::to_string (l) + ", " + std::to_string (i) + ")";
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
                m.first_coordinate = "(" + std::to_string (j) + ", " + std::to_string (i) + ")";
                m.second_coordinate = "(" + std::to_string (l) + ", " + std::to_string (i) + ")";
                output.insert (m);
            }
        }
    }
}

void check_lowright_diag (char puzzle [m][n], int i, int j, unordered_set<string>& s, set<match>& output)
{
    string test = "";
    for (int k = i, l = j; k < m && l < n && test.length() <= 45; ++k, ++l)
    {
        test += puzzle [k][l];  // Add char to test string
        if (test.length() >= 6 && test.length() <= 45) // Max length of word in dictionary is 45
        {
            if (s.find(test) != s.end())    // If a match found --> print the word and coordinate range, break loop
            {
                match m;
                m.word = test;
                m.first_coordinate = "(" + std::to_string (j) + ", " + std::to_string (i) + ")";
                m.second_coordinate = "(" + std::to_string (l) + ", " + std::to_string (k) + ")";
                output.insert (m);
            }
        }
    }
}

void check_upright_diag (char puzzle [m][n], int i, int j, unordered_set<string>& s, set<match>& output)
{
    string test = "";
    for (int k = i, l = j; k >= 0 && l < n && test.length() <= 45; --k, ++l)
    {
        test += puzzle [k][l];  // Add char to test string
        if (test.length() >= 6 && test.length() <= 45) // Max length of word in dictionary is 45
        {
            if (s.find(test) != s.end())    // If a match found --> print the word and coordinate range, break loop
            {
                match m;
                m.word = test;
                m.first_coordinate = "(" + std::to_string (j) + ", " + std::to_string (i) + ")";
                m.second_coordinate = "(" + std::to_string (l) + ", " + std::to_string (k) + ")";
                output.insert (m);
            }
        }
    }
}

void check_lowleft_diag (char puzzle [m][n], int i, int j, unordered_set<string>& s, set<match>& output)
{
    string test = "";
    for (int k = i, l = j; k < m && l >= 0 && test.length() <= 45; ++k, --l)
    {
        test += puzzle [k][l];  // Add char to test string
        if (test.length() >= 6 && test.length() <= 45) // Max length of word in dictionary is 45
        {
            if (s.find(test) != s.end())    // If a match found --> print the word and coordinate range, break loop
            {
                match m;
                m.word = test;
                m.first_coordinate = "(" + std::to_string (j) + ", " + std::to_string (i) + ")";
                m.second_coordinate = "(" + std::to_string (l) + ", " + std::to_string (k) + ")";
                output.insert (m);
            }
        }
    }
}

void check_upleft_diag (char puzzle [m][n], int i, int j, unordered_set<string>& s, set<match>& output) 
{
    string test = "";
    for (int k = i, l = j; k >= 0 && l >= 0 && test.length() <= 45; --k, --l)
    {
        test += puzzle [k][l];  // Add char to test string
        if (test.length() >= 6 && test.length() <= 45) // Max length of word in dictionary is 45
        {
            if (s.find(test) != s.end())    // If a match found --> print the word and coordinate range, break loop
            {
                match m;
                m.word = test;
                m.first_coordinate = "(" + std::to_string (j) + ", " + std::to_string (i) + ")";
                m.second_coordinate = "(" + std::to_string (l) + ", " + std::to_string (k) + ")";
                output.insert (m);
            }
        }
    }
}


