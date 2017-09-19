#include <cmath>
#include <cstdio>
#include <vector>
#include <climits>
#include <algorithm>
#include <iostream>
using namespace std;

long long MAX_NODES = 1e5 + 10;
long long MAX_K = 200 + 10;
long long weights[MAX_NODES] = 0;
bool visited[MAX_NODES] = {false};
long long visited_order[MAX_NODES] = {0};
long long subtrees[MAX_NODES] = {0};
//long long sums[MAX_NODES] = {0};
long long dp[MAX_NODES][MAX_K];


vector<vector<int> > adjs;

long long dp[MAX_NODES][MAX_K] = {0};
long long curIndex = 0;

void dfs(int u)
{
	visited[u] = true;
	int mark = curIndex;
	visited_order[curIndex++] = u;

	for(auto v : adjs[u])
	{
		if(visited[v] == true)
		{
			continue;
		}

		dfs(v);
	}

	subtrees[u] = curIndex - mark;
}

int main()
{
	ios_base::sync_with_stdio(false);
	int n, k;
	cin >> n >> k;

	for(int i = 1; i <= n; ++i)
	{
		cin >> weights[i];
	}

	adjs.assign(n + 1, vector<int>());

	int start, end;

	for(int e = 1; e <= n - 1; ++e)
	{
		cin >> start >> end;
		adjs[start].push_back(end);
		adjs[end].push_back(start);
	}

	curIndex = 1;


	for(int i = 0; i <= n; ++i)
	{
		visited[i] = false;
	}

	dfs(1);

	for(int i = 0; i <= n; ++i)
	{
		for(int j = 0; j <= k; ++j)
		{
			dp[i][j] = numeric_limits<long long>::min();
		}
	}

	for(int j = 0; j <= k; ++j)
	{
		dp[0][j] = 0;
	}

	for(int i = 1; i <= n; ++i)
	{
		dp[i][0] = dp[i-1][0] + weights[visited_order[i]];
	}


	for(int i = 1; i <= n; ++i)
	{
		for(int j = 0; j <= k; ++j)
		{
			//if use node[i]
			dp[i][j] = max(dp[i][j], dp[i-1][j] + weights[visited_order[i]]);

			//if not use node[i]
			dp[i + subtrees[visited_order[i]] - 1][j + 1] = max(dp[i + subtrees[visited_order[i]] - 1][j + 1], dp[i-1][j]);
		}
	}

	cout << dp[n][k] << endl;

}