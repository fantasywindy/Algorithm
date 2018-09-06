#include <iostream>
#include <cstdio>
#include <cstring>
#include <set>
#include <vector>
using namespace std;

const int maxn = 11;
const int maxw = 11;
const int maxh = 11;

int n, w, h;



int cache[maxn + 1][maxw + 1][maxh + 1];

struct Cell
{
	Cell(int x = 0, int y = 0)
		:x(x), y(y)
	{

	}
	int x;
	int y;

	bool operator < (const Cell& rhs) const {
    	return x < rhs.x || (x == rhs.x && y < rhs.y);
  	}
};


typedef set<Cell> Poly;

set<Poly> ans[maxn + 1];

Poly norm(Poly p)
{
	int minx = 1e9;
	int miny = 1e9;
	for(auto c : p)
	{
		minx = min(minx, c.x);
		miny = min(miny, c.y);
	}

	Poly p1;
	for(auto c : p)
	{
		p1.insert(Cell(c.x - minx, c.y - miny));
	}
	return p1;
}

Poly rotate(Poly p)
{
	Poly p1;
	for(auto c : p)
	{
		p1.insert(Cell(c.y, -c.x));
	}

	return norm(p1);
}

Poly flip(Poly p)
{
	Poly p1;
	for(auto c : p)
	{
		p1.insert(Cell(c.x, -c.y));
	}
	return norm(p1);
}

vector<pair<int, int>> dirs = {
	{0, 1},
	{0, -1},
	{-1, 0},
	{1, 0}
};

void update(Poly p, int curn)
{
	p = norm(p);


	for(int i = 0; i < 4; ++i)
	{
		if(ans[curn + 1].count(p) != 0) return;

		p = rotate(p);
	}

	p = flip(p);

	for(int i = 0; i < 4; ++i)
	{
		if(ans[curn + 1].count(p) != 0) return;

		p = rotate(p);
	}

	//now we consider p is a differnt Poly, add it to ans

	ans[curn + 1].insert(p);
}

void generate()
{
	Cell c(0, 0);
	Poly start;
	start.insert(c);

	ans[1].insert(start);

	for(int n = 2; n < maxn; ++n)
	{
		for(auto p : ans[n - 1])
		{
			for(auto c : p)
			{
				for(auto dir : dirs)
				{
					auto c1 = c;
					c1.x += dir.first;
					c1.y += dir.second;
					if(p.count(c1) != 0)
					{
						continue;
					}
					auto p1 = p;
					p1.insert(c1);
					update(p1, n - 1);
				}
			}
		}
	}
}

void calc()
{
	int cnt = 0;

	for(int i = 1; i <= maxn; ++i)
	{
		for(auto p : ans[i])
		{
			int maxx = 0, maxy = 0;
			for(auto c : p)
			{
				maxx = max(maxx, c.x);
				maxy = max(maxy, c.y);
			}

			for(int x = 0; x < maxw; ++x)
			{
				for(int y = 0; y < maxh; ++y)
				{
					if((maxx < x && maxy < y) || (maxx < y && maxy < x))
					{
						++cache[i][x][y];
					}
				}
			}
			
		}
	}
}

int solve()
{
	return cache[n][w][h];
}


int main()
{
	memset(cache, 0, sizeof(cache));

	generate();

	calc();

	while(scanf("%d%d%d", &n, &w, &h) == 3)
	{
		cout << solve() << endl;
	}

	return 0;
}