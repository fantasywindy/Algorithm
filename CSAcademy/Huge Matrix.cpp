#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

const int MAX_N = 100005;
const int MAX_M = 100005;
const int MAX_K = 15;


vector<int> add[MAX_M];
vector<int> del[MAX_M];

int N, M;

int diffCnt = 1;

int maxDiffCnt = 1;

int freq[MAX_K];

void incr(int val, int delta)
{
    //only effect 0 and val frequency
    int oldCnt = !!freq[0] + !!freq[val];
    
    freq[0] -= delta;
    
    freq[val] += delta;
    
    int newCnt = !!freq[0] + !!freq[val];
    
    diffCnt += (newCnt - oldCnt);
}

int main()
{
    ios_base::sync_with_stdio(false);
    
    cin >> N >> M;
    
    for(int i = 0; i < N; ++i)
    {
        int st;
        int fn;
        int val;
        cin >> st >> fn >> val;
        
        add[st].push_back(val);
        del[fn].push_back(val);
    }
    
    memset(freq, 0, sizeof(freq));
    
    freq[0] = N;
    
    for(int col = 1; col <= M; ++col)
    {
        for(auto v : add[col])
        {
            incr(v, 1);
        }
        
        maxDiffCnt = max(maxDiffCnt, diffCnt);
        
        for(auto v : del[col])
        {
            incr(v, -1);
        }
    }
    
    cout << maxDiffCnt << endl;
    
    return 0;
}
