#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

const int MAX_N = 50 + 5;

const int MAX_T = 250 + 5;

const int MAX_M1 = 50 + 5;

const int MAX_M2 = 50 + 5;


int N, T;

int tm[MAX_N];

int M1, M2;

int d[MAX_M1];

int e[MAX_M2];

int dp[MAX_N][MAX_T];

const int INF = 1000000;

int hasTrain[MAX_N][MAX_T][2];

void reset()
{
	memset(tm, 0, sizeof(tm));
	memset(d, 0, sizeof(d));
	memset(e, 0, sizeof(e));
	memset(dp, 0, sizeof(dp));
	memset(hasTrain, 0, sizeof(hasTrain));
}

void calcHasTrain()
{
	//left to right
	for(int m1 = 1; m1 <= M1; ++m1)
	{
		int curT = d[m1];

		hasTrain[1][curT][0] = 1;
		for(int i = 2; i <= N; ++i)
		{
			curT = curT + tm[i-1];
			if(curT < MAX_T)
			{
				hasTrain[i][curT][0] = 1;
			}
		}
	}

	//right to left
	for(int m2 = 1; m2 <= M2; ++m2)
	{
		
		int curT = e[m2];
		hasTrain[N][curT][1] = 1;
		for(int i = N - 1; i >= 1; --i)
		{
			curT = curT + tm[i];
			if(curT < MAX_T)
			{
				hasTrain[i][curT][1] = 1;
			}
			
		}
	}
}

void initialization()
{
	for(int s = 1; s <= N - 1; ++s)
	{
		dp[s][T] = INF;
	}

	dp[N][T] = 0;
}

int solution()
{
	calcHasTrain();

	//initialization
	initialization();


	for(int t = T - 1; t >= 0; --t)
	{
		for(int s = 1; s <= N; ++s)
		{
			dp[s][t] = INF;
			//if wait on the station
			if(dp[s][t+1] != INF)
			{
				dp[s][t] = min(dp[s][t+1] + 1, dp[s][t]);
			}
			

			//if not wait
			//1. catch the train goes from left to right
			if(s < N && t + tm[s] <= T && hasTrain[s][t][0] == 1)
			{
				dp[s][t] = min(dp[s+1][t + tm[s]], dp[s][t]);
			}
			

			//2. catch the train goes from right to left
			if(s > 1 && t + tm[s - 1] <= T && hasTrain[s][t][1] == 1)
			{
				dp[s][t] = min(dp[s-1][t + tm[s - 1]], dp[s][t]);
			}
			
		}
	}

	return dp[1][0];
}


int main()
{
	int TestNumber = 1;
	while(scanf("%d", &N) == 1 && N)
	{
		reset();

		scanf("%d", &T);

		for(int i = 1; i <= N - 1; ++i)
		{
			scanf("%d", &tm[i]);
		}

		scanf("%d", &M1);

		for(int m1 = 1; m1 <= M1; ++m1)
		{
			scanf("%d", &d[m1]);
		}

		scanf("%d", &M2);
		for(int m2 = 1; m2 <= M2; ++m2)
		{
			scanf("%d", &e[m2]);
		}

		int ret = solution();
		if(ret != INF)
		{
			cout << "Case Number " << TestNumber++ << ": " << ret << endl;
		}
		else
		{
			cout << "Case Number " << TestNumber++ << ": " << "impossible" << endl;
		}
	}

	return 0;
	
}



