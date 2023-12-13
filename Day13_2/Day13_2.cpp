#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iomanip>      // std::setw

int checkRow(int row, const std::vector<std::string>& mirror) {
	const auto isSame = [&mirror](int a, int b) {
		for (int x = 0; x < mirror[0].size(); ++x) {
			if (mirror[a][x] != mirror[b][x]) {
				return false;
			}
		}
		return true;
	};
	for (int y = row; y < mirror.size(); ++y) {
		int other = row - (y - row + 1);
		if (other < 0) {
			break;
		}
		if (!isSame(y, other)) {
			return false;
		}
	}
	return true;
};

int checkColumn(int col, const std::vector<std::string>& mirror) {
	const auto isSame = [&mirror](int a, int b) {
		for (int y = 0; y < mirror.size(); ++y) {
			if (mirror[y][a] != mirror[y][b]) {
				return false;
			}
		}
		return true;
	};
	for (int x = col; x < mirror[0].size(); ++x) {
		int other = col - (x - col + 1);
		if (other < 0) {
			break;
		}
		if (!isSame(x, other)) {
			return false;
		}
	}
	return true;
};

int main()
{
	std::ifstream stream("..\\input13.txt");
	std::string line;
	std::vector<std::vector<std::string>> mirrors(1);
	while (std::getline(stream, line)) {
		if (line.empty()) {
			mirrors.push_back({});
			continue;
		}
		mirrors.back().push_back(line);
	}
	int sum = 0;
	for (auto& mirror : mirrors) {
		int xxx = -1;
		int yyy = -1;
		for (int y = 1; y < mirror.size(); ++y) {
			if (checkRow(y, mirror)) {
				yyy = y;
			}
		}
		for (int x = 1; x < mirror[0].size(); ++x) {
			if (checkColumn(x, mirror)) {
				xxx = x;
			}
		}
		int newX = -1;
		int newY = -1;
		for (int yy = 0; yy < mirror.size(); ++yy) {
			for (int xx = 0; xx < mirror[0].size(); ++xx) {
				mirror[yy][xx] = mirror[yy][xx] == '.' ? '#' : '.';
				for (int y = 1; y < mirror.size(); ++y) {
					if (checkRow(y, mirror) && y != yyy) {
						newY = y;
					}
				}
				for (int x = 1; x < mirror[0].size(); ++x) {
					if (checkColumn(x, mirror) && x != xxx) {
						newX = x;
					}
				}
				mirror[yy][xx] = mirror[yy][xx] == '.' ? '#' : '.';
			}
		}
		newX = std::max(0, newX);
		newY = std::max(0, newY);
		sum += newY * 100 + newX;
	}
	std::cout << sum << std::endl;
}
