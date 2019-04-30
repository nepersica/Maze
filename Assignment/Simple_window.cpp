
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
// ������ �̺�Ʈ ����.
// ��� �̺�Ʈ�� (�⺻ ���۴��) ó���ϰ�, button_pushed�� true�̸� ��� ����.
// �� �Լ��� �������� ���� ���� ���� �׷��Ƚ��� ó���� �� �ִ�.
{
    show();
#if 1
    // Simpler handler
    while (!button_pushed) Fl::wait();	// wait()�� ���𰡸� ó���� ������ ����� �ڵ�� ��ȯ�� � ���� ������ �� �ִ� ��ȸ�� ��.
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

// **cb_exit()�Լ��� �ý��ۿ��� ����ϴ� �ݹ鿡 ���� ��Ģ�� �Ϲ����� ��� �Լ� ȣ��� ��ȯ.
// exit()���� �츮�� �Ϸ��� �۾��� ������.
void Simple_window::cb_exit(Address, Address pw)
// pw�� ��ġ�� �������� Simple_window::exit() ȣ��.
{  
    reference_to<Simple_window>(pw).exit();    
}

//------------------------------------------------------------------------------

void Simple_window::exit()
{
    button_pushed = true;
    hide();
}

//------------------------------------------------------------------ �̷� ����

void Simple_window::cb_create(Address, Address pw) {
	reference_to<Simple_window>(pw).create();
}

void Simple_window::create() {
	button_pushed = true;
}

 //------------------------------------------------------------------ �̷� ã��

void Simple_window::cb_find(Address, Address pw) {
	reference_to<Simple_window>(pw).find();
}

void Simple_window::find() {
	button_pushed = true;
}