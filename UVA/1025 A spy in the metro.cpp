#include <cstdio>
#include <cstring>
#include <climits>
#include <iostream>


using namespace std;


const int MAX_N = 50 + 5;
const int MAX_M1 = 50 + 5;
const int MAX_M2 = 50 + 5;
const int MAX_T = 250 + 5;

int M1_table[MAX_M1];
int M2_table[MAX_M2];
int t_table[MAX_N];

int M1;
int M2;

int N;
int T;

bool hasTrain[MAX_T][MAX_N][2];

int dp[MAX_T][MAX_N];

int main()
{

	int test_id = 1;

	while(scanf("%d", &N) == 1 && N)
	{
		memset(hasTrain, 0, sizeof(hasTrain));
		scanf("%d", &T);

		for(int i = 1; i <= N - 1; ++i)
		{
			scanf("%d", &t_table[i]);
		}

		scanf("%d", &M1);

		for(int m1 = 1; m1 <= M1; ++m1)
		{
			scanf("%d", &M1_table[m1]);
		}

		scanf("%d", &M2);

		for(int m2 = 1; m2 <= M2; ++m2)
		{
			scanf("%d", &M2_table[m2]);
		}


		//left to right
		for(int m1 = 1; m1 <= M1; ++m1)
		{
			int startTime = M1_table[m1];

			hasTrain[startTime][1][0] = true;

			for(int i = 1; i <= N - 1; ++i)
			{
				startTime += t_table[i];
				if(startTime < MAX_T)
				{
					hasTrain[startTime][i + 1][0] = true;
				}
				
			}
		}

		//right to left
		for(int m2 = 1; m2 <= M2; ++m2)
		{
			int startTime = M2_table[m2];
			hasTrain[startTime][N][1] = true;

			for(int i = N; i >= 2; --i)
			{
				startTime += t_table[i - 1];
				if(startTime < MAX_T)
				{
					hasTrain[startTime][i - 1][1] = true;
				}
				
			}
		}


		//end case, when time is T, at station n, how long do we have to wait?

		dp[T][N] = 0;

		for(int i = 1; i <= N - 1; ++i)
		{
			dp[T][i] = INT_MAX;
		}


		for(int t = T - 1; t >= 0; --t)
		{
			for(int s = 1; s <= N; ++s)
			{
				dp[t][s] = INT_MAX;
				//if we just wait
				if(dp[t + 1][s] != INT_MAX)
				{
					dp[t][s] = dp[t + 1][s] + 1;
				}

				//if we take a train from left to right

				if(s < N && hasTrain[t][s][0] && t + t_table[s] <= T)
				{
					dp[t][s] = min(dp[t][s], dp[t + t_table[s]][s + 1]);
				}

				//if we take a train from right to left

				if(s > 1 && hasTrain[t][s][1] && t + t_table[s - 1] <= T)
				{
					dp[t][s] = min(dp[t][s], dp[t + t_table[s - 1]][s - 1]);
				}
				
			}
		}

		//we have to know when time is 0 and we are at station 1, how long do we have to wait?

		if(dp[0][1] == INT_MAX)
		{
			cout << "Case Number " << test_id << ": " << "impossible" << endl;
		}
		else
		{
			cout << "Case Number " << test_id << ": " << dp[0][1] << endl;
		}

		++test_id;
	}

	return 0;
}