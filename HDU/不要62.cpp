#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

int n, m;

const int maxn = 8;

typedef long long LL;

LL dp[20][20][2];


LL dfs(int pos, int pre, bool tight, vector<int> & digits, string str)
{
	//cout << "pos " << pos << " pre " << pre << " str " << str << endl;
	if(pos == -1)
	{
		//cout << preval << endl;
		//cout << str << endl;

		return 1;
	}

	if(tight == false && dp[pos][pre][tight] != -1)
	{
		return dp[pos][pre][tight];
	}


	LL ans = 0;

	int up = tight ? digits[pos] : 9; 

	for(int k = 0; k <= up; ++k)
	{
		if(pre == 6 && k == 2)
		{
			continue;
		}

		if(k == 4) continue;

		bool newtight = tight && (digits[pos] == k);

		ans += dfs(pos - 1, k, newtight, digits, str + string(1, k + '0'));
	}

	dp[pos][pre][tight] = ans;

	return ans;
}


LL solve(int val)
{
	// 3 6 2

	// => 2 6 3


	vector<int> digits;
	while(val)
	{
		digits.push_back(val % 10);
		val /= 10;
	}

	int pos = digits.size() - 1;

	memset(dp, -1, sizeof(dp));

	return dfs(pos, 0, true, digits, "");
}



int main()
{
	while(scanf("%d%d", &n, &m) == 2 && n && m)
	{
		//cout << "solve 1 " << endl;
		LL ans1 = solve(n - 1);
		//cout << "solve 2 " << endl; 
		LL ans2 = solve(m);

		cout << ans2 - ans1 << endl;
	}
	return 0;
}