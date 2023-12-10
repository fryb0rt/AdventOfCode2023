#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iomanip>      // std::setw

struct Point {
	int x, y;
	int step;
};
struct Tile
{
	char symbol;
	int distance = -1;
	Point previous;
	bool done = false;
};

int computeArea(std::vector < std::vector<Tile>> tilesOrig, int x, int y) {
	auto tiles = tilesOrig;
	for (auto& tLine : tiles) {
		for (auto& t : tLine) {
			t.symbol = '.';
			t.done = false;
		}
	}
	while (!tiles[y][x].done) {
		tiles[y][x].done = true;
		int xx = tiles[y][x].previous.x;
		int yy = tiles[y][x].previous.y;
		tiles[y][x].symbol = tilesOrig[y][x].symbol;
		x = xx;
		y = yy;
	}
	std::vector<std::vector<bool>> visited(tiles.size() + 1);
	for (auto& v : visited) {
		v.resize(tiles[0].size() + 1, false);
	}
	std::vector<Point> stack = { Point{0,0} };
	while (!stack.empty()) {
		Point p = stack.back();
		stack.pop_back();
		if (visited[p.y][p.x]) {
			continue;
		}
		visited[p.y][p.x] = true;
		for (int y = std::max(p.y - 1, 0); y <= std::min(p.y, int(tiles.size() - 1)); ++y) {
			for (int x = std::max(p.x - 1, 0); x <= std::min(p.x, int(tiles[0].size() - 1)); ++x) {
				if (tiles[y][x].symbol == '.') {
					tiles[y][x].symbol = '0';
				}
			}
		}
		const auto move = [&](int x, int y, int direction) {
			if (y < 0 || y >= visited.size() || x < 0 || x >= visited[0].size()) {
				return;
			}
			switch (direction) {
			case 0: // UP
				if ((x == 0 || !(tiles[y][x - 1].symbol == '-' || tiles[y][x - 1].symbol == 'L' || tiles[y][x - 1].symbol == 'F')) &&
					(x == tiles[0].size() || !(tiles[y][x].symbol == '-' || tiles[y][x].symbol == 'J' || tiles[y][x].symbol == '7'))) {
					stack.push_back(Point{ x,y });
				}
				break;
			case 1: // DOWN
				if ((x == 0 || !(tiles[p.y][x - 1].symbol == '-' || tiles[p.y][x - 1].symbol == 'L' || tiles[p.y][x - 1].symbol == 'F')) &&
					(x == tiles[0].size() || !(tiles[p.y][x].symbol == '-' || tiles[p.y][x].symbol == 'J' || tiles[p.y][x].symbol == '7'))) {
					stack.push_back(Point{ x,y });
				}
				break;
			case 2: // LEFT
				if ((y == 0 || !(tiles[y - 1][x].symbol == '|' || tiles[y - 1][x].symbol == '7' || tiles[y - 1][x].symbol == 'F')) &&
					(y == tiles.size() || !(tiles[y][x].symbol == '|' || tiles[y][x].symbol == 'L' || tiles[y][x].symbol == 'J'))) {
					stack.push_back(Point{ x,y });
				}
				break;
			case 3: // RIGHT
				if ((y == 0 || !(tiles[y - 1][p.x].symbol == '|' || tiles[y - 1][p.x].symbol == '7' || tiles[y - 1][p.x].symbol == 'F')) &&
					(y == tiles.size() || !(tiles[y][p.x].symbol == '|' || tiles[y][p.x].symbol == 'L' || tiles[y][p.x].symbol == 'J'))) {
					stack.push_back(Point{ x,y });
				}
				break;
			}
		};
		move(p.x, p.y - 1, 0);
		move(p.x, p.y + 1, 1);
		move(p.x - 1, p.y, 2);
		move(p.x + 1, p.y, 3);
	}
	int count = 0;
	for (auto& tLine : tiles) {
		for (auto& t : tLine) {
			if (t.symbol == '.') {
				++count;
			}
		}
	}
	return count;
}

int main()
{
	std::ifstream stream("..\\input10.txt");
	std::string line;

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
	int largest = -1;
	while (!stack.empty()) {
		Point p = stack.back();
		stack.pop_back();
		Tile& t = tiles[p.y][p.x];
		if (t.distance == -1 || p.step < t.distance) {
			t.distance = p.step;
			const auto add = [&](int xx, int yy) {
				if (yy < 0 || yy >= tiles.size()) {
					return;
				}
				if (xx < 0 || xx >= tiles[yy].size()) {
					return;
				}
				if (t.previous.x == xx && t.previous.y == yy) {
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
						n.distance = p.step + 1;
						n.previous = p;
						tiles[y][x].previous = Point{ xx,yy };
						if (tiles[y][x].symbol == 'S') {
							if (largest < p.step + 2) {
								largest = std::max(largest, p.step + 2);
								std::cout << computeArea(tiles, x, y) << std::endl;
							}
							return;
						}
						stack.push_back(Point{ x,y,p.step + 2 });
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
