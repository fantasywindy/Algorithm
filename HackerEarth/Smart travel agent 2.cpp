#include <vector>
#include <set>
#include <iostream>
#include <algorithm>
#include <fstream>

using namespace std;

#define LOCAL_FILE
#ifdef LOCAL_FILE
fstream fs("/Users/ice/Documents/codeforce/input.txt");
#define input fs
#else
#define input cin

#endif


const int MAX_N = 100 + 5;

int N;
int R;

int S;
int D;
int T;

vector<pair<int, long long> > G[MAX_N];

//long long dist[MAX_N];

bool visited[MAX_N];

int parent[MAX_N];

struct DIST
{
    DIST()
    {
        val = INT_MIN;
        path.clear();
        id = 0;
    }
    long long val;
    vector<int> path;
    int id;
};

bool operator<(const DIST & l, const DIST & r)
{
    return l.val > r.val || (l.val == r.val && l.path < r.path);
}


DIST dist[MAX_N];

int main()
{
    ios_base::sync_with_stdio(false);
    input >> N >> R;
    
    int c1, c2;
    long long p;
    for(int r = 1; r <= R; ++r)
    {
        input >> c1 >> c2 >> p;
        G[c1].push_back({c2, p});
        G[c2].push_back({c1, p});
    }
    
    input >> S >> D >> T;
    
    //fill(dist, dist + MAX_N, INT_MIN);
    
    for(int i = 1; i <= N; ++i)
    {
        dist[i].id = i;
    }
    
    fill(visited, visited + MAX_N, false);
    
    fill(parent, parent + MAX_N, 0);
    
    multiset<DIST> Q;
    
    dist[S].val = INT_MAX;
    dist[S].path.push_back(S);
    Q.insert(dist[S]);
    
    while(Q.empty() == false)
    {
        auto cur = *(Q.begin());
        Q.erase(Q.begin());
        
        int curNode = cur.id;
        
        if(visited[curNode] == true)
        {
            continue;
        }
        
        if(curNode == D)
        {
            break;
        }
        
        visited[curNode] = true;
        
        for(auto edge : G[curNode])
        {
            int nextNode = edge.first;
            long long edgeVal = edge.second;
            
            if(visited[nextNode] == true)
            {
                continue;
            }
            
            DIST temp = cur;
            temp.id = nextNode;
            temp.val = min(temp.val, edgeVal);
            temp.path.push_back(nextNode);
            
            if(temp < dist[nextNode])
            {
                dist[nextNode] = temp;
                Q.insert(temp);
            }
        }
    }
    
    int max_pass = dist[D].val;
    
    int trips = 0;
    if(T % (max_pass - 1) == 0)
    {
        trips = T / (max_pass - 1);
    }
    else
    {
        trips = T / (max_pass - 1) + 1;
    }
    
    for(auto node : dist[D].path)
    {
        cout << node << " ";
    }
    
    cout << endl;
    
    cout << trips << endl;
    
    return 0;
    
}