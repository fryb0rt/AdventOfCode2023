#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iomanip>      // std::setw

void tilltNorth(std::vector<std::string>& lines) {
	for (int x = 0; x < lines[0].size(); ++x) {
		for (int y = 1; y < lines.size(); ++y) {
			if (lines[y][x] == 'O') {
				int yy = y - 1;
				while (yy >= 0 && lines[yy][x] == '.') {
					std::swap(lines[yy + 1][x], lines[yy][x]);
					--yy;
				}
			}
		}
	}
}

void tilltSouth(std::vector<std::string>& lines) {
	for (int x = 0; x < lines[0].size(); ++x) {
		for (int y = lines.size()-2; y >= 0; --y) {
			if (lines[y][x] == 'O') {
				int yy = y + 1;
				while (yy < lines.size() && lines[yy][x] == '.') {
					std::swap(lines[yy - 1][x], lines[yy][x]);
					++yy;
				}
			}
		}
	}
}

void tilltWest(std::vector<std::string>& lines) {
	for (int y = 0; y < lines.size(); ++y) {
		for (int x = 1; x < lines[0].size(); ++x) {
			if (lines[y][x] == 'O') {
				int xx = x - 1;
				while (xx >= 0 && lines[y][xx] == '.') {
					std::swap(lines[y][xx + 1], lines[y][xx]);
					--xx;
				}
			}
		}
	}
}

void tilltEast(std::vector<std::string>& lines) {
	for (int y = 0; y < lines.size(); ++y) {
		for (int x = lines[0].size() - 2; x >= 0; --x) {
			if (lines[y][x] == 'O') {
				int xx = x + 1;
				while (xx < lines[0].size() && lines[y][xx] == '.') {
					std::swap(lines[y][xx - 1], lines[y][xx]);
					++xx;
				}
			}
		}
	}
}

void cycle(std::vector<std::string>& lines) {
	tilltNorth(lines);
	tilltWest(lines);
	tilltSouth(lines);
	tilltEast(lines);
}

void print(const std::vector<std::string>& lines) {
	for (int y = 0; y < lines.size(); ++y) {
		for (int x = 0; x < lines[0].size(); ++x) {
			std::cout << lines[y][x];
		}
		std::cout << std::endl;
	}
}

bool compare(const std::vector<std::string>& linesA, const std::vector<std::string>& linesB) {
	for (int y = 0; y < linesA.size(); ++y) {
		for (int x = 0; x < linesA[0].size(); ++x) {
			if (linesA[y][x] != linesB[y][x]) {
				return false;
			}
		}
	}
	return true;
}

int compute(const std::vector<std::string>& lines) {
	int sum = 0;
	for (int x = 0; x < lines[0].size(); ++x) {
		for (int y = 0; y < lines.size(); ++y) {
			if (lines[y][x] == 'O') {
				sum += lines.size() - y;
			}
		}
	}
	return sum;
}

int main()
{
	std::ifstream stream("..\\input14.txt");
	std::vector<std::string> lines;
	std::string line;
	while (std::getline(stream, line)) {
		if (line.empty()) {
			continue;
		}
		lines.push_back(line);
	}
	std::vector<std::vector<std::string>> stack{ lines };
	int found = -1;
	while (found == -1) {
		cycle(lines);
		for (int i = 0; i < stack.size(); ++i) {
			if (compare(stack[i], lines)) {
				found = i;
			}
		}
		stack.push_back(lines);
	}
	int64_t total = 1000000000 - stack.size() + 1;
	int period = stack.size() - 1 - found;
	total %= period;
	for (int64_t i = 0; i < total; ++i) {
		cycle(lines);
	}
	print(lines);
	std::cout << compute(lines) << std::endl;
}
