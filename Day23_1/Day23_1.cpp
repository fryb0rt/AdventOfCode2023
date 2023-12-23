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
		bool operator<(const El& el) const {
			return steps > el.steps || (steps == el.steps && p.y > el.p.y);
		}
		P p0, p1;
		//std::set<P> previous;

	};
	std::vector<std::vector<int>> steps(lines.size());
	for (auto& s : steps) {
		s.resize(lines[0].size(), -1);
	}
	std::priority_queue<El> queue;
	queue.push(El{ P{0,1}, 0, P{-1,-1},P{-1,-1} });
	while (!queue.empty()) {
		El el = queue.top();
		queue.pop();
		if (
			el.p.y < 0 || el.p.y >= lines.size() || el.p0 == el.p || el.p1 == el.p || lines[el.p.y][el.p.x] == '#' || steps[el.p.y][el.p.x] >= el.steps) {
			continue;
		}
		steps[el.p.y][el.p.x] = el.steps;
		++el.steps;
		if (el.steps % 100 == 0) {
			std::cout << el.steps << std::endl;
		}
		el.p1 = el.p0;
		switch (lines[el.p.y][el.p.x]) {
		case '>':
			queue.push(El{ P{el.p.y ,el.p.x + 1}, el.steps, el.p, el.p0 });
			break;
		case '<':
			queue.push(El{ P{el.p.y ,el.p.x - 1}, el.steps, el.p, el.p0 });
			break;
		case 'v':
			queue.push(El{ P{el.p.y + 1,el.p.x}, el.steps, el.p, el.p0 });
			break;
		case '^':
			queue.push(El{ P{el.p.y - 1 ,el.p.x}, el.steps, el.p, el.p0 });
			break;
		case '.':
			queue.push(El{ P{el.p.y ,el.p.x + 1}, el.steps, el.p, el.p0 });
			queue.push(El{ P{el.p.y ,el.p.x - 1}, el.steps, el.p, el.p0 });
			queue.push(El{ P{el.p.y + 1,el.p.x}, el.steps, el.p, el.p0 });
			queue.push(El{ P{el.p.y - 1 ,el.p.x}, el.steps, el.p, el.p0 });
			break;
		}
	}
	std::cout << steps.back()[lines[0].size() - 2] << std::endl;
}
