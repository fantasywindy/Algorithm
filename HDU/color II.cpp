#include <cstring>
#include <iostream>
#include <cstdio>
#include <string>
#include <algorithm>

using namespace std;

const long long MOD = (1ll<<32); 


const int MAX_N = 18 + 2;

int max_state = 0;

char G[MAX_N][MAX_N];

int n;

char str[MAX_N];

int hasConnected[1 << MAX_N];


const int INF = 1000000000;


int dp[1 << MAX_N];


int main()
{
	int t;
	scanf("%d", &t);

	while(t--)
	{
		memset(str, 0, sizeof(str));
		memset(G, 0, sizeof(G));
		memset(hasConnected, 0, sizeof(hasConnected));
		
		scanf("%d", &n);

		max_state = (1 << n);

		for(int i = 0; i < n; ++i)
		{
			scanf("%s", G[i]);

			for(int j = 0; j < n; ++j)
			{
				G[i][j] -= '0';
			}
		}

		for(int state = 0; state < max_state; ++state)
		{
			for(int i = 0; i < n && !hasConnected[state]; ++i)
			{
				if( (state & (1 << i)) == 0 )
				{
					continue;
				}

				for(int j = i + 1; j < n; ++j)
				{
					if( (state & (1 << j)) == 0 )
					{
						continue;
					}

					if(G[i][j] == 1)
					{
						hasConnected[state] = 1;
						break;
					}
				}
			}

		}


		int max_state = 1 << n;

		for(int i = 0; i < max_state; ++i)
		{
			dp[i] = INF;
		}

		dp[0] = 0;

		

		for(int state = 1; state < max_state; ++state)
		{
			for(int sub = state; sub; sub = (sub - 1) & state)
			{
		
				if(hasConnected[sub] == 1)
				{
					continue;
				}

				int temp = dp[state ^ sub];

				if(temp == INF)
				{
					continue;
				}

				if(temp + 1 < dp[state])
				{
					dp[state] = temp + 1;
				}
			}
		}

		long long ans=1;  
	    long long res=0;  
	    for(int i=1;i<(1<<n);i++){  
	        ans*=233;  
	        ans%=MOD;  
	        res+=ans*dp[i];  
	        res%=MOD;  
	    }  
	    printf("%lld\n",res);
	}

	return 0;
}