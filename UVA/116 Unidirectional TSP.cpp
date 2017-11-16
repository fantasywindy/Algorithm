#include <vector>
#include <algorithm>
#include <iostream>
#include <climits>
#include <cstdio>
#include <cstring>


using namespace std;


const int MAX_R = 10 + 5;
const int MAX_C = 100 + 5;


int matrix[MAX_R][MAX_C];

struct DP
{
	DP()
	{
		w = INT_MAX;
	}
	int w;
	vector<int> path;
};

bool operator<(const DP & l, const DP & r)
{
	return l.w < r.w || (l.w == r.w && l.path < r.path);
}

int main()
{
	int rows, cols;

	while(scanf("%d%d", &rows, &cols) == 2 && rows && cols)
	{
		memset(matrix, 0, sizeof(matrix));

		for(int r = 0; r < rows; ++r)
		{
			for(int c = 0; c < cols; ++c)
			{
				scanf("%d", &matrix[r][c]);
			}
		}

		DP dp[MAX_R];

		for(int r = 0; r < rows; ++r)
		{
			dp[r].w = matrix[r][0];
			dp[r].path.push_back(r + 1);
		}

		for(int curCol = 1; curCol < cols; ++curCol)
		{
			DP dp1[MAX_R];

			for(int r = 0; r < rows; ++r)
			{
				vector<int> preRow = {-1, 0, 1};

				for(auto pre : preRow)
				{
					int pre_r = (r - pre) % rows;
					if(pre_r < 0)
					{
						pre_r += rows;
					}

					DP temp = dp[pre_r];
					temp.w += matrix[r][curCol];
					temp.path.push_back(r + 1);

					if(temp < dp1[r])
					{
						dp1[r] = temp;
					}
				}
			}

			copy(dp1, dp1 + MAX_R, dp);
		}

		DP min_dp;

		for(int r = 0; r < rows; ++r)
		{
			min_dp = min(min_dp, dp[r]);
		}

		cout << min_dp.path.front();
		for(int i = 1; i < min_dp.path.size(); ++i)
		{
			cout << " " << min_dp.path[i];
		}

		cout << endl;

		cout << min_dp.w << endl;
	}

	return 0;
}