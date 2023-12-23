#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iomanip>      // std::setw
#include <set>
#include <queue>

int main()
{
	std::ifstream stream("..\\input23.txt");
	std::vector<std::string> lines;
	std::string line;
	while (std::getline(stream, line)) {
		if (line.empty()) {
			continue;
		}
		lines.push_back(line);
	}
	struct P {
		int y, x;
		bool operator==(const P& p) const {
			return p.x == x && p.y == y;
		}
		bool operator<(const P& p) const {
			return y < p.y || (y == p.y && x < p.x);
		}
	};
	struct El {
		P p;
		int steps;
		P p0, p1;

	};
	const P end{ int(lines.size() - 1), int(lines[0].size() - 2) };
	int steps = 0;
	std::vector<El> stack;
	stack.push_back(El{ P{0,1}, 0, P{-1,-1},P{-1,-1} });
	while (!stack.empty()) {
		El el = stack.back();
		stack.pop_back();
		if (el.p.y < 0 || el.p.y >= lines.size() || el.p0 == el.p || el.p1 == el.p || lines[el.p.y][el.p.x] == '#') {
			continue;
		}
		if (el.p == end) {
			steps = std::max(el.steps, steps);
		}
		++el.steps;
		el.p1 = el.p0;
		switch (lines[el.p.y][el.p.x]) {
		case '>':
			stack.push_back(El{ P{el.p.y ,el.p.x + 1}, el.steps, el.p, el.p0 });
			break;
		case '<':
			stack.push_back(El{ P{el.p.y ,el.p.x - 1}, el.steps, el.p, el.p0 });
			break;
		case 'v':
			stack.push_back(El{ P{el.p.y + 1,el.p.x}, el.steps, el.p, el.p0 });
			break;
		case '^':
			stack.push_back(El{ P{el.p.y - 1 ,el.p.x}, el.steps, el.p, el.p0 });
			break;
		case '.':
			stack.push_back(El{ P{el.p.y ,el.p.x + 1}, el.steps, el.p, el.p0 });
			stack.push_back(El{ P{el.p.y ,el.p.x - 1}, el.steps, el.p, el.p0 });
			stack.push_back(El{ P{el.p.y + 1,el.p.x}, el.steps, el.p, el.p0 });
			stack.push_back(El{ P{el.p.y - 1 ,el.p.x}, el.steps, el.p, el.p0 });
			break;
		}
	}
	std::cout << steps << std::endl;
}
