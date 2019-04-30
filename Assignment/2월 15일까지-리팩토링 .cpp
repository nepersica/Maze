#include <iostream>
#include <fstream>
#include <string>
#include "GUI.h"
#include "Graph.h"
#include "Window.h"
#include <FL\Fl_Box.H>
#include <FL\Fl_Check_Button.H>
#include <FL\Fl_Multiline_Output.H>
#include <FL\Fl_File_Chooser.H>
#include <FL\Fl_Menu_Bar.H>
#include <FL\Fl_Choice.H>
#include <FL\Fl.H>
#include <time.h>
#include <vector>
#include <list>
#include <thread>
//#include "Maze_windows.h"


using namespace std;
using namespace Graph_lib;

int Which_mode = 0;	// random : 1, text = 2
int Which_type = 0;	// int : 1, char = 2

const int maze_size_x = 12;
const int maze_size_y = 12;

string output_Maze = "";
string before_Maze = "";
string result_maze = "";
string before_result = "";

string** maze_st = new string*[11];

int** maze_arr = new int*[11];
int** save_maze = new int*[11];

int cancel =0;


vector<string> vector_maze;

int start_X = -1;	int start_Y = -1;
int goal_X = -1;	int goal_Y = -1;	int create_count = 0;

struct Maze_window : Window {
	Maze_window(Point xy, int w, int h, const string& title);

private:

	Text Maze;
	Text Display_Maze;
	Out_box Display;

	Button Create_button;	// Create Maze
	Button Quit_button;
	Button Find_button;		// Find Route

	Text Mode_text;
	Graph_lib::Rectangle Mode_rect;
	CheckButton Random_button;	// Randomly
	CheckButton Text_button;	// input


	Text Type_text;
	Graph_lib::Rectangle Type_rect;
	CheckButton Int_button;		// by int
	CheckButton Char_button;	// by char

	Text Answer;
	Text result;
	Out_box Answer_of_Maze;

	static void cb_exit(Address, Address);
	void exit();
	static void cb_create(Address, Address);
	void create();
	void printMaze(int** maze, int xLoc, int yLoc);
	void final_maze();
	void print_arr(int **maze);
	static void cb_find(Address, Address);
	void find();

	static void cb_random(Address, Address);
	void random();
	void Create_random();
	void Create_text();
	static void cb_text(Address, Address);
	void text();

	static void cb_int(Address, Address);
	void Int();
	static void cb_char(Address, Address);
	void Char();
	int mazeTraverse(int** maze, int xLoc, int yLoc, int facing);
};

Maze_window::Maze_window(Point xy, int w, int h, const string& title)
	:Window(xy, w, h, title),

	Maze(Point(40, 40), "<< MAZE GAME XD >>"),
	Display_Maze(Point(40, 40), output_Maze),
	Display(Point(40, 55), 200, 200, ""),

	Quit_button(Point(x_max() - 70, 0), 70, 20, "Quit", cb_exit),
	Create_button(Point(40, y_max() - 160), 90, 80, "Create Maze", cb_create),
	Find_button(Point(150, y_max() - 160), 90, 80, "Find Maze", cb_find),

	Mode_text(Point(x_max() - 160, y_max() - 435), "[ Mode ]"),
	Mode_rect(Point(x_max() - 170, y_max() - 425), 110, 70),
	Random_button(Point(x_max() - 160, y_max() - 420), 40, 30, "Random", cb_random),
	Text_button(Point(x_max() - 160, y_max() - 395), 40, 30, "Text", cb_text),

	Type_text(Point(x_max() - 160, y_max() - 335), "[ Type ]"),
	Type_rect(Point(x_max() - 170, y_max() - 325), 110, 70),
	Int_button(Point(x_max() - 160, y_max() - 320), 40, 30, "Int", cb_int),
	Char_button(Point(x_max() - 160, y_max() - 295), 40, 30, "Char", cb_char),

	Answer(Point(x_max() - 160, y_max() - 220), "! Answer !"),
	result(Point(40, 40), result_maze),
	Answer_of_Maze(Point(x_max() - 215, y_max() - 215), 200, 200, "")

