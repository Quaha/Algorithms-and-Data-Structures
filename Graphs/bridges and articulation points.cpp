#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

namespace Bridges {

	/* 
	* The implementation has been tested on:
	* - https://codeforces.com/gym/100083, task C
	*/

	/* 
	* Time Complexity: O(N+M)
	* Memory Complexity: O(N+M)
	*/

	vector<pair<int, int>> bridges;
	vector<int> deeps;

	//Tarjan's algorithm for finding bridges in an undirected graph
	void dfs(int curr_V, int last_V, const vector<vector<int>>& g, int curr_deep = 0) {

		// Building a dfs tree
		deeps[curr_V] = curr_deep;
		for (int next_V : g[curr_V]) {
			if (deeps[next_V] != -1) continue;
			dfs(next_V, curr_V, g, curr_deep + 1);
		}

		// Updating the lowest achievable depth for a current vertex
		for (int next_V : g[curr_V]) {
			if (next_V == last_V) continue;
			deeps[curr_V] = min(deeps[curr_V], deeps[next_V]);
		}

		// The current vertex should not be the root
		if (curr_deep == deeps[curr_V] && curr_V != last_V) {
			bridges.push_back({ curr_V, last_V });
		}
	}

	/*
	* Finds all bridges in an undirected graph.
	* 
	* @param g: An undirected unweighted graph given by adjacency lists
	* @return bridges: Vector of bridges defined by incident vertices
	* 
	*/
	vector<pair<int, int>> getBridges(const vector<vector<int>>& g) {

		bridges.clear();

		int N = g.size();

		deeps.resize(N, -1);

		// Bypassing all connectivity components
		for (int start_V = 0; start_V < N; start_V++) {
			if (deeps[start_V] == -1) {
				dfs(start_V, start_V, g);
			}
		}

		deeps.clear();
		deeps.shrink_to_fit();

		return move(bridges);
	}
}
