#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

int main()
{
	std::ifstream stream("..\\input3.txt");
	std::string line;
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
	struct Data {
		int count = 0;
		int product = 1;
	};
	std::vector<std::vector<Data>> adjacent(input.size());
	for (int y = 0; y < input.size(); ++y) {
		adjacent[y].resize(input[y].size());
	}
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
				for (int yy = std::max(y - 1, 0); yy < std::min(y + 2, int(input.size())); ++yy) {
					for (int xx = std::max(start - 1, 0); xx < std::min(x + 1, int(input[yy].size())); ++xx) {
						adjacent[yy][xx].count += 1;
						adjacent[yy][xx].product *= number;
					}
				}
			}
		}
	}
	int sum = 0;
	for (int y = 0; y < input.size(); ++y) {
		for (int x = 0; x < input[y].size(); ++x) {
			if (input[y][x] == '*' && adjacent[y][x].count == 2) {
				sum += adjacent[y][x].product;
			}
		}
	}
	std::cout << sum << std::endl;
	return 0;
}