#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>
using namespace std;

const int maxm = 3000 + 5;

int n, m;

// dp[i][j] is we need at least how many matched to get a i digits value which has modular j against m

// max digits is 50

const int maxd = 100 + 2;

int dp[maxd][maxm];

int cnt[10] = {6, 2, 5, 5, 4, 5, 6, 3, 7, 6};

int mod[maxd];

void pre_calc()
{
	mod[1] = 1;
	for(int i = 2; i < maxd; ++i)
	{
		mod[i] = (mod[i-1] * 10) % m;
	}
}


vector<int> solve()
{
	vector<int> ans;

	for(int i = 1; i < maxd; ++i)
	{
		for(int j = 0; j < maxm; ++j)
		{
			dp[i][j] = 1e9;
		}
	}

	

	for(int i = 0; i < 9; ++i)
	{
		if(dp[1][i % m] > cnt[i])
		{
			dp[1][i % m] = cnt[i];
		}
	}

	//cout << dp[3][88] << endl;


	for(int i = 2; i < maxd; ++i)
	{
		for(int j = 0; j < maxm; ++j)
		{
			for(int k = 0; k <= 9; ++k)
			{
				// use digit k for ith
				int x = (mod[i] * (k % m)) % m;

				int j1 = (j - x + m) % m;

				if(dp[i-1][j1] != 1e9)
				{
					if(dp[i][j] > (cnt[k] + dp[i-1][j1]))
					{
						dp[i][j] = cnt[k] + dp[i-1][j1];
					}
				}
			}
		}
	}

	int i = n;

	while(i > 0 && dp[i][0] > n)
	{
		--i;
	}


	if(i == 0)
	{
		return ans;
	}
	else
	{
		// dp[i][0] < n

		int j = 0;
		int matches = n;

		while(i > 1)
		{
			for(int k = 9; k >= 0; --k)
			{
				int x = (mod[i] * (k % m)) % m;

				int j1 = (j - x + m) % m;

				if(dp[i - 1][j1] <= (matches - cnt[k]))
				{
					matches -= cnt[k];

					j = j1;

					ans.push_back(k);

					break;
				}
			}

			--i;
		}

		for(int k = 9; k >= 0; --k)
		{
			if(k % m == j)
			{
				ans.push_back(k);
				break;
			}
		}
	}

	return ans;	
}

void trim(vector<int> & vec)
{
	while(vec.size() > 1 && vec.front() == 0)
	{
		vec.erase(vec.begin());
	}
}

int main()
{
	int kase = 1;

	while(scanf("%d", &n) == 1)
	{
		if(n == 0)
		{
			break;
		}
		scanf("%d", &m);
		if(kase != 1)
		{
			cout << endl;	
		}
		pre_calc();

		cout << "Case " << kase++ << ": ";

		auto ans = solve();

		if(ans.size() == 0)
		{
			cout << -1;
			continue;
		}
		trim(ans);

		for(auto item : ans)
		{
			cout << item;
		}
	}
	return 0;
}