// 미로 window에 띄우기
#include "Maze_Display.h"

string Maze_Display::Float2Display(Maze_Control &cmc) {
	cmc.Set_BeforeMaze();
	cmc.ResetOutput_Maze();
	return cmc.Get_BeforeMaze();
}

void Maze_Display::ChoseWrong_Display() {
	fl_choice("You chose the Wrong Type", "Change the Type", 0, 0);
}

void Maze_Display::FileChange_Display() {
	fl_choice("File has wrong type of word", "Change the Type", 0, 0);
}

string Maze_Display::GetIdxRecord(int Idx, Maze_Control &cmc) {
	cmc.SaveBefore_maze(cmc.IdxofRecord(Idx));
	return cmc.IdxofRecord(Idx);
}

void Maze_Display::ToBlank_AnswerBox(Maze_Control &cmc)
{
	cmc.Reset_ResultMaze();
}
