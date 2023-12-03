#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

int main()
{
	std::ifstream stream("..\\input3.txt");
	std::string line;
	int sum = 0;
	std::vector<std::string> input;
	while (std::getline(stream, line)) {
		input.push_back(line);
	}
	const auto check = [&input](int x, int y) {
		const auto checkOneSymbol = [&input](int xx, int yy) {
			return yy >= 0 && yy < input.size() && xx >= 0 && xx < input[yy].size() && input[yy][xx] != '.' && !(input[yy][xx] >= '0' && input[yy][xx] <= '9');
		};
		return checkOneSymbol(x + 1, y) || checkOneSymbol(x + 1, y + 1) || checkOneSymbol(x, y + 1) || checkOneSymbol(x - 1, y + 1) || checkOneSymbol(x - 1, y)
			|| checkOneSymbol(x - 1, y - 1) || checkOneSymbol(x, y - 1) || checkOneSymbol(x + 1, y - 1);
	};
	for (int y = 0; y < input.size(); ++y) {
		for (int x = 0; x < input[y].size(); ++x) {
			int start = x;
			int number = 0;
			while (x < input[y].size() && input[y][x] >= '0' && input[y][x] <= '9') {
				number *= 10;
				number += input[y][x] - '0';
				++x;
			}
			if (start < x) {
				// We found number
				bool anySymbol = false;
				for (int i = start; i < x; ++i) {
					anySymbol |= check(i, y);
				}
				if (anySymbol) {
					sum += number;
				}
			}
		}
	}
	std::cout << sum << std::endl;
	return 0;
}