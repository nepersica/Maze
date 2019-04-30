
//
// This is a GUI support code to the chapters 12-16 of the book
// "Programming -- Principles and Practice Using C++" by Bjarne Stroustrup
//

#ifndef SIMPLE_WINDOW_GUARD
#define SIMPLE_WINDOW_GUARD 1

#include "GUI.h"    // for Simple_window only (doesn't really belong in Window.h)
#include "Graph.h"

using namespace Graph_lib;

//------------------------------------------------------------------------------

struct Simple_window : Window {
    Simple_window(Point xy, int w, int h, const string& title );

    bool wait_for_button(); // simple event loop

private:
    Button Exit_button;     // the "next" button, Button은 모두 Widget.
    bool button_pushed;     // 상세 구현 -> exit()를 실행한 후 버튼이 눌렸는지 확인하는 용도.

    static void cb_exit(Address, Address); // Exit_button의 콜백 -> 버튼 입력을 발생시키는?
    void exit();            // Exit_button이 눌렸을 때 수행할 동작.

	//------------------------------------------  미로 생성 버튼
	
	Button Create_Maze_button;
	static void cb_create(Address, Address);
	void create();

	// ------------------------------------------  미로 찾기 버튼

	Button Find_Route_Button;
	static void cb_find(Address, Address);
	void find();

};

//------------------------------------------------------------------------------

#endif // SIMPLE_WINDOW_GUARD
