#include <vector>
#include <algorithm>
#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>

using namespace std;


const int MAX_C = 1000 + 5;
const int MAX_N = 50 + 5;

vector<int> x_left;
vector<int> x_right;
vector<int> y_left;
vector<int> y_right;
vector<int> z_left;
vector<int> z_right;

vector<int> xs;
vector<int> ys;
vector<int> zs;

int color[MAX_N * 2][MAX_N * 2][MAX_N * 2];

int area, volume;

int dx[] = {1,-1,0,0, 0, 0};
int dy[] = {0,0,1,-1 ,0, 0};
int dz[] = {0,0,0, 0, 1, -1};

struct Cell
{
	Cell(int x, int y, int z):
	x(x), y(y), z(z)
	{

	}

	bool isSolid() const
	{
		return color[x][y][z] == 1;
	}

	bool isValid() const
	{
		return x >= 0 && y >= 0 && z >= 0 && (x <= xs.size() - 2 ) && (y <= ys.size() - 2) && (z <= zs.size() - 2);
	}

	void visit()
	{
		color[x][y][z] = 2;
	}

	bool isVisited() const
	{
		return color[x][y][z] == 2;
	}

	Cell next(int d)
	{
		return Cell(x + dx[d], y + dy[d], z + dz[d]);
	}

	int volume()
	{
		return (xs[x + 1] - xs[x]) * (ys[y + 1] - ys[y]) * (zs[z + 1] - zs[z]);
	}

	int area(int d)
	{
		if(dx[d] != 0)
		{
			return (ys[y + 1] - ys[y]) * (zs[z + 1] - zs[z]);
		}
		else if(dy[d] != 0)
		{
			return (xs[x + 1] - xs[x]) * (zs[z + 1] - zs[z]);
		}
		else
		{
			return (xs[x + 1] - xs[x]) * (ys[y + 1] - ys[y]);
		}
	}

	int x, y, z;

};



void discretize(vector<int> & vec)
{
	sort(vec.begin(), vec.end());

	vec.erase(unique(vec.begin(), vec.end()), vec.end());
}

int getIndex(vector<int> & vec, int val)
{
	return distance(vec.begin(), lower_bound(vec.begin(), vec.end(), val));
}

void floodfill()
{
	queue<Cell> Q;
	Cell startCell(0, 0, 0);
	Q.push(startCell);
	startCell.visit();

	while(Q.empty() == false)
	{
		auto cur = Q.front();
		Q.pop();

		volume += cur.volume();



		//cout << "cur volume" << volume << endl;

		for(int d = 0; d < 6; ++d)
		{
			Cell next = cur.next(d);

			if(next.isValid() == false)
			{
				continue;
			}

			//cout << "next is valid" << endl;

			if(next.isSolid())
			{
				area += cur.area(d);
				//cout << "cur area" << cur.area(d) << endl;
			}
			else
			{
				if(next.isVisited() == false)
				{
					next.visit();
					Q.push(next);
				}
			}
		}
	}

	//cout << "MAXC " << MAX_C * MAX_C * MAX_C << endl;

	volume = MAX_C * MAX_C * MAX_C - volume;
}

void reset()
{
	x_left.clear();
	y_left.clear();
	z_left.clear();

	x_right.clear();
	y_right.clear();
	z_right.clear();

	xs.clear();
	ys.clear();
	zs.clear();

	area = 0;
	volume = 0;

	memset(color, 0, sizeof(color));
}

void test()
{
	int n;
	scanf("%d", &n);

	reset();

	xs.push_back(0);
	ys.push_back(0);
	zs.push_back(0);

	xs.push_back(MAX_C);
	ys.push_back(MAX_C);
	zs.push_back(MAX_C);

	int x0, y0, z0, x1, y1, z1;

	for(int i = 0; i < n; ++i)
	{
		scanf("%d%d%d%d%d%d", &x0, &y0, &z0, &x1, &y1, &z1);

		x1 += x0;
		y1 += y0;
		z1 += z0;

		x_left.push_back(x0);
		x_right.push_back(x1);

		y_left.push_back(y0);
		y_right.push_back(y1);

		z_left.push_back(z0);
		z_right.push_back(z1);

		xs.push_back(x0);
		xs.push_back(x1);

		ys.push_back(y0);
		ys.push_back(y1);

		zs.push_back(z0);
		zs.push_back(z1);
	}

	discretize(xs);
	discretize(ys);
	discretize(zs);


	for(int i = 0; i < n; ++i)
	{
		int xl = getIndex(xs, x_left[i]);
		int xr = getIndex(xs, x_right[i]);

		int yl = getIndex(ys, y_left[i]);
		int yr = getIndex(ys, y_right[i]);

		int zl = getIndex(zs, z_left[i]);
		int zr = getIndex(zs, z_right[i]);

		for(int x = xl; x < xr; ++x)
		{
			for(int y = yl; y < yr; ++y)
			{
				for(int z = zl; z < zr; ++z)
				{
					//solid
					color[x][y][z] = 1;
				}
			}
		}
	}

	floodfill();

	cout << area << " " << volume << endl;
}

int main()
{
	int t;

	scanf("%d", &t);

	for(int t1 = 1; t1 <= t; ++t1)
	{
		test();

	}

	return 0;
}