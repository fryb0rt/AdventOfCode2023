#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

int main()
{
	std::ifstream stream("..\\input10.txt");
	std::string line;
	struct Point {
		int x, y;
		int step;
		char previous;
	};
	struct Tile
	{
		char symbol;
		int distance = -1;
	};
	std::vector<std::vector<Tile>> tiles;
	int sum = 0;
	
	Point start;
	{
		int y = 0;
		while (std::getline(stream, line)) {
			if (line.empty()) {
				continue;
			}
			std::vector<Tile> tileLine;
			int x = 0;
			for (char c : line) {
				tileLine.push_back(Tile{ c, -1 });
				if (c == 'S') {
					start.x = x;
					start.y = y;
					start.step = 0;
				}
				++x;
			}
			tiles.push_back(tileLine);
			++y;
		}
	}
	std::vector<Point> stack;
	stack.push_back(start);
	int largest = 0;
	while (!stack.empty()) {
		Point p = stack.back();
		stack.pop_back();
		Tile& t = tiles[p.y][p.x];
		if (t.symbol == 'S' && p.step > largest) {
			largest = std::max(largest, p.step);
			std::cout << largest / 2 << std::endl;
			continue;
		}
		if (t.distance == -1 || p.step < t.distance) {
			t.distance = p.step;
			const auto add = [&](int xx, int yy) {
				if (yy < 0 || yy >= tiles.size()) {
					return;
				}
				if (xx < 0 || xx >= tiles[yy].size()) {
					return;
				}
				Tile& n = tiles[yy][xx];
				const auto addNew = [&](int x, int y, std::string allowed) {
					if (y < 0 || y >= tiles.size()) {
						return;
					}
					if (x < 0 || x >= tiles[y].size()) {
						return;
					}
					if (allowed.find(tiles[y][x].symbol) != std::string::npos) {
						stack.push_back(Point{ x,y,p.step + 2, n.symbol });
					}
				};
				switch (n.symbol) {
				case '|':
					if (xx == p.x) {
						if (yy < p.y) {
							addNew(xx, yy - 1, "F7|S");
						}
						else {
							addNew(xx, yy + 1, "LJ|S");
						}
					}
					break;
				case '-':
					if (yy == p.y) {
						if (xx < p.x) {
							addNew(xx - 1, yy, "LF-S");
						}
						else {
							addNew(xx + 1, yy, "J7-S");
						}
					}
					break;
				case 'L':
					if (yy == p.y && xx == p.x - 1) {
						addNew(xx, yy - 1, "F7|S");
					}
					if (yy == p.y + 1 && xx == p.x) {
						addNew(xx + 1, yy, "J7-S");
						
					}
					break;
				case 'J':
					if (yy == p.y && xx == p.x + 1) {
						addNew(xx, yy - 1, "F7|S");
					}
					if (yy == p.y + 1 && xx == p.x) {
						addNew(xx - 1, yy, "LF-S");
					}
					break;
				case '7':
					if (yy == p.y && xx == p.x + 1) {
						addNew(xx, yy + 1, "LJ|S");
					}
					if (yy == p.y - 1 && xx == p.x) {
						addNew(xx - 1, yy, "LF-S");
					}
					break;
				case 'F':
					if (yy == p.y && xx == p.x - 1) {
						addNew(xx, yy + 1, "LJ|S");
					}
					if (yy == p.y - 1 && xx == p.x) {
						addNew(xx + 1, yy, "J7-S");
					}
					break;
				default:break;
				}
			};
			add(p.x, p.y + 1);
			add(p.x, p.y - 1);
			add(p.x + 1, p.y);
			add(p.x - 1, p.y);
		}
	}
}