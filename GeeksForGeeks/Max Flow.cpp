/*
 Given a graph with N vertices numbered 1 to N and M edges, the task is to find the max flow from vertex 1 to vertex N.
 
 Input:
 The first line of input contains an integer T denoting the no of test cases. Then T test cases follow.
 The first line of each test case contains two space separated integers N and M .
 Then in the next line are M space separated triplets x, y, z denoting an undirected edge from x to y with
 a flow capacity of z.
 
 Output:
 For each test case in a new line print a single integer denoting the maximum flow between 1 to N.
 
 Constraints:
 1<=T<=100
 1<=N,M<=1000
 
 Example:
 Input:
 2
 5 4
 1 2 1 3 2 2 4 2 3 2 5 5
 4 4
 1 2 8 1 3 10 2 4 2 3 4 3
 
 
 Output:
 1
 5
 */
#include <fstream>

#include <queue>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <algorithm>
#include <climits>

using namespace std;


bool bfs(int N, vector<vector<int> > & g, unordered_map<int, int> & parent, int src, int dst)
{
    vector<bool> visited(N + 1, false);
    
    queue<int> Q;
    
    Q.push(src);
    
    visited[src] = true;
    
    bool foundPath = false;
    
    while(Q.empty() == false && foundPath == false)
    {
        auto cur = Q.front();
        Q.pop();
        
        for(int next = 1; next <= N; ++next)
        {
            if(next == cur)
            {
                continue;
            }
            
            if(g[cur][next] != 0 && visited[next] == false)
            {
                parent[next] = cur;
                visited[next] = true;
                Q.push(next);
                
                if(next == dst)
                {
                    foundPath = true;
                    break;
                }
            }
        }
    }
    
    return foundPath;
}

int main()
{
#ifdef LOCAL_FILE
    fstream fs("/Users/ice/Documents/codeforce/input.txt");
#define input fs
#else
#define input cin
    
#endif
    
    
    int t = 0;
    input >> t;
    for(int t1 = 0; t1 < t; ++t1)
    {
        //cout << "test " << t1 << endl;
        int max_flow = 0;
        
        int N;
        int M;
        input >> N >> M;
        
        vector<vector<int> > g(N + 1, vector<int>(N + 1, 0));
        
        
        for(int e = 1; e <= M; ++e)
        {
            int u, v, w;
            
            input >> u >> v >> w;
            g[u][v] += w;
            g[v][u] += w;
        }
        
        unordered_map<int, int> parent;
        
        while(bfs(N, g, parent, 1, N))
        {
            //if we can find the path
            
            int u = N;
            
            vector<int> path;
            int flow = INT_MAX;
            while(u != 0)
            {
                if(parent[u] != 0)
                {
                    flow = min(g[parent[u]][u], flow);
                }
                path.push_back(u);
                u = parent[u];
            }
            
            reverse(path.begin(), path.end());
            
            //            for(auto item : path)
            //            {
            //                cout << item << " ";
            //            }
            //
            //            cout << endl;
            //
            //            cout << "flow is " << flow << endl;
            
            if(path.size() != 1)
            {
                for(int i = 1; i < path.size(); ++i)
                {
                    int p = path[i-1];
                    int c = path[i];
                    
                    //cout << p << " " << c << " - flow " << endl;
                    g[p][c] -= flow;
                    g[c][p] += flow;
                }
            }
            
            max_flow += flow;
            parent.clear();
        }
        
        cout << max_flow << endl;
    }
    
    return 0;
    
}


