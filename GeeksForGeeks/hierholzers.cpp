#include <iostream>
#include <map>
#include <vector>
#include <stack>

using namespace std;

const int maxn = 100 + 5;

map<int, int> remainEdges;

stack<int> curStack;

int n;

vector<int> circuit;

vector<int> G[maxn];


void dfs(int u)
{
	if(G[u].empty() == false)
	{
		return;
	}

	curStack.push(u);

	for(auto v : G[u])
	{
		dfs(v);
	}
}

void solve()
{
	//for example we start with 0

	for(int u = 0; u < n; ++u)
	{
		for(auto v : G[u])
		{
			remainEdges[u]++;
		}
	}

	curStack.push(3);

	int u = 3;

	while(curStack.empty() == false)
	{
		if(remainEdges[u] != 0)
		{
			curStack.push(u);
			auto v = G[u].back();
			G[u].pop_back();
			--remainEdges[u];
			u = v;
		}
		else
		{
			cout << "push in circuit " << u << endl; 
			circuit.push_back(u);

			u = curStack.top();

			curStack.pop();
		}
	}

	for(int k = circuit.size() - 1; k >= 0; --k)
	{
		cout << circuit[k] << endl;
	}
}

int main()
{
	//input the graph

	G[0].push_back(1);
	G[1].push_back(2);
	G[2].push_back(0);
	G[1].push_back(3);
	G[3].push_back(4);
	G[4].push_back(1);

	n = 5;

	solve();

	return 0;
}

