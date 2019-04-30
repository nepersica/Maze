#pragma once
#include "Maze_windows.h"


struct Maze_Idx
{
	int firstIdx;
	int secondIdx;
	int idxY;
	int idxX;

	Maze_Idx(){}
	Maze_Idx(int firstIdx, int secondIdx, int idxY, int idxX) : firstIdx(firstIdx), secondIdx(secondIdx),
		idxY(idxY), idxX(idxX) {}
};			

class Maze_Maker
{
private:
	static void ChangeIdxToM(list < pair < int, int> >::iterator &m, Maze_Idx idx)
	{
		(*m).first += idx.firstIdx;
		(*m).second += idx.secondIdx;
	}
	static void Make_Maze_Step(bool &remove_driller, bool IsRemove_driller,
		vector < vector < bool > > &maze, list < pair < int, int> >::iterator &m,		
		Maze_Idx idx)
	{		
		if (IsRemove_driller) {
			remove_driller = true;
		}
		else {
			maze[(*m).second + idx.idxY][(*m).first + idx.idxX] = true;
		}
	}

public:
	
	static void Create_random(Maze_Control &cmc);
	static int boolTOint(vector<vector<bool>> maze, Maze_Control &cmc, int door);

	static void Create_text(Maze_Control &cmc);
	
	

};