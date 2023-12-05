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
	struct Seed {
		int64_t start, end;
	};
	std::vector<Seed> seeds;
	{
		std::getline(stream, line);
		std::istringstream iss(line);
		std::string tmp;
		iss >> tmp;
		while (iss) {
			int64_t seed, range;
			iss >> seed >> range;
			if (iss) {
				seeds.push_back(Seed{ seed, seed + range });
			}
		}
	}
	std::getline(stream, line);
	struct Mapping {
		int64_t rangeStart;
		int64_t previousRangeStart;
		int64_t previousRangeEnd;
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
			iss1 >> m.rangeStart >> m.previousRangeStart >> m.previousRangeEnd;
			m.previousRangeEnd += m.previousRangeStart;
			mapping.back().push_back(m);
		} while (true);
	}
	struct Element {
		int index;
		Seed seed;
	};
	std::vector<Element> stack;
	for (Seed seed : seeds) {
		stack.push_back(Element{ 0, seed });
	}
	int64_t lowestLocation = -1;
	while (!stack.empty()) {
		Element e = stack.back();
		stack.pop_back();
		if (e.index == mapping.size()) {
			if (lowestLocation == -1 || lowestLocation > e.seed.start) {
				lowestLocation = e.seed.start;
			}
			continue;
		}
		bool anyIntersection = false;
		for (auto& m : mapping[e.index]) {
			// Intersection
			int64_t start = std::max(m.previousRangeStart, e.seed.start);
			int64_t end = std::min(m.previousRangeEnd, e.seed.end);
			if (start < end) {
				stack.push_back(Element{ e.index + 1, Seed{ start - m.previousRangeStart + m.rangeStart, end - m.previousRangeStart + m.rangeStart } });
				anyIntersection = true;
				if (start > e.seed.start) {
					stack.push_back(Element{ e.index, Seed{ e.seed.start, start} });
				}
				if (end < e.seed.end) {
					stack.push_back(Element{ e.index, Seed{ end, e.seed.end} });
				}
				break;
			}
		}
		if (!anyIntersection) {
			stack.push_back(Element{ e.index + 1, e.seed });
		}
	}
	std::cout << lowestLocation << std::endl;
	return 0;
}