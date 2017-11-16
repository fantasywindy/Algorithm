#include <cstdio>
#include <vector>
#include <algorithm>
#include <iostream>
#include <cstring>

using namespace std;


struct Block
{
	Block(int x, int y, int z)
		:x(x), y(y), z(z)
	{

	}

	int x, y, z;

	string str()
	{
		return to_string(x) + " " + to_string(y) + " " + to_string(z);
	}
};

const int MAX_N = 30 + 5;

bool canBeContained(Block & l, Block & r)
{
	//cout << "canBeContained " << l.str() << " ***  " << r.str() << endl;
	return l.x < r.x && l.y < r.y;
}

void test(int n, int test_id)
{
	//cout << "test id " << test_id << endl;
		vector<Block> blocks;
		int xi, yi, zi;

		for(int i = 0; i < n; ++i)
		{
			scanf("%d%d%d", &xi, &yi, &zi);
			blocks.push_back(Block(xi, yi, zi));
			blocks.push_back(Block(xi, zi, yi));
			blocks.push_back(Block(yi, zi, xi));
			blocks.push_back(Block(yi, xi, zi));
			blocks.push_back(Block(zi, xi, yi));
			blocks.push_back(Block(zi, yi, xi));
		}
		

		sort(blocks.begin(), blocks.end(), [](const Block & l, const Block & r)
		{
			return l.x < r.x || (l.x == r.x && l.y < r.y);
		});

		// for(auto block : blocks)
		// {
		// 	cout << block.x << " " << block.y << " " << block.z << endl;
		//}

		int dp[MAX_N * 6];

		memset(dp, 0, sizeof(dp));

		dp[0] = 0;

		int max_h = 0;

		for(int i = 1; i <= blocks.size(); ++i)
		{
			dp[i] = blocks[i-1].z;
			for(int j = 1; j < i; ++j)
			{
				if(canBeContained(blocks[j-1], blocks[i-1]))
				{
					dp[i] = max(dp[i], dp[j] + blocks[i-1].z);
				}
			}
			max_h = max(max_h, dp[i]);
		}

		cout << "Case " << test_id << ": maximum height = " << max_h << endl; 
}

int main()
{
	int n;
	int test_id = 1;

	while(scanf("%d", &n) == 1 && n)
	{
		test(n, test_id);
		++test_id;
	}

	return 0;
}