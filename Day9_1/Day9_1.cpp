#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

int main()
{
	std::ifstream stream("..\\input9.txt");
	std::string line;
	int sum = 0;
	while (std::getline(stream, line)) {
		if (line.empty()) {
			continue;
		}
		std::istringstream iss(line);
		std::vector<std::vector<int>> numbers(1);
		while (iss) {
			int value;
			iss >> value;
			if (iss) {
				numbers[0].push_back(value);
			}
		}
		bool allZeros = false;
		while (!allZeros) {
			numbers.push_back({});
			auto& current = numbers[numbers.size() - 1];
			auto &previous = numbers[numbers.size() - 2];
			allZeros = true;
			for (int i = 0; i < previous.size() - 1; ++i) {
				current.push_back(previous[i + 1] - previous[i]);
				allZeros &= current.back() == 0;
			}
		}
		int diff = 0;
		for (int i = numbers.size() - 2; i >= 0; --i) {
			diff += numbers[i].back();
		}
		sum += diff;
	}
	std::cout << sum << std::endl;
}