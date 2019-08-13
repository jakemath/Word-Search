# Word-Search
A program which reads a n X m word search puzzle from a txt file into an n X m 2-dimensional array and uses a dictionary stored in an unordered set to detect any words of length 6 or more. The program utilizes 8 different helper functions for detecting words in the directions up, down, left, right, upper left, upper right, lower left, and lower right. These functions are called based on the location of a given coordinate (i,j) relative to the edges of the array. The program records the starting (i,j) and ending (k,l) coordinates for any matches detected and stores them in a set in alphabetical order. 

Include a sample dictionary txt file and puzzle txt file which are used in main().

To run the code, place all the files in the same directory and enter:

    >>> g++ -std=c++2a main.cpp routines.h routines.cpp
    >>> ./a.out
    
The program will begin searching through the puzzle and will return all the matches with their respective coordinates.
