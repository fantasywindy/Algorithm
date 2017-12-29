#include <vector>
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

const int MAX_N = 100 + 5;

int N, M;


int G[MAX_N][MAX_N];

vector<int> ans;

bool ok;

int visited[MAX_N];

void reset()
{
	memset(G, 0, sizeof(G));
	ok = true;
	memset(visited, 0, sizeof(visited));
	ans.clear();
}

void dfs(int );

void solution()
{
	for(int i = 1; i <= N; ++i)
	{
		if(ok == false)
		{
			return;
		}

		if(visited[i] == 0)
		{
			dfs(i);
		}
	}
}

void dfs(int i)
{
	if(ok == false)
	{
		return;
	}

	visited[i] = -1;

	for(int j = 1; j <= N; ++j)
	{
		if(ok == false)
		{
			return;
		}

		if(G[i][j] != 1)
		{
			continue;
		}

		if(visited[j] == 0)
		{
			dfs(j);
		}
		else if(visited[j] == -1)
		{
			ok = false;
			return;
		}
	}

	ans.insert(ans.begin(), i);

	visited[i] = 1;
}

void print_ans()
{
	if(ok == false)
	{
		return;
	}

	cout << ans.front();

	for(int i = 1; i < ans.size(); ++i)
	{
		cout << " " << ans[i];
	}
	cout << endl;
}


int main()
{
	while(scanf("%d%d", &N, &M) == 2)
	{
		if(N == 0 && M == 0)
		{
			break;
		}

		reset();

		int u, v;
		for(int i = 0; i < M; ++i)
		{
			scanf("%d%d", &u, &v);
			G[u][v] = 1;
		}

		solution();

		print_ans();
	}

	return 0;
}