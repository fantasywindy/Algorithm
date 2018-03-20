const int maxn = 10 + 5;

#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;


int n;

int arr[maxn];

void reset()
{
	memset(arr, 0, sizeof(arr));
}

void input()
{
	for(int i = 0; i < n; ++i)
	{
		scanf("%d", &arr[i]);
	}
	arr[n] = n + 1;
}

int maxd;

int h()
{
	int ret = 0;
	for(int i = 0; i < n; ++i)
	{
		if(arr[i] + 1 != arr[i+1])
		{
			++ret;
		}
	}
	return ret;
}

bool dfs(int d, int maxd)
{
	int cnt = h();
	if(cnt == 0)
	{
			//cout << "cnt " << " d " <<  d << " maxd " << maxd << endl;

		//cout << "return true" << endl;
		return true;
	}

	if(3 * (maxd - d) < cnt)
	{
		return false;
	}

	int remain[maxn];

	int old_arr[maxn];

	memcpy(old_arr, arr, maxn * sizeof(int));

	for(int i = 0; i < n; ++i)
	{
		for(int j = i; j < n; ++j)
		{
			//i is left, j is right
			int remainCnt = 0;
			for(int k = 0; k < n; ++k)
			{
				if(k < i || k > j)
				{
					remain[remainCnt++] = arr[k];
				}
			}

			for(int slen = 0; slen <= remainCnt; ++slen)
			{
				//copy start part
				memcpy(arr, remain, slen * sizeof(int));

				//copy the middle part
				memcpy(arr + slen, old_arr + i, (j - i + 1) * sizeof(int));

				//copy the right part
				memcpy(arr + slen + (j - i + 1), remain + slen, (n - slen - (j - i + 1)) * sizeof(int));

				if(dfs(d + 1, maxd) == true)
				{
					return true;
				}
				else
				{
					//restore
					memcpy(arr, old_arr, maxn * sizeof(int));
				}
			}
		}

	}

	return false;
}

int solve()
{
	maxd = 8;
	for(int d = 0; d <= maxd; ++d)
	{
		if(dfs(0, d) == true)
		{
			return d;
		}
	}

	return -1;
}

int main()
{
	int kase = 1;
	while(scanf("%d", &n) == 1 && n)
	{
		reset();
		input();
		cout << "Case " << kase++ << ": " << solve() << endl;
	}
}