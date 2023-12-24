#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iomanip>      // std::setw
#include <set>
#include <queue>

const int64_t min = 200000000000000;
const int64_t max = 400000000000000;

struct P {
	int64_t x, y, z;
};
struct HailStone {
	P p, v;
	bool intersect(const HailStone& other, long double& x, long double&y) {
		const auto nom = (p.x - other.p.x) * (-other.v.y) - (p.y - other.p.y) * (-other.v.x);
		const auto denom = (-v.x) * (-other.v.y) - (-v.y) * (-other.v.x);
		if (denom != 0) {
			long double tx = nom / long double(denom);
			const auto nom2 = (other.p.x - p.x) * (-v.y) - (other.p.y - p.y) * (-v.x);
			const auto denom2 = (-other.v.x) * (-v.y) - (-other.v.y) * (-v.x);
			long double ux = nom2 / long double(denom2);
			if (tx >= -1.e-6f && ux >= -1.e-6f) {
				x = p.x + tx * v.x;
				y = p.y + tx * v.y;
				return true;
			}
		}
		return false;
	}
};
int main()
{
	std::ifstream stream("..\\input24.txt");
	std::vector<HailStone> hs;
	std::string line;
	while (std::getline(stream, line)) {
		if (line.empty()) {
			continue;
		}
		HailStone h;
		int64_t x, y, z, vx, vy, vz;
		sscanf_s(line.c_str(), "%lli,%lli,%lli @ %lli,%lli,%lli", &x, &y, &z, &vx, &vy, &vz);
		h.p.x = x;
		h.p.y = y;
		h.p.z = x;
		h.v.x = vx;
		h.v.y = vy;
		h.v.z = vz;
		hs.push_back(h);
	}
	int sum = 0;
	for (int i = 0; i < hs.size(); ++i) {
		for (int j = i+1; j < hs.size(); ++j) {
			long double x, y;
			
			/*const long double min = 7;
			const long double max = 27;*/
			if (hs[i].intersect(hs[j], x, y) && x >= min && y >= min && x <= max && y <= max) {
				++sum;
			}
		}
	}
	std::cout << sum << std::endl;
}
