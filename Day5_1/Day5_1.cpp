#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

int main()
{
	std::ifstream stream("..\\input5.txt");
	std::string line;
	std::vector<std::string> input;
	std::vector<int64_t> seeds;
	{
		std::getline(stream, line);
		std::istringstream iss(line);
		std::string tmp;
		iss >> tmp;
		while (iss) {
			int64_t seed;
			iss >> seed;
			if (iss) {
				seeds.push_back(seed);
			}
		}
	}
	std::getline(stream, line);
	struct Mapping {
		int64_t rangeStart;
		int64_t previousRangeStart;
		int64_t rangeLength;
	};
	std::vector<std::vector<Mapping>> mapping;
	while (!stream.eof()) {
		std::getline(stream, line);
		mapping.push_back({});
		do {
			std::getline(stream, line);
			if (line.empty() || stream.eof()) {
				break;
			}
			std::istringstream iss1(line);
			Mapping m;
			iss1 >> m.rangeStart >> m.previousRangeStart >> m.rangeLength;
			mapping.back().push_back(m);
		} while (true);
	}
	int64_t lowestLocation = -1;
	for (int64_t seed : seeds) {
		for (auto& m1 : mapping) {
			for (auto& m : m1) {
				if (m.previousRangeStart <= seed && m.previousRangeStart + m.rangeLength > seed) {
					seed = seed - m.previousRangeStart + m.rangeStart;
					break;
				}
			}
			std::cout << seed << " ";
		}
		std::cout << std::endl << " ";
		if (lowestLocation == -1) {
			lowestLocation = seed;
		}
		else {
			lowestLocation = std::min(seed, lowestLocation);
		}
	}
	std::cout << lowestLocation << std::endl;
	return 0;
}