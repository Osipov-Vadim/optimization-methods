//#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
//#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES 

#include <iostream>
#include <vector>
#include <iomanip> 
#include <fstream>
#include <array>
#include <list>
#include <queue>

struct way {
	size_t idx_from;
	size_t idx_to;
	size_t weight;
};

auto findMinWay(
	std::vector<std::vector<way>> &ways, size_t idx_from, size_t idx_to)
{
	std::vector<int> min_costs(ways.size(), -1);
	std::vector<int> prev_idx(ways.size(), -1);
	min_costs[idx_from] = 0;
	prev_idx[idx_from] = 0;
	std::queue<way> q;

	for (size_t i = 0; i < ways[1].size(); ++i) {
		q.push(ways[idx_from][i]);
	}
	while (q.size() != 0) {
		auto t_way = q.front();
		q.pop();
		if (min_costs[t_way.idx_to] == -1 ||
			min_costs[t_way.idx_to] > min_costs[t_way.idx_from] + t_way.weight) 
		{
			min_costs[t_way.idx_to] = min_costs[t_way.idx_from] + t_way.weight;
			prev_idx[t_way.idx_to] = t_way.idx_from;
			for (size_t i = 0; i < ways[t_way.idx_to].size(); ++i) {
				q.push(ways[t_way.idx_to][i]);
			}
		}
	}

	std::vector<int> res;
	size_t c_idx = idx_to;
	while (c_idx != 0) {
		res.push_back(c_idx);
		c_idx = prev_idx[c_idx];
	}
	std::reverse(res.begin(), res.end());
	return std::make_pair(min_costs[idx_to], res);
}

int main() {
	//--------------------------------
	setlocale(LC_ALL, "Russian");
	system("color F2");
	std::ios_base::sync_with_stdio(false);
	std::ifstream fin("input.txt");
	std::ofstream fout("output.txt");
	std::cout << std::fixed << std::setprecision(4);
	//--------------------------------


	std::vector<std::vector<way>> ways
		{	{},
		{	{1, 4, 7},	{1, 3, 3},	{1, 2, 5}},
		{	{2, 7, 6}	},
		{	{3, 6, 7}, {3, 7, 5}	},
		{	{4, 6, 4}	},
		{	{}	},
		{	{6, 7, 9},	{6, 8, 5}	},
		{	{7, 8, 2},	{7, 9, 8}	},
		{	{8, 10, 11}	},
		{	{9, 10, 7}	},
		{	{}	} };


	
	auto res = findMinWay(ways, 1, 10);

	std::cout << res.first << '\n';
	for (size_t i = 0; i < res.second.size(); ++i) {
		std::cout << res.second[i] << ' ';
	}








	system("pause");
	return 0;
}

