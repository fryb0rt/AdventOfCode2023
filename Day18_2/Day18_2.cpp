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
		int64_t count;
		std::string color;
		int64_t sx, sy, ex, ey, miny, maxy, minx, maxx;
		bool horizontal;
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
		l.color = l.color.substr(1, l.color.size() - 2);
		switch (l.color.back()) {
		case '0':l.dir = 'R'; break;
		case '1':l.dir = 'D'; break;
		case '2':l.dir = 'L'; break;
		case '3':l.dir = 'U'; break;
		}
		l.count = 0;
		for (int i = 1; i < l.color.size() - 1; ++i) {
			if (l.color[i] >= '0' && l.color[i] <= '9') {
				l.count = l.count * 16 + l.color[i] - '0';
			}
			else {
				l.count = l.count * 16 + l.color[i] - 'a' + 10;
			}
		}
		lines.push_back(l);
	}
	int64_t x = 0, y = 0, maxx = 0, maxy = 0, minx = 0, miny = 0;
	for (Line& l : lines) {
		l.sx = x;
		l.sy = y;
		switch (l.dir) {
		case 'R':
			x += l.count;
			break;
		case 'L':
			x -= l.count;
			break;
		case 'D':
			y += l.count;
			break;
		case 'U':
			y -= l.count;
			break;
		}
		l.ex = x;
		l.ey = y;
		maxx = std::max(x, maxx);
		maxy = std::max(y, maxy);
		minx = std::min(x, minx);
		miny = std::min(y, miny);
		l.miny = std::min(l.sy, l.ey);
		l.maxy = std::max(l.sy, l.ey);
		l.minx = std::min(l.sx, l.ex);
		l.maxx = std::max(l.sx, l.ex);
		l.horizontal = l.dir == 'L' || l.dir == 'R';
	}
	std::sort(lines.begin(), lines.end(), [](const Line& a, const Line& b) {
		return a.miny < b.miny || (a.miny == b.miny && !a.horizontal && b.horizontal); });
	std::vector<int> onLine;
	int64_t total = 0;
	int lineStartY = 0;
	for (y = miny; y <= maxy; ++y) {
		onLine.clear();
		while (lines[lineStartY].maxy < y) {
			++lineStartY;
		}
		for (int i = lineStartY; i < lines.size(); ++i) {
			if (lines[i].miny <= y && lines[i].maxy >= y) {
				onLine.push_back(i);
			}
			else if (lines[i].miny > y){
				break;
			}
		}
		std::sort(onLine.begin(), onLine.end(), [&lines](int a, int b) {
			return lines[a].minx < lines[b].minx; });
		char c = lines[onLine[0]].dir;
		for (int start = 0; start < onLine.size();) {
			int i = start + 1;
			while (i < onLine.size() && (lines[onLine[i]].dir != c || lines[onLine[i]].horizontal)) {
				++i;
			}
			const int lineCount = lines[onLine[i - 1]].maxx - lines[onLine[start]].minx + (!lines[onLine[i - 1]].horizontal);
			total += lineCount;
			start = i;
		}
	}
	std::cout << total << std::endl;
}
