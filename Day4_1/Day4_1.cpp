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
	while (std::getline(stream, line)) {
		std::istringstream iss(line);
		std::string tmp;
		iss >> tmp; // Card
		int cardId;
		iss >> cardId;
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
			sum += 1 << (count - 1);
		}
	}
	std::cout << sum << std::endl;
	return 0;
}