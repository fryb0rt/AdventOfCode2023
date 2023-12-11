#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iomanip>      // std::setw

int main()
{
	std::ifstream stream("..\\input11.txt");
	std::string line;
	struct Galaxy {
		int x, y;
		std::vector<int> distances;
	};
	
	std::vector<std::string> lines;
	while (std::getline(stream, line)) {
		if (line.empty()) {
			continue;
		}
		lines.push_back(line);
	}
	std::vector<bool> emptyRows(lines.size()), emptyColumns(lines[0].size());
	std::vector<Galaxy> galaxies;
	for (int row = 0; row < lines.size(); ++row) {
		bool anyGalaxy = false;
		for (int column = 0; column < lines[0].size(); ++column) {
			anyGalaxy |= lines[row][column] == '#';
			if (lines[row][column] == '#') {
				Galaxy galaxy;
				galaxy.x = column;
				galaxy.y = row;
				galaxies.push_back(galaxy);
			}
		}
		emptyRows[row] = !anyGalaxy;
	}
	for (int column = 0; column < lines[0].size(); ++column) {
		bool anyGalaxy = false;
		for (int row = 0; row < lines.size(); ++row) {
			anyGalaxy |= lines[row][column] == '#';
		}
		emptyColumns[column] = !anyGalaxy;
	}
	int64_t sum = 0;
	for (int i = 0; i < galaxies.size(); ++i) {
		for (int j = i + 1; j < galaxies.size(); ++j) {
			int minx = std::min(galaxies[i].x, galaxies[j].x);
			int maxx = std::max(galaxies[i].x, galaxies[j].x);
			int miny = std::min(galaxies[i].y, galaxies[j].y);
			int maxy = std::max(galaxies[i].y, galaxies[j].y);
			int eC = 0;
			for (int x = minx; x <= maxx; ++x) {
				eC += int(emptyColumns[x]);
			}
			int eR = 0;
			for (int y = miny; y <= maxy; ++y) {
				eR += int(emptyRows[y]);
			}
			int64_t distance = (maxx - minx) + (eC + eR) + (maxy - miny);
			sum += distance;
		}
	}
	std::cout << sum  << std::endl;
}
