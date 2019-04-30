#include "Maze_windows.h"
#include "Maze_Control.h"


Maze_window::Maze_window(Point xy, int w, int h, const string& title)
	:Window(xy, w, h, title),

	Maze(Point(40, 40), "<< MAZE GAME XD >>"),
	Display_Maze(Point(40, 40), ""),
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
	result(Point(40, 40), ""),
	Answer_of_Maze(Point(x_max() - 215, y_max() - 215), 200, 200, "")

{
	// attach 함수 -> InitWidget
	InitWidget(Maze, 20);
	InitWidget(Mode_text);
	InitWidget(Type_text);
	InitWidget(Answer);
	InitWidget(Display_Maze);

	InitWidget(Mode_rect);
	InitWidget(Type_rect);


	InitWidget(Display);

	InitWidget(Quit_button);
	InitWidget(Create_button);
	InitWidget(Find_button);

	InitWidget(Random_button);
	InitWidget(Text_button);

	InitWidget(Int_button);
	InitWidget(Char_button);

	InitWidget(Answer_of_Maze);
}

void Maze_window::cb_int(Address, Address pw)
{
	reference_to<Maze_window>(pw).Int();
}

void Maze_window::Int()
{
	cMaze_Control.SetWhich_type(MAZE_TYPE::INT);
	Char_button.ClearValue();
}

void Maze_window::cb_char(Address, Address pw)
{
	reference_to<Maze_window>(pw).Char();
}

void Maze_window::Char()
{
	cMaze_Control.SetWhich_type(MAZE_TYPE::CHAR);
	Int_button.ClearValue();
}
void Maze_window::cb_random(Address, Address pw)
{
	reference_to<Maze_window>(pw).Random();
}

void Maze_window::Random()
{
	cMaze_Control.SetWhich_mode(MAZE_MODE::RANDOM);
	Text_button.ClearValue();
}

void Maze_window::cb_text(Address, Address pw)
{
	reference_to<Maze_window>(pw).Text();
}

void Maze_window::Text()
{
	cMaze_Control.SetWhich_mode(MAZE_MODE::TEXT);
	Random_button.ClearValue();
}

void Maze_window::cb_exit(Address, Address pw)
{
	reference_to<Maze_window>(pw).Exit();
}

void Maze_window::Exit()
{
	hide();
}

void Maze_window::cb_create(Address, Address pw)
{
	reference_to<Maze_window>(pw).Create();
}

