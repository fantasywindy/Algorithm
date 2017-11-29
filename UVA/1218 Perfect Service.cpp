#include <vector>
#include <iostream>
#include <cstring>
#include <numeric>
#include <algorithm>


using namespace std;


const int MAX_N = 10000 + 5;

const int INF = 1000000000;

int dp[MAX_N][3];

vector<int> dfs_order;

int N;

vector<int> G[MAX_N];

int pn[MAX_N];

void dfs_util(int u, int p)
{
    dfs_order.push_back(u);
    for(auto v : G[u])
    {
        if(v == p)
        {
            continue;
        }

        pn[v] = u;

        dfs_util(v, u);
    }
}

void dfs()
{    
    dfs_util(1, 0);
}


void reset()
{
    for(auto & vec : G)
    {
        vec.clear();
    }

    memset(pn, 0, sizeof(pn));

    dfs_order.clear();

    memset(dp, 0, sizeof(dp));
}

void calc()
{
    for(int i = dfs_order.size() - 1; i >= 0; --i)
    {
        int u = dfs_order[i];

        dp[u][0] = 1;
        dp[u][1] = 0;

        for(auto v : G[u])
        {
            if(v == pn[u])
            {
                continue;
            }

            dp[u][0] += min(dp[v][0], dp[v][1]);
            dp[u][1] += dp[v][2];
            if(dp[u][0] > INF)
            {
                dp[u][0] = INF;
            }
            if(dp[u][1] > INF)
            {
                dp[u][1] = INF;
            }
        }

        dp[u][2] = INF;
        for(auto v : G[u])
        {
            if(v == pn[u])
            {
                continue;
            }

            dp[u][2] = min(dp[u][2], dp[u][1] + dp[v][0] - dp[v][2]);
        } 
    }

    int src = dfs_order[0];

    cout << min(dp[src][0], dp[src][2]) << endl;
}

int main()
{
    // if (!freopen("/Users/ice/Desktop/input.txt", "r", stdin)) {
    //     perror("freopen");
    //     return -1;
    // }
    
    while(scanf("%d", &N) == 1 && N)
    {
        reset();
        int u, v;
        for(int k = 0; k < N - 1; ++k)
        {
            scanf("%d%d", &u, &v);
            G[u].push_back(v);
            G[v].push_back(u);
        }
        
        dfs();
        
        calc();
        
        int t = 0;
        scanf("%d", &t);
        
        if(t == 0)
        {
            continue;
        }
        else if(t == -1)
        {
            break;
        }
    }
    
    return 0;
    
    
    
}
