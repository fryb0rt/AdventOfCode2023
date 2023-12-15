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
	struct Box {
		struct Num {
			std::string label;
			int value;
		};
		std::vector<Num> nums;
		int64_t focusValue(int64_t boxIndex) {
			int64_t sum = 0;
			int64_t i = 0;
			for (Num& n : nums) {
				sum += (boxIndex + 1) * (i + 1) * n.value;
				++i;
			}
			return sum;
		}

	};
	std::vector<Box> boxes(256);

	const auto insert = [&](const std::string& str) {
		auto p = str.find('=');
		if (p != std::string::npos) {
			std::string label = str.substr(0, p);
			std::stringstream iss(str.substr(p + 1));
			int value;
			iss >> value;
			Box& box = boxes[hash(label)];
			for (int i = 0; i < box.nums.size(); ++i) {
				if (box.nums[i].label == label) {
					box.nums[i].value = value;
					return;
				}
			}
			box.nums.push_back(Box::Num{ label, value });
		}
		p = str.find('-');
		if (p != std::string::npos) {
			std::string label = str.substr(0, p);
			bool found = true;
			Box& box = boxes[hash(label)];
			for (int i = 0; i < box.nums.size(); ++i) {
				if (box.nums[i].label == label) {
					found = true;
					for (int k = i + 1; k < box.nums.size(); ++k) {
						box.nums[k-1] = box.nums[k];
					}
					box.nums.pop_back();
					return;
				}
			}
		}
	};
	std::ifstream stream("..\\input15.txt");
	std::string line;
	std::getline(stream, line);
	int last = 0;
	int64_t sum = 0;
	for (int i = 0; i < line.size(); ++i) {
		if (line[i] == ',') {
			auto ss = line.substr(last, i - last);
			insert(ss);
			last = i + 1;
		}
	}
	auto ss = line.substr(last, line.size() - last);
	insert(ss);
	for (int i = 0; i < boxes.size(); ++i) {
		sum += boxes[i].focusValue(i);
	}
	std::cout << sum << std::endl;
}
