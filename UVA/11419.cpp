#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>
using namespace std;

const int maxn = 1010 + 5;

int gUsed[maxn];
int bUsed[maxn];

int gMatch[maxn];
int bMatch[maxn];

int line[maxn][maxn];

int R, C, N;

vector<int> girlsUnmatch;
vector<int> boysMatch;

bool dfs(int x)
{
	gUsed[x] = 1;

	for(int y = 1; y <= C; ++y)
	{
		if(line[x][y] == 1 && bUsed[y] == 0)
		{
			bUsed[y] = 1;
			if(bMatch[y] == 0 || dfs(bMatch[y]))
			{
				gMatch[x] = y;
				bMatch[y] = x;
				return true;
			}
		}
	}

	return false;
}


int main()
{
	while(scanf("%d%d%d", &R, &C, &N) == 3 && R && C && N)
	{
		memset(line, 0, sizeof(line));
		for(int i = 0; i < N; ++i)
		{
			int r, c;
			cin >> r >> c;
			line[r][c] = 1;
		}

		memset(gMatch, 0, sizeof(gMatch));
		memset(bMatch, 0, sizeof(bMatch));

		int match = 0;
		for(int x = 1; x <= R; ++x)
		{
			memset(gUsed, 0, sizeof(gUsed));
			memset(bUsed, 0, sizeof(bUsed));
			if(gMatch[x] == 0)
			{
				if(dfs(x))
				{
					++match;
				}
			}
		}

		cout << match;

		memset(gUsed, 0, sizeof(gUsed));
		memset(bUsed, 0, sizeof(bUsed));

		girlsUnmatch.clear();
		boysMatch.clear();

		for(int x = 1; x <= R; ++x)
		{
			if(gMatch[x] == 0)
			{
				dfs(x);
			}
		}

		for(int x = 1; x <= R; ++x)
		{
			if(!gUsed[x])
			{
				girlsUnmatch.push_back(x);
			}
		}

		for(int y = 1; y <= C; ++y)
		{
			if(bUsed[y])
			{
				boysMatch.push_back(y);
			}
		}

		for(auto item : girlsUnmatch)
		{
			cout << " r" << item;
		}

		for(auto item : boysMatch)
		{
			cout << " c" << item;
		}

		cout << endl;
	}
}