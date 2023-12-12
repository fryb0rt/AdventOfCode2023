#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iomanip>      // std::setw

int main()
{
	std::ifstream stream("..\\input12.txt");
	std::string line;
	struct Line {
		std::string data;
		std::vector<int> counts;
		std::vector<int> remainder;
		
		int64_t solve(int start = 0, int index = 0) {
			if (index + 1 == counts.size()) {
				return 1;
			}
			if (start == counts.size()) {
				return 0;
			}
			if (index < counts.size() && remainder[counts.size() - 1 - index] > data.size() - start) {
				return 0;
			}
			
			int64_t sum = 0;
			sum += solve(start + 1, index);
			for (int i = 0; i < counts[index]; ++i,++start) {
				if (start == data.size() || data[start] == '.') {
					return sum;
				}
			}
			if (index < counts.size() - 1) {
				if (start == data.size() || data[start] == '#') {
					return sum;
				}
				++start;
			}
			if (index + 1 == counts.size()) {
				return 1;
			}
			sum += solve(start, index + 1);
			return sum;
		}
		void unfold() {
			std::string total = data;
			std::vector<int> totalC = counts;
			for (int i = 0; i < 4; ++i) {
				total += "?" + data;
				for (int val : counts) {
					totalC.push_back(val);
				}
			}
			data = total;
			counts = totalC;
			int sum = totalC.back();
			remainder.push_back(sum);
			for (int i = totalC.size()-2; i >= 0; --i) {
				sum += 1 + totalC[i];
				remainder.push_back(sum);
			}
		}
	};
	int64_t sum = 0;
	while (std::getline(stream, line)) {
		if (line.empty()) {
			continue;
		}
		std::istringstream iss(line);
		Line dataLine;
		iss >> dataLine.data;
		while (iss) {
			int val;
			iss >> val;
			dataLine.counts.push_back(val);
			char c;
			iss >> c; //,
		}
		dataLine.unfold();
		int64_t val = dataLine.solve();
		std::cout << val << std::endl;
		sum += val;
	}
	std::cout << sum << std::endl;
}
