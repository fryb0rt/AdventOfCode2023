#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iomanip>      // std::setw
#include <set>

struct RuleLine {
	struct Rule {
		char var;
		int varI;
		int value;
		char condition;
		std::string next;
		int nextI;
		bool stop;
		void parse(const std::string& s) {
			if (s.find(':') == std::string::npos) {
				next = s;
				stop = true;
				return;
			}
			stop = false;
			var = s[0];
			condition = s[1];
			std::istringstream iss(s.substr(2));
			iss >> value;
			char c;
			iss >> c;
			iss >> next;
			if (var == 'x') {
				varI = 0;
			}
			if (var == 'm') {
				varI = 1;
			}
			if (var == 'a') {
				varI = 2;
			}
			if (var == 's') {
				varI = 3;
			}
		}
	};
	std::vector<Rule> rules;
	std::string name;
	void parse(const std::string& s) {
		int i = 0;
		while (s[i] != '{') {
			++i;
		}
		name = s.substr(0, i);
		++i;
		while (i < s.size()) {
			int start = i;
			while (s[i] != ',' && s[i] != '}') {
				++i;
			}
			Rule r;
			r.parse(s.substr(start, i - start));
			rules.push_back(r);
			++i;
		}
	}
};

struct Data {
	int val[4];
	Data(const std::string& s) {
		sscanf_s(s.c_str(), "{x=%i,m=%i,a=%i,s=%i}", &val[0], &val[1], &val[2], &val[3]);
	}
};
int main()
{
	std::ifstream stream("..\\input19.txt");
	std::vector<RuleLine> rules;
	std::string line;
	while (std::getline(stream, line)) {
		if (line.empty()) {
			break;
		}
		RuleLine rl;
		rl.parse(line);
		rules.push_back(rl);
	}
	std::vector<Data> data;
	while (std::getline(stream, line)) {
		if (line.empty()) {
			continue;
		}
		data.push_back(Data(line));
	}
	int start = -1;
	int index = 0;
	for (RuleLine& r : rules) {
		if (r.name == "in") {
			start = index;
		}
		for (RuleLine::Rule& rr : r.rules) {
			int j = 0;
			for (RuleLine& r : rules) {
				if (r.name == rr.next) {
					rr.nextI = j;
					break;
				}
				++j;
			}
		}
		++index;
	}
	int64_t sum = 0;
	for (Data& d : data) {
		
		int index = start;
		while (index != -1) {
			for (RuleLine::Rule& rr : rules[index].rules) {
				const auto dd = [&]() {
					if (rr.next == "A") {
						for (int& v : d.val) {
							sum += v;
						}
						index = -1;
						return;
					}
					if (rr.next == "R") {

						index = -1;
						return;
					}
					index = rr.nextI;
				};
				if (rr.stop) {
					dd();
					break;
				}
				if (rr.condition == '<' && d.val[rr.varI] < rr.value) {
					dd();
					break;
				}
				if (rr.condition == '>' && d.val[rr.varI] > rr.value) {
					dd();
					break;
				}
			}
		}
	}
	std::cout << sum << std::endl;
}
