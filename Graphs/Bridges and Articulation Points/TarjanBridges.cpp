#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

using vi = vector<int>;
using vvi = vector<vector<int>>;
using vii = vector<pair<int, int>>;

class TarjanBridges {

	/*
	* Tarjan's algorithm for finding bridges in an undirected graph
	*
	* Time Complexity: O(N+M)
	* Memory Complexity: O(N+M)
	* (|V| = N, |E| = M)
	*
	* The implementation has been tested on:
	* - https://codeforces.com/gym/100083, task C
	*/

private:
	static void dfs(int curr_V, int last_V, vi& deeps, vii& bridges, const vvi& g, int curr_deep = 0) {

		// Building a dfs tree
		deeps[curr_V] = curr_deep;
		for (int next_V : g[curr_V]) {
			if (deeps[next_V] != -1) continue;
			dfs(next_V, curr_V, deeps, bridges, g, curr_deep + 1);
		}

		// Updating the lowest achievable depth from the current vertex
		for (int next_V : g[curr_V]) {
			if (next_V == last_V) continue;
			deeps[curr_V] = min(deeps[curr_V], deeps[next_V]);
		}

		// The current vertex should not be the root
		if (curr_deep == deeps[curr_V] && curr_V != last_V) {
			bridges.push_back({ curr_V, last_V });
		}
	}

public:
	TarjanBridges() = delete;

    	/*
    	* Finds all bridges in an undirected graph.
	*
    	* The function takes a graph g:
    	* -graph assignment method:  adjacency lists
    	* -connectivity:             Yes/No
    	* -directed:                 No
    	* -weighted:                 No (does not match the graph assignment method)
	* -loops:                    Yes/No
	* -multiple edges:           No
    	* -other features:            -
    	* 
    	* The function returns a vector of pairs of vertices, the edges connecting which are bridges
    	*/

	static vii getBridges(const vvi& g) {

		int N = g.size();

		vii bridges(0);
		vi deeps(N, -1);

		// Bypassing all connectivity components
		for (int start_V = 0; start_V < N; start_V++) {
			if (deeps[start_V] == -1) {
				dfs(start_V, start_V, deeps, bridges, g);
			}
		}

		return bridges;
	}
};
