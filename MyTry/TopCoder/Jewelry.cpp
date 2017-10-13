/*
Class: Jewelry
Method: howMany
Parameters: vector <int>
Returns: long long
Method signature: long long howMany(vector <int> values)
(be sure your method is public)
*/
#include <vector>
using namespace std;


class Jewelry
{
public:
	long long howMany(vector <int> values)
	{
		int n = value.size();

		const int max_total_values = 1000 * 30 + 10;
		long long dp[n][n][max_total_values] = {0};

		sort(values.begin(), values.end());

		for(int i = 0; i < n; ++i)
		{
			for(int j = 0; j < i; ++j)
			{
				dp[i][j][0] = 1;
			}
		}


		for(int i = 0; i < n; ++i)
		{
			dp[i][i][values[i]] = 1;
		}

		for(int len = 2; len <= n; ++len)
		{
			for(int left = 0; left + len - 1 < n; ++left)
			{
				int right = left + len - 1;

				for(int val = 1; val <= max_total_values; ++val)
				{
					//not use left
					dp[left][right][val] += dp[left + 1][right][val];

					//use left
					if(val >= values[left])
					{
						dp[left][right][val] += dp[left + 1][right][val - values[left]];
					}
				}
			}
		}




		long long ret = 0;

		if(n >= 1)
		{
			ret = dp[1][n - 1][values[0]];
		}

		for(int bob = 1; bob < n - 1; ++bob)
		{
			for(int bob_val = values[bob]; bob_val <= max_total_values; ++bob_val)
			{
				long long left = dp[0][bob - 1][bob_val - values[bob]];
				long long right = dp[bob + 1][n - 1][bob_val];
				ret += left * right;
			}
		}

		return ret;
	}
};