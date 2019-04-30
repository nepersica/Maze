#pragma once
#include "Maze_Changer.h"

class Maze_Display {

public:
	static string Float2Display(Maze_Control &cmc);
	static void ChoseWrong_Display();
	static void FileChange_Display();
	static string GetIdxRecord(int Idx, Maze_Control &cmc);
	static void ToBlank_AnswerBox(Maze_Control &cmc);
};
