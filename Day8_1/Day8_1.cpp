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
	int start, end;
	for (int i = 0; i < nodes.size(); ++i) {
		Node& node = nodes[i];
		if (node.name == "AAA") {
			start = i;
		}
		if (node.name == "ZZZ") {
			end = i;
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
	int index = start;
	int i = 0;
	while (index != end) {
		char c = instructions[i % instructions.size()];
		++i;
		if (c == 'L') {
			index = nodes[index].leftIndex;
		}
		if (c == 'R') {
			index = nodes[index].rightIndex;
		}
	}
	std::cout << i << std::endl;
}