#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>

using namespace std;

typedef long long LL;
LL n;

const int maxn = 20;

LL dp[maxn][10][2];


LL dfs(int pos, bool tight, int pre, vector<int> & digits)
{
	if(pos == -1)
	{
		return 1;
	}

	if(tight == false && dp[pos][pre][tight] != -1)
	{
		return dp[pos][pre][tight];
	}

	int up = tight ? digits[pos] : 9;

	LL ans = 0;

	for(int k = 0; k <= up; ++k)
	{
		if(pre == 4 && k == 9) continue;

		bool newtight = tight && (k == digits[pos]);

		ans += dfs(pos - 1, newtight, k, digits);
	}

	dp[pos][pre][tight] = ans;

	return ans;
}

LL solve()
{
	bool tight = true;
	int pre = 0;

	memset(dp, -1, sizeof(dp));

	vector<int> digits;
	while(n)
	{
		digits.push_back(n % (LL)10);
		n /= (LL)10;
	}

	return dfs(digits.size() - 1, tight, pre, digits);
}


int main()
{
	int T;
	scanf("%d", &T);

	while(T--)
	{
		scanf("%lld", &n);
		cout << n + 1 - solve() << endl;
	}
	return 0;
}