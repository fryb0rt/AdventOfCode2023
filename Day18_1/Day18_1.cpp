#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iomanip>      // std::setw
#include <set>

int main()
{
	std::ifstream stream("..\\input18.txt");
	struct Line {
		char dir;
		int count;
		std::string color;
	};
	std::vector<Line> lines;
	std::string line;
	while (std::getline(stream, line)) {
		if (line.empty()) {
			continue;
		}
		std::istringstream iss(line);
		Line l;
		iss >> l.dir;
		iss >> l.count;
		iss >> l.color;
		lines.push_back(l);
	}
	int x = 0, y = 0;
	int maxx = 0, maxy = 0, minx = 0, miny = 0;
	for (Line& l : lines) {
		for (int i = 0; i < l.count; ++i) {
			switch (l.dir) {
			case 'R':
				++x;
				break;
			case 'L':
				--x;
				break;
			case 'D':
				++y;
				break;
			case 'U':
				--y;
				break;
			}
			maxx = std::max(x, maxx);
			maxy = std::max(y, maxy);
			minx = std::min(x, minx);
			miny = std::min(y, miny);
		}
	}
	std::vector<std::vector<char>> field(maxy - miny + 1);
	for (auto& f : field) {
		f.resize(maxx - minx + 1, '.');
	}
	x = 0; 
	y = 0;
	field[y - miny][x - minx] = '#';
	for (Line& l : lines) {
		for (int i = 0; i < l.count; ++i) {
			switch (l.dir) {
			case 'R':
				++x;
				break;
			case 'L':
				--x;
				break;
			case 'D':
				++y;
				break;
			case 'U':
				--y;
				break;
			}
			field[y-miny][x-minx] = '#';
		}
	}
	struct P {
		int x, y;
	};
	std::vector<P> stack{ P{258,1} };
	while (!stack.empty()) {
		P p = stack.back();
		stack.pop_back();
		if (p.x < 0 || p.y < 0 || p.x >= field[0].size() || p.y >= field.size()) {
			continue;
		}
		if (field[p.y][p.x] == '#') {
			continue;
		}
		field[p.y][p.x] = '#';
		stack.push_back(P{ p.x + 1, p.y });
		stack.push_back(P{ p.x - 1, p.y });
		stack.push_back(P{ p.x, p.y + 1 });
		stack.push_back(P{ p.x, p.y - 1 });
	}
	int sum = 0;
	std::ofstream ofstream("out.txt");
	for (auto& f : field) {
		for (char c : f) {
			ofstream << c;
			sum += c == '#';
		}
		ofstream << std::endl;
		}
	std::cout << sum << std::endl;
}