void Maze_window::Create()
{
	cMaze_Control.Set_Createstate();
	if (cMaze_Control.GetWhich_mode() == MAZE_MODE::RANDOM		// Random
		&& cMaze_Control.GetWhich_type() != MAZE_TYPE::NONE)
	{	
		Maze_Maker::Create_random(cMaze_Control);
		Display.put(Maze_Display::Float2Display(cMaze_Control));

		Maze_Display::ToBlank_AnswerBox(cMaze_Control);
		Answer_of_Maze.put(cMaze_Control.Get_ResultMaze());
	}
	else if (cMaze_Control.GetWhich_mode() == MAZE_MODE::TEXT	// Text
		&& cMaze_Control.GetWhich_type() != MAZE_TYPE::NONE)
	{	

		Maze_Maker::Create_text(cMaze_Control);
		switch (cMaze_Control.GetWhich_error())
		{
		case ERROR_CODE::CNGCHAR:
			Display.put(Maze_Display::Float2Display(cMaze_Control));
			Maze_window::SetChar_Btn();
			/*Maze_Display::ToBlank_AnswerBox(cMaze_Control);
			Answer_of_Maze.put(cMaze_Control.Get_ResultMaze());*/
			break;
		case ERROR_CODE::CNGINT:
			Display.put(Maze_Display::Float2Display(cMaze_Control));
			Maze_window::SetInt_Btn();
			/*Maze_Display::ToBlank_AnswerBox(cMaze_Control);
			Answer_of_Maze.put(cMaze_Control.Get_ResultMaze());*/
			break;
		case ERROR_CODE::SUCCESS:
			Display.put(Maze_Display::Float2Display(cMaze_Control));
			break;
		/*case ERROR_CODE::FAIL:
			cMaze_Control.Set_ResultMaze(cMaze_Control.Get_BeforeResult());
			cout << cMaze_Control.Get_ResultMaze() << endl;
			Clear_allBtn();
			cMaze_Control.SetWhich_type(MAZE_TYPE::NONE);
			cMaze_Control.SetWhich_mode(MAZE_MODE::NONE);
			break;*/
		}
		if (cMaze_Control.GetWhich_error() == ERROR_CODE::FAIL)
		{
			/*cMaze_Control.Set_ResultMaze(cMaze_Control.Get_BeforeResult());*/
			Answer_of_Maze.put(cMaze_Control.Get_BeforeResult());
			cout << cMaze_Control.Get_ResultMaze() << endl;
			Clear_allBtn();
			cMaze_Control.SetWhich_type(MAZE_TYPE::NONE);
			cMaze_Control.SetWhich_mode(MAZE_MODE::NONE);
		}
		else
		{
			Maze_Display::ToBlank_AnswerBox(cMaze_Control);
			Answer_of_Maze.put(cMaze_Control.Get_ResultMaze());
		}
		// 추가
		cMaze_Control.SaveBefore_error(cMaze_Control.GetWhich_error());
	}
	else
	{
		cMaze_Control.Reset_Createstate();
		Give_SelectCaution(); 
	}
	cMaze_Control.Set_BeforeMaze();
	cMaze_Control.ResetOutput_Maze();
}

void Maze_window::cb_find(Address, Address pw)
{
	reference_to<Maze_window>(pw).find();
}

void Maze_window::find()
{
	if (cMaze_Control.Get_Createstate() == false || cMaze_Control.GetBefore_error() == ERROR_CODE::FAIL)	// 실패한 경우.
	{
		Answer_of_Maze.put(cMaze_Control.Get_BeforeResult());
		Give_SelectCaution();
	}
	else
	{
		Maze_Finder::Maze_Traverse(cMaze_Control.Getstart_X(), cMaze_Control.Getstart_Y(), 1, cMaze_Control);
		Display_Record();
		Answer_of_Maze.put(cMaze_Control.Get_ResultMaze());
		
		cMaze_Control.ClearData();	Clear_allBtn();
	}
	
}

void Maze_window::Display_Record()
{
	for (int i = 0; i < cMaze_Control.SizeofRecord(); i++)
	{
		flush();
		Display.put(Maze_Display::GetIdxRecord(i, cMaze_Control));
		Sleep(100);
	}
	cMaze_Control.Set_ResultMaze(Maze_Display::GetIdxRecord(cMaze_Control.SizeofRecord() - 1, cMaze_Control));
	cMaze_Control.Set_BeforeResult(Maze_Display::GetIdxRecord(cMaze_Control.SizeofRecord() - 1, cMaze_Control));
}

void Maze_window::Clear_allBtn()
{
	Random_button.ClearValue();	Text_button.ClearValue();
	Int_button.ClearValue();	Char_button.ClearValue();
}

void Maze_window::SetInt_Btn()
{
	Char_button.ClearValue();	Int_button.SetValue();
}

void Maze_window::SetChar_Btn()
{
	Int_button.ClearValue();	Char_button.SetValue();
}

void Maze_window::Give_SelectCaution()
{
	fl_choice("Select Mode or Type of the Maze !", "Okay", 0, 0);
	Clear_allBtn();
	cMaze_Control.SetWhich_type(MAZE_TYPE::NONE);
	cMaze_Control.SetWhich_mode(MAZE_MODE::NONE);
}

void Maze_window::Give_CreateCaution()
{
	fl_choice("Create the Maze first !", "Okay", 0, 0);
}