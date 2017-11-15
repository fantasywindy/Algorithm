#include <iostream>
#include <vector>
#include <cstdio>
#include <cstring>
#include <climits>

using namespace std;

#define REP(i, n) for(int i = 0; i < (n); ++i)


const int MAX_N = 30 + 5;

struct Block
{
	Block(int x, int y, int z, int id)
		:x(x), y(y), z(z), id(id)
	{

	}

	int x, y, z, id;

	//0 is x
	//1 is y
	//2 is z
};

bool canContain(Block & A, int da, Block & B, int db)
{
	int a1;
	int a2;

	int b1;
	int b2;

	if(da == 0)
	{
		a1 = A.y;
		a2 = A.z;
	}
	else if(da == 1)
	{
		a1 = A.x;
		a2 = A.z;
	}
	else
	{
		a1 = A.x;
		a2 = A.y;
	}

	if(db == 0)
	{
		b1 = B.y;
		b2 = B.z;
	}
	else if(db == 1)
	{
		b1 = B.x;
		b2 = B.z;
	}
	else
	{
		b1 = B.x;
		b2 = B.y;
	}

	return (a1 > b1 && a2 > b2) || (a1 > b2 && a2 > b1);
}

int getHeight(Block & A, int d)
{
	if(d == 0)
	{
		return A.x;
	}
	else if(d == 1)
	{
		return A.y;
	}
	else
	{
		return A.z;
	}
}

int cache[MAX_N][3];

int dp(vector<Block> & blocks, int i, int d)
{
	if(cache[i][d] != 0)
	{
		return cache[i][d];
	}

	int ans = 0;

	REP(j, blocks.size())
	{
		REP(k, 3)
		{
			if(canContain(blocks[i], d, blocks[j], k))
			{
				ans = max(ans, dp(blocks, j, k));
			}
		}
	}

	ans += getHeight(blocks[i], d);

	cache[i][d] = ans;

	return ans;
}


int solution(vector<Block> & blocks)
{
	int n = blocks.size();

	int max_len = 0;

	memset(cache, 0, sizeof(cache));

	REP(i, n)
	{
		REP(j, 3)
		{
			max_len = max(max_len, dp(blocks, i, j));
		}
	}

	return max_len;
}


int main()
{
	int n;
	int test_id = 1;
	while(scanf("%d", &n) == 1 && n)
	{
		int xi, yi, zi;

		vector<Block> blocks;

		for(int i = 1; i <= n; ++i)
		{
			scanf("%d%d%d", &xi, &yi, &zi);
			blocks.push_back(Block(xi, yi, zi, i));
		}


		cout << "Case " << test_id++ << ": maximum height = " << solution(blocks) << endl;
	}

	return 0;
}