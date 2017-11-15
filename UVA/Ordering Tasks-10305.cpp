/*
John has n tasks to do. Unfortunately, the tasks are not independent and the execution of one task is
only possible if other tasks have already been executed.
Input
The input will consist of several instances of the problem. Each instance begins with a line containing
two integers, 1 ≤ n ≤ 100 and m. n is the number of tasks (numbered from 1 to n) and m is the
number of direct precedence relations between tasks. After this, there will be m lines with two integers
i and j, representing the fact that task i must be executed before task j.
An instance with n = m = 0 will finish the input.
Output
For each instance, print a line with n integers representing the tasks in a possible order of execution.
Sample Input
5 4
1 2
2 3
1 3
1 5
0 0
Sample Output

*/

#include <iostream>
#include <vector>
#include <sstream>

using namespace std;


int n;
int m;

const int MAX_N = 100 + 5;

struct Edge
{
	Edge(int u = 0, int v = 0):
		u(u), v(v)
		{

		}
	int u;
	int v;
};

vector<int> G[MAX_N];

vector<Edge> edges;

void addEdge(int u, int v)
{
	edges.push_back(Edge(u, v));
	int idx = edges.size() - 1;
	G[u].push_back(idx);
}

int visited[MAX_N];


vector<int> path;

bool dfs(int i)
{
	visited[i] = -1; //visiting now

	for(int j = 0; j < G[i].size(); ++j)
	{
		int e = G[i][j];

		if(visited[edges[e].v] == -1)
		{
			return false;
		}

		if(visited[edges[e].v] == 0 && !dfs(edges[e].v))
		{
			return false;
		}
	}

	visited[i] = 1;

	path.insert(path.begin(), i);

	return true;
}

bool topsort()
{
	for(int i = 1; i <= n; ++i)
	{
		if(visited[i] == 0)
		{
			if(!dfs(i))
			{
				return false;
			}
		}
	}

	return true;
}

int main()
{
	ios_base::sync_with_stdio(false);

	string line;

	while(getline(cin, line))
	{
		stringstream ss(line);

		ss >> n >> m;

		if(n == 0 && m == 0)
		{
			break;
		}

		edges.clear();

		for(int i = 0; i < MAX_N; ++i)
		{
			G[i].clear();
		}

		for(int i = 0; i < m; ++i)
		{
			getline(cin, line);
			stringstream ss1(line);
			int u, v;
			ss1 >> u >> v;
			addEdge(u, v);
		}

		memset(visited, 0, sizeof(visited));

		path.clear();

		if(topsort())
		{
			cout << path.front();

			for(int k = 1; k < path.size(); ++k)
			{
				cout << " " << path[k];
			}

			cout << endl;
		}
		// else
		// {
		// 	cout << "has cycle" << endl;
		// }
	}

	return 0;
}