#include <vector>
#include <algorithm>
#include <queue>
#include <iostream>
#include <cstdio>
#include <cstring>
#include <climits>



using namespace std;


int n, m;

const int MAX_N = 100005;
const int MAX_M = 200005;

struct Edge
{
	Edge(int u, int v, int c)
		:u(u), v(v), c(c)
		{

		}
	int u;
	int v;
	int c;
};

vector<Edge> edges;

vector<int> G[MAX_N];

int dist[MAX_N];

int parent[MAX_N];

int pathColor[MAX_N];

int visited[MAX_N];


void reset()
{
	edges.clear();
	for(int i = 0; i < MAX_N; ++i)
	{
		G[i].clear();
	}

	memset(visited, 0, sizeof(visited));
	memset(parent, 0, sizeof(parent));
	memset(dist, 0, sizeof(dist));
	memset(pathColor, 0, sizeof(pathColor));

}

void bfs()
{
	memset(visited, 0, sizeof(visited));

	visited[1] = 1;

	cout << dist[1] - 1 << endl;
	vector<int> curNodes;
	curNodes.push_back(1);


	for(int d = dist[1]; d > 1; --d)
	{
		vector<int> nextRound;

		int minColor = INT_MAX;

		for(auto cur : curNodes)
		{
			for(auto edge : G[cur])
			{
				int next = edges[edge].v;
				int color = edges[edge].c;

				if(dist[next] != dist[cur] - 1)
				{
					continue;
				}

				minColor = min(minColor, color);
			}
		}

		if(d == dist[1])
		{
			cout << minColor;
		}
		else
		{
			cout << " " << minColor;
		}

		for(auto cur : curNodes)
		{
			for(auto edge : G[cur])
			{
				int next = edges[edge].v;
				int color = edges[edge].c;

				if(dist[next] != dist[cur] - 1)
				{
					continue;
				}

				if(color == minColor && visited[next] == 0)
				{
					nextRound.push_back(next);
					parent[next] = cur;
					pathColor[next] = minColor;
					visited[next] = 1;
				}
			}
		}

		curNodes = nextRound;
	}
	cout << endl;

}

void print()
{
	//cout << "print  " << endl;
	// cout << dist[1] - 1 << endl;

	// int node = n;

	// vector<int> path;

	// while(node)
	// {
	// 	//cout << "curNode " << node << endl;
	// 	int pNode = parent[node];
	// 	//cout << "curNode " << pNode << endl;
	// 	if(pNode != 0)
	// 	{
	// 		path.push_back(pathColor[node]);
	// 	}
	// 	node = pNode;
	// }

	// reverse(path.begin(), path.end());

	// cout << path.front();

	// for(int k = 1; k < path.size(); ++k)
	// {
	// 	cout << " " << path[k];
	// }

	// cout << endl;
}

void reverse_bfs()
{
	//cout << "reverse bfs" << endl;


	queue<int> Q;

	Q.push(n);

	visited[n] = 1;

	dist[n] = 1;

	bool finish = false;

	while(!Q.empty() && finish == false)
	{
		auto cur = Q.front();
		Q.pop();

		for(auto edge : G[cur])
		{
			int next = edges[edge].v;
			if(visited[next] == 0)
			{
				//cout << "cur " << cur << " next " << next << endl;
				dist[next] = dist[cur] + 1;
				visited[next] = 1;
				Q.push(next);

				if(next == 1)
				{
					finish = true;
					break;
				}
			}
		}
	}

	//we got the dists from any node to node n
}

int addEdge(int ai, int bi, int ci)
{
	int index = edges.size();
	edges.push_back(Edge(ai, bi, ci));
	return index;
}


int main()
{
	ios_base::sync_with_stdio(false);

	while(scanf("%d%d", &n, &m) == 2 && n && m)
	{

		reset();

		for(int e = 0; e < m; ++e)
		{
			int ai, bi, ci;
			scanf("%d%d%d", &ai, &bi, &ci);
			int edge1 = addEdge(ai, bi, ci);
			G[ai].push_back(edge1);
			int edge2 = addEdge(bi, ai, ci);
			G[bi].push_back(edge2);
		}

		reverse_bfs();

		//cout << "from 1 to n " << dist[1] << endl;

		bfs();

		print();
	}
}