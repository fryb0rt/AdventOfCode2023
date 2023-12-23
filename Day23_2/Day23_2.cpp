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
	int y, x;
	bool operator==(const P& p) const {
		return p.x == x && p.y == y;
	}
};

int main()
{
	std::ifstream stream("..\\input23.txt");
	std::vector<std::string> lines;
	std::string line;
	while (std::getline(stream, line)) {
		if (line.empty()) {
			continue;
		}
		lines.push_back(line);
	}
	std::vector<P> vertices;
	vertices.push_back(P{ 0,1 });
	lines[0][1] = '#';
	for (int i = 1; i < lines.size() - 1; ++i) {
		for (int j = 1; j < lines[0].size() - 1; ++j) {
			if (lines[i][j] != '#') {
				int cnt = 0;
				cnt += lines[i - 1][j] != '#';
				cnt += lines[i + 1][j] != '#';
				cnt += lines[i][j - 1] != '#';
				cnt += lines[i][j + 1] != '#';
				if (cnt > 2) {
					vertices.push_back(P{ i,j });
					lines[i][j] = '#';
				}
			}
		}
	}
	lines.back()[lines[0].size() - 2] = '#';
	vertices.push_back(P{ int(lines.size() - 1),int(lines[0].size() - 2) });

	struct Edge {
		int steps;
		int vertex;
	};
	std::vector<std::vector<Edge>> dist(vertices.size());
	for (int i = 0; i < vertices.size(); ++i) {
		for (int j = i + 1; j < vertices.size(); ++j) {
			struct El {
				P p;
				int steps;
				P previous;
			};
			std::vector<El> stack;
			int steps = -1;
			stack.push_back(El{ vertices[i], 0 });
			const auto push_back = [&](const El& el, P prev) {
				if (el.p == vertices[j]) {
					steps = el.steps;
					return;
				}
				if (el.p.y < 0 || el.p.y >= lines.size() || el.p == prev || lines[el.p.y][el.p.x] == '#') {
					return;
				}
				stack.push_back(el);
			};
			while (!stack.empty()) {
				El el = stack.back();
				stack.pop_back();
				++el.steps;
				push_back(El{ P{el.p.y ,el.p.x + 1}, el.steps, el.p }, el.previous);
				push_back(El{ P{el.p.y ,el.p.x - 1}, el.steps, el.p }, el.previous);
				push_back(El{ P{el.p.y + 1,el.p.x}, el.steps, el.p }, el.previous);
				push_back(El{ P{el.p.y - 1 ,el.p.x}, el.steps, el.p }, el.previous);
			}

			if (steps != -1) {
				dist[i].push_back(Edge{ steps, j });
				dist[j].push_back(Edge{ steps, i });
			}
		}
	}

	struct El {
		int vertexIndex;
		int steps;
		uint64_t previous = 0;
	};
	int steps = 0;
	std::vector<El> stack;
	stack.push_back(El{ 0, 0 });
	const auto push = [&](El&& el) {
		if ((el.previous & (1ull << uint64_t(el.vertexIndex))) > 0) {
			return;
		}
		if (el.vertexIndex == vertices.size() - 1) {
			steps = std::max(steps, el.steps);
			return;
		}
		stack.push_back(el);
	};

	while (!stack.empty()) {
		El el = stack.back();
		stack.pop_back();
		el.previous |= 1ull << uint64_t(el.vertexIndex);
		for (Edge& e : dist[el.vertexIndex]) {
			push(El{ e.vertex, el.steps + e.steps, el.previous });
		}
	}
	std::cout << steps << std::endl;
}
