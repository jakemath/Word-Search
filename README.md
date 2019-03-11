# Word-Search
A program which reads a n X m word search puzzle from a txt file into an n X m 2-dimensional array and uses a dictionary stored in an unordered set to detect any words of length 6 or more. The program utilizes 8 different helper functions for detecting words in the directions up, down, left, right, upper left, upper right, lower left, and lower right. These functions are called based on the location of a given coordinate (i,j) relative to the edges of the array. The program records the starting and ending (i,j) coordinates for any matches detected and stores them in a set in alphabetical order. I've included a sample dictionary txt file and puzzle txt file which are used in main ().

To run the code:

    >>> g++ main.cpp routines.h routines.cpp
    >>> ./a.out
    
Assuming the dictionary.txt and puzzle.txt files are in the working directory, the program will begin searching through the puzzle and will return all the matches with their respective coordinates.
