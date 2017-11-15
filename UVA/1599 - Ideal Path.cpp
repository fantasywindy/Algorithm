#include <vector>
#include <queue>
#include <utility>
#include <iostream>
#include <set>
#include <unordered_map>
#include <algorithm>
#include <queue>
#include <cstring>
#include <climits>
#include <sstream>

using namespace std;

const int maxn = 100000 + 5;
const int INF = 1000000000; // maximal color

struct Edge {
    int u, v, c;
    Edge(int u=0, int v=0, int c=0):u(u),v(v),c(c) {}
};

vector<Edge> edges;
vector<int> G[maxn];

void AddEdge(int u, int v, int c) {
    edges.push_back(Edge(u, v, c));
    int idx = edges.size() - 1;
    G[u].push_back(idx);
}

int n, vis[maxn];
int d[maxn];
// reverse bfs to find out the distance from each node to n-1
void rev_bfs(){
    memset(vis, 0, sizeof(vis));
    
    
    d[n] = 0;
    
    vis[n] = true;
    
    queue<int> q;
    q.push(n);
    
    
    while(!q.empty()){
        int v = q.front(); q.pop();
        
        for(int i = 0; i < G[v].size(); i++){
            int e = G[v][i];
            int u = edges[e].v;
            if(!vis[u]){
                vis[u] = true;
                d[u] = d[v] + 1;
                
                q.push(u);
            }
        }
    }
}

vector<int> ans;


void bfs(){
    memset(vis, 0, sizeof(vis));
    vis[1] = true;
    ans.clear();
    
    
    vector<int> next;
    next.push_back(1);
    
    
    for(int i = 0; i < d[1]; i++){
        int min_color = INF;
        
        for(int j = 0; j < next.size(); j++){
            int u = next[j];
            for(int k = 0; k < G[u].size(); k++){
                int e = G[u][k];
                int v = edges[e].v;
                
                if(d[u] == d[v] + 1)
                    min_color = min(min_color, edges[e].c);
            }
        }
        
        ans.push_back(min_color);
        
        vector<int> next2;
        
        for(int j = 0; j < next.size(); j++){
            int u = next[j];
            
            for(int k = 0; k < G[u].size(); k++){
                int e = G[u][k];
                int v = edges[e].v;
                
                if(d[u] == d[v] + 1 && !vis[v] && edges[e].c == min_color){
                    vis[v] = true;
                    next2.push_back(v);
                    
                }
            }
        }
        
        next = next2;
    }
    
    cout << ans.size() << endl;
    
    cout << ans.front();
    
    for(auto it = ans.begin() + 1; it != ans.end(); ++it)
    {
        cout << " " << *it;
    }
    
    cout << endl;
    
    
}



int main()
{
    ios_base::sync_with_stdio(false);
    
    string line;
    while(getline(cin, line))
    {
        stringstream ss(line);
        int m;
        ss >> n >> m;
        
        for(int i = 1; i < maxn; ++i) G[i].clear();
        
        edges.clear();
        
        for(int i = 0; i < m; ++i)
        {
            getline(cin, line);
            stringstream ss1(line);
            int a, b, c;
            ss1 >> a >> b >> c;
                
            AddEdge(a, b, c);
            AddEdge(b, a, c);
        }
        
        rev_bfs();
        
        bfs();

    }
    
    return 0;
}
