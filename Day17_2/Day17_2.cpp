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
	std::ifstream stream("..\\input17.txt");
	std::vector<std::string> lines;
	std::string line;
	while (std::getline(stream, line)) {
		if (line.empty()) {
			continue;
		}
		lines.push_back(line);
	}
	struct S {
		int x, y;
		int direction;
		int same;
		int heatLoss;
	};
	struct Cache {
		struct Direction {
			int s[11] = { -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1 };
		};
		Direction d[4];
	};
	std::vector<std::vector<Cache>> cache;
	cache.resize(lines.size());
	for (auto& c : cache) {
		c.resize(lines[0].size());
	}
	std::vector<S> stack{ S{0,0,-1,0,0} };
	int leastHeatLoss = -1;
	while (!stack.empty()) {
		S s = stack.back();
		stack.pop_back();
		if (s.x < 0 || s.y < 0 || s.x >= lines[0].size() || s.y >= lines.size()) {
			continue;
		}
		if (s.direction != -1) {
			const int h = lines[s.y][s.x] - '0';
			s.heatLoss = s.heatLoss + h;
			int& c = cache[s.y][s.x].d[s.direction].s[s.same];
			if (c == -1 || s.heatLoss < c) {
				c = s.heatLoss;
			}
			else {
				continue;
			}
		}
		if (s.heatLoss >= leastHeatLoss && leastHeatLoss != -1) {
			continue;
		}
		if (s.x == lines[0].size() - 1 && s.y == lines.size() - 1) {
			leastHeatLoss = s.heatLoss;
			continue;
		}

		switch (s.direction) {
		case 0: // RIGHT
			if (s.same != 10) {
				stack.push_back(S{ s.x + 1,s.y, s.direction, s.same + 1, s.heatLoss });
				
			}
			if (s.same >= 4) {
				stack.push_back(S{ s.x,s.y - 1, 3, 1, s.heatLoss });
				stack.push_back(S{ s.x,s.y + 1, 2, 1, s.heatLoss });
			}
			break;
		case 1: // LEFT
			if (s.same != 10) {
				stack.push_back(S{ s.x - 1,s.y, s.direction, s.same + 1, s.heatLoss });
			}
			if (s.same >= 4) {
				stack.push_back(S{ s.x,s.y - 1, 3, 1, s.heatLoss });
				stack.push_back(S{ s.x,s.y + 1, 2, 1, s.heatLoss });
			}
			break;
		case 2: // DOWN
			if (s.same != 10) {
				stack.push_back(S{ s.x,s.y + 1, s.direction, s.same + 1, s.heatLoss });
			}
			if (s.same >= 4) {
				stack.push_back(S{ s.x - 1,s.y, 1, 1, s.heatLoss });
				stack.push_back(S{ s.x + 1,s.y, 0, 1, s.heatLoss });
			}
			break;
		case 3: // UP
			if (s.same != 10) {
				stack.push_back(S{ s.x,s.y - 1, s.direction, s.same + 1, s.heatLoss });
			}
			if (s.same >= 4) {
				stack.push_back(S{ s.x - 1,s.y, 1, 1, s.heatLoss });
				stack.push_back(S{ s.x + 1,s.y, 0, 1, s.heatLoss });
			}
			break;
		case -1:
			stack.push_back(S{ 1, 0, 0, 1, s.heatLoss });
			stack.push_back(S{ 0, 1, 2, 1, s.heatLoss });
			break;
		}
	}
	std::cout << leastHeatLoss << std::endl;
}
