#include "Simple_window.h"	// "Next" 버튼이 필요한 경우
#include "Graph.h"

int main() {

	Simple_window win{ Point{100,100}, 600, 400, "grid" };

	int x_size = win.x_max();	int y_size = win.y_max();
	int x_grid = 80;	int y_grid = 40;

	Lines grid;
	for (int x = x_grid; x < x_size; x += x_grid) 
		grid.add(Point{ x,0 }, Point{ x,y_size });
	for (int y = y_grid; y < y_size; y += y_grid)
		grid.add(Point{ 0,y }, Point{ x_size, y });

	grid.set_color(Color::red);
	grid.set_style(Line_style::dot);

	Open_polyline opl;
	opl.add(Point{ 100,100 });	opl.add(Point{ 150,200 });
	opl.add(Point{ 250,250 });	opl.add(Point{ 300,200 });
	opl.set_color(Color::invisible);

	Closed_polyline cpl;
	cpl.add(Point{ 100,100 });	cpl.add(Point{ 150,200 });
	cpl.add(Point{ 250,250 });	cpl.add(Point{ 300,200 });	cpl.add(Point{ 100, 250 });
	cpl.set_color(Color::invisible);

	Graph_lib::Rectangle rect00{ Point{150,100}, 200, 100 };
	Graph_lib::Rectangle rect11{ Point{ 50,50 }, Point{250,150} };
	Graph_lib::Rectangle rect12{ Point{ 50,150 }, Point{ 250,250 } };
	Graph_lib::Rectangle rect21{ Point{ 250,50 }, 200, 100};
	Graph_lib::Rectangle rect22{ Point{ 250,150 }, 200, 100 };
	rect00.set_color(Color::invisible); rect11.set_color(Color::invisible); rect12.set_color(Color::invisible);
	rect21.set_color(Color::invisible); rect22.set_color(Color::invisible);
	rect00.set_fill_color(Color::yellow); rect11.set_fill_color(Color::blue);
	rect12.set_fill_color(Color::red); rect21.set_fill_color(Color::dark_green);

	rect11.move(400, 0);
	rect11.set_fill_color(Color:: white);

	Text t{ Point{200,200}, "A closed polyline that isn't a polygon" };
	t.set_color(Color::white);

	Circle c1{ Point{100,200}, 50 };
	Circle c2{ Point{ 150,200 }, 100 };
	Circle c3{ Point{ 200,200 }, 150 };
	c1.set_color(Color::invisible);	c2.set_color(Color::invisible);	c3.set_color(Color::invisible);

	Graph_lib :: Ellipse e1{ Point{200,200}, 50, 50 };
	Graph_lib::Ellipse e2{ Point{ 200,200 }, 100, 50 };
	Graph_lib::Ellipse e3{ Point{ 200,200 }, 100, 150 };
	e1.set_color(Color::invisible);	e2.set_color(Color::invisible);	e3.set_color(Color::invisible);

	Marked_polyline mpl("1234");
	mpl.add(Point(100, 100));
	mpl.add(Point(150, 200));
	mpl.add(Point(250, 250));
	mpl.add(Point(300, 200));
	mpl.set_color(Color::invisible);
	

	Marks pp("x");
	pp.add(Point{ 100,100 });	pp.add(Point{ 150,200 });
	pp.add(Point{ 250,250 });	pp.add(Point{ 300,200 });
	pp.set_color(Color::invisible);

	Mark m1{ Point{ 100,200 }, 'x' };
	Mark m2{ Point{ 150,200 }, 'y' };
	Mark m3{ Point{ 200,200 }, 'z' };
	c1.set_color(Color::blue);
	c2.set_color(Color::red);
	c3.set_color(Color::green);

	Image rita{ Point{0,0},"images.jpg" };
	Image path{ Point{0,0}, "lulu.gif" };
	path.set_mask(Point{ 0,0 }, 600, 400);

	win.attach(grid);	win.attach(opl);	win.attach(cpl);
	win.attach(rect00);	win.attach(rect11);	win.attach(rect12);
	win.attach(rect21);	win.attach(rect22);	win.attach(t);
	win.attach(c1);	win.attach(c2);	win.attach(c3);
	win.attach(e1);	win.attach(e2);	win.attach(e3);
	//win.attach(mpl);	win.attach(pp);
	win.attach(m1);	win.attach(m2);	win.attach(m3);
	win.attach(rita);	win.attach(path);
	
	win.put_on_top(rita);

	win.wait_for_button();

}
