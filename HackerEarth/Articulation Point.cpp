/* Given an undirected graph containing N vertices and M edges, find all the articulation points and all the bridges in
the graph.

Input: First line consists of two space separated integers denoting N and M. M lines follow, each containing two space
separated integers X and Y denoting there is an edge between X and Y.

Output: If the number of articulation points in the graph is p and that of bridges is q , then print as shown below: 
p 
p space separated integers, the articulation points, sorted in increasing order 
q 
q lines, each containing two space separated integers, the bridges in the graph. For a bridge u-v, print u first if u < v, otherwise print v first. Print
all the bridges in increasing order of first vertex, and if first vertex is same, then in increasing order of second
vertex.

3 2
0 1
1 2


1
1
2
0 1
1 2



*/

#include <vector>
#include <algorithm>
#include <iostream>
#include <utility>
#include <climits>


using namespace std;



const int MAX_N = 10 + 2;
const int MAX_M = 10 + 2;


int N; 
int M;

vector<vector<int> > adjs;

bool visited[MAX_N];

int low[MAX_N];

int touch[MAX_N];

int parent[MAX_N];

bool ap[MAX_N];

vector<pair<int, int> > bridge;


void dfs(int u, int t)
{
	visited[u] = true;

	low[u] = touch[u] = t + 1;

	int childs = 0;

	for(auto v : adjs[u])
	{
		if(visited[v] == false)
		{
			++childs;
			parent[v] = u;
			dfs(v, t + 1);
			low[u] = min(low[u], low[v]);

			if(parent[u] == -1 && childs > 1)
			{
				ap[u] = true;
			}
			else if(parent[u] != -1 && low[v] >= touch[u])
			{
				ap[u] = true;
			}

			if(low[v] > touch[u])
			{
				bridge.push_back({min(u, v), max(u, v)});
			}
		}
		else
		{
			if(v != parent[u])
			{
				low[u] = min(low[u], touch[v]);
			}
		}
	}

}


int main() 
{     
	ios_base::sync_with_stdio(false);

	cin >> N >> M;

	int start, end;

	adjs.assign(N, vector<int>());

	fill(visited, visited + MAX_N, false);

	fill(low, low + MAX_N, INT_MAX);

	fill(touch, touch + MAX_N, 0);

	fill(parent, parent + MAX_N, -1);

	fill(ap, ap + MAX_N, false);

	for(int i = 0; i < M; ++i)
	{
		cin >> start >> end;
		adjs[start].push_back(end);
		adjs[end].push_back(start);
	}


	dfs(1, 0);

	int ap_count = count(ap, ap + MAX_N, true);

	cout << ap_count << endl;

	for(int i = 0; i < N; ++i)
	{
		if(ap[i] == true)
		{
			cout << i << " ";
		}
	}

	cout << bridge.size() << endl;

	sort(bridge.begin(), bridge.end(), [](const pair<int, int> & l, const pair<int, int> & r)
	{
		return l.first < r.first || (l.first == r.first && l.second < r.second);
	});

	for(auto b : bridge)
	{
		cout << b.first << " " << b.second << endl;
	}

	return 0;
}




