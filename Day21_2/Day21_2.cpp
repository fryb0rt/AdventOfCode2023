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
	int tx, ty;
	bool operator <(const P& o) const {
		return ty < o.ty || (
			ty == o.ty && (tx < o.tx || (tx == o.tx && (y < o.y || (y == o.y && x < o.x))))
			);
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
			s.tx = 0;
			s.ty = 0;
		}
	}

	std::set<P> pos0{ s }, pos1;
	const auto l = [&lines, &pos1](int x, int y, P p) {
		int tx = p.tx;
		int ty = p.ty;
		if (x < 0) {
			x += lines[0].size();
			--tx;
		}
		if (y < 0) {
			y += lines.size();
			--ty;
		}
		if (x >= lines[0].size()) {
			x -= lines[0].size();
			++tx;
		}
		if (y >= lines.size()) {
			y -= lines.size();
			++ty;
		}
		if (lines[y][x] != '#') {
			pos1.insert(P{ x,y,tx,ty });
		}
	};

	int steps = 26501365;
	int maxI = steps % lines.size() + lines.size() * 4;
	for (int i = 0; i < maxI; ++i) {
		while (!pos0.empty()) {
			P p = *pos0.begin();
			pos0.erase(p);
			l(p.x - 1, p.y, p);
			l(p.x + 1, p.y, p);
			l(p.x, p.y - 1, p);
			l(p.x, p.y + 1, p);
		}
		std::swap(pos1, pos0);
	}
	std::vector<std::vector<int64_t>> tiles(9);
	for (auto& t : tiles) {
		t.resize(9, 0);
	}
	for (const P& p : pos0) {
		if (abs(p.tx) > 4 || abs(p.ty) > 4) {
			continue;
		}
		tiles[p.ty + 4][p.tx + 4] += 1;
	}
	for (int i = 0; i < 9; ++i) {
		for (int j = 0; j < 9; ++j) {
			std::cout << std::setw(4) << tiles[i][j] << " ";
		}
		std::cout << std::endl;
	}
	const int64_t repeat = steps / lines.size();
	std::cout << repeat << std::endl;

	int64_t sum = tiles[0][4] + tiles[4][0] + tiles[4][8] + tiles[8][4]; // Ends of the diamond
	sum += repeat * (tiles[0][3] + tiles[0][5] + tiles[5][0] + tiles[5][8]); // Outter edges
	sum += (repeat - 1) * (tiles[1][3] + tiles[1][5] + tiles[5][1] + tiles[5][7]); // Inner edges
	sum += tiles[4][4] * (repeat - 1) * (repeat - 1); // Check #1
	sum += tiles[4][5] * repeat * repeat; // Check #2
	std::cout << sum << std::endl;
}
