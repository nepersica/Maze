#include "Maze_windows.h"


int main() {

	try {
		Maze_window win( Point(1000, 300), 470, 470, "MAZE");
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