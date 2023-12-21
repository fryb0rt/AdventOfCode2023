#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iomanip>      // std::setw
#include <set>
#include <queue>

struct P {
	int x, y;
	bool operator <(const P& o) const {
		return y < o.y || (y == o.y && x < o.x);
	}
};
int main()
{
	std::ifstream stream("..\\input21.txt");
	std::vector<std::string> lines;
	std::string line;
	P s;
	while (std::getline(stream, line)) {
		if (line.empty()) {
			continue;
		}
		lines.push_back(line);
		auto k = line.find('S');
		if (k != std::string::npos) {
			s.y = lines.size() - 1;
			s.x = k;
		}
	}
	
	std::set<P> pos0{ s }, pos1;
	for (int i = 0; i < 64; ++i) {
		while (!pos0.empty()) {
			P p = *pos0.begin();
			pos0.erase(p);
			if (p.x > 0 && lines[p.y][p.x - 1] != '#') {
				pos1.insert(P{ p.x - 1, p.y });
			}
			if (p.y > 0 && lines[p.y-1][p.x] != '#') {
				pos1.insert(P{ p.x, p.y-1 });
			}
			if (p.x < lines[0].size()-1 && lines[p.y][p.x+1] != '#') {
				pos1.insert(P{ p.x + 1, p.y });
			}
			if (p.y < lines.size()-1 && lines[p.y+1][p.x] != '#') {
				pos1.insert(P{ p.x, p.y + 1 });
			}
		}
		std::swap(pos1, pos0);
	}
	std::cout << pos0.size() << std::endl;
}
