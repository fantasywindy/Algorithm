#include <vector>
#include <ostringstream>
#include <unordered_set>

using namespace std;

/*
Class: AvoidRoads
Method: numWays
Parameters: int, int, vector <string>
Returns: long long
Method signature: long long numWays(int width, int height, vector <string> bad)
*/

class AvoidRoads
{
public:
	long long numWays(int width, int height, vector <string> bad)
	{
		unordered_set<string> t;

		for(auto b : bad)
		{
			t.insert(b);
		}

		vector<vector<long long> > dp(width + 1, vector<long long>(height + 1, 0));


		for(int i = 0; i <= width; ++i)
		{
			for(int j = 0; j <= height; ++j)
			{
				//if (i - 1, j) has path to (i, j)
				if(i == 0 && j == 0)
				{
					dp[i][j] = 1;
				}
				else
				{
					if(i >= 1)
					{
						ostringstream ss;
						ss << (i - 1) << " " << j << " " << i << " " << j;
						string path1 = ss.str();

						ss.str("");

						ss << i << " " << j << " " << (i - 1) << " " << j;
						string path2 = ss.str();

						if(t.count(path1) == 0 &&  t.count(path2) == 0)
						{
							dp[i][j] += dp[i-1][j];
						}

					}
					
					if(j >= 1)
					{
						ostringstream ss;
						ss << i << " " << (j - 1) << " " << i << " " << j;
						string path1 = ss.str();

						ss.str("");

						ss << i << " " << j << " " << i << " " << (j - 1);
						string path2 = ss.str();

						if(t.count(path1) == 0 && t.count(path2) == 0)
						{
							dp[i][j] += dp[i][j - 1];
						}
					}

				}
			}
		}

		return dp[width][height];
	}
};