{
	attach(Maze);	Maze.set_color(Color::black);	Maze.set_font_size(20);
	attach(Display_Maze);
	attach(Display);

	attach(Quit_button);
	attach(Create_button);
	attach(Find_button);

	attach(Mode_text);	Mode_text.set_color(Color::black);
	attach(Mode_rect);	Mode_rect.set_color(Color::black);
	attach(Random_button);
	attach(Text_button);

	attach(Type_text);	Type_text.set_color(Color::black);
	attach(Type_rect);	Type_rect.set_color(Color::black);
	attach(Int_button);
	attach(Char_button);

	attach(Answer);	Answer.set_color(Color::black);
	attach(Answer_of_Maze);

}

void Maze_window::cb_int(Address, Address pw) {
	reference_to<Maze_window>(pw).Int();
}

void Maze_window::Int() {
	Which_type = 1;
	Char_button.ClearValue();
}

void Maze_window::cb_char(Address, Address pw) {
	reference_to<Maze_window>(pw).Char();
}

void Maze_window::Char() {
	Which_type = 2;
	Int_button.ClearValue();
}

void Maze_window::cb_random(Address, Address pw) {
	reference_to<Maze_window>(pw).random();
}

void Maze_window::random() {	// create random maze
	Which_mode = 1;
	Text_button.ClearValue();
}

void Maze_window::cb_text(Address, Address pw) {
	reference_to<Maze_window>(pw).text();
}

void Maze_window::text() {		// create text maze
	Which_mode = 2;
	Random_button.ClearValue();
}

void Maze_window::cb_exit(Address, Address pw) {
	reference_to<Maze_window>(pw).exit();
}

void Maze_window::exit() {
	hide();
}

void Maze_window::cb_create(Address, Address pw) {
	reference_to<Maze_window>(pw).create();
}

void Maze_window::create() {
	for (int i = 0; i < 11; i++) {
		save_maze[i] = new int[11];
	}
	create_count = 1;
	if (Which_mode == 1 && Which_type != 0) {	// random
		Create_random();
		Display.put(output_Maze);
		result_maze = "";

		before_result = result_maze;
		save_maze = maze_arr;
		vector_maze.clear();
	}
	else if (Which_mode == 2 && Which_type != 0) {	// text
		Create_text();
		Display.put(output_Maze);
		save_maze = maze_arr;
	}
	else {
		output_Maze.append("Select Mode or Type of the Maze");
		Display.put(output_Maze);
		result_maze = "";
		Random_button.ClearValue();	Text_button.ClearValue();
		Int_button.ClearValue();	Char_button.ClearValue();
		Which_mode = 0; Which_type = 0;
	}
	redraw();
	output_Maze = "";
	Answer_of_Maze.put(result_maze);
	result_maze = "";
}

void Maze_window::cb_find(Address, Address pw) {
	reference_to<Maze_window>(pw).find();
}

void Maze_window::final_maze() {
	result_maze = "";
	maze_arr[start_X][start_Y] = 6;
	maze_arr[goal_X][goal_Y] = 7;
	for (int i = 0; i < 11; i++) {
		for (int j = 0; j < 11; j++) {
			if (maze_arr[i][j] == 0 || maze_arr[i][j] == 9)
				result_maze.append("    ");
			if (maze_arr[i][j] == 1) {
				if (Which_type == 1)
					result_maze.append("11");
				if (Which_type == 2)
					result_maze.append("XX");
			}
			if (maze_arr[i][j] == 5) {
				if (Which_type == 1)
					result_maze.append("0  ");
				if (Which_type == 2)
					result_maze.append("o  ");
			}
			if (maze_arr[i][j] == 6) {
				if (Which_type == 1) {
					result_maze.append("2  ");
				}
				else if (Which_type == 2) {
					result_maze.append("P  ");
				}
			}
			if (maze_arr[i][j] == 7) {
				if (Which_type == 1) {
					result_maze.append("  4");
				}
				else if (Which_type == 2) {
					result_maze.append("H  ");
				}
			}
		}
		result_maze.append("\n");
	}
}


