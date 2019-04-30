#pragma once
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
#include "Maze_Control.h"
#include "Maze_Maker.h"
#include "Maze_Changer.h"
#include "Maze_Finder.h"
#include "Maze_Display.h"

using namespace std;
using namespace Graph_lib;


class Maze_window :Window {

public:
	Maze_window(Point xy, int w, int h, const string& title);
	Out_box Display;
	Out_box Answer_of_Maze;

	void Clear_allBtn();
	void SetInt_Btn();
	void SetChar_Btn();

private:
	Maze_Control cMaze_Control;		

private:
	Text Maze;
	Text Display_Maze;

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

	static void cb_exit(Address, Address);
	void Exit();
	static void cb_create(Address, Address);
	void Create();
	void printMaze(int** maze, int xLoc, int yLoc);
	void final_maze();
	static void cb_find(Address, Address);
	void find();
	void Display_Record();

	static void cb_random(Address, Address);
	void Random();
	void Create_random();
	void Create_text();
	static void cb_text(Address, Address);
	void Text();

	static void cb_int(Address, Address);
	void Int();
	static void cb_char(Address, Address);
	void Char();
	int mazeTraverse(int** maze, int xLoc, int yLoc, int facing);
	
	void Give_SelectCaution();
	void Give_CreateCaution();

	template<typename T>
	inline void InitWidget(T &sp, int fontSize = 15)
	{
		attach(sp);
	}

	template<>
	inline void InitWidget(Graph_lib::Rectangle &sp, int fontSize)
	{
		attach(sp);
		sp.set_color(Color::black);
	}

	template<>
	inline void InitWidget(Graph_lib::Text &sp, int fontSize)
	{
		attach(sp);
		sp.set_color(Color::black);
		sp.set_font_size(fontSize);
	}
};
