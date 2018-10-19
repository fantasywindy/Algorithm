#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

const int maxn = 100000 + 5;

long long N;

long long a[maxn];

long long c[maxn];

long long d[maxn];

long long x[maxn];

long long y[maxn];


long long lowbit(long long val)
{
	return val & (-val);
}

void update(int i)
{
	long long val = a[i];

	while(val <= maxn - 1)
	{
		x[val] += 1;
		val += lowbit(val);
	}

}

void update1(int i)
{
	long long val = a[i];

	while(val <= maxn - 1)
	{
		y[val] += 1;
		val += lowbit(val);
	}

}

long long getSum(int i)
{
	long long val = a[i];
	long long ans = 0;
	while(val > 0)
	{
		ans += x[val];
		val -= lowbit(val);
	}
	return ans;
}

long long getSum1(int i)
{
	long long val = a[i];
	long long ans = 0;
	while(val > 0)
	{
		ans += y[val];
		val -= lowbit(val);
	}
	return ans;
}

int main()
{
	int T;
	scanf("%d", &T);

	while(T--)
	{
		memset(x, 0, sizeof(x));
		memset(y, 0, sizeof(y));
		memset(c, 0, sizeof(c));
		memset(d, 0, sizeof(d));
		memset(a, 0, sizeof(a));


		scanf("%lld", &N);

		for(int i = 1; i <= N; ++i)
		{
			scanf("%lld", &a[i]);
		}


		for(int i = 1; i <= N; ++i)
		{

			long long lessThan = getSum(i);

			c[i] = lessThan;

			//cout << "less " << a[i] << " is " << c[i] << endl;

			update(i);
		}


		for(int i = N; i >= 1; --i)
		{
			long long greatThan = (N - i) - getSum1(i);

			d[i] = greatThan;

			//cout << "great " << a[i] << " is " << d[i] << endl;

			update1(i);
		}		

		long long ans = 0;

		for(int i = 2; i <= N - 1; ++i)
		{
			ans += c[i] * d[i] + (N - i - d[i]) * (i - 1 - c[i]);
		}

		cout << ans << endl;
	}

	return 0;
}