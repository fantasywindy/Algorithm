#include <iostream>
#include <vector>

using namespace std;

const int MAX_WEIGHT = 100 + 5;
const int MAX_VAL = 100 * 100 + 5;
const int MAX_N = 100 + 5;

int main() {
	//code
	ios_base::sync_with_stdio(false);
	int test;
	cin >> test;
	
	for(int t = 0; t < test; ++t)
	{
	    int n, W;
	    cin >> n;
	    cin >> W;
	    
	    vector<int> weights(n);
	    vector<int> values(n);
	    for(int i = 0; i < n; ++i)
	    {
	        cin >> values[i];   
	    }

	    for(int i = 0; i < n; ++i)
	    {
	    	cin >> weights[i];
	    }
	    
	    vector<vector<int> > dp(n + 1, vector<int>(W + 1, 0));
	    
	    for(int i = 1; i <= n; ++i)
	    {
	        for(int w = 0; w <= W; ++w)
	        {
	            dp[i][w] = dp[i-1][w];
	            if(w >= weights[i - 1])
	            {
	                dp[i][w] = max(dp[i][w], dp[i-1][w - weights[i - 1]] + values[i - 1]);
	            }
	        }
	    }
	    
	    cout << dp[n][W] << endl;
	}
	return 0;
}