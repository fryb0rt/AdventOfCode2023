#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iomanip>      // std::setw

struct Laser {
	int x, y, direction;
};

struct Visited {
	int direction[4] = { 0,0,0,0 };
};

int run(Laser start, std::vector<std::string>& lines) {
	struct Visited {
		int direction[4] = { 0,0,0,0 };
	};
	std::vector<Laser> stack{ start };
	std::vector<std::vector<Visited>> visited(lines.size());
	for (auto& v : visited) {
		v.resize(lines[0].size());
	}
	Laser movement[4] = { Laser{1,0,0}, Laser{-1,0,0},Laser{0,1,0},Laser{0,-1,0} };

	while (!stack.empty()) {
		Laser l = stack.back();
		stack.pop_back();
		if (l.x < 0 || l.y < 0 || l.y >= lines.size() || l.x >= lines[0].size()) {
			continue;
		}
		if (visited[l.y][l.x].direction[l.direction] == 1) {
			continue;
		}
		visited[l.y][l.x].direction[l.direction] = 1;
		switch (lines[l.y][l.x]) {
		case '.':
			stack.push_back(Laser{ l.x + movement[l.direction].x,l.y + movement[l.direction].y, l.direction });
			break;
		case '-':
			if (l.direction == 0 || l.direction == 1) {
				stack.push_back(Laser{ l.x + movement[l.direction].x,l.y + movement[l.direction].y, l.direction });
				break;
			}
			else {
				stack.push_back(Laser{ l.x + 1,l.y, 0 });
				stack.push_back(Laser{ l.x - 1,l.y, 1 });
				break;
			}
		case '|':
			if (l.direction == 2 || l.direction == 3) {
				stack.push_back(Laser{ l.x + movement[l.direction].x,l.y + movement[l.direction].y, l.direction });
				break;
			}
			else {
				stack.push_back(Laser{ l.x,l.y + 1, 2 });
				stack.push_back(Laser{ l.x,l.y - 1, 3 });
				break;
			}
		case '/': {
			switch (l.direction) {
			case 0:
				stack.push_back(Laser{ l.x,l.y - 1, 3 });
				break;
			case 1:
				stack.push_back(Laser{ l.x,l.y + 1, 2 });
				break;
			case 2:
				stack.push_back(Laser{ l.x - 1,l.y, 1 });
				break;
			case 3:
				stack.push_back(Laser{ l.x + 1,l.y, 0 });
				break;
			}
			break;
		}
		case '\\': {
			switch (l.direction) {
			case 0:
				stack.push_back(Laser{ l.x,l.y + 1, 2 });
				break;
			case 1:
				stack.push_back(Laser{ l.x,l.y - 1, 3 });
				break;
			case 2:
				stack.push_back(Laser{ l.x + 1,l.y, 0 });
				break;
			case 3:
				stack.push_back(Laser{ l.x - 1,l.y, 1 });
				break;
			}
			break;
		}

		}
	}
	int sum = 0;
	for (int y = 0; y < visited.size(); ++y) {

		for (int x = 0; x < visited[0].size(); ++x) {
			bool v = visited[y][x].direction[0] == 1 || visited[y][x].direction[1] == 1 || visited[y][x].direction[2] == 1 || visited[y][x].direction[3] == 1;
			sum += int(v);

		}
	}
	return sum;
}

int main()
{
	std::ifstream stream("..\\input16.txt");
	std::vector<std::string> lines;
	std::string line;
	while (std::getline(stream, line)) {
		if (line.empty()) {
			continue;
		}
		lines.push_back(line);
	}
	std::cout << run(Laser{ 0,0,0 }, lines) << std::endl;
}