void Maze_window::find() {	// 0:통로, 1:벽, 2:플레이어, 3:출발점, 4:도착점, 5:지나간 길
	if (cancel == 1) {
		output_Maze.append("Select Mode or Type of the Maze");
		Display.put(output_Maze);
		output_Maze = "";
		result_maze = "";
		cancel = 0;
	}
	else if (Which_mode == 0 || Which_type == 0 || (Which_mode == 0 && Which_type == 0)) {
		output_Maze.append("Select Mode or Type of the Maze");
		Display.put(output_Maze);
		output_Maze = "";
		result_maze = "";
	}
	else if (create_count == 0) {
		output_Maze.append("You have to recreate the Maze ");
		Display.put(output_Maze);
		output_Maze = "";
		result_maze = "";
		Answer_of_Maze.put(result_maze);
	}
	else if (create_count == 1) {
		mazeTraverse(maze_arr, start_X, start_Y, 1);
		for (int i = 0; i < vector_maze.size(); i++) {
			flush();
			Display.put(vector_maze[i]);
			//redraw();
			Sleep(100);
			before_Maze = vector_maze[i];
		}
		final_maze();
		Random_button.ClearValue();	Text_button.ClearValue();
		Int_button.ClearValue();	Char_button.ClearValue();
		Which_mode = 0; Which_type = 0;
	}
	else {
		output_Maze.append("You have to recreate the Maze ");
		Display.put(output_Maze);
		output_Maze = "";
		result_maze = "";
		Answer_of_Maze.put(result_maze);
	}
	vector_maze.clear();
	create_count = 0;
	Answer_of_Maze.put(result_maze);
	before_result = result_maze;
}

void Maze_window::printMaze(int** maze, int xLoc, int yLoc)
{
	// nested for loops to iterate through maze
	for (int x = 0; x < 11; ++x) {
		for (int y = 0; y < 11; ++y) {
			if ((x == xLoc) && (y == yLoc)) {
				if (Which_type == 1) {
					output_Maze.append("2  ");
				}
				if (Which_type == 2) {
					output_Maze.append("P  ");
				}
			}
			else {
				if (maze_arr[x][y] == 0 || maze_arr[x][y] == 9)
					output_Maze.append("    ");
				else if (maze_arr[x][y] == 1) {
					if (Which_type == 1)
						output_Maze.append("11");
					if (Which_type == 2)
						output_Maze.append("XX");
				}
				else if (maze_arr[x][y] == 5) {
					if (Which_type == 1)
						output_Maze.append("0  ");
					if (Which_type == 2)
						output_Maze.append("o  ");
				}
				else if (maze_arr[x][y] == 3) {
					if (Which_type == 1) {
						output_Maze.append("2  ");
					}
					else if (Which_type == 2) {
						output_Maze.append("P ");
					}
				}
				else if (maze_arr[x][y] == 4) {
					if (Which_type == 1) {
						output_Maze.append("4  ");
					}
					else if (Which_type == 2) {
						output_Maze.append("H ");
					}
				}
			}
		}
		output_Maze.append("\n");
	}
} // end function printMaze

  // Traverse through the maze one square at a time
