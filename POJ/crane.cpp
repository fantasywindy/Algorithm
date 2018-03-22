#include <cstdio>
#include <iostream>
#include <cstring>
#include <iostream>
#include <cmath>
#include <math.h>
#include <iomanip>



#define pi 3.14159265358979323846 

using namespace std;

const int maxn = (1 << 15) - 1;




int n, c;


int len[maxn];
double pre[maxn];

class SegmentTree
{

public:


	double vx[maxn];
	double vy[maxn];
	double angle[maxn];

	SegmentTree()
	{
		memset(vx, 0, sizeof(vx));
		memset(vy, 0, sizeof(vy));
		memset(angle, 0, sizeof(angle));
	}

	void init(int s, int l, int r)
	{
		vx[s] = 0;
		angle[s] = 0;
		if(r - l == 1)
		{
			vy[s] = len[l];
		}
		else
		{
			int chl = s * 2 + 1;
			int chr = s * 2 + 2;
			init(chl, l, (l + r) / 2);
			init(chr, (l + r) / 2, r);
			vy[s] = vy[chl] + vy[chr];
		}
	}


	void change(int s, double a, int v, int l, int r)
	{
		if(s <= l) return;

		if(s < r)
		{
			int chl = 2 * v + 1, chr = 2 * v + 2;
			int m = (l + r) / 2;

			change(s, a, chl, l, m);
			change(s, a, chr, m, r);

			if(s <= m) angle[v] += a;

			double sinval = sin(angle[v]);
            double cosval = cos(angle[v]);
            vx[v] = vx[chl] + (cosval * vx[chr] - sinval * vy[chr]);
            vy[v] = vy[chl] + (sinval * vx[chr] + cosval * vy[chr]);
		}
	}


};




int main()
{
	int kase = 1;
	while(scanf("%d%d", &n, &c) == 2)
	{
		//cout << "here1" << endl;
		memset(len, 0, sizeof(len));
		memset(pre, 0, sizeof(pre));

		for(int i = 0; i < n; ++i)
		{
			scanf("%d", &len[i]);
			pre[i] = pi;
		}

		//cout << "here2" << endl;

		SegmentTree tree;
		tree.init(0, 0, n);

		//cout << "here3" << endl;

		if(kase != 1)
		{
			cout << endl; 
		}

		for(int i = 0; i < c; ++i)
		{
			int s;
			int A;
			scanf("%d%d", &s, &A);
			double a = A / 360.0 * 2 * pi; 
			tree.change(s, a - pre[s], 0, 0, n);
			pre[s] = a;
			cout << std::fixed << setprecision(2) << tree.vx[0] << " " << tree.vy[0] << endl;
		}

		kase++;

		//cout << "here4" << endl;
	}

	return 0;
};