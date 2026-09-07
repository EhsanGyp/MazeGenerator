#include <iostream>
#include <vector>

#include "MazeGen.h"

std :: vector < std :: vector <char> > MazeInit()
{
    int MazeRow;
    int MazeCol;

    std :: cout << "Enter Numbers of Rows: " << std :: endl << std :: flush;
    std :: cin >> MazeRow;
    
    std :: cout << "Enter Numbers of Columns: " << std :: endl << std :: flush;
    std :: cin >> MazeCol;

    if(MazeRow < 0 || MazeCol < 0)
    {
        std :: cerr << "Invalid input. Rows and Columns can't be negative!" << std :: endl;
        return {};
    }

    std :: vector < std :: vector <char> >  Maze (MazeRow, std :: vector <char>  (MazeCol, '#'));  

    return Maze;
}

MazeCell DefStart(std :: vector < std :: vector <char> > & Maze)
{
    MazeCell Start;

    std :: cout << "Enter start row: " << std :: endl;
    std :: cin >> Start.Row;

    std :: cout << "Enter start col: " << std :: endl;
    std :: cin >> Start.Col;

    if((Start.Row > Maze.size() || Start.Row < 0) || (Start.Col > Maze[0].size() || Start.Col < 0)) 
    {
        std :: cerr << "Invalid start coordinate!" << std :: endl;
        return {};
    }
    return Start;
}

void ExploreNeighbor(std :: vector < std :: vector <char> > & Maze, MazeCell & Current)
{
    int UD[4] = {-1, 1, 0, 0};
    int LR[4] = {0, 0, -1, 1};

    for(int i = 0; i < 4; i ++)
    {
        int NewRow = Current.Row + UD[i];
        int NewCol = Current.Col + LR[i];

        if(NewRow < Maze.size() && NewRow >= 0 && NewCol < Maze[0].size() && NewCol >= 0)
        {
           MazeCell Neighbor; 

           Neighbor.Row = NewRow;
           Neighbor.Col = NewCol;
           
           /* push neighbor in stack :D */

        }   
    }
}

void DfsBackTracking(std :: vector < std :: vector <char> > & Maze, MazeCell start)
{
    std :: vector <bool> Visited (Maze.size() * Maze[0].size());

}

//int main()
//{
//    std :: vector < std :: vector <char> > Maze = MazeInit();
//    
//    return 0;
//}
