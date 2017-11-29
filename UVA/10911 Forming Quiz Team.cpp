#include <cmath>
#include <cstring>
#include <cstdio>
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <iomanip>




using namespace std;

const int MAX_N = 8 + 1;

int N ;

double x[MAX_N * 2];

double y[MAX_N * 2];

const int MAX_C = 20 + 2;
char name[MAX_C];

const int INF = 1000000000;

double dp[2 * MAX_N][(1 << (2 * MAX_N))];

double dist(int i, int j)
{
	double xi = x[i];
	double xj = x[j];
	double yi = y[i];
	double yj = y[j];

	double temp = (xi - xj) * (xi - xj) + (yi - yj) * (yi - yj);

	return sqrt(temp);
}

void reset()
{
	memset(dp, 0, sizeof(dp));
	memset(name, 0, sizeof(name));
	memset(x, 0, sizeof(x));
	memset(y, 0, sizeof(y));

}

string valToBits(int val)
{
	vector<int> bits;

	while(val != 0)
	{
		bits.push_back(val % 2);
		val /= 2;
	}

	reverse(bits.begin(), bits.end());

	string ret = "";
	for(auto i : bits)
	{
		ret.push_back(i + '0');
	}
	return ret;
}

int main()
{
	int case_id = 1;
	while(scanf("%d", &N) == 1 && N)
	{
		reset();
		for(int i = 0; i < 2 * N; ++i)
		{
			scanf("%s", name);
			scanf("%lf%lf", &x[i], &y[i]);
		}

		int n = 2 * N;

		for(int S = 0; S < (1 << n); ++S)
		{
			dp[0][S] = 0;
		}

		for(int i = 1; i < n; ++i)
		{
			dp[i][0] = 0;
			for(int S = 1; S < (1 << n); ++S)
			{
				dp[i][S] = INF;

				if((S & (1 << i)))
				{
					for(int j = i - 1; j >= 0; --j)
					{
						if((S & (1 << j)) != 0)
						{
							
							dp[i][S] = min(dp[i][S], dist(i, j) + dp[i-1][S ^ (1 << i) ^ (1 << j)]);

						}
						
					}
				}
				else
				{
					dp[i][S] = dp[i-1][S];
				}

				
			}
		}

		cout << "Case " << case_id++ << ": " << std::fixed << setprecision(2) << dp[n-1][(1 << n) - 1] << endl;
	}

	return 0;
}