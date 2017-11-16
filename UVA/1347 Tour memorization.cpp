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
double cache[MAX_N][MAX_N];

double dist(vector<Point> & pts, int i, int j)
{
	double dist_square = (pts[i-1].x - pts[j-1].x) * (pts[i-1].x - pts[j-1].x) + (pts[i-1].y - pts[j-1].y) * (pts[i-1].y - pts[j-1].y);
	return sqrt(dist_square);
}

double dfs(vector<Point> & pts, int i, int j)
{
	//it is guaranteed that i is greater than j

	if(cache[i][j] > 0)
	{
		return cache[i][j];
	}

	int n = pts.size();

	if(i == pts.size() - 1)
	{
		double ret = dist(pts, n - 1, n) + dist(pts, j, n);
		cache[i][j] = ret;
		return ret;
	}

	double case1 = dfs(pts, i + 1, j) + dist(pts, i, i + 1);
	double case2 = dfs(pts, i + 1, i) + dist(pts, j, i + 1);

	double ret = min(case1, case2);

	cache[i][j] = ret;

	return ret;
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

		for(int i = 0; i < MAX_N; ++i)
		{
			for(int j = 0; j < MAX_N; ++j)
			{
				cache[i][j] = -1.0;
			}
		}

		double ret = dfs(pts, 2, 1) + dist(pts, 1, 2);

		cout << std::fixed << std::setprecision(2) << ret << endl;
	}

	return 0;
}