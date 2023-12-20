#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iomanip>      // std::setw
#include <set>
#include <queue>

struct S{
	int type;
	std::string name;
	std::vector<std::string> output;
	std::vector<std::pair<int,bool>> input;
	std::vector<int> outputI;
	bool on;
};

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
	int broad = 0;
	for (int i = 0; i < modules.size(); ++i) {
		if (modules[i].type == 0) {
			broad = i;
		}
		for (auto& s : modules[i].output) {
			bool found = false;
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
	int64_t l = 0, h = 0;
	for (int64_t i = 0; i < 1000; ++i) {
		int low = 0, high = 0;
		++low;
		for (int o : modules[broad].outputI) {
			++low;
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
				for (int o : modules[s.index].outputI) {
					low += lowS;
					high += !lowS;
					if (o != -1) {
						signals.push(Signal{ lowS, o, s.index });
					}
				}
			}
		}
		l += low;
		h += high;
	}
	
	std::cout << l * h << std::endl;
}
