#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iomanip>      // std::setw

int64_t hash(const std::string& str) {
	int64_t res = 0;
	for (int i = 0; i < str.size(); ++i) {
		res += str[i];
		res *= 17;
		res %= 256;
	}
	return res;
}
int main()
{
	std::ifstream stream("..\\input15.txt");
	std::string line;
	std::getline(stream, line);
	int last = 0;
	int64_t sum = 0;
	for (int i = 0; i < line.size(); ++i) {
		if (line[i] == ',') {
			sum += hash(line.substr(last, i - last));
			last = i + 1;
		}
	}
	sum += hash(line.substr(last, line.size() - last));
	std::cout << sum << std::endl;
}
