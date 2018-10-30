#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

const int maxm = 20 + 5;
const int maxn = 20 + 5;
const int maxk = 20 + 5;

int g[maxm][maxn];

int m, n, k;

int vis[maxm][maxn][maxk];

int solve()
{
	queue<vector<int> > Q;

	Q.push({0, 0, k, 0});

	vis[0][0][k] = 1;

	static vector<pair<int, int> > dirs = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

	while(!Q.empty())
	{

		auto cur = Q.front();

		Q.pop();

		//cout << cur[0] << " " << cur[1] << " " << cur[2] << " " << cur[3] << endl;

		if(cur[0] == m - 1 && cur[1] == n - 1)
		{
			return cur[3];
		}

		for(auto dir : dirs)
		{
			int nx = cur[0] + dir.first;
			int ny = cur[1] + dir.second;
			int turbo = cur[2];
			int move = cur[3];
			if(nx < 0 || nx >= m || ny < 0 || ny >= n) continue;

			if(g[nx][ny] == 1)
			{
				if(turbo > 0)
				{
					--turbo;
				}
				else
				{
					continue;
				}
			}
			else
			{
				turbo = k;
			}

			if(vis[nx][ny][turbo] == 1) continue;

			vis[nx][ny][turbo] = 1;

			Q.push({nx, ny, turbo, move + 1});
		}
	}

	return -1;

}


int main()
{
	ios::sync_with_stdio(false);

	int T;
	cin >> T;

	while(T--)
	{
		//cout << "Test " << endl;
		memset(g, 0, sizeof(g));

		memset(vis, 0, sizeof(vis));

		cin >> m >> n >> k;

		for(int i = 0; i < m; ++i)
		{
			for(int j = 0; j < n; ++j)
			{
				cin >> g[i][j];
			}
		}


		cout << solve() << endl;
	}
	return 0;
}