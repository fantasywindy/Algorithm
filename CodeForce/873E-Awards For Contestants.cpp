
/*
 
 
 
 */

#include <utility>
#include <vector>
#include <iostream>
#include <algorithm>




#define all(a) (a).begin(), (a).end()
#define sz(a) (int)(a).size()
#define pb push_back

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef double ld;
typedef pair<ll, ll> pll;

const int rmax = 15;
const int nmax = 100500;

#include <fstream>

//#define LOCAL_FILE
#ifdef LOCAL_FILE
fstream fs("/Users/ice/Documents/codeforce/input.txt");
#define input fs
#else
#define input cin

#endif


struct DP{
    int x;
    int y;
    int z;
    
    int i;
    int j;
    int k;
};

bool operator<(const DP & l, const DP & r)
{
    return l.x < r.x || (l.x == r.x && l.y < r.y) || (l.x == r.x && l.y == r.y && l.z < r.z);
}

class SparseTable
{
public:
    SparseTable(vector<pii> & vals)
    {
        N = vals.size();
        sparse.assign(N, vector<pii>(rmax));
        init();
        build(vals);
    }
                      
    void build(vector<pii> & vals)
    {
        for(int i = 0; i < vals.size(); ++i)
        {
            sparse[i][0] = vals[i];
        }
        
        for(int r = 1; r < rmax; ++r)
        {
            for(int i = 0; i < N; ++i)
            {
                int t = min(N - 1, i + (1 << (r - 1)));
                sparse[i][r] = max(sparse[i][r - 1], sparse[t][r - 1]);
            }
        }
    }
    
    pii getMax(int l, int r)
    {
        int len = r - l + 1;
        
        int k = deg[len];
        
        return max(sparse[l][k], sparse[l + len - (1 << k)][k]);
    }
    
    void init()
    {
        deg.assign(nmax, 0);
        
        deg[0] = -1;
        
        for(int i = 1; i < nmax; ++i)
        {
            deg[i] = deg[i-1];
            if(!(i & (i - 1)))
            {
                ++deg[i];
            }
        }
    }
    
private:
    vector<vector<pii> > sparse;
    int N = 0;
    vector<int> deg;
};


int main()
{
    ios_base::sync_with_stdio(false);
    
    int n;
    input >> n;
    
    vector<int> vec(n);
    
    vector<pii> a;
    
    for(int i = 0; i < n; ++i)
    {
        input >> vec[i];
        
        a.pb({vec[i], i});
    }
    
    sort(all(a));
    
    vector<pii> vals;
    
    vals.pb({a[0].first, 0});
    
    for(int i = 1; i < n; ++i)
    {
        vals.pb({a[i].first - a[i-1].first, i});
    }
    
    SparseTable st(vals);
    
    DP ret;
    ret.x = -1;
    ret.y = -1;
    ret.z = -1;
    ret.i = 0;
    ret.j = 0;
    ret.k = 0;
    
    for(int i = n - 1; i >= 0; --i)
    {
        for(int j = i - 1; j >= 0; --j)
        {
            int len_a = n - 1 - i + 1;
            
            int len_b = i - 1 - j + 1;
            
            if(len_a > 2 * len_b || len_b > 2 * len_a)
            {
                continue;
            }
            
            int max_len_c = min({j, 2 * len_a, 2 * len_b});
            
            int min_len_c = max({1, (len_a + 1) / 2, (len_b + 1) / 2});
            
            if(max_len_c < min_len_c)
            {
                continue;
            }
            
            //range d
            
            //cout << "query " << j - max_len_c << " " << j - min_len_c << endl;
            
            
            pii p = st.getMax(j - max_len_c, j - min_len_c);
            
            //cout << "result is" << p.first << endl;

            
            DP temp;
            temp.x = a[i].first - a[i-1].first;
            temp.y = a[j].first - a[j-1].first;
            temp.z = p.first;
            temp.i = i;
            temp.j = j;
            temp.k = p.second;
            
            if(ret < temp)
            {
                ret = temp;
            }
        }
    }
    
    //cout << ret.k << " " << ret.j << " " << ret.i << " " << ret.x << " " << ret.y << " " << ret.z << endl;
    
    vector<int> ans(n);
    
    for(int i = 0; i < ret.k; ++i)
    {
        ans[a[i].second] = -1;
    }
    
    for(int i = ret.k; i < ret.j; ++i)
    {
        ans[a[i].second] = 3;
    }
    
    for(int i = ret.j; i < ret.i; ++i)
    {
        ans[a[i].second] = 2;
    }
    
    for(int i = ret.i; i < n; ++i)
    {
        ans[a[i].second] = 1;
    }
    
    for(int i = 0; i < n; ++i)
    {
        cout << ans[i] << " ";
    }
    
    cout << endl;
    
    return 0;
    
}



