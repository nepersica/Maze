// 미로 길 찾기
#include "Maze_Finder.h"

int Maze_Finder::Maze_Traverse(int xLoc, int yLoc, int facing, Maze_Control &cmc)
{
	int success = 0;

	cmc.SetMaze_arr(xLoc, yLoc, 5);

	int maze[11][11] = { 0, };
	for (int i = 0; i < 11; i++)
	{
		for (int j = 0; j < 11; j++)
		{
			maze[i][j] = cmc.GetMaze_arr(i, j);
		}
	}
	Maze_Changer::arrToStr(maze, cmc);

	// 움직이는 output_Maze 벡터에 넣어주기
	cmc.Add_Record(cmc.GetOutput_Maze()); /*vector_maze.push_back(output_Maze);*/
	cmc.ResetOutput_Maze(); /*output_Maze = "";*/

	while (success == 0)	// While success is not equal to 0...
	{
		if ((xLoc == cmc.Getgoal_X()) && (yLoc == cmc.Getgoal_Y()))	// If current location is the exit of the maze...
		{
			success = 1;	// ...set success to 1.
		}
		else if (facing == 2)	// If facing down...
		{

			if ((xLoc + 1) <= 10 && ( cmc.GetMaze_arr(xLoc + 1, yLoc) == 0 || cmc.GetMaze_arr(xLoc + 1, yLoc) == 4))	// ...check square below for valid move...
			{
				success = Maze_Traverse(xLoc + 1, yLoc, 2, cmc);	// Move down.
			}
			else if ((yLoc + 1) <= 10 && (cmc.GetMaze_arr(xLoc, yLoc + 1) == 0 || cmc.GetMaze_arr(xLoc, yLoc + 1) == 4))	// ...check square to the right for valid move...
			{
				success = Maze_Traverse(xLoc, yLoc + 1, 1, cmc);	// Move to the right.
			}

			else if ((yLoc - 1) >= 0 && (cmc.GetMaze_arr(xLoc, yLoc - 1) == 0 || cmc.GetMaze_arr(xLoc, yLoc - 1) == 4))	// ...check square to the left for valid move...
			{
				success = Maze_Traverse(xLoc, yLoc - 1, 3,cmc);	// Move to the left.
			}
			else
			{	// If nowhere to go...
				cmc.SetMaze_arr(xLoc, yLoc, 9);//maze[xLoc][yLoc] = 9;
				return 0;	// ...close recursion to the previous junction.
			}
		}
		else if (facing == 1)	// If facing right...
		{
			if ((xLoc + 1) <= 10 && (cmc.GetMaze_arr(xLoc + 1, yLoc) == 0 || cmc.GetMaze_arr(xLoc + 1, yLoc) == 4))	// ...check square below for valid move...
			{
				success = Maze_Traverse(xLoc + 1, yLoc, 2, cmc);	// Move down.
			}
			else if ((yLoc + 1) <= 10 && (cmc.GetMaze_arr(xLoc, yLoc + 1) == 0 || cmc.GetMaze_arr(xLoc, yLoc + 1) == 4))	// ...check square to the right for valid move...
			{
				success = Maze_Traverse(xLoc, yLoc + 1, 1, cmc);	// Move right.
			}
			else if ((xLoc - 1) >= 0 && (cmc.GetMaze_arr(xLoc - 1, yLoc) == 0 || cmc.GetMaze_arr(xLoc - 1,yLoc) == 4))	// ...check square above for valid move...
			{
				success = Maze_Traverse(xLoc - 1, yLoc, 0, cmc);	// Move up.
			}
			else
			{	// If nowhere to go...
				cmc.SetMaze_arr(xLoc, yLoc, 9); // maze[xLoc][yLoc] = 9;
				return 0;	// ...close recursion to the previous junction.
			}
		}
		else if (facing == 3)	// If facing left...
		{
			if ((xLoc + 1) <= 10 && (cmc.GetMaze_arr(xLoc + 1, yLoc) == 0 || cmc.GetMaze_arr(xLoc + 1, yLoc) == 4))	// ...check square below for valid move...
			{
				success = Maze_Traverse(xLoc + 1, yLoc, 2, cmc);	// Move down.
			}
			else if ((xLoc - 1) >= 0 && (cmc.GetMaze_arr(xLoc - 1, yLoc) == 0 || cmc.GetMaze_arr(xLoc - 1, yLoc) == 4))	// ...check square above for valid move...
			{
				success = Maze_Traverse(xLoc - 1, yLoc, 0, cmc);	// Move up.
			}
			else if ((yLoc - 1) >= 0 && (cmc.GetMaze_arr(xLoc, yLoc - 1) == 0 || cmc.GetMaze_arr(xLoc, yLoc - 1) == 4))	// ...check square to the left for valid move...
			{
				success = Maze_Traverse(xLoc, yLoc - 1, 3, cmc);	// Move to the left.
			}
			else
			{	// If nowhere to go...
				cmc.SetMaze_arr(xLoc, yLoc, 9); //maze[xLoc][yLoc] = 9;
				return 0;	// ...close recursion to the previous junction.
			}
		}
		else if (facing == 0)	// Else if facing up...
		{
			if ((yLoc + 1) <= 10 && (cmc.GetMaze_arr(xLoc, yLoc + 1) == 0 || cmc.GetMaze_arr(xLoc, yLoc + 1) == 4))	// ...check square to the right for valid move...
			{
				success = Maze_Traverse(xLoc, yLoc + 1, 1, cmc);	// Move to the right.
			}
			else if ((xLoc - 1) >= 0 && (cmc.GetMaze_arr(xLoc - 1, yLoc) == 0 || cmc.GetMaze_arr(xLoc - 1, yLoc) == 4))	// ...check square above for valid move...
			{
				success = Maze_Traverse(xLoc - 1, yLoc, 0, cmc);	// Move up.
			}
			else if ((yLoc - 1) >= 0 && (cmc.GetMaze_arr(xLoc, yLoc - 1) == 0 || cmc.GetMaze_arr(xLoc, yLoc - 1) == 4))	// ...check square to the left for valid move...
			{
				success = Maze_Traverse(xLoc, yLoc - 1, 3, cmc);	// Move to the left.
			}
			else
			{	// If nowhere to go...
				cmc.SetMaze_arr(xLoc, yLoc, 9); //maze[xLoc][yLoc] = 9;
				return 0;	// ...close recursion to the previous junction.
			}
		}

	}	// ...end while loop.

	return success;	// Return value of success.
}