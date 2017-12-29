/*
// Sample code to perform I/O:

scanf("%s", name);              // Reading input from STDIN
printf("Hi, %s.\n", name);      // Writing output to STDOUT

// Warning: Printing unwanted or ill-formatted data to output will cause the test cases to fail
*/

// Write your code here
#include <vector>
#include <set>
#include <algorithm>
#include <utility>
#include <iostream>

using namespace std;


const int MAX_N = 10 + 5;
const int MAX_M = 10 + 5;

vector<int> G[MAX_N];

int visited[MAX_N];

int disc[MAX_N];

int low[MAX_N];

int N, M;

int isAP[MAX_N];

set<int> AP;

vector<pair<int, int> > BG;

int t = 0;

void dfs(int u, int p)
{
    visited[u] = 1;

    low[u] = disc[u] = t;

    ++t;

    int child_cnt = 0;

    for(auto v : G[u])
    {
        if(v == p)
        {
            //v is what we come from, just skip
            continue;
        }

        if(visited[v] == 0)
        {
            //we can go
            ++child_cnt;
            dfs(v, u);
            low[u] = min(low[u], low[v]);
            if(p != -1 && disc[u] <= low[v])
            {
                //cout << "dist[ " << u << "] " << disc[u] << " low[ " << v << "] " << low[v] << endl; 
                //cout << "other is in" << endl;
                AP.insert(u);
            }

            if(p == -1 && child_cnt >= 2)
            {
                //cout << "root is in" << endl;
                AP.insert(u);
            }

            if(disc[u] < low[v])
            {

                BG.push_back({u, v});
            }
        }
        else
        {
            low[u] = min(low[u], disc[v]);
        }
    }
}

int main()
{
    scanf("%d%d", &N, &M);
    memset(visited, 0, sizeof(visited));
    memset(disc, 0, sizeof(disc));
    memset(low, 0, sizeof(low));
    
    for(int i = 0; i < M; ++i)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        G[u].push_back(v);
        G[v].push_back(u);
    }
    
    dfs(0, -1);
    cout << AP.size() << endl;
    auto it = AP.begin();
    cout << *it++;
    for(; it != AP.end(); ++it)
    {
        cout << " " << *it;
    }
    cout << endl;
    
    cout << BG.size() << endl;
    for(auto br : BG)
    {
        cout << br.first << " " << br.second << endl;
    }
    return 0;
}/*
// Sample code to perform I/O:

scanf("%s", name);              // Reading input from STDIN
printf("Hi, %s.\n", name);      // Writing output to STDOUT

// Warning: Printing unwanted or ill-formatted data to output will cause the test cases to fail
*/

// Write your code here
#include <vector>
#include <set>
#include <algorithm>
#include <utility>
#include <iostream>

using namespace std;


const int MAX_N = 10 + 5;
const int MAX_M = 10 + 5;

vector<int> G[MAX_N];

int visited[MAX_N];

int disc[MAX_N];

int low[MAX_N];

int N, M;

int isAP[MAX_N];

set<int> AP;

vector<pair<int, int> > BG;

int t = 0;

void dfs(int u, int p)
{
    visited[u] = 1;

    low[u] = disc[u] = t;

    ++t;

    int child_cnt = 0;

    for(auto v : G[u])
    {
        if(v == p)
        {
            //v is what we come from, just skip
            continue;
        }

        if(visited[v] == 0)
        {
            //we can go
            ++child_cnt;
            dfs(v, u);
            low[u] = min(low[u], low[v]);
            if(p != -1 && disc[u] <= low[v])
            {
                //cout << "dist[ " << u << "] " << disc[u] << " low[ " << v << "] " << low[v] << endl; 
                //cout << "other is in" << endl;
                AP.insert(u);
            }

            if(p == -1 && child_cnt >= 2)
            {
                //cout << "root is in" << endl;
                AP.insert(u);
            }

            if(disc[u] < low[v])
            {

                BG.push_back({u, v});
            }
        }
        else
        {
            low[u] = min(low[u], disc[v]);
        }
    }
}

int main()
{
    scanf("%d%d", &N, &M);
    memset(visited, 0, sizeof(visited));
    memset(disc, 0, sizeof(disc));
    memset(low, 0, sizeof(low));
    
    for(int i = 0; i < M; ++i)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        G[u].push_back(v);
        G[v].push_back(u);
    }
    
    dfs(0, -1);
    cout << AP.size() << endl;
    auto it = AP.begin();
    cout << *it++;
    for(; it != AP.end(); ++it)
    {
        cout << " " << *it;
    }
    cout << endl;
    
    cout << BG.size() << endl;
    for(auto br : BG)
    {
        cout << br.first << " " << br.second << endl;
    }
    return 0;
}