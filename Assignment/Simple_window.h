
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
    Button Exit_button;     // the "next" button, Button�� ��� Widget.
    bool button_pushed;     // �� ���� -> exit()�� ������ �� ��ư�� ���ȴ��� Ȯ���ϴ� �뵵.

    static void cb_exit(Address, Address); // Exit_button�� �ݹ� -> ��ư �Է��� �߻���Ű��?
    void exit();            // Exit_button�� ������ �� ������ ����.

	//------------------------------------------  �̷� ���� ��ư
	
	Button Create_Maze_button;
	static void cb_create(Address, Address);
	void create();

	// ------------------------------------------  �̷� ã�� ��ư

	Button Find_Route_Button;
	static void cb_find(Address, Address);
	void find();

};

//------------------------------------------------------------------------------

#endif // SIMPLE_WINDOW_GUARD
