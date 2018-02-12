#include <cstdio>
#include <iostream>
#include <cstring>
#include <queue>

using namespace std;


const int maxn = 200 + 5;

int vis[maxn][maxn];

int ans[maxn];

int cap[3];


struct Node
{
	int v[3];
	int dist;
	bool operator<(const Node & r) const
	{
		return dist > r.dist;
	}
};

void update_ans(const Node & u)
{
	for(int i = 0; i < 3; ++i)
	{
		int d = u.v[i];
		if(ans[d] < 0 || ans[d] > u.dist)
		{
			ans[d] = u.dist;
		}
	}
}

void solve(int a, int b, int c, int d)
{
	cap[0] = a; cap[1] = b; cap[2] = c;
	memset(vis, 0, sizeof(vis));
	memset(ans, -1, sizeof(ans));
	priority_queue<Node> q;
	Node start;
	start.v[0] = 0; start.v[1] = 0; start.v[2] = c; start.dist = 0;
	q.push(start);
	vis[0][0] = 1;

	while(q.empty() == false)
	{
		auto u = q.top();
		q.pop();
		update_ans(u);
		if(ans[d] >= 0) break;
		for(int i = 0; i < 3; ++i)
		{
			for(int j = 0; j < 3; ++j)
			{
				if(i == j) continue;
				if(u.v[i] == 0 || u.v[j] == cap[j]) continue;
				int amount = min(u.v[i], cap[j] - u.v[j]);
				Node u2;
				memcpy(&u2, &u, sizeof(u));
				u2.dist = u.dist + amount;
				u2.v[i] -= amount;
				u2.v[j] += amount;
				if(!vis[u2.v[0]][u2.v[1]])
				{
					vis[u2.v[0]][u2.v[1]] = 1;
					q.push(u2);
				}
			}
		}
	}

	while(d >= 0)
	{
		if(ans[d] >= 0)
		{
			cout << ans[d] << " " << d << endl;
			break;
		}
		--d;
	}
}

int main()
{
	int t;
	scanf("%d", &t);
	while(t--)
	{
		int a, b, c, d;
		scanf("%d%d%d%d", &a, &b, &c, &d);
		solve(a, b, c, d);
	}
	return 0;
}