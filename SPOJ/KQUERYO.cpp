/*
 Input:
 6
 8 9 3 5 1 9
 5
 2 3 5
 3 3 7
 0 0 11
 0 0 2
 3 7 4
 
 Output:
 1
 1
 0
 0
 2
 */

#include <vector>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <fstream>

#define LOCAL_FILE


using namespace std;

class SegmentTree
{
public:
    void init(vector<int> & vec)
    {
        N = vec.size();
        trees.assign(4 * N, vector<int>());
        build(1, 0, N, vec);
    }
    
    int query(int l, int r, int val)
    {
        return count(1, l, r, 0, N, val);
    }
    
private:
    void build(int id, int l, int r, vector<int> & src)
    {
        if(r - l < 2)
        {
            trees[id].push_back(src[l]);
            return;
        }
        
        int mid = l + (r - l) / 2;
        
        build(id * 2, l, mid, src);
        build(id * 2 + 1, mid, r, src);
        
        trees[id].clear();
        
        merge(trees[id * 2].begin(), trees[id * 2].end(), trees[id * 2 + 1].begin(), trees[id * 2 + 1].end(), back_inserter(trees[id]));
    }
    
    int count(int id, int x, int y, int l, int r, int val)
    {
        if(x >= r || y <= l)
        {
            return 0;
        }
        
        if(l >= x && r <= y)
        {
            return trees[id].size() - (distance(trees[id].begin(), upper_bound(trees[id].begin(), trees[id].end(), val)));
        }
        
        int mid = l + (r - l) / 2;
        
        return count(id * 2, x, y, l, mid, val) + count(id * 2 + 1, x, y, mid, r, val);
    }
    
private:
    int N;
    vector<vector<int> > trees;
};

int main()
{
    
#ifdef LOCAL_FILE
    fstream fs("/Users/ice/Desktop/input.txt");
#define input fs
#else
#define input cin
    
#endif

    
    
    ios_base::sync_with_stdio(false);
    
    int n;
    input >> n;
    
    vector<int> vec(n, 0);
    
    for(int i = 0; i < n; ++i)
    {
        input >> vec[i];
    }
    
    SegmentTree T;
    T.init(vec);
    
    int q;
    input >> q;
    
    int lastAns = 0;
    
    for(int i = 0; i < q; ++i)
    {
        int start, end, val;
        input >> start >> end >> val;
        
        start = start ^ lastAns;
        end = end ^ lastAns;
        start = (start < 1 ? 1 : start);
        end = (end > n ? n : end);
        if(start > end)
        {
            lastAns = 0;
            cout << lastAns << '\n';
        }
        else
        {
            lastAns = T.query(start - 1, end, val);
            cout << lastAns << '\n';
        }
    }
    
    return 0;
}
