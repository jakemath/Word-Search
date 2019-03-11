//
//  main.cpp
//  Word Search
//
//  Created by Jacob Mathai on 5/31/18.
//  Copyright © 2018 Jacob Mathai. All rights reserved.
//

#include <iostream>
#include <fstream>
#include "routines.h"

using std::cout;
using std::endl;

int main ()
{
    unordered_set<string> s;    // Write dictionary to unordered set
    string word;
    std::ifstream in;
    in.open ("words.txt");
    while (in >> word)
    {
        if (word.length() > 5)
            s.insert (word);
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
            cout << puzzle [i][j] << " "; // Print puzzle
        }
        cout << endl << endl;
    }
    p.close();
    set<match> output;  // Store matches in a set to sort alphabetically
    search (puzzle, s, output); // Search puzzle
    cout << "Words found, with corresponding coordinates: " << endl;
    for (set<match>::iterator i = output.begin(); i != output.end(); ++i)   // Iterate through the set
        cout << i -> word << ", from point " << i -> first_coordinate << " to point " << i -> second_coordinate << endl;
    cout << output.size() << " words." << endl;
}
