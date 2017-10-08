#include <iostream>
#include <vector>
#include <set>
#include <utility>
#include <climits>
#include <fstream>
#include <algorithm>

using namespace std;


//#define LOCAL_FILE


struct classcomp {
    bool operator() (const pair<int, int> & l, const pair<int, int> & r)
    {
        return l.first > r.first || (l.first == r.first && l.second < r.second);
    };

};



int main()
{
    
#ifdef LOCAL_FILE
    fstream fs("/Users/ice/Desktop/input.txt");
#define input fs
#else
#define input cin
    
#endif
    
    int N;
    int R;
    
    input >> N >> R;
    
    vector<vector<pair<int, int> > > adjs(N + 1);
    
    for(int r = 1; r <= R; ++r)
    {
        int start, end, max_p;
        input >> start >> end >> max_p;
        
        adjs[start].push_back({end, max_p});
        
        adjs[end].push_back({start, max_p});
    }
    
    int src, dest, p;
    
    input >> src >> dest >> p;
    
    vector<int> take_p(N + 1, INT_MIN);
    
    vector<int> parent(N + 1, INT_MAX);
    
    vector<bool> visited(N + 1, false);
    
    take_p[src] = INT_MAX;
    
    parent[src] = 0;
    
    multiset<pair<int, int>, classcomp> Q;
    
    
    Q.insert({INT_MAX, src});
    
    while(Q.empty() == false)
    {
        auto cur = *Q.begin();
        Q.erase(Q.begin());
        
        int curNode = cur.second;
        int curP = cur.first;
        
        if(visited[curNode] == true)
        {
            continue;
        }
        
        visited[curNode] = true;
        
        
        for(auto next : adjs[curNode])
        {
            int nextNode = next.first;
            int nextWeight = next.second;
            
            if(visited[nextNode] == true)
            {
                continue;
            }
            
            if(take_p[nextNode] < min(curP, nextWeight))
            {
                take_p[nextNode] = min(curP, nextWeight);
                parent[nextNode] = curNode;
                Q.insert({take_p[nextNode], nextNode});
            }
            else if(take_p[nextNode] == min(curP, nextWeight) && curNode < parent[nextNode])
            {
                parent[nextNode] = curNode;
                Q.insert({take_p[nextNode], nextNode});
            }
        }
        
        //all the parent and take_p have been calculated, now get the src -> dst one
    }
    
    
    int max_can_p = take_p[dest];
    
    
    //cout << max_can_p << endl;
    
    bool coulddivide = p % (max_can_p - 1) == 0;
    
    int trips = p / (max_can_p - 1);
    
    trips += coulddivide ? 0 : 1;

    vector<int> path;
    
    while(parent[dest] != 0)
    {
        path.push_back(dest);
        dest = parent[dest];
    }
    
    path.push_back(src);
    
    reverse(path.begin(), path.end());
    
    for(auto item : path)
    {
        cout << item << " ";
    }
    cout << endl;
    
    cout << trips << endl;
    
    return 0;
    
}
