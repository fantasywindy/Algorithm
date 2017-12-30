#include <string>
#include <iostream>
#include <climits>
#include <map>
#include <vector>


using namespace std;


int T;
string str;

int solution()
{
	int n = str.size();
	
	vector<int> dp(n, 0);

	map<char, int> last;

	last[str[0]] = 0;

	dp[0] = 1;

	int max_dp = 1;

	for(int i = 1; i < n; ++i)
	{
		//cout << i << " " << (last.find(str[i]) == last.end() ? "no exist" : to_string(last[str[i]])) << endl;
		if( last.find(str[i]) == last.end() || (i - dp[i-1]) >= (last[str[i]] + 1))
		{
			dp[i] = dp[i-1] + 1;
		}
		else
		{
			dp[i] = i - last[str[i]];
		}

		last[str[i]] = i;

		max_dp = max(max_dp, dp[i]);

		//cout << str.substr(0, i + 1) << " " << dp[i] << endl;
	}

	return max_dp;


}



int main()
{
	ios_base::sync_with_stdio(false);
	cin >> T;

	while(T--)
	{
		cin >> str;
		cout << solution() << endl;
	}
	return 0;
}