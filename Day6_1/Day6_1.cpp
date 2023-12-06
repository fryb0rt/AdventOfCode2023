#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

int main()
{
	std::ifstream stream("..\\input6.txt");
	
	std::vector<int> times;
	std::vector<int> distances;
	const auto readLine = [&stream](std::vector<int>& res) {
		std::string line;
		std::getline(stream, line);
		std::istringstream iss(line);
		std::string tmp;
		iss >> tmp;
		while (iss) {
			int64_t seed;
			iss >> seed;
			if (iss) {
				res.push_back(seed);
			}
		}
	};
	readLine(times);
	readLine(distances);
	int product = 1;
	for (int i = 0; i < times.size(); ++i) {
		int num = 0;
		for (int t = 0; t <= times[i]; ++t) {
			int dist = (times[i] - t) * t;
			if (dist > distances[i]) {
				++num;
			}
		}
		product *= num;
	}
	std::cout << product << std::endl;
}