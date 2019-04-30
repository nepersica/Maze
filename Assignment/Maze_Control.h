#pragma once

enum class ERROR_CODE
{
	SUCCESS, CNGCHAR, CNGINT, FAIL, NONE
};

enum class MAZE_MODE
{
	NONE, RANDOM, TEXT
};

enum class MAZE_TYPE
{
	NONE, INT, CHAR
};

enum class CATCH_ERROR
{
	CNGTYPE, EDITFILE, NONE
};

class Maze_Control
{
private:	
	MAZE_MODE Which_mode = MAZE_MODE::NONE;
	MAZE_TYPE Which_type = MAZE_TYPE::NONE;
	ERROR_CODE Which_error = ERROR_CODE::SUCCESS;
	CATCH_ERROR Which_catch = CATCH_ERROR::NONE;

	bool Create_state = false;

	int start_X = 0;	int start_Y = 0;	// start position of the maze
	int goal_X = 0;		int goal_Y = 0;		// goal position of the maze

	int maze_arr[11][11];

	MAZE_TYPE previous_type = MAZE_TYPE::NONE;
	ERROR_CODE previous_error = ERROR_CODE::NONE;

	string output_Maze = "";	// send to Maze_Display's Display
	string result_Maze = "";	// send to Maze_Display's Answer of Maze
	string before_Maze = "";	// prior maze
	string before_Result = "";	// prior result

	int diff_type = 0;	int select_type = 0;  int sp = 0;

	vector<string> maze_record;	// save the moving of the player

public:
	const int MAZE_SIZE_X = 12;
	const int MAZE_SIZE_Y = 12;

public:

	MAZE_MODE GetWhich_mode() { return Which_mode; }
	MAZE_TYPE GetWhich_type() { return Which_type; }
	ERROR_CODE GetWhich_error() { return Which_error; }
	CATCH_ERROR GetWhich_catch() { return Which_catch; }

	void SetWhich_mode(MAZE_MODE mode)	{ Which_mode = mode; }
	void SetWhich_type(MAZE_TYPE type)	{ Which_type = type; }
	void SetWhich_error(ERROR_CODE error) { Which_error = error; }
	void SetWhich_catch(CATCH_ERROR error) { Which_catch = error; }

	// Ãß°¡
	void SaveBefore_type(MAZE_TYPE type)	{	previous_type = type;	}
	MAZE_TYPE GetBefore_type()	{	return previous_type;	}
	void SaveBefore_error(ERROR_CODE error)	{	previous_error = error;	}
	ERROR_CODE GetBefore_error()	{	return previous_error;	}


	int GetMAZE_SIZE_X() { return MAZE_SIZE_X; }	int GetMAZE_SIZE_Y() { return MAZE_SIZE_Y; }


	void Setstart_X(int start) { start_X = start; }		void Setstart_Y(int start) { start_Y = start; }
	int Getstart_X() { return start_X; }				int Getstart_Y() { return start_Y; }	// make & return maze's start position
	void Clear_StartPosition() { start_X = 0; start_Y = 0; }

	void Setgoal_X(int goal) { goal_X = goal; }		void Setgoal_Y(int goal) { goal_Y = goal; }
	int Getgoal_X() { return goal_X; }				int Getgoal_Y() { return goal_Y; }	// make & return maze's start position
	void Clear_GoalPosition() { goal_X = 0; goal_Y = 0; }
	
	/*
	Maze_arr Function
	*/
	void CopyMaze_arr(int arr[][11], int col, int row) { 
		for(int i=0; i<col; i++)
			for (int j = 0; j < row; j++) {
				maze_arr[i][j] = arr[i][j];
			}
	}

	int **GetMaze_arr()
	{
		int **tempArr = new int*[11];
		for (int i = 0; i < 11; ++i)
		{
			tempArr[i] = new int[11];
		}

		for (int i = 0; i<MAZE_SIZE_Y-1; i++)
			for (int j = 0; j < MAZE_SIZE_X-1; j++) {
				tempArr[i][j] = maze_arr[i][j];
			}

		return tempArr;
	}

	int GetMaze_arr(int idxX, int idxY)	{ return maze_arr[idxX][idxY]; }
	void SetMaze_arr(int idxX, int idxY, int value)	{ maze_arr[idxX][idxY] = value; }
	void ResetMaze_arr() {
		for (int i = 0; i < MAZE_SIZE_Y - 1; i++) {
			for (int j = 0; j < MAZE_SIZE_X - 1; j++) {
				maze_arr[i][j] = 0;
			}
		}
	}
	void PrintMaze_arr()	// print the array of maze
	{
		for (int i = 0; i < 11; i++) {
			for (int j = 0; j < 11; j++) {
				cout << maze_arr[i][j];
			}
			cout << endl;
		}
		cout << endl;
	}
	void ClearMaze_arr()
	{
		for (int i = 0; i < 11; i++)
		{
			for (int j = 0; j < 11; j++)
			{
				maze_arr[i][j] = 0;
			}
		}
	}

	/*
	output_Maze function
	*/
	void ResetOutput_Maze()	{ output_Maze = ""; }
	void AttachOutput_Maze(string add) { output_Maze.append(add); }
	string GetOutput_Maze() { return output_Maze; }
	void PrintOutput_Maze() { cout << output_Maze; }
	
	void Set_BeforeMaze() { before_Maze = output_Maze; }
	string Get_BeforeMaze() { return before_Maze; }

	void Set_ResultMaze(string maze) { result_Maze = maze; }
	string Get_ResultMaze() { return result_Maze; }
	void Reset_ResultMaze() { result_Maze = ""; }

	void Set_BeforeResult(string result) { before_Result = result; }
	string Get_BeforeResult()	{ return before_Result;	}
	void Reset_BeforeResult() { before_Result = ""; }
	void Print_BeforeResult() { cout << before_Result; }

	void IncDiff_type() { diff_type++; }	int GetDiff_type() { return diff_type; }
	void Inc_sp() { sp++; }		int Get_sp() { return sp; }
	void IncSelect_type() { select_type++; };	int GetSelect_type() { return select_type; }

	void Reset_condition() { diff_type = 0;  sp = 0; select_type = 0; }

	void Add_Record(string output_Maze) { maze_record.push_back(output_Maze); }
	void Reset_Record() { maze_record.clear(); } int SizeofRecord() { return maze_record.size(); }
	string IdxofRecord(int Idx) { return maze_record[Idx]; }

	void SaveBefore_maze(string before) { before_Maze = before; }

	void ClearData()
	{
		ResetOutput_Maze(); result_Maze = ""; Clear_StartPosition(); Clear_GoalPosition(); ClearMaze_arr();
		Which_mode = MAZE_MODE::NONE;	Which_type = MAZE_TYPE::NONE;
		Which_error = ERROR_CODE::NONE;
		CATCH_ERROR Which_error = CATCH_ERROR::NONE; 
		maze_record.clear();	Reset_Createstate();	previous_type = MAZE_TYPE::NONE;
		// before_Maze = ""; before_Result = "";
	}

	void Set_Createstate()	{ Create_state = true;	}
	void Reset_Createstate() { Create_state = false; }
	bool Get_Createstate() { return Create_state; }
	
};
	

