#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <thread>

#include "MazeGen.h"

std :: vector < std :: vector <char> > MazeInit()
{
    int MazeRow;
    int MazeCol;

    std :: cout << "Enter Numbers of Rows: " << std :: endl << std :: flush;
    std :: cin >> MazeRow;
    
    std :: cout << "Enter Numbers of Columns: " << std :: endl << std :: flush;
    std :: cin >> MazeCol;

    if(MazeRow <= 0 || MazeCol <= 0)
    {
        std :: cerr << "Invalid input. Rows and Columns can't be negative!" << std :: endl;
        return {};
    }

    int RowRooms = (MazeRow + 1) / 2;
    int ColRooms = (MazeCol + 1) / 2;

    int ActualRows = (2 * RowRooms) - 1;
    int ActualCols = (2 * ColRooms) - 1;

    std :: vector < std :: vector <char> > Maze ( ActualRows, std :: vector <char>  (ActualCols, '#'));  

    return Maze;
}

MazeCell DefStart(std :: vector < std :: vector <char> > & Maze)
{
    MazeCell Start;

    std :: cout << "Enter start row: " << std :: endl;
    std :: cin >> Start.Row;

    std :: cout << "Enter start col: " << std :: endl;
    std :: cin >> Start.Col;

    if((Start.Row >= Maze.size() || Start.Row < 0) || (Start.Col >= Maze[0].size() || Start.Col < 0)) 
    {
        while((Start.Row >= Maze.size() || Start.Row <= 0) || (Start.Col >= Maze[0].size() || Start.Col <= 0))
        {
            std :: cerr << "Invalid start coordinate! Start point can not be on the edge!" << std :: endl;

            std :: cout << "Enter start row: " << std :: endl;
            std :: cin >> Start.Row;

            std :: cout << "Enter start col: " << std :: endl;
            std :: cin >> Start.Col;
        }
    }

    if(Start.Row % 2 != 0 || Start.Col % 2 != 0)
    {
        while(Start.Row % 2 != 0 || Start.Col % 2 != 0)
        {
            std :: cerr << "Invalid start coordinate! Row and Col must both be even numbers (0, 2, 4, ...)." << std :: endl;

            std :: cout << "Enter start row: " << std :: endl;
            std :: cin >> Start.Row;

            std :: cout << "Enter start col: " << std :: endl;
            std :: cin >> Start.Col;
        }
    }
    return Start;
}

bool ExploreNeighbor(std :: vector < std :: vector <char> > & Maze, MazeCell & Current, std :: vector <std :: vector <bool> > * Visited, std :: vector <MazeCell> * Stack)
{
    std :: vector <MazeCell> Candidates;

    int UD[4] = {-2, 2, 0, 0};
    int LR[4] = {0, 0, -2, 2};

    for(int i = 0; i < 4; i ++)
    {
        int NewRow = Current.Row + UD[i];
        int NewCol = Current.Col + LR[i];

        if(NewRow < Maze.size() && NewRow >= 0 && NewCol < Maze[0].size() && NewCol >= 0 && !(* Visited)[NewRow][NewCol])
        {
            MazeCell Neighbor; 
            Neighbor.Row = NewRow;
            Neighbor.Col = NewCol;
            
            Candidates.push_back(Neighbor);
        }
    }

    std :: random_device rd;
    std :: mt19937 gen(rd());
    if(Candidates.empty())
    {
      //std :: cerr << "Candidates Stack is Empty!";
        return false;
    }
    else
    {
        std :: uniform_int_distribution<> dist(0, Candidates.size() - 1);
        int Pick = dist(gen);
        
        MazeCell Wall;
        Wall.Row = (Current.Row + Candidates[Pick].Row) /2;
        Wall.Col = (Current.Col + Candidates[Pick].Col) /2;

        Current = Candidates[Pick];
        Stack->push_back(Current);
        (* Visited)[Current.Row][Current.Col] = true;
        Maze[Current.Row][Current.Col] = '.';
        Maze[Wall.Row][Wall.Col] = '.';
        
        return true;
    }
}

void DfsBackTracking(std :: vector < std :: vector <char> > & Maze, MazeCell Start)
{
    std :: vector <std :: vector <bool> > Visited (Maze.size(), std :: vector <bool> (Maze[0].size(),false));
    std :: vector <std :: vector <bool> > * Visited_ptr = & Visited;
    
    std :: vector <MazeCell> Stack; 
    std :: vector <MazeCell> * Stack_ptr = & Stack;

    Visited[Start.Row][Start.Col] = true;
    Stack.push_back(Start);
    Maze[Start.Row][Start.Col] = '.';

    while(!Stack.empty())
    {   
        MazeCell Current = Stack.back();
        bool Found = ExploreNeighbor(Maze, Current, Visited_ptr, Stack_ptr);
        
        if(!Found)
            Stack.pop_back();

        std :: cout << "\033[H";
        DisplayMaze(Maze, Current);
        std :: this_thread :: sleep_for(std :: chrono :: milliseconds(50));
      
    }
}

void DisplayMaze(std :: vector < std :: vector <char> > & Maze, MazeCell & Current)
{
    int Rows = Maze.size();
    int Cols = Maze[0].size();

    for(int j = 0; j < Cols + 2; j ++)
        std :: cout << '#';
    std :: cout << std :: endl;

    for(int i = 0; i < Rows; i ++)
    {
        std :: cout << '#';
        for(int j = 0; j < Cols; j ++)
        {
            if(i == Current.Row && j == Current.Col)
                std :: cout << "\033[31m" << 'X' << "\033[0m";
            else
               std :: cout << Maze[i][j];
        }    
        std :: cout << '#';
        std :: cout << std :: endl;
    }
    
    for(int j = 0; j < Cols + 2; j ++)
        std :: cout << '#';
    std :: cout << std :: endl;
}

int main()
{
    std :: vector < std :: vector <char> > Maze = MazeInit();
    MazeCell Start = DefStart(Maze);

    MazeCell Helper = {-1, -1};

    DfsBackTracking(Maze, Start);
    DisplayMaze(Maze, Helper);

    return 0;
}
