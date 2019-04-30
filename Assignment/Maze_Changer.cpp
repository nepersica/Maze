#include "Maze_Changer.h"

void Maze_Changer::arrToStr(int arr[][11], Maze_Control &cmc) {
	for (int i = 0; i < 11; i++) {
		for (int j = 0; j < 11; j++) {
			Switch_intArr(arr[i][j], cmc);
		}
		cmc.AttachOutput_Maze("\n");
	}
}

void Maze_Changer::Switch_intArr(int num, Maze_Control &cmc) {
	switch (num) {
	case 0: case 9:	// way
		cmc.AttachOutput_Maze("    ");
		break;

	case 1:	// wall
		if (cmc.GetWhich_type() == MAZE_TYPE::INT)
			cmc.AttachOutput_Maze("11");
		else
			cmc.AttachOutput_Maze("XX");
		break;

	case 3:	// start
		if (cmc.GetWhich_type() == MAZE_TYPE::INT)
			cmc.AttachOutput_Maze("2  ");
		else
			cmc.AttachOutput_Maze("P  ");
		break;

	case 4:	// goal
		if (cmc.GetWhich_type() == MAZE_TYPE::INT)
			cmc.AttachOutput_Maze("4  ");
		else
			cmc.AttachOutput_Maze("H  ");
		break;
	case 5:
		if (cmc.GetWhich_type() == MAZE_TYPE::INT)
			cmc.AttachOutput_Maze("0  ");
		else
			cmc.AttachOutput_Maze("o  ");
		break;		
	}
}

void Maze_Changer::FileTo_arr(string sentence, int arr_x, int arr[][11], Maze_Control &cmc) {

	
	int catched = 0; int arr_y = -1;
	int count = 0;	// counting the number of word.

	for (int i = 0; i < sentence.size(); i++) {
		char now = sentence.at(i);
		if (Check_Range(now, cmc)) {	// true : the word is belong the type.
			if (cmc.GetWhich_type() == MAZE_TYPE::INT) {
				if (now == '1') {	// wall
					count++; cmc.IncSelect_type();
					if (count == 2) {
						count = 0; arr_y++;
						arr[arr_x][arr_y] = 1;/*cmc.SetMaze_arr(arr_x, arr_y, 1);*/
					}
				}
				else if (now == '2') {	// 출발점
					count = 2; i++; cmc.IncSelect_type(); cmc.Inc_sp(); arr_y++;
					if (count == 2) {
						arr[arr_x][arr_y] = 3; /*cmc.SetMaze_arr(arr_x, arr_y, 3);	*/
						count = 0; cmc.Setstart_X(arr_x);	cmc.Setstart_Y(arr_y);
					}
				}
				else if (now == ' ') {
					cmc.Inc_sp(); count++;
					if (count == 2) {
						count = 0;	arr_y++;
						arr[arr_x][arr_y] = 0; /*cmc.SetMaze_arr(arr_x, arr_y, 0);*/
					}
				}
				else if (now == '4') {
					arr_y++; count = 2; i++; cmc.IncSelect_type(); cmc.Inc_sp();
					if (count == 2) {
						arr[arr_x][arr_y] = 4; /*cmc.SetMaze_arr(arr_x, arr_y, 4); */
						count = 0;	cmc.Setgoal_X(arr_x);	cmc.Setgoal_Y(arr_y);
					}

				}
				else {
					count++; cmc.IncSelect_type();
					if (count == 2) {
						count = 0;	arr_y++;
						arr[arr_x][arr_y] = 1; /*cmc.SetMaze_arr(arr_x, arr_y, 1);*/
					}
				}
			}
			else if (cmc.GetWhich_type() == MAZE_TYPE::CHAR) {
				if (now == 'X') {
					count++; cmc.IncSelect_type();
					if (count == 2) {
						count = 0; arr_y++;
						arr[arr_x][arr_y] = 1; /*cmc.SetMaze_arr(arr_x, arr_y, 1);*/
					}
				}
				else if (now == 'P') {	// 출발점
					count = 2; i++; cmc.IncSelect_type(); cmc.Inc_sp(); arr_y++;
					if (count == 2) {
						arr[arr_x][arr_y] = 3; /*cmc.SetMaze_arr(arr_x, arr_y, 3);*/
						count = 0;	cmc.Setstart_X(arr_x);	cmc.Setstart_Y(arr_y);
					}
				}
				else if (now == ' ') {
					cmc.Inc_sp(); count++;
					if (count == 2) {
						count = 0;	arr_y++;
						arr[arr_x][arr_y] = 0; /*cmc.SetMaze_arr(arr_x, arr_y, 0);*/
					}
				}
				else if (now == 'H') {
					arr_y++; count = 2; i++; cmc.IncSelect_type(); cmc.Inc_sp();
					if (count == 2) {
						arr[arr_x][arr_y] = 4; /*cmc.SetMaze_arr(arr_x, arr_y, 4); */
						count = 0;	cmc.Setgoal_X(arr_x);	cmc.Setgoal_Y(arr_y);
					}
				}
				else {
					count++; cmc.IncSelect_type();
					if (count == 2) {
						count = 0;	arr_y++;
						arr[arr_x][arr_y] = 1; /*cmc.SetMaze_arr(arr_x, arr_y, 1);*/
					}
				}
			}
		}
		else {
			if (cmc.GetWhich_type() == MAZE_TYPE::CHAR)
			{
				if (now == '2')
				{
					arr_y++; count = 2; i++; cmc.IncDiff_type(); cmc.Inc_sp();
					if (count == 2)
					{
						arr[arr_x][arr_y] = 3; /*cmc.SetMaze_arr(arr_x, arr_y, 3);	*/
						count = 0; cmc.Setstart_X(arr_x);	cmc.Setstart_Y(arr_y);
					}
				}
				else if (now == '4')
				{
					arr_y++; count = 2; i++; cmc.IncDiff_type(); cmc.Inc_sp();
					if (count == 2)
					{
						arr[arr_x][arr_y] = 4; /*cmc.SetMaze_arr(arr_x, arr_y, 4); */
						count = 0;	cmc.Setgoal_X(arr_x);	cmc.Setgoal_Y(arr_y);
					}
				}
				else {
					count++; cmc.IncDiff_type();
					if (count == 2)
					{
						count = 0;	arr_y++;
						arr[arr_x][arr_y] = 1; /*cmc.SetMaze_arr(arr_x, arr_y, 1);*/
					}
				}
			}
			else if (cmc.GetWhich_type() == MAZE_TYPE::INT)
			{
				if (now == 'P')
				{
					arr_y++; count = 2; i++; cmc.IncDiff_type(); cmc.Inc_sp();
					if (count == 2)
					{
						arr[arr_x][arr_y] = 3; /*cmc.SetMaze_arr(arr_x, arr_y, 3);	*/
						count = 0; cmc.Setstart_X(arr_x);	cmc.Setstart_Y(arr_y);
					}
				}
				else if (now == 'H')
				{
					arr_y++; count = 2; i++; cmc.IncDiff_type(); cmc.Inc_sp();
					if (count == 2)
					{
						arr[arr_x][arr_y] = 4; /*cmc.SetMaze_arr(arr_x, arr_y, 4); */
						count = 0;	cmc.Setgoal_X(arr_x);	cmc.Setgoal_Y(arr_y);
					}
				}
				else {
					count++; cmc.IncDiff_type();
					if (count == 2)
					{
						count = 0;	arr_y++;
						arr[arr_x][arr_y] = 1; /*cmc.SetMaze_arr(arr_x, arr_y, 1);*/
					}
				}
			}
		}
	}
}