int Maze_window::mazeTraverse(int **maze, int xLoc, int yLoc, int facing)
{
	int success = 0;

	//cout << endl;
	//for (int i = 0; i < 11; i++) {
	//	for (int j = 0; j < 11; j++) {
	//		cout << maze[i][j];
	//	}
	//	cout << endl;
	//}
	//cout << endl;

	maze[xLoc][yLoc] = 5;   // Mark current location in the maze.


	//Display.put(output_Maze);	
	//redraw();

	output_Maze = "";
	printMaze(maze_arr, xLoc, yLoc);
	//cout << output_Maze << endl << endl;

	// 움직이는 output_Maze 벡터에 넣어주기
	vector_maze.push_back(output_Maze);
	output_Maze = "";

	//Sleep(1000);

	while (success == 0)	// While success is not equal to 0...
	{
		print_arr(maze);
		cout << endl << endl;

		if ((xLoc == goal_X) && (yLoc == goal_Y))	// If current location is the exit of the maze...
		{
			success = 1;	// ...set success to 1.
		}
		else if (facing == 2)	// If facing down...
		{

			if ((xLoc + 1) <= 10 && (maze[xLoc + 1][yLoc] == 0 || maze[xLoc + 1][yLoc] == 4))	// ...check square below for valid move...
			{
				success = mazeTraverse(maze, xLoc + 1, yLoc, 2);	// Move down.
			}
			else if ((yLoc + 1) <= 10 && (maze[xLoc][yLoc + 1] == 0 || maze[xLoc][yLoc + 1] == 4))	// ...check square to the right for valid move...
			{
				success = mazeTraverse(maze, xLoc, yLoc + 1, 1);	// Move to the right.
			}

			else if ((yLoc - 1) >= 0 && (maze[xLoc][yLoc - 1] == 0 || maze[xLoc][yLoc - 1] == 4))	// ...check square to the left for valid move...
			{
				success = mazeTraverse(maze, xLoc, yLoc - 1, 3);	// Move to the left.
			}
			else {	// If nowhere to go...
				maze[xLoc][yLoc] = 9;
				return 0;	// ...close recursion to the previous junction.
			}
		}
		else if (facing == 1)	// If facing right...
		{
			if ((xLoc + 1) <= 10 && (maze[xLoc + 1][yLoc] == 0 || maze[xLoc + 1][yLoc] == 4))	// ...check square below for valid move...
			{
				success = mazeTraverse(maze, xLoc + 1, yLoc, 2);	// Move down.
			}
			else if ((yLoc + 1) <= 10 && (maze[xLoc][yLoc + 1] == 0 || maze[xLoc][yLoc + 1] == 4))	// ...check square to the right for valid move...
			{
				success = mazeTraverse(maze, xLoc, yLoc + 1, 1);	// Move right.
			}
			else if ((xLoc - 1) >= 0 && (maze[xLoc - 1][yLoc] == 0 || maze[xLoc - 1][yLoc] == 4))	// ...check square above for valid move...
			{
				success = mazeTraverse(maze, xLoc - 1, yLoc, 0);	// Move up.
			}
			else {	// If nowhere to go...
				maze[xLoc][yLoc] = 9;
				return 0;	// ...close recursion to the previous junction.
			}
		}
		else if (facing == 3)	// If facing left...
		{
			if ((xLoc + 1) <= 10 && (maze[xLoc + 1][yLoc] == 0 || maze[xLoc + 1][yLoc] == 4))	// ...check square below for valid move...
			{
				success = mazeTraverse(maze, xLoc + 1, yLoc, 2);	// Move down.
			}
			else if ((xLoc - 1) >= 0 && (maze[xLoc - 1][yLoc] == 0 || maze[xLoc - 1][yLoc] == 4))	// ...check square above for valid move...
			{
				success = mazeTraverse(maze, xLoc - 1, yLoc, 0);	// Move up.
			}
			else if ((yLoc - 1) >= 0 && (maze[xLoc][yLoc - 1] == 0 || maze[xLoc][yLoc - 1] == 4))	// ...check square to the left for valid move...
			{
				success = mazeTraverse(maze, xLoc, yLoc - 1, 3);	// Move to the left.
			}
			else {	// If nowhere to go...
				maze[xLoc][yLoc] = 9;
				return 0;	// ...close recursion to the previous junction.
			}
		}
		else if (facing == 0)	// Else if facing up...
		{
			if ((yLoc + 1) <= 10 && (maze[xLoc][yLoc + 1] == 0 || maze[xLoc][yLoc + 1] == 4))	// ...check square to the right for valid move...
			{
				success = mazeTraverse(maze, xLoc, yLoc + 1, 1);	// Move to the right.
			}
			else if ((xLoc - 1) >= 0 && (maze[xLoc - 1][yLoc] == 0 || maze[xLoc - 1][yLoc] == 4))	// ...check square above for valid move...
			{
				success = mazeTraverse(maze, xLoc - 1, yLoc, 0);	// Move up.
			}
			else if ((yLoc - 1) >= 0 && (maze[xLoc][yLoc - 1] == 0 || maze[xLoc][yLoc - 1] == 4))	// ...check square to the left for valid move...
			{
				success = mazeTraverse(maze, xLoc, yLoc - 1, 3);	// Move to the left.
			}
			else {	// If nowhere to go...
				maze[xLoc][yLoc] = 9;
				return 0;	// ...close recursion to the previous junction.
			}
		}

	}	// ...end while loop.

	return success;	// Return value of success.
}

