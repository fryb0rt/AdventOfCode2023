#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

int main()
{
	std::ifstream stream("..\\input6.txt");
	const auto readLine = [&stream]() {
		std::string line;
		std::getline(stream, line);
		std::istringstream iss(line);
		std::string tmp;
		iss >> tmp;
		std::string num = "";
		while (iss) {
			iss >> tmp;
			if (iss) {
				num += tmp;
			}
		}
		int64_t res;
		std::istringstream iss2(num);
		iss2 >> res;
		return res;
	};
	int64_t time = readLine();
	int64_t distance = readLine();
	const auto traveled = [&](const int64_t t) {
		return (time - t) * t;
	};
	const auto binarySearch = [&](const int sign) {
		int64_t val = time / 2;
		int64_t intervalSize = time / 2;
		while (traveled(val) <= distance || traveled(val + sign) > distance) {
			intervalSize = std::max(1ll, intervalSize / 2);
			if (traveled(val) > distance) {
				val += sign * intervalSize;
				continue;
			}
			if (traveled(val) <= distance) {
				val -= sign * intervalSize;
				continue;
			}
		}
		return val;
	};
	const int64_t start = binarySearch(-1);
	const int64_t end = binarySearch(1);
	std::cout << (end - start + 1) << std::endl;
}