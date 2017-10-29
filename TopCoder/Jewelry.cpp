/*
Class: Jewelry
Method: howMany
Parameters: vector <int>
Returns: long long
Method signature: long long howMany(vector <int> values)
(be sure your method is public)

- values will contain between 2 and 30 elements inclusive.
- Each element of values will be between 1 and 1000 inclusive.

*/

#include <vector>
#include <numeric>
#include <algorithm>
using namespace std;


const int MAX_N = 30 + 5;

const int MAX_V = 1000 * 30 + 5;

long long f[MAX_N][MAX_V];

long long b[MAX_N][MAX_V];

long long cnk[MAX_N][MAX_N];

void comb(int n)
{
    for(int i = 0; i <= n; ++i)
    {
        cnk[0][i] = 0;
    }

    cnk[0][0] = 1;

    for(int i = 1; i <= n; ++i)
    {
        cnk[i][0] = 1;

        for(int j = 1; j <= i; ++j)
        {
            cnk[i][j] = cnk[i-1][j] + cnk[i-1][j-1];
        }
    }
}

void calc(vector<int> & nums, long long dp[MAX_N][MAX_V])
{
    int n = nums.size();
    int sum = accumulate(nums.begin(), nums.end(), 0);

    for(int v = 0; v <= sum; ++v)
    {
        dp[0][v] = 0;
    }

    dp[0][0] = 1;

    for(int i = 1; i <= n; ++i)
    {
        for(int v = 0; v <= sum; ++v)
        {
            dp[i][v] = dp[i-1][v];

            if(v >= nums[i-1])
            {
                dp[i][v] += dp[i-1][v - nums[i-1]];
            }
        }
    }
}

class Jewelry
{
public:
    long long howMany(vector <int> values)
    {
        int n = values.size();

        if(n == 0)
        {
            return 0;
        }

        comb(n);

        sort(values.begin(), values.end());

        calc(values, f);

        reverse(values.begin(), values.end());

        calc(values, b);

        reverse(values.begin(), values.end());

        int sum = accumulate(values.begin(), values.end(), 0);

        long long ret = 0;

        for(int i = 0; i < n; )
        {
            int j = i;

            while(j < n && values[j] == values[i])
            {
                ++j;
            }

            int max_cnt = j - i;

            //at least choose 1
            for(int v = values[i]; v <= sum; ++v)
            {
                int cnt = 1;
                while(v >= cnt * values[i] && cnt <= max_cnt)
                {
                    ret += f[i][v - cnt * values[i]] * cnk[max_cnt][cnt] * b[n - i - cnt][v];
                    ++cnt;
                }
            }

            i = j;
        }

        return ret;
    }
};