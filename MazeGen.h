#ifndef MAZEGEN_H
#define MAZEGEN_H

#include <iostream>
#include <vector>

typedef struct
{
    int Row;
    int Col;
} MazeCell;

std :: vector < std :: vector <char> > MazeInit();
MazeCell DefStart(std :: vector < std :: vector <char> > & Maze);
bool ExploreNeighbor(std :: vector < std :: vector <char> > & Maze, MazeCell & Current, std :: vector <std :: vector <bool> > * Visited, std :: vector <MazeCell> * Stack);
void DfsBackTracking(std :: vector < std :: vector <char> > & Maze, MazeCell Start);
void DisplayMaze(std :: vector < std :: vector <char> > & Maze, MazeCell & Current);

#endif
