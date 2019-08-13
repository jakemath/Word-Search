//
//  main.cpp
//  Word Search
//
//  Created by Jacob Mathai on 5/31/18.
//  Copyright © 2018 Jacob Mathai. All rights reserved.
//

#include "routines.h"

int main()
{
    std::ifstream in("words.txt");
    unordered_set<string> dict;    // Write dictionary to unordered set
    string word;
    while (in >> word)
    {
        if (word.length() > 5)
            dict.insert(word);
    }
    in.close();
    std::ifstream p("puzzle.txt"); // Read puzzle txt file into 2D array
    vector<vector<char>> puzzle;
    for (int i = 0; i < m; ++i)
    {
        puzzle.push_back(vector<char>(m));
        for (int j = 0; j < n; ++j)
        {
            p >> puzzle[i][j];
            cout << puzzle[i][j] << " "; // Print puzzle
        }
        cout << endl;
    }
    p.close();
    cout << endl << "Solving... " << endl << endl;
    set<match> output;  // Store matches in a set to sort alphabetically
    search(puzzle, dict, output); // Search puzzle
    cout << "Words found, with corresponding coordinates: " << endl;
    for (set<match>::iterator i = output.begin(); i != output.end(); ++i) // Print results
        cout << i -> get_word() << ", from point " << i -> get_start() << " to point " << i -> get_end() << endl;
    cout << output.size() << " words." << endl;
}
