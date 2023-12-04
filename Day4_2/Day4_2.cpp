#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

int main()
{
	std::ifstream stream("..\\input4.txt");
	std::string line;
	std::vector<std::string> input;
	int sum = 0;
	std::vector<int> copy = { 0 };
	int max = 0;
	while (std::getline(stream, line)) {
		std::istringstream iss(line);
		std::string tmp;
		iss >> tmp; // Card
		int cardId;
		iss >> cardId;
		if (copy.size() < cardId) {
			copy.resize(cardId, 0);
			copy[cardId - 1] = 0;
		}
		copy[cardId - 1] += 1;
		++max;
		iss >> tmp; //:
		std::vector<int> winning;
		do {
			iss >> tmp;
			std::istringstream iss2(tmp);
			int value;
			iss2 >> value;
			if (tmp != "|") {
				winning.push_back(value);
			}
		} while (tmp != "|");
		int count = 0;
		while (!iss.eof()) {
			int value;
			iss >> value;
			for (int v : winning) {
				if (value == v) {
					++count;
				}
			}
		}
		if (count > 0) {
			int copies = count;
			for (int i = 0; i < copies; ++i) {
				if (copy.size() < cardId + i + 1) {
					copy.resize(cardId + i + 1, 0);
					copy[cardId + i] = 0;
				}
				copy[cardId + i] += copy[cardId - 1];
			}
		}
	}
	for (int i = 0; i < max; ++i) {
		sum += copy[i];
	}
	std::cout << sum << std::endl;
	return 0;
}