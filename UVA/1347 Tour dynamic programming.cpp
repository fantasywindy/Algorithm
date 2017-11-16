#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iomanip>


using namespace std;


struct Point
{
	Point(double x, double y)
		:x(x), y(y)
	{

	}
	double x, y;
};


const int MAX_N = 1000 + 5;

double dist(vector<Point> & pts, int i, int j)
{
	double dist_square = (pts[i-1].x - pts[j-1].x) * (pts[i-1].x - pts[j-1].x) + (pts[i-1].y - pts[j-1].y) * (pts[i-1].y - pts[j-1].y);
	return sqrt(dist_square);
}



int main()
{
	int n;
	while(scanf("%d", &n) == 1 && n)
	{
		vector<Point> pts;
		double x, y;
		for(int i = 0; i < n; ++i)
		{
			scanf("%lf%lf", &x, &y);
			pts.push_back(Point(x, y));
		}

		double dp[MAX_N][MAX_N];

		for(int i = 0; i < MAX_N; ++i)
		{
			for(int j = 0; j < MAX_N; ++j)
			{
				dp[i][j] = numeric_limits<double>::max();
			}
		}

		for(int j = 1; j <= pts.size(); ++j)
		{
			dp[n-1][j] = dist(pts, n - 1, n) + dist(pts, j, n);
		}


		for(int i = n - 2; i >= 1; --i)
		{
			for(int j = 1; j < i; ++j)
			{
				if(dp[i+1][j] != numeric_limits<double>::max())
				{
					dp[i][j] = min(dp[i][j], dp[i+1][j] + dist(pts, i, i + 1));
				}

				if(dp[i+1][i] != numeric_limits<double>::max())
				{
					dp[i][j] = min(dp[i][j], dp[i+1][i] + dist(pts, j, i + 1));
				}
			}
		}

		cout << std::fixed << std::setprecision(2) << (dp[2][1] + dist(pts, 1, 2)) << endl;
	}

	return 0;
}