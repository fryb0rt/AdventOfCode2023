#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iomanip>      // std::setw
#include <set>
#include <queue>

struct S {
	int type;
	std::string name;
	std::vector<std::string> output;
	std::vector<std::pair<int, bool>> input;
	std::vector<int> outputI;
	bool on;
	int highP = -1;
};


int64_t gcd(int64_t a, int64_t b) {
	if (b == 0)
		return a;
	return gcd(b, a % b);
}

int64_t lcm(int64_t a, int64_t b) {
	return (a / gcd(a, b)) * b;
}

int main()
{
	std::ifstream stream("..\\input20.txt");
	std::vector<S> modules;
	std::string line;
	while (std::getline(stream, line)) {
		if (line.empty()) {
			break;
		}
		std::istringstream iss(line);
		S s;
		iss >> s.name;
		switch (s.name[0]) {
		case '&': s.type = 2; break;
		case '%': s.type = 1; break;
		default: s.type = 0; break;
		}
		if (s.type != 0) {
			s.name = s.name.substr(1);
		}
		std::string tmp;
		iss >> tmp; // ->
		while (!iss.eof()) {
			iss >> tmp;
			if (tmp.back() == ',') {
				tmp = tmp.substr(0, tmp.size() - 1);
			}
			s.output.push_back(tmp);
		}
		s.on = false;
		modules.push_back(s);
	}
	int broad = 0, rxInput = 0;
	for (int i = 0; i < modules.size(); ++i) {
		if (modules[i].type == 0) {
			broad = i;
		}
		for (auto& s : modules[i].output) {
			bool found = false;
			if (s == "rx") {
				rxInput = i;
			}
			for (int j = 0; j < modules.size(); ++j) {
				if (modules[j].name == s) {
					modules[j].input.push_back({ i, true });
					modules[i].outputI.push_back(j);
					found = true;
					break;
				}
			}
			if (!found) {
				modules[i].outputI.push_back(-1);
			}
		}
	}

	struct Signal {
		bool low;
		int index;
		int from;
	};
	std::queue<Signal> signals;
	int highPCount = 0;
	for (int64_t i = 0; highPCount < modules.size()-1; ++i) {
		for (int o : modules[broad].outputI) {
			signals.push(Signal{ true, o, broad });
		}
		while (!signals.empty()) {
			Signal s = signals.front();
			signals.pop();
			bool send = false;
			bool lowS = false;
			if (modules[s.index].type == 1) {
				if (s.low) {
					modules[s.index].on = !modules[s.index].on;
					lowS = !modules[s.index].on;
					send = true;
				}
			}
			if (modules[s.index].type == 2) {
				bool highs = true;
				for (auto& pair : modules[s.index].input) {
					if (pair.first == s.from) {
						pair.second = s.low;
					}
					highs &= !pair.second;
				}
				send = true;
				lowS = highs;
			}
			if (send) {
				if (!lowS && modules[s.index].highP == -1) {
					modules[s.index].highP = i + 1;
					++highPCount;
				}
				for (int o : modules[s.index].outputI) {
					if (o != -1) {
						signals.push(Signal{ lowS, o, s.index });
					}
				}
			}
		}
	}
	int64_t result = 1;
	for (auto& pair : modules[rxInput].input) {
		result = lcm(modules[pair.first].highP, result);
	}
	std::cout << result << std::endl;

}