ERROR_CODE Maze_Changer::Analyze_file(ifstream &ist, Maze_Control &cmc) {

	CATCH_ERROR error = CATCH_ERROR::NONE;
	string in_line ="";  int arr_x = -1; int arr[11][11];
	vector<string> Save_line; vector<string> edited_set;

	try {
		while (getline(ist, in_line)) {
			FileTo_arr(in_line, ++arr_x, arr, cmc);
			Save_line.push_back(in_line);
		}

		cmc.CopyMaze_arr(arr, 11, 11);

		if ((cmc.GetDiff_type() + cmc.Get_sp() == 242)) {	// 전체 다를 때 타입 바꾸기만 해주기
			throw error = CATCH_ERROR::CNGTYPE;
		}
		else if ((cmc.GetSelect_type() + cmc.Get_sp()) == 242) {
		}
		else if (cmc.GetSelect_type() > cmc.GetDiff_type()) { // Change the other type of words.
			cmc.ResetOutput_Maze();
			throw error = CATCH_ERROR::EDITFILE;
		}
		else { // select_type < diff_type
			if (cmc.GetWhich_type() == MAZE_TYPE::INT) {
				cmc.SetWhich_type(MAZE_TYPE::CHAR);
			}
			else if (cmc.GetWhich_type() == MAZE_TYPE::CHAR) {
				cmc.SetWhich_type(MAZE_TYPE::INT);
			}
			cmc.ResetOutput_Maze();
			throw error = CATCH_ERROR::EDITFILE;
		}

		arrToStr(arr, cmc);
		cmc.Reset_condition();
		return ERROR_CODE::SUCCESS;

	}
	catch (CATCH_ERROR error) {
		cmc.Reset_condition();
		switch (error)
		{
		case CATCH_ERROR::CNGTYPE:
			Maze_Display::ChoseWrong_Display();
			if (cmc.GetWhich_type() == MAZE_TYPE::INT) {
				cmc.SetWhich_type(MAZE_TYPE::CHAR);
				arrToStr(arr, cmc);
				return ERROR_CODE::CNGCHAR;
			}
			else if (cmc.GetWhich_type() == MAZE_TYPE::CHAR) {
				cmc.SetWhich_type(MAZE_TYPE::INT);
				arrToStr(arr, cmc);
				return ERROR_CODE::CNGINT;	
			}
			break;

		case CATCH_ERROR::EDITFILE:	// Change the word.
			Maze_Display::FileChange_Display(); 
			arrToStr(arr, cmc);
			cmc.SetWhich_catch(CATCH_ERROR::EDITFILE);
			return ERROR_CODE::SUCCESS;
			break;
		}
	}


}

bool Maze_Changer::Check_Range(char word, Maze_Control &cmc) {	// Is the word belong the type?
	int plus = (cmc.GetWhich_type() == MAZE_TYPE::INT) ? 0 : 17;
	int more = (cmc.GetWhich_type() == MAZE_TYPE::INT) ? 0 : 16;
	if (((char)(48+plus) <= (char)word && (char)word <= (char)(57+plus+more)) || (char)word == (char)(32)) {
		return true;
	}
	else
		return false;

}

string Maze_Changer::Control_sp(Maze_Control &cmc)
{
	string EditingLine = cmc.GetOutput_Maze();
	string EditedLine = replace_All(EditingLine, "  ", " ");
	return EditedLine;
}

string Maze_Changer::replace_All( string message, string pattern, string replace)
{
	string result = message;
	string::size_type pos = 0;
	string::size_type offset = 0;

	while ((pos = result.find(pattern, offset)) != std::string::npos)
	{
		result.replace(result.begin() + pos, result.begin() + pos + pattern.size(), replace);
		offset = pos + replace.size();
	}
	return result;
}