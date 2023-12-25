#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iomanip>      // std::setw
#include <set>
#include <queue>


struct Node {
	struct Edge {
		int v;
		int e;
	};
	std::string name;
	std::vector<std::string> cn;
	std::vector<Edge> c;
	int dfs, pred;
	bool visited;
};

int main()
{
	std::ifstream stream("..\\input25.txt");
	std::vector<Node> nodes;
	std::string line;
	while (std::getline(stream, line)) {
		if (line.empty()) {
			continue;
		}
		std::istringstream iss(line);
		Node node;
		iss >> node.name;
		node.name = node.name.substr(0, node.name.size() - 1);
		while (iss) {
			std::string tmp;
			iss >> tmp;
			if (iss) {
				node.cn.push_back(tmp);
			}
		}
		nodes.push_back(node);
	}
	struct Edge {
		int v1, v2;
		bool used = false;
		bool dfs = false;
		bool removed = false;
	};
	std::vector<Edge> c;
	for (int i = 0; i < nodes.size(); ++i) {
		for (const auto& cn : nodes[i].cn) {
			bool found = false;
			for (int j = 0; j < nodes.size(); ++j) {
				if (nodes[j].name == cn) {
					c.push_back({ i,j });
					found = true;
					break;
				}
			}
			if (!found) {
				c.push_back({ i, int(nodes.size()) });
				nodes.push_back(Node{ cn });
			}
		}
	}
	for (int i = 0; i < c.size(); ++i) {
		nodes[c[i].v1].c.push_back(Node::Edge{ c[i].v2, i });
		nodes[c[i].v2].c.push_back(Node::Edge{ c[i].v1, i });
	}
	int test = 0;
	int max = 0;
	std::vector<std::pair<int,int>> stack{ 0 };
	std::vector<int> dfs;
	const auto decomp = [&]() {
		for (Node& node : nodes) {
			node.visited = false;
			node.dfs = -1;
		}
		for (Edge& e : c) {
			e.used = false;
			e.dfs = false;
		}
		// Do DFS
		dfs.clear();
		stack.clear();
		stack.push_back({ 0,-1 });
		while (!stack.empty()) {
			auto p = stack.back();
			stack.pop_back();
			Node& n = nodes[p.first];
			if (n.dfs != -1) {
				continue;
			}
			n.dfs = dfs.size();
			n.pred = p.second;
			dfs.push_back(p.first);
			for (const auto& e : n.c) {
				if (c[e.e].removed) {
					continue;
				}
				stack.push_back({ e.v, p.first });
			}
		}
		// Traverse node based on DFS order
		for (int index : dfs) {
			Node& n = nodes[index];
			n.visited = true;
			for (const auto& e : n.c) {
				if (c[e.e].removed) {
					continue;
				}
				int v = e.v;
				if (nodes[v].pred != index && n.pred != v) {
					// NON-DFS edge
					c[e.e].used = true;
					while (!nodes[v].visited) {
						nodes[v].visited = true;
						for (auto& e2 : nodes[v].c) {
							if (c[e2.e].removed) {
								continue;
							}
							if (e2.v == nodes[v].pred) {
								// DFS edge back to root
								c[e2.e].used = true;
								v = e2.v;
								break;
							}
						}
					}
				}
			}
		}
		for (int k = 0; k < c.size(); ++k) {
			if (c[k].used == false && !c[k].removed) {
				c[k].removed = true;
				for (Node& node : nodes) {
					node.dfs = -1;
				}
				int cnt = 0;
				std::vector<int> stack{ 0 };
				while (!stack.empty()) {
					int index = stack.back();
					stack.pop_back();
					Node& n = nodes[index];
					if (n.dfs != -1) {
						continue;
					}
					++cnt;
					n.dfs = 0;
					for (auto& e : n.c) {
						if (c[e.e].removed) {
							continue;
						}
						stack.push_back(e.v);
					}
				}
				int val = cnt * (nodes.size() - cnt);
				if (val > 0) {
					std::cout << val << std::endl;
					return true;
				}
				c[k].removed = false;
			}
		}
		return false;
	};
	for (int i = 0; i < c.size(); ++i) {
		c[i].removed = true;
		for (int j = i + 1; j < c.size(); ++j) {
			c[j].removed = true;
			if (decomp()) {
				return 0;
			}
			c[j].removed = false;
		}
		c[i].removed = false;
	}
}
