#pragma once
#include "Maze_Maker.h"

// maze string���� ������ֱ� || ���� maze�� int�� ��ȯ���ֱ�
class Maze_Changer {

private :
	ERROR_CODE Which_mode = ERROR_CODE::SUCCESS;

public : 
	static void arrToStr(int arr[][11], Maze_Control &cmc);
	static ERROR_CODE Analyze_file(ifstream &ist, Maze_Control &cmc);
	
	static void Switch_intArr(int num, Maze_Control &cmc); // �迭 switch������ ���ڿ� �����
	static void FileTo_arr(string sentence,  int arr_x, int arr[][11],  Maze_Control &cmc);
	static bool Check_Range(char word, Maze_Control &cmc);
	static string Control_sp(Maze_Control &cmc);
	static string replace_All(string message, string pattern, string replace);
};