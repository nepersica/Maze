
//
// This is a GUI support code to the chapters 12-16 of the book
// "Programming -- Principles and Practice Using C++" by Bjarne Stroustrup
//

#include "Simple_window.h"

//------------------------------------------------------------------------------

Simple_window::Simple_window(Point xy, int w, int h, const string& title) :
    Window(xy,w,h,title),
    Exit_button(Point(x_max()-70,0), 70, 20, "Exit", cb_exit),
	Create_Maze_button(Point(50,y_max()-100), 120, 40, "Create Maze", cb_create),
	Find_Route_Button(Point(200, y_max() - 100), 120, 40, "Find Maze", cb_find),
    button_pushed(false)
{
    attach(Exit_button);
	attach(Create_Maze_button);
	attach(Find_Route_Button);
}
	

//------------------------------------------------------------------------------

bool Simple_window::wait_for_button()
// 수정된 이벤트 루프.
// 모든 이벤트를 (기본 동작대로) 처리하고, button_pushed가 true이면 대기 종료.
// 이 함수를 바탕으로 제어 반전 없이 그래픽스를 처리할 수 있다.
{
    show();
#if 1
    // Simpler handler
    while (!button_pushed) Fl::wait();	// wait()는 무언가를 처리할 때마다 사용자 코드로 반환해 어떤 일을 수행할 수 있는 기회를 줌.
	button_pushed = false;
    Fl::redraw();
#else
    // To handle the case where the user presses the X button in the window frame
    // to kill the application, change the condition to 0 to enable this branch.
    Fl::run();
#endif
    return button_pushed;
}

//------------------------------------------------------------------------------

// **cb_exit()함수는 시스템에서 욕우하는 콜백에 대한 규칙을 일반적인 멤버 함수 호출로 변환.
// exit()에서 우리가 하려는 작업을 수행함.
void Simple_window::cb_exit(Address, Address pw)
// pw에 위치한 윈도우의 Simple_window::exit() 호출.
{  
    reference_to<Simple_window>(pw).exit();    
}

//------------------------------------------------------------------------------

void Simple_window::exit()
{
    button_pushed = true;
    hide();
}

//------------------------------------------------------------------ 미로 생성

void Simple_window::cb_create(Address, Address pw) {
	reference_to<Simple_window>(pw).create();
}

void Simple_window::create() {
	button_pushed = true;
}

 //------------------------------------------------------------------ 미로 찾기

void Simple_window::cb_find(Address, Address pw) {
	reference_to<Simple_window>(pw).find();
}

void Simple_window::find() {
	button_pushed = true;
}