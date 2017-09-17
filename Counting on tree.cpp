#include <iostream>
#include <vector>
#include <fstream>


using namespace std;

#define LOCAL_FILE

int f[50000 + 100][100 + 10] = {0};
int g[50000 + 100][100 + 10] = {0};
int weight[50000 + 100] = {0};
vector<vector<int> > adj;
int n;
int k;

const long long MOD = 1e9 + 7;
const long long MOD2 = static_cast<long long>(MOD) * MOD;



void dfs(int u, int p)
{
    long long dp[100 + 10] = {0};
    long long dp_buffer[100 + 10] = {0};
    long long dp1[100 + 10] = {0};
    
    dp[weight[u]] = 1;
    
    for(auto c : adj[u])
    {
        if(c == p)
        {
            continue;
        }
        
        dfs(c, u);
        
        for(int j = 0; j <= k; ++j)
        {
            dp_buffer[j] = 0;
        }
        
        for(int j = 0; j <= k; ++j)
        {
            long long temp = 0;
            temp = dp[j];
            // dp_buffer[j] = dp[j];
            for(int l = 0; l <= j; ++l)
            {
                temp += dp[l] * 1ll * f[c][j-l];
                while(temp >= MOD2)
                {
                    temp -= MOD2;
                }
                //dp_buffer[j] = dp_buffer[j] + dp[l] * f[c][j - l];
            }
            dp_buffer[j] = temp % MOD;
        }
        
        for(int j = 0; j <= k; ++j)
        {
            if(c == p)
            {
                continue;
            }
            dp1[j] = (dp1[j] + g[c][j]) % MOD;
            dp1[j] = (dp1[j] + f[c][j]) % MOD;
        }
        
        for(int j = 0; j <= k; ++j)
        {
            dp[j] = dp_buffer[j];
        }
    }
    
    for(int j = 0; j <= k; ++j)
    {
        f[u][j] = dp[j];
        g[u][j] = dp1[j];
    }
}


int main()
{
    /*
     3
     3 1
     1 0 1
     1 2
     1 3
     5 2
     0 1 0 1 1
     1 2
     1 3
     1 4
     2 5
     3 0
     1 1 0
     1 2
     2 3
     */
    
    
    
#ifdef LOCAL_FILE
    fstream fs("/Users/ice/Desktop/input.txt");
#define input fs
#else
#define input cin
    
#endif
    
    int tests = 0;
    input >> tests;
    for(int t = 0; t < tests; ++t)
    {
        
        for(int i = 0; i <= 50000; ++i)
        {
            for(int j = 0; j <= 100; ++j)
            {
                f[i][j] = 0;
                g[i][j] = 0;
            }
            weight[i]= 0;
        }
        
        input >> n >> k;
        for(int i = 1; i <= n; ++i)
        {
            input >> weight[i];
        }
        adj.assign(n + 1, vector<int>());
        int start;
        int end;
        for(int i = 1; i <= n - 1; ++i)
        {
            input >> start >> end;
            adj[start].push_back(end);
            adj[end].push_back(start);
        }
        
        dfs(1, 0);
        
        cout << (f[1][k] + g[1][k]) % MOD << endl;
        
    }
    return 0;
}

