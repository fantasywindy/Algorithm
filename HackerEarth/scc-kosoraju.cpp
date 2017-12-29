#include <iostream>
#include <vector>
#include <cstring>
#include <cstdio>
#include <stack>
using namespace std;


const int MAX_N = 15 + 5;

int N, M;
vector<int> G[MAX_N];
vector<int> RG[MAX_N];

int visited[MAX_N];

vector<vector<int> > scc;

stack<int> S;

void dfs_util(int u)
{
	visited[u] = 1;

	for(auto v : G[u])
	{
		if(visited[v] == 0)
		{
			dfs_util(v);
		}
	}

	S.push(u);
}

void dfs()
{
	memset(visited, 0, sizeof(visited));

	for(int i = 0; i < N; ++i)
	{
		if(visited[i] == 0)
		{
			dfs_util(i);
		}
	} 
}



void dfs_again_util(int u, vector<int> & temp)
{
	visited[u] = 1;

	temp.push_back(u);

	for(auto v : RG[u])
	{
		if(visited[v] == 0)
		{
			dfs_again_util(v, temp);
		}
	}
}

void dfs_again()
{
	memset(visited, 0, sizeof(visited));

	while(S.empty() == false)
	{
		auto u = S.top();
		S.pop();

		if(visited[u] == 0)
		{
			vector<int> temp;
			dfs_again_util(u, temp);
			scc.push_back(temp);
		}
	}
}

int main()
{
	scanf("%d%d", &N, &M);
	for(int i = 0; i < M; ++i)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		--u;
		--v;
		G[u].push_back(v);
		RG[v].push_back(u);
	}


	dfs();

	dfs_again();

	int C = 0;
	int D = 0;

	for(auto s : scc)
	{
		if(s.size() % 2 == 0)
		{
			D += s.size();
		}
		else
		{
			C += s.size();
		}
	}

	cout << C - D << endl;

	return 0;
}