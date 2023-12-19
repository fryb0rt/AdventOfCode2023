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
	struct Elem {
		int min[4];
		int max[4];
		int rule;
		int64_t comb() {
			int64_t prod = 1;
			for (int i = 0; i < 4; ++i) {
				int cnt = max[i] - min[i] + 1;
				if (cnt <= 0) {
					return 0;
				}
				prod *= cnt;
			}
			return prod;
		}
	};
	Elem s;
	for (int i = 0; i < 4; ++i) {
	s.min[i] = 1;
	s.max[i] = 4000;
}
	s.rule = start;
	std::vector<Elem> elems{ s };
	std::vector<Elem> accepted;
	while (!elems.empty()) {
		Elem el = elems.back();
		elems.pop_back();
		for (RuleLine::Rule& rr : rules[el.rule].rules) {
			if (rr.stop && rr.next == "A") {
				accepted.push_back(el);
				break;
			}
			else if (rr.stop && rr.next == "R") {
				break;
			}
			else if (rr.stop) {
				el.rule = rr.nextI;
				elems.push_back(el);
				break;
			}
			else {
				if (rr.condition == '<' && el.min[rr.varI] < rr.value) {
					Elem el2 = el;
					el2.max[rr.varI] = std::min(el.max[rr.varI], rr.value - 1);
					el2.rule = rr.nextI;
					if (rr.next == "A") {
						accepted.push_back(el2);
					}
					else if (rr.next != "R") {
						elems.push_back(el2);
					}
					if (el2.max[rr.varI] < el.max[rr.varI]) {
						el.min[rr.varI] = el2.max[rr.varI] + 1;
					}
					else {
						break;
					}
				}
				if (rr.condition == '>' && el.max[rr.varI] > rr.value) {
					Elem el2 = el;
					el2.min[rr.varI] = std::max(el.min[rr.varI], rr.value + 1);
					el2.rule = rr.nextI;
					if (rr.next == "A") {
						accepted.push_back(el2);
					}
					else if (rr.next != "R") {
						elems.push_back(el2);
					}
					if (el2.min[rr.varI] > el.min[rr.varI]) {
						el.max[rr.varI] = el2.min[rr.varI] - 1;
					}
					else {
						break;
					}
				}
			}
		}
	}
	for (Elem& el : accepted) {
		sum += el.comb();
	}
	std::cout << sum << std::endl;
}
