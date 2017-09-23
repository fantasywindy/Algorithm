#include <iostream>
#include <vector>
#include <fstream>


using namespace std;

//#define LOCAL_FILE





#include <iostream>
#include <vector>
using namespace std;



const long long MAX_N = 100 + 5;
const long long MAX_Q = 100 + 5;
int f[MAX_N][MAX_Q] = {0};

int N;
int Q;


int weights[MAX_N][MAX_N] = {0};

vector<vector<int> > adjs;


void dfs(int u, int p)
{
    for(auto v : adjs[u])
    {
        if(v == p)
        {
            continue;
        }
        
        dfs(v, u);
    }
    
    int dp[MAX_Q] = {0};
    
    int dp_buffer[MAX_Q] = {0};
    
    
    dp[0] = 0;
    
    
    for(auto v : adjs[u])
    {
        if(v == p)
        {
            continue;
        }
        
        for(int i = 0; i <= Q; ++i)
        {
            dp_buffer[i] = 0;
        }
        
        for(int i = 0; i <= Q; ++i)
        {
            dp_buffer[i] = dp[i];
            
            for(int j = 1; j <= i; ++j)
            {
                dp_buffer[i] = max(dp_buffer[i], dp[i - j] + weights[u][v] + f[v][j - 1]);
            }
        }
        
        for(int i = 0; i <= Q; ++i)
        {
            dp[i] = dp_buffer[i];
        }
    }
    
    for(int i = 0; i <= Q; ++i)
    {
        f[u][i] = dp[i];
    }
}

int main()
{
#ifdef LOCAL_FILE
    fstream fs("/Users/ice/Desktop/input.txt");
#define input fs
#else
#define input cin
    
#endif
    
    
    ios_base::sync_with_stdio(false);
    
    input >> N >> Q;
    
    adjs.assign(N + 1, vector<int>());
    int start, end, w;
    
    for(int i = 1; i <= N - 1; ++i)
    {
        input >> start >> end >> w;
        adjs[start].push_back(end);
        adjs[end].push_back(start);
        weights[start][end] = w;
        weights[end][start] = w;
    }
    
    dfs(1, 0);
    
    cout << f[1][Q] << endl;
    
    return 0;
    
}
