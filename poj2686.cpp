#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <iomanip>
using namespace std;

const int maxn = 8 + 2;
const int maxm = 30 + 2;

int n, m, p, a, b;

int t[maxn];

int dist[maxm][maxm];

double dp[1 << maxn][maxm];

const int INF = 1e9;


void solve()
{
	double res = INF;

	// define dp[s][u] is that now we are at u, and we still have s tickets

	dp[(1 << n) - 1][a] = 0;

	for(int s = (1 << n) - 1; s >= 0; --s)
	{
		res = min(res, dp[s][b]);

		for(int u = 0; u < m; ++u)
		{
			if(dp[s][u] == INF) continue;

			for(int k = 0; k < n; ++k)
			{
				if((s & (1 << k)) != 0)
				{
					// we have kth tickets
					for(int v = 0; v < m; ++v)
					{
						// no road between u and v
						if(dist[u][v] < 0) continue;

						// use kth ticket
						int s1 = s & (~(1 << k));

						dp[s1][v] = min(dp[s1][v], dp[s][u] + (double)dist[u][v] / t[k]);
					}
				}
			}
		}
	}

	if(res == INF)
	{
		cout << "Impossible" << endl;
	}
	else
	{
		cout << std::fixed << std::setprecision(3) << res << endl;
	}
}


int main()
{
	while(scanf("%d%d%d%d%d", &n, &m, &p, &a, &b) == 5 && n != 0 && m != 0)
	{
		memset(dist, -1, sizeof(dist));

		for(int i = 0; i < (1 << n); ++i)
		{
			fill(dp[i], dp[i] + m, INF);
		}

		--a;
		--b;

		for(int i = 0; i < n; ++i)
		{
			scanf("%d", &t[i]);
		}

		for(int i = 0; i < p; ++i)
		{
			int u, v, w;
			scanf("%d%d%d", &u, &v, &w);
			--u;
			--v;
			dist[u][v]= w;
			dist[v][u] = w;
		}
		

		solve();
	}

	return 0;
}