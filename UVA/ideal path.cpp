#include <vector>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>

using namespace std;


const int MAX_N = 100000 + 5;
const int INF = 1000000000 + 5;

struct Edge
{
	Edge(int u, int v, int c)
		:u(u), v(v), c(c)
	{

	}
	int u, v, c;
};

vector<Edge> edges;

vector<int> G[MAX_N];

int N, M;

int dist[MAX_N];

int visited[MAX_N];

vector<int> ans;


void addEdge(int u, int v, int c)
{
	int sz = edges.size();
	edges.push_back(Edge(u, v, c));
	G[u].push_back(sz);
}

void reverse_bfs()
{
	memset(visited, 0, sizeof(visited));
	queue<int> Q;
	Q.push(N);
	dist[N] = 0;
	visited[N] = 1;
	while(!Q.empty())
	{
		auto cur = Q.front();
		Q.pop();

		for(auto eidx : G[cur])
		{
			auto edge = edges[eidx];
			auto next = edge.v;

			if(visited[next] == 0)
			{
				dist[next] = dist[cur] + 1;
				visited[next] = 1;
				Q.push(next);
			}
		}
	}
}

void bfs()
{
	memset(visited, 0, sizeof(visited));

	vector<int> thisRound;
	thisRound.push_back(1);
	visited[1] = 1;

	for(int d = dist[1]; d > 0; --d)
	{
		int min_color = INF;

		for(auto cur : thisRound)
		{
			for(auto eidx : G[cur])
			{
				auto edge = edges[eidx];

				auto next = edge.v;
				auto color = edge.c;

				if(dist[next] == dist[cur] - 1)
				{
					min_color = min(min_color, color);
				}
			}
		}

		ans.push_back(min_color);

		vector<int> nextRound;

		for(auto cur : thisRound)
		{
			for(auto eidx : G[cur])
			{
				auto edge = edges[eidx];
				auto next = edge.v;
				auto color = edge.c;

				if(dist[next] == dist[cur] - 1 && color == min_color && visited[next] == 0)
				{
					nextRound.push_back(next);
					visited[next] = 1;
				}
			}
		}

		thisRound = nextRound;
	}

}

void print_ans()
{
	cout << ans.size() << endl;

	cout << ans.front();

	for(int j = 1; j < ans.size(); ++j)
	{
		cout << " " << ans[j];
	}

	cout << endl;
}


void reset()
{
	memset(visited, 0, sizeof(visited));
	memset(dist, 0, sizeof(dist));
	edges.clear();
	for(auto & vec : G)
	{
		vec.clear();
	}
	ans.clear();
}

void input()
{
	int ai, bi, ci;
	for(int i = 0; i < M; ++i)
	{
		scanf("%d%d%d", &ai, &bi, &ci);
		addEdge(ai, bi, ci);
		addEdge(bi, ai, ci);
	}
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

		input();

		reverse_bfs();

		bfs();

		print_ans();
	}

	return 0;
}

