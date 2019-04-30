#include <iostream>
#include <time.h>

using namespace std;

#define SIZE_X 20
#define SIZE_Y 20

int main() {

	int x = 0; int y = 0; int rotate; int count = 0;
	int map[SIZE_X][SIZE_Y];

	for (int i = 0; i < SIZE_Y; i++) {
		for (int j = 0; j < SIZE_X; j++) {
			map[j][i] = 0;
		}
	}

	srand(time(NULL));
	
	for (int i = 0; i < 100000; i++) {
			rotate = rand() % 4 + 1;	// 1:��, 2:����, 3:�Ʒ�, 4:��
			if (rotate == 1) {
				if (y == 0)	// ���� ������ �������� rotate�� �ٽ� �������ش�.
					continue;
				if (map[x][y - 2] == 0) {// �� ĭ ���� ����ٸ�
					y--;	map[x][y] == 1;
					y--;	map[x][y] == 1;
				}
				else
					y -= 2;
			}
			if (rotate == 2) {
				if (x == SIZE_X - 2)
					continue;
				if (map[x + 2][y] == 0) {
					x++;	map[x][y] = 1;
					x++; map[x][y] = 1;
				}
				else
					x += 2;
			}
			if (rotate == 3) {
				if (y == SIZE_Y - 2)
					continue;
				if (map[x][y + 2] == 0) {
					y++; map[x][y] = 1;
					y++; map[x][y] = 1;
				}
				else
					y += 2;
			}
			if (rotate == 4) {
				if (x == 0)
					continue;
				if (map[x - 2][y] == 0) {
					x--;	map[x][y] = 1;
					x--;	map[x][y] = 1;
				}
				else
					x -= 2;
			}
			if (count == 0) {
				map[x][y] == 2;
				count++;	
			}
	}

	for (int i = 0; i < SIZE_Y - 1; i++) {
		for (int j = 0; j < SIZE_X - 1; j++) {
			if (map[j][i] == 0)
				cout << "  ";
			if (map[j][i] == 1)
				cout << "xx";
			if (map[j][i] == 2)
				cout << "fr";
			if (map[j][i] == 3)
				cout << "to";
		}
		cout << endl;
	}
	system("pause");
}