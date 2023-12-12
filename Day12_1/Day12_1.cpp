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
		bool check(const std::string& d) {
			int index = 0;
			for (int i = 0; i < d.size(); ++i) {
				while (i < d.size() && d[i] == '.') {
					++i;
				}
				int cnt = 0;
				while (i < d.size() && d[i] == '#') {
					++i;
					++cnt;
				}
				if (cnt == 0) {
					continue;
				}
				if ((index == counts.size() && cnt > 0) || counts[index] != cnt) {
					return false;
				}
				++index;
			}
			return index == counts.size();
		}
		int solve() {
			for (int i = 0; i < data.size(); ++i) {
				if (data[i] == '?') {
					int sum = 0;
					data[i] = '.';
					sum += solve();
					data[i] = '#';
					sum += solve();
					data[i] = '?';
					return sum;
				}
			}
			if (check(data)) {
				return 1;
			}
			return 0;
		}
	};
	int sum = 0;
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
		int val = dataLine.solve();;
		sum += val;
	}
	std::cout << sum << std::endl;
}
