/*
Class: StripePainter
Method: minStrokes
Parameters: string
Returns: int
Method signature: int minStrokes(string stripes)
(be sure your method is public)
*/

#include <climits>
#include <string>
#include <vector>
using namespace std;


class StripePainter
{
public:
	int minStrokes(string stripes)
	{
		int n = stripes.size();

		vector<vector<int> > dp(n, vector<int>(n, INT_MAX));

		for(int i = 0; i < n; ++i)
		{
			dp[i][i] = 1;
		}

		for(int len = 2; len <= n; ++len)
		{
			for(int left = 0; left + len - 1 < n; ++left)
			{
				int right = left + len - 1;

				//the worst case, right could not match to anyone, just need another paint
				dp[left][right] = 1 + dp[left][right - 1];

				for(int match = left; match < right; ++match)
				{
					//use match to pair with right
					if(stripes[match] == stripes[right])
					{
						//if could pair, then match previously could paint to right - 1, but it could cost it nothing to paint to right
						dp[left][right] = min(dp[left][right], (left > match - 1 ? 0 : dp[left][match - 1]) + dp[match][right - 1]);	
					}
				}
			}
		}

		return dp[0][n - 1];
	}
};