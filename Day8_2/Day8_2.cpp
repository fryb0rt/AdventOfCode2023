#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

int main()
{
	struct Node {
		std::string name, left, right;
		int leftIndex, rightIndex;
		bool isEnd = false;
	};

	std::ifstream stream("..\\input8.txt");
	std::string instructions;
	stream >> instructions;
	std::vector<Node> nodes;
	std::string line;
	while (std::getline(stream, line)) {
		if (line.empty()) {
			continue;
		}
		Node node;
		std::istringstream iss(line);
		iss >> node.name;
		std::string tmp;
		iss >> tmp;
		iss >> tmp;
		node.left = tmp.substr(1, 3);
		iss >> tmp;
		node.right = tmp.substr(0, 3);
		nodes.push_back(node);
	}
	std::vector<int> starts;
	for (int i = 0; i < nodes.size(); ++i) {
		Node& node = nodes[i];
		if (node.name[2] == 'A') {
			starts.push_back(i);
		}
		if (node.name[2] == 'Z') {
			node.isEnd = true;
		}
		for (int j = 0; j < nodes.size(); ++j) {
			if (nodes[j].name == node.left) {
				node.leftIndex = j;
			}
			if (nodes[j].name == node.right) {
				node.rightIndex = j;
			}
		}
	}
	std::vector<int> steps(starts.size(), -1);
	int atEnd = 0;
	int i = 0;
	while (atEnd != starts.size()) {
		char c = instructions[i % instructions.size()];
		++i;
		if (c == 'L') {
			int k = 0;
			for (int& index : starts) {
				index = nodes[index].leftIndex;
				if (nodes[index].isEnd) {
					std::cout << k << " " << i << std::endl;
					atEnd += 1;
					steps[k] = i;
				}
				++k;
			}

		}
		if (c == 'R') {
			int k = 0;
			for (int& index : starts) {
				index = nodes[index].rightIndex;
				if (nodes[index].isEnd) {
					std::cout << k << " " << i << std::endl;
					atEnd += 1;
					steps[k] = i;
				}
				++k;
			}
		}

	}
	int64_t product = 1;
	while (true) {
		for (int i = 2; true; ++i) {
			int ones = 0;
			bool any = false;
			do {
				ones = 0;
				any = false;
				for (int& s : steps)
				{
					if (s % i == 0) {
						any = true;
						s /= i;
					}
					ones += s == 1;
				}
				if (any) {
					product *= i;
				}
			} while (any);
			if (ones == steps.size()) {
				std::cout << product << std::endl;
				return 0 ;
			}
		}

	}
}