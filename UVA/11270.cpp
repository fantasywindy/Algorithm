#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
using namespace std;


const int maxn = 10 + 5;

int m, n;

long long dp[2][1 << maxn];

long long memo[maxn * maxn][maxn * maxn];


void update(int from, int to, int cur)
{
	if(to & (1 << m))
	{
		dp[cur][to ^ (1 << m)] += dp[1 - cur][from];
	}
}

long long solve()
{
	memset(dp, 0, sizeof(dp));

	int cur = 0;

	dp[0][ (1 << m) - 1] = 1;

	for(int i = 0; i < n; ++i)
	{
		for(int j = 0; j < m; ++j)
		{
			// every time exchange buffer
			cur = cur ^ 1;

			memset(dp[cur], 0, sizeof(dp[cur]));

			for(int k = 0; k < (1 << m); ++k)
			{
				// not put title at [i][j]
				update(k, k << 1, cur);

				// put title vertically

				if(i > 0 && !(k & (1 << (m - 1))))
				{
					update(k, (k << 1) ^ (1 << m) ^ 1, cur);
				}

				// put title horizontally

				if(j > 0 && !(k & 1))
				{
					update(k, (k << 1) ^ 3, cur);
				}
			}
		}
	}

	return dp[cur][(1 << m) - 1];

}

int main()
{
	memset(memo, -1, sizeof(memo));


	while(scanf("%d%d", &m, &n) == 2)
	{
		if(m > n)
		{
			swap(m, n);
		}


		if(memo[m][n] != -1)
		{
			cout << memo[m][n] << endl;
		}
		else
		{
			long long ans = solve();
			memo[m][n] = ans;
			cout << ans << endl;
		}
	}

	return 0;
}