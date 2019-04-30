#pragma once
#include "Maze_Maker.h"

// maze string으로 만들어주기 || 파일 maze를 int로 변환해주기
class Maze_Changer {

private :
	ERROR_CODE Which_mode = ERROR_CODE::SUCCESS;

public : 
	static void arrToStr(int arr[][11], Maze_Control &cmc);
	static ERROR_CODE Analyze_file(ifstream &ist, Maze_Control &cmc);
	
	static void Switch_intArr(int num, Maze_Control &cmc); // 배열 switch문으로 문자열 만들기
	static void FileTo_arr(string sentence,  int arr_x, int arr[][11],  Maze_Control &cmc);
	static bool Check_Range(char word, Maze_Control &cmc);
	static string Control_sp(Maze_Control &cmc);
	static string replace_All(string message, string pattern, string replace);
};