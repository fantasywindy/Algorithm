#include <vector>
#include <queue>
#include <utility>
#include <iostream>
#include <set>
#include <unordered_map>
#include <algorithm>
#include <queue>
#include <cstring>



using namespace std;

#include <fstream>

#define LOCAL_FILE
#ifdef LOCAL_FILE
fstream fs("/Users/ice/Documents/codeforce/input.txt");
#define input fs
#else
#define input cin

#endif


/*
 Polycarp is in really serious trouble — his house is on fire! It's time to save the most valuable items. Polycarp estimated that it would take ti seconds to save i-th item. In addition, for each item, he estimated the value of di — the moment after which the item i will be completely burned and will no longer be valuable for him at all. In particular, if ti ≥ di, then i-th item cannot be saved.
 
 Given the values pi for each of the items, find a set of items that Polycarp can save such that the total value of this items is maximum possible. Polycarp saves the items one after another. For example, if he takes item a first, and then item b, then the item a will be saved in ta seconds, and the item b — in ta + tb seconds after fire started.
 
 Input
 The first line contains a single integer n (1 ≤ n ≤ 100) — the number of items in Polycarp's house.
 
 Each of the following n lines contains three integers ti, di, pi (1 ≤ ti ≤ 20, 1 ≤ di ≤ 2 000, 1 ≤ pi ≤ 20) — the time needed to save the item i, the time after which the item i will burn completely and the value of item i.
 
 Output
 In the first line print the maximum possible total value of the set of saved items. In the second line print one integer m — the number of items in the desired set. In the third line print m distinct integers — numbers of the saved items in the order Polycarp saves them. Items are 1-indexed in the same order in which they appear in the input. If there are several answers, print any of them.
 
 Examples
 input
 3
 3 7 4
 2 6 5
 3 7 6
 output
 11
 2
 2 3
 input
 2
 5 6 1
 3 3 5
 output
 1
 1
 1
 Note
 In the first example Polycarp will have time to save any two items, but in order to maximize the total value of the saved items, he must save the second and the third item. For example, he can firstly save the third item in 3 seconds, and then save the second item in another 2 seconds. Thus, the total value of the saved items will be 6 + 5 = 11.
 
 In the second example Polycarp can save only the first item, since even if he immediately starts saving the second item, he can save it in 3 seconds, but this item will already be completely burned by this time.
 
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
struct Item
{
    int t;
    int d;
    int p;
    int id;
};

struct DP
{
    vector<int> vec;
    int val;
};

bool operator<(const DP & l, const DP & r)
{
    return l.val < r.val;
}


const int MAX_N = 100 + 5;
//const int MAX_T = 20 + 5;
const int MAX_D = 2000 + 5;
//const int MAX_P = 20 + 5;

int main()
{
    ios_base::sync_with_stdio(false);
    
    int n;
    input >> n;
    
    int max_d = INT_MIN;
    
    vector<Item> items;
    for(int i = 1; i <= n; ++i)
    {
        Item a;
        input >> a.t >> a.d >> a.p;
        a.id = i;
        items.push_back(a);
        max_d = max(max_d, a.d);
    }
    
    sort(items.begin(), items.end(), [](const Item & l, const Item & r)
         {
             return l.d < r.d || (l.d == r.d && l.t < r.t);
         });
    
    
    
    DP dp[MAX_N][MAX_D];
    
    for(int i = 0; i < MAX_N; ++i)
    {
        for(int j = 0; j < MAX_D; ++j)
        {
            dp[i][j].val = INT_MIN;
        }
    }
    
    for(int i = 0; i < MAX_N; ++i)
    {
        dp[i][0].val = 0;
    }
    
    for(int j = 0; j < MAX_D; ++j)
    {
        dp[0][j].val = 0;
    }
    
    DP max_val;
    max_val.val = INT_MIN;
    for(int i = 1; i <= n; ++i)
    {
        for(int t = 0; t <= max_d; ++t)
        {
            dp[i][t] = max(dp[i][t], dp[i-1][t]);
            if(t < items[i-1].d && t >= items[i-1].t)
            {
                //can save it
                DP temp = dp[i-1][t - items[i-1].t];
                temp.val += items[i-1].p;
                temp.vec.push_back(i);
                dp[i][t] = max(dp[i][t], temp);
            }
            max_val = max(max_val, dp[i][t]);
        }
    }
    
    cout << max_val.val << endl;
    
    cout << max_val.vec.size() << endl;
    for(auto item : max_val.vec)
    {
        cout << items[item - 1].id << " ";
    }
    cout << endl;
    
    return 0;
}