void Maze_window::print_arr(int **maze)
{
	for (int i = 0; i < 11; i++)
	{
		for (int j = 0; j < 11; j++)
		{
			cout << maze[i][j];
		}
		cout << endl;
	}

}

void Maze_window::Create_text() {

	for (int i = 0; i < 11; i++) {
		maze_arr[i] = new int[11];
	}

	Fl_File_Chooser chooser(".", "*.txt", Fl_File_Chooser::MULTI, "File Chooser");        // title
	chooser.show();

	while (chooser.shown())
	{
		Fl::wait();
	}

	if (chooser.value() == NULL)
	{
		cout << "(User hit 'Cacel')" << endl; 
		maze_arr = save_maze;
		output_Maze = before_Maze;
		result_maze = before_result;
		Text_button.ClearValue();	Int_button.ClearValue();	Char_button.ClearValue();
		cancel = 1;
		return;
	}


	ifstream ist{ chooser.value() };
	if (!ist) error("입력 파일을 열 수 없음 : ", chooser.value());

	string in_line;

	int catched = 0; int arr_x = 0; int arr_y = -1;
	int line = 0; int sp = 0;
	try {
		int select_w = 0;	int diff_word = 0; int count = 0;
		while (getline(ist, in_line)) {
			if (Which_type == 1) {// 1:int, 2: char
				for (int i = 0; i < in_line.size(); i++) {
					if (((char)48 <= (char)in_line.at(i) && (char)in_line.at(i) <= (char)57) || (char)in_line.at(i) == (char)32) {	// 0~9 문자, 띄어쓰기인 경우
						if (in_line.at(i) == '1') {
							count++; select_w++;
							if (count == 2) {
								count = 0;
								arr_y++; maze_arr[arr_x][arr_y] = 1;
							}

						}
						else if (in_line.at(i) == '0') {	// 출발점
							count = 2; i++; select_w++; sp++;
								arr_y++; maze_arr[arr_x][arr_y] = 3;
								start_X = arr_x; start_Y = arr_y;
							
						}
						else if (in_line.at(i) == ' ') {
							sp++; count++; 
							if (count == 2) {
								count = 0;
								arr_y++;  maze_arr[arr_x][arr_y] = 0;
							}
						}
						else if (in_line.at(i) == '2') {
							arr_y++; count == 2; i++; select_w++; sp++;
							 maze_arr[arr_x][arr_y] = 4;
								goal_X = arr_x; goal_Y = arr_y;
							
						}
						else {
							count++; select_w++;
							if (count == 2) {
								count = 0;
								arr_y++; maze_arr[arr_x][arr_y] = 1;
							}
						}
					}
					else {
						diff_word++; count++;
						if (count == 2) {
							count = 0;
							arr_y++; maze_arr[arr_x][arr_y] = 1;
						}
					}
				}
				cout << endl;
				
			}

			else if (Which_type == 2) {
				for (int i = 0; i < in_line.size(); i++) {
					if (((char)65 <= (char)in_line.at(i) && (char)in_line.at(i) <= (char)90) || (char)in_line.at(i) == (char)32) {	// 0~9 문자, 띄어쓰기인 경우
						if (in_line.at(i) == 'X') {
							count++; select_w++;
							if (count == 2) {
								count = 0;
								arr_y++; maze_arr[arr_x][arr_y] = 1;
								cout << maze_arr[arr_x][arr_y];
							}
						}
						else if (in_line.at(i) == 'P') {	// 출발점
							count == 2; i++; select_w++; sp++;
							arr_y++; maze_arr[arr_x][arr_y] = 3;
							start_X = arr_x; start_Y = arr_y;
							cout << maze_arr[arr_x][arr_y];
						}
						else if (in_line.at(i) == ' ') {
							sp++; count++;
							if (count == 2) {
								count = 0;
								arr_y++;  maze_arr[arr_x][arr_y] = 0;
								cout << maze_arr[arr_x][arr_y];
							}
						}
						else if (in_line.at(i) == 'H') {
							arr_y++; count == 2; i++; select_w++; sp++;
							maze_arr[arr_x][arr_y] = 4;
							goal_X = arr_x; goal_Y = arr_y;
							cout << maze_arr[arr_x][arr_y];
						}
						else {
							count++; select_w++;
							if (count == 2) {
								count = 0;
								arr_y++; maze_arr[arr_x][arr_y] = 1;
								cout << maze_arr[arr_x][arr_y];
							}
						}
					}
					else {
						diff_word++; count++;
						if (in_line.at(i) == '0') {
							arr_y++; maze_arr[arr_x][arr_y] = 3; i++;
							start_X = arr_x; start_Y = arr_y;
							cout << maze_arr[arr_x][arr_y];
						}
						if (in_line.at(i) == '2') {
							arr_y++; maze_arr[arr_x][arr_y] = 4; i++;
							goal_X = arr_x; goal_Y = arr_y;
							cout << maze_arr[arr_x][arr_y];
						}
						if (count == 2) {
							count = 0;
							arr_y++; maze_arr[arr_x][arr_y] = 1;
							cout << maze_arr[arr_x][arr_y];
						}
					}

				}
				cout << endl;
			}
			cout << endl;
			arr_x++; arr_y = -1; line++;
			if (line == 11) {
				if ((diff_word+sp) == 242) {	// 전체 다를 때 타입 바꾸기만 해주기
					for (int i = 0; i < 11; i++) {
						for (int j = 0; j < 11; j++) {
							cout <<maze_arr[i][j];
						}
						cout << endl;
					}
					throw catched = 0;
				}
				else if ((select_w + sp) == 242) {
					break;
				}
				if (select_w > diff_word) {
					output_Maze = "";	// 특정 단어만 바꾸기.
					throw catched = 1;
				}
				else {
					if (Which_type == 1) {
						Which_type = 2;
						Int_button.ClearValue();	Char_button.SetValue();
					}
					else if (Which_type == 2) {
						Which_type = 1;
						Char_button.ClearValue();	Int_button.SetValue();
					}
					throw  catched = 1;
				}
			}
		}


		for (int i = 0; i < 11; i++) {
			for (int j = 0; j < 11; j++) {
				cout << maze_arr[i][j];
			}
			cout << endl;
		}
		cout << endl;

		for (int i = 0; i < 11; i++) {
			for (int j = 0; j < 11; j++) {
				if (maze_arr[i][j] == 0)
					output_Maze.append("    ");
				else if (maze_arr[i][j] == 3) {
					if (Which_type == 1)
						output_Maze.append("2  ");
					else if (Which_type == 2)
						output_Maze.append("P  ");
				}
				else if (maze_arr[i][j] == 4) {
					if (Which_type == 1)
						output_Maze.append("4  ");
					else if (Which_type == 2)
						output_Maze.append("H  ");
				}
				else {
					if (Which_type == 1)
						output_Maze.append("11");
					else if (Which_type == 2)
						output_Maze.append("XX");
				}
			}
			output_Maze.append("\n");
		}
		before_Maze = output_Maze;
		result_maze = "";
		before_result = result_maze;
		save_maze = maze_arr;
		
	}
	catch (int catched) {
		if (catched == 0) {
			if (Which_type == 1) {
				fl_choice("You chose the Wrong Type", "Change the Type", 0, 0);
				Which_type = 2;
				Int_button.ClearValue();	Char_button.SetValue();	
				result_maze = "";
			}
			else if (Which_type == 2) {
				fl_choice("You chose the Wrong Type", "Change the Type", 0, 0);
				Which_type = 1;
				Char_button.ClearValue();	Int_button.SetValue();
				result_maze = "";
			}
			maze_arr[start_X][start_Y] = 3;
			maze_arr[goal_X][goal_Y] = 4;
			for (int i = 0; i < 11; i++) {
				for (int j = 0; j < 11; j++) {
					if (maze_arr[i][j] == 0)
						output_Maze.append("    ");
					else if (maze_arr[i][j] == 3) {
						if (Which_type == 1)
							output_Maze.append("2  ");
						else if (Which_type == 2)
							output_Maze.append("P  ");
					}
					else if (maze_arr[i][j] == 4) {
						if (Which_type == 1)
							output_Maze.append("4  ");
						else if (Which_type == 2)
							output_Maze.append("H  ");
					}
					else {
						if (Which_type == 1)
							output_Maze.append("11");
						else if (Which_type == 2)
							output_Maze.append("XX");
					}
				}
				output_Maze.append("\n");
			}
			before_Maze = output_Maze;
			before_result = result_maze;
			cout << output_Maze;
			cout << endl;
			result_maze = "";
		}
		else if (catched == 1) { // 문자 바꿔주기
			fl_choice("File has wrong type of word", "Change the Type", 0, 0);

			vector<string> edit;
			int i = 0; string to_output = "";
			ifstream ist{ chooser.value() };
			while (getline(ist, in_line)) {
				for (int i = 0; i < in_line.size(); i++) {
					if (Which_type == 1) {	// type이 int로 선택 되었는데 char가 들어온 경우
						create_count = 1;
						if (((char)48 <= (char)in_line.at(i) && (char)in_line.at(i) <= (char)57) || (char)in_line.at(i) == (char)32) {
							if (in_line.at(i) == '1' ) {
								to_output.append("1");
							}
							else if (in_line.at(i) == '0') {
								to_output.append("2");
							}
							else if (in_line.at(i) == '2') {
								to_output.append("4");
							}
							else if (in_line.at(i) == ' ') {
								to_output.append("  ");
							}
							else {
								to_output.append("1");
								in_line = in_line.replace(i, 1, "1");
							}
						}
						else {
							to_output.append("1");
							in_line = in_line.replace(i, 1, "1");
						}

					}
					else if (Which_type == 2) { // type이 char로 선택 되었는데 int가 들어온 경우
						create_count = 1;
						if (((char)65 <= (char)in_line.at(i) && (char)in_line.at(i) <= (char)90) || (char)in_line.at(i) == (char)32) {
							if (in_line.at(i) == 'X') {
								to_output.append("X");
							}
							else if (in_line.at(i) == 'P') {
								to_output.append("P");
							}
							else if (in_line.at(i) == 'H') {
								to_output.append("H");
							}
							else if (in_line.at(i) == ' ') {
								to_output.append("  ");
							}
							else {
								to_output.append("X");
								in_line = in_line.replace(i, 1, "X");
							}
						}
						else {
							to_output.append("X");
							in_line = in_line.replace(i, 1, "X");
						}
					}
				}
				to_output.append("\n");
				edit.push_back(in_line + "\n");
				cout << in_line << endl;
				i++;
			}

			for (int i = 0; i < edit.size(); i++) {
				cout << edit[i];
			}

			ofstream ost;
			ost.open(chooser.value());
			if (ost.is_open()) {
				for (int i = 0; i < 11; i++) {
					ost << edit[i];
				}
			}
			ost.close();

			output_Maze = to_output;
			before_Maze = output_Maze;
			before_result = result_maze;
			result_maze = "";
		}
	}

}

void Maze_window::Create_random() {		// 
	srand(time(0));

	int door = 0;

	vector < vector < bool > > maze;
	list < pair < int, int> > drillers;

	maze.resize(maze_size_y);
	for (size_t y = 0; y < maze_size_y; y++)
		maze[y].resize(maze_size_x);

	for (size_t x = 0; x < maze_size_x; x++)
		for (size_t y = 0; y < maze_size_y; y++)
			maze[y][x] = false;

	drillers.push_back(make_pair(maze_size_x / 2, maze_size_y / 2));
	while (drillers.size() > 0)
	{
		list < pair < int, int> >::iterator m, _m, temp;
		m = drillers.begin();
		_m = drillers.end();
		while (m != _m)
		{
			bool remove_driller = false;
			switch (rand() % 4)
			{
			case 0:
				(*m).second -= 2;
				if ((*m).second < 0 || maze[(*m).second][(*m).first])
				{
					remove_driller = true;
					break;
				}
				maze[(*m).second + 1][(*m).first] = true;
				break;
			case 1:
				(*m).second += 2;
				if ((*m).second >= maze_size_y || maze[(*m).second][(*m).first])
				{
					remove_driller = true;
					break;
				}
				maze[(*m).second - 1][(*m).first] = true;
				break;
			case 2:
				(*m).first -= 2;
				if ((*m).first < 0 || maze[(*m).second][(*m).first])
				{
					remove_driller = true;
					break;
				}
				maze[(*m).second][(*m).first + 1] = true;
				break;
			case 3:
				(*m).first += 2;
				if ((*m).first >= maze_size_x || maze[(*m).second][(*m).first])
				{
					remove_driller = true;
					break;
				}
				maze[(*m).second][(*m).first - 1] = true;
				break;
			}
			if (remove_driller)
				m = drillers.erase(m);
			else
			{
				drillers.push_back(make_pair((*m).first, (*m).second));
				drillers.push_back(make_pair((*m).first, (*m).second));

				maze[(*m).second][(*m).first] = true;
				++m;
			}
		}
	}

	for (int i = 0; i < 11; i++) {
		maze_arr[i] = new int[11];
	}

	for (int i = 0; i < 11; i++) {
		maze_st[i] = new string[11];
	}

	int start = 0;	int end = 0;
	for (size_t y = 0; y < maze_size_y - 1; y++) {
		for (size_t x = 0; x < maze_size_x - 1; x++)
		{
			if (maze[y][x] == true) {
				if (y == 0 || y == maze_size_y - 2 || x == 0 || x == maze_size_x - 2) {
					door++;
					if (start == 0) {
						maze_arr[y][x] = 3;
						maze_st[y][x] = "Go"; start++;
						start_X = y;
						start_Y = x;
						continue;
					}
				}
				maze_arr[y][x] = 0;
				maze_st[y][x] = "  ";
			}
			else {
				if (Which_type == 1) {
					maze_arr[y][x] = 1;
					maze_st[y][x] = "11";
				}
				else if (Which_type == 2) {
					maze_arr[y][x] = 1;
					maze_st[y][x] = "XX";
				}
			}
		}
	}

	for (int i = maze_size_y - 2; i >= 0; i--) {
		for (int j = maze_size_x - 2; j >= 0; j--) {
			if (maze[i][j] == true) {
				if (end == 0) {
					maze_arr[i][j] = 4;
					maze_st[i][j] = "Fi"; end++;
					goal_X = i; goal_Y = j;
					break;
				}
			}
		}
		if (end == 1)
			break;
	}

	for (size_t y = 0; y < maze_size_y - 1; y++) {
		for (size_t x = 0; x < maze_size_x - 1; x++)
		{
			if (maze[y][x] == true) {
				if (maze_arr[y][x] == 3) {
					if (Which_type == 1) {
						output_Maze.append("2  ");
					}
					if (Which_type == 2) {
						output_Maze.append("P  ");
					}
					continue;
				}
				if (maze_arr[y][x] == 4) {
					if (Which_type == 1) {
						output_Maze.append("4  ");
					}
					if (Which_type == 2) {
						output_Maze.append("H  ");
					}	continue;
				}
				output_Maze.append("    ");
			}
			else {
				if (Which_type == 1) {
					output_Maze.append(maze_st[y][x]);
				}
				else if (Which_type == 2) {
					output_Maze.append(maze_st[y][x]);
				}
			}
		}
		output_Maze.append("\n");
	}


	if (door <= 2) {
		output_Maze = "";
		for (int i = 0; i < maze_size_y - 1; i++) {
			for (int j = 0; j < maze_size_x - 1; j++) {
				maze_arr[i][j] = 0;
			}
		}
		Create_random();
	}

}

int main() {

	try {

		Maze_window win(Point(1000, 300), 470, 470, "MAZE");
		return gui_main();
	}
	catch (exception& e) {
		cerr << "exception: " << e.what() << '\n';
		return 1;
	}
	catch (...) {
		cerr << "Some exception\n";
		return 2;
	}

}