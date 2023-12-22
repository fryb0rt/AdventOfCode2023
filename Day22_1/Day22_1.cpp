#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iomanip>      // std::setw
#include <set>
#include <queue>

struct P {
	int x, y, z;
};

struct Brick {
	P p0, p1;

	bool operator<(const Brick& b) const {
		return p0.z < b.p0.z;
	}
	bool intersected(const Brick& b) const {
		bool x = (p1.x < b.p0.x) || (b.p1.x < p0.x);
		bool y = (p1.y < b.p0.y) || (b.p1.y < p0.y);
		bool z = (p1.z < b.p0.z) || (b.p1.z < p0.z);
		return !x && !y && !z;
	}
};

int main()
{
	std::ifstream stream("..\\input22.txt");
	std::vector<Brick> bricks;
	std::string line;
	while (std::getline(stream, line)) {
		if (line.empty()) {
			continue;
		}
		Brick b;
		sscanf_s(line.c_str(), "%i,%i,%i~%i,%i,%i", &b.p0.x, &b.p0.y, &b.p0.z, &b.p1.x, &b.p1.y, &b.p1.z);
		P min, max;
		min.x = std::min(b.p0.x, b.p1.x);
		min.y = std::min(b.p0.y, b.p1.y);
		min.z = std::min(b.p0.z, b.p1.z);
		max.x = std::max(b.p0.x, b.p1.x);
		max.y = std::max(b.p0.y, b.p1.y);
		max.z = std::max(b.p0.z, b.p1.z);
		b.p0 = min;
		b.p1 = max;
		bricks.push_back(b);
	}
	std::sort(bricks.begin(), bricks.end());
	for (int i = 0; i < bricks.size(); ++i) {
		bool canMove = true;
		Brick& b = bricks[i];
		while (canMove) {
			if (std::min(b.p0.z, b.p1.z) == 1) {
				canMove = false;
				break;
			}
			--b.p0.z;
			--b.p1.z;
			for (int j = 0; j < bricks.size(); ++j) {
				if (i == j) {
					continue;
				}
				if (b.intersected(bricks[j])) {
					++b.p0.z;
					++b.p1.z;
					canMove = false;
					break;
				}
			}
		}
	}

	int sum = 0;
	for (int i = 0; i < bricks.size(); ++i) {
		bool anyFall = false;
		for (int j = 0; j < bricks.size(); ++j) {
			Brick& b = bricks[j];
			if (i == j || b.p0.z == 1) {
				continue;
			}
			--b.p0.z;
			--b.p1.z;
			bool is = false;
			for (int k = 0; k < bricks.size(); ++k) {
				if (k == j || k == i) {
					continue;
				}
				if (b.intersected(bricks[k])) {
					is = true;
					break;
				}
			}
			++b.p0.z;
			++b.p1.z;
			anyFall = !is;
			if (anyFall) {
				break;
			}
		}
		if (!anyFall) {
			++sum;
		}
	}
	std::cout << sum << std::endl;

}
