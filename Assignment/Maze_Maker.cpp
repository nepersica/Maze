// 미로 생성
#include "Maze_Maker.h"

void Maze_Maker::Create_random(Maze_Control &cmc) {		// 
	
	srand(time(0));

	int door = 0;

	vector < vector < bool > > maze;
	list < pair < int, int> > drillers;
	
	maze.resize(cmc.GetMAZE_SIZE_Y());

	for (size_t y = 0; y < cmc.GetMAZE_SIZE_Y(); y++)
		maze[y].resize(cmc.GetMAZE_SIZE_X());

	for (size_t x = 0; x < cmc.GetMAZE_SIZE_X(); x++)
		for (size_t y = 0; y < cmc.GetMAZE_SIZE_Y(); y++)
			maze[y][x] = false;

	drillers.push_back(make_pair(cmc.GetMAZE_SIZE_X() / 2, cmc.GetMAZE_SIZE_Y() / 2));
	while (drillers.size() > 0)
	{
		list < pair < int, int> >::iterator m, _m, temp;
		m = drillers.begin();
		_m = drillers.end();
		while (m != _m)
		{
			bool remove_driller = false;
			Maze_Idx temp_Idx;
			bool condition = false;
			switch (rand() % 4)
			{
			case 0:
				temp_Idx = Maze_Idx(0, -2, 1, 0);
				ChangeIdxToM(m, temp_Idx);
				condition = (*m).second < 0 || maze[(*m).second][(*m).first];				
				break;
			case 1:
				temp_Idx = Maze_Idx(0, 2, -1, 0);
				ChangeIdxToM(m, temp_Idx);
				condition = (*m).second >= cmc.GetMAZE_SIZE_Y() || maze[(*m).second][(*m).first];				
				break;
			case 2:
				temp_Idx = Maze_Idx(-2, 0, 0, 1);
				ChangeIdxToM(m, temp_Idx);
				condition = (*m).first < 0 || maze[(*m).second][(*m).first];				
				break;
			case 3:
				temp_Idx = Maze_Idx(2, 0, 0, -1);
				ChangeIdxToM(m, temp_Idx);
				condition = (*m).first >= cmc.GetMAZE_SIZE_X() || maze[(*m).second][(*m).first];				
				break;
			}

			Make_Maze_Step(remove_driller,
				condition, maze, m, temp_Idx);

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

	door = boolTOint(maze, cmc, door);

	if (door <= 2) {
		cmc.ResetOutput_Maze();
		cmc.ResetMaze_arr();
		Create_random(cmc);
	}
}

int Maze_Maker::boolTOint(vector<vector<bool>> maze, Maze_Control &cmc, int door) {
	int start = 0; int end = 0;
	int maze_arr[11][11];

	for (int i = 0; i < 11; i++) {
		for (int j = 0; j < 11; j++) {
			if (maze[i][j] == true) {
				if (i == 0 || j == 10 || i == 0 || j == 10) {
					door++;
					if (start == 0) {
						maze_arr[i][j] = 3; start++;
						cmc.Setstart_X(i);	cmc.Setstart_Y(j);
						continue;
					}
						
				}
				maze_arr[i][j] = 0;
			}
			else {
				maze_arr[i][j] = 1;
			}
		}
	}


	for (int i = 10; i >= 0; i--) {
		for (int j = 10; j >= 0; j--) {
			if (maze[i][j] == true) {
				if (end == 0) {
					maze_arr[i][j] = 4; end++;
					cmc.Setgoal_X(i); cmc.Setgoal_Y(j);
					break;
				}
			}
		}
		if (end == 1)
			break;
	}
	cmc.CopyMaze_arr(maze_arr, 11, 11);

	Maze_Changer::arrToStr(maze_arr, cmc);

	return door;
}

void Maze_Maker::Create_text(Maze_Control &cmc) {
	Fl_File_Chooser chooser(".", "*.txt", Fl_File_Chooser::MULTI, "File Chooser");        // title
	chooser.show();

	while (chooser.shown())
	{
		Fl::wait();
	}

	if (chooser.value() == NULL)
	{
		cout << "(User hit 'Cacel')" << endl;
		cmc.SetWhich_error(ERROR_CODE::FAIL);
		
	}
	else {
		ifstream ist{ chooser.value() };
		if (!ist) error("입력 파일을 열 수 없음 : ", chooser.value());
		cmc.SetWhich_error((Maze_Changer::Analyze_file(ist, cmc)));

		if (cmc.GetWhich_catch() == CATCH_ERROR::EDITFILE)
		{
			ofstream ost;
			ost.open(chooser.value());
			if (ost.is_open())
			{
				ost << Maze_Changer::Control_sp(cmc);
			}
			ost.close();
		}
		cmc.SetWhich_catch(CATCH_ERROR::NONE);
	}
}

