#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

const int maxn = 30;

const int maxsum = 30 * 9;

typedef long long LL;

LL dp[maxn][maxsum][2];

int digits[maxn];

LL a, b;

LL dfs(int pos, bool tight, LL sum)
{
	if(pos == -1)
	{
		return sum;
	}
	
	if(tight == false && dp[pos][sum][tight] != -1)
	{
		return dp[pos][sum][tight];
	}
	
	int bound = tight ? digits[pos] : 9;
	
	LL ans = 0;
	
	for(int k = 0; k <= bound; ++k)
	{
		bool newtight = tight ? digits[pos] == k : false;
		
		ans += dfs(pos - 1, newtight, sum + k);
	}
	
	dp[pos][sum][tight] = ans;
	
	return ans;
}

LL solve(LL val)
{
	memset(digits, 0, sizeof(digits));
	
	memset(dp, -1, sizeof(dp));
	
	int i = 0;
	
	while(val)
	{
		digits[i++] = val % (LL)10;
		val /= (LL)10;
	}

	// for(int j = 0; j < i; ++j)
	// {
	// 	cout << digits[j] << " ";
	// }

	// cout << endl;
	
	bool tight = true;
	
	LL sum = 0;
	
	int pos = i - 1;
	
	return dfs(pos, tight, sum);
}

int main() {
	
	// your code here
	while(scanf("%lld%lld", &a, &b) == 2 && a != -1 && b != -1)
	{
		LL sum1 = solve(a - 1);
		LL sum2 = solve(b);
		
		cout << sum2 - sum1 << endl;
	}
	return 0;
}