#include <iostream>
#include <vector>
#include <cstring>
#include <cstdio>
#include <stack>
#include <set>
#include <algorithm>


using namespace std;


const int MAX_N = 10 + 5;

int N, M;
vector<int> G[MAX_N];

int visited[MAX_N];

vector<set<int> > bcc;

int disc[MAX_N];

int low[MAX_N];

int t = 0;

stack<pair<int, int> > edges;

void addToBcc(int u, int v)
{
	set<int> temp;
	while(edges.top() != make_pair(u, v))
	{
		auto top = edges.top();
		edges.pop();
		temp.insert(top.first);
		temp.insert(top.second);
	}

	auto top = edges.top();
	edges.pop();
	temp.insert(top.first);
	temp.insert(top.second);

	bcc.push_back(temp);
}

void BCC(int u, int p)
{
	low[u] = disc[u] = t;
	t = t + 1;
	visited[u] = 1;

	int child_cnt = 0;

	for(auto v : G[u])
	{
		if(v == p)
		{
			continue;
		}

		if(visited[v] == 0)
		{
			edges.push({u, v});
			++child_cnt;
			BCC(v, u);
			low[u] = min(low[u], low[v]);

			if( (p == -1 && child_cnt >= 2) ||
				(p != -1 && disc[u] <= low[v])
				)
			{
				addToBcc(u, v);
			}
		}
		else
		{
			if(low[u] > disc[v])
			{
				low[u] = disc[v];
				edges.push({u, v});
			}
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
		G[u].push_back(v);
		G[v].push_back(u);
	}

	for(int i = 0; i < N; ++i)
	{
		if(visited[i] == 0)
		{
			BCC(i, -1);
			set<int> temp;
			while(edges.empty() == false)
			{
				auto cur = edges.top();
				edges.pop();
				temp.insert(cur.first);
				temp.insert(cur.second);
			}
			bcc.push_back(temp);
		}
	}

	int odd = count_if(bcc.begin(), bcc.end(), [](const auto & bc)
	{
		return bc.size() % 2 != 0;
	});

	int even = bcc.size() - odd;

	cout << odd << " " << even << endl;

	return 0;
}