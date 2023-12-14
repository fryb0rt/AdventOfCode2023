#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iomanip>      // std::setw

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
	int sum = 0;
	for (int x = 0; x < lines[0].size(); ++x) {
		for (int y = 1; y < lines.size(); ++y) {
			if (lines[y][x] == 'O') {
				int yy = y - 1;
				while (yy >= 0 && lines[yy][x] == '.') {
					std::swap(lines[yy+1][x], lines[yy][x]);
					--yy;
				}
			}
		}
		for (int y = 0; y < lines.size(); ++y) {
			if (lines[y][x] == 'O') {
				sum += lines.size() - y;
			}
		}
	}
	for (int y = 0; y < lines.size(); ++y) {
		for (int x = 0; x < lines[0].size(); ++x) {
			std::cout << lines[y][x];
		}
		std::cout << std::endl;
	}
	std::cout << sum << std::endl;
}
