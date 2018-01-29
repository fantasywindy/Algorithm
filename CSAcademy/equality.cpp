#include <iostream>
#include <set>

using namespace std;

const int MAX_VAL = 100005;

int cnt[MAX_VAL] = {0};

int main() {
    ios_base::sync_with_stdio(false);
    multiset<int> t;
    
    int N, K;
    cin >> N >> K;
    
    for(int i = 0; i < N; ++i)
    {
        int a;
        cin >> a;
        ++cnt[a];
    }
    
    int low = 1;
    int high = MAX_VAL - 1;
    
    while(low <= high && cnt[low] == 0)
    {
        ++low;
    }
    
    while(high >= low && cnt[high] == 0)
    {
        --high;
    }
    
    int action = 0;
    
    while(true)
    {
        if(low >= high)
        {
            break;
        }
        
        if(high - low <= K)
        {
            break;
        }
        
        int min_cnt = min(cnt[low], cnt[high]);
        
        action += min_cnt;
        
        cnt[low] -= min_cnt;
        
        cnt[low + 1] += min_cnt;
        
        cnt[high] -= min_cnt;
        
        cnt[high - 1] += min_cnt;
        
        if(cnt[low] == 0)
        {
            ++low;
        }
        
        if(cnt[high] == 0)
        {
            --high;
        }
    }
    
    cout << action << endl;
    
    return 0;
}