#include <utility>
#include <map>
#include <vector>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <climits>



using namespace std;

vector<pair<double, double> > pts;

int N;

map<int, map<int, double> > cache;

double dist(int i, int j)
{
	double xi = pts[i].first;
	double yi = pts[i].second;
	double xj = pts[j].first;
	double yj = pts[j].second;
	double delta_x = xi - xj;
	double delta_y = yi - yj;
	return sqrt(delta_x * delta_x + delta_y * delta_y);
}

double dfs(int i, int j)
{
	//ensure i > j
	if(cache.find(i) != cache.end() && cache[i].find(j) != cache[i].end())
	{
		return cache[i][j];
	}

	double temp = INT_MAX;

	if(i == N - 1)
	{
		temp = dist(N - 1, N) + dist(j, N);
		cache[i][j] = temp;
		return temp;
	}

	temp = min(dfs(i + 1, j) + dist(i, i + 1), dfs(i + 1, i) + dist(j, i + 1));

	cache[i][j] = temp;
	return temp;
}

double solution()
{
	return dfs(2, 1) + dist(2, 1);
}

void reset()
{
	pts.clear();
	cache.clear();

}

int main()
{
	while(scanf("%d", &N) == 1)
	{
		reset();
		double x, y;
		//padding to let index begin at 1
		pts.push_back({0, 0});

		for(int i = 0; i < N; ++i)
		{
			scanf("%lf%lf", &x, &y);
			pts.push_back(make_pair(x, y));
		}
		
		cout << std::fixed << std::setprecision(2) << solution() << endl;
	}

	return 0;
}