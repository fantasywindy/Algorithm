#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;


const int MAX_N = 100000 + 5;

int N, T;

vector<int> sub[MAX_N];

void reset()
{
	for(int i = 0; i < MAX_N; ++i)
	{
		sub[i].clear();
	}
}

int dp(int i)
{

	if(sub[i].size() == 0)
	{
		//if no sub, file directly
		return 1;
	}

	vector<int> subDP;

	for(auto e : sub[i])
	{
		subDP.push_back(dp(e));
	}

	sort(subDP.begin(), subDP.end());

	int c = (sub[i].size() * T - 1) / 100 + 1;

	int t = 0;
	for(int k = 0; k < c; ++k)
	{
		t += subDP[k];
	}	
	return t;
}

int solution()
{
	return dp(0);
}

//dp(i) means how much worker needed to make i make petition




int main()
{
	while(scanf("%d%d", &N, &T) == 2)
	{
		if(N == 0 && T == 0)
		{
			break;
		}

		reset();

		int boss;
		for(int i = 1; i <= N; ++i)
		{
			scanf("%d", &boss);
			sub[boss].push_back(i);
		}

		cout << solution() << endl;
	}

	return 0;
}