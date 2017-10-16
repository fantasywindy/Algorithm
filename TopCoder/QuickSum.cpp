
/*
 Class: QuickSums
 Method: minSums
 Parameters: string, int
 Returns: int
 Method signature: int minSums(string numbers, int sum)
 
 */
#include <vector>
#include <string>
#include <iostream>
#include <climits>



using namespace std;



const int MAX_N = 10 + 2;

const int MAX_SUM = 100 + 2;

class QuickSums
{
public:
    
    
    int minSums(string numbers, int sum)
    {
        int n = numbers.size();
        
        
        int dp[MAX_N][MAX_N][MAX_SUM];
        
        for(int i = 0; i < n; ++i)
        {
            for(int j = 0; j < n; ++j)
            {
                for(int k = 0; k < MAX_SUM; ++k)
                {
                    dp[i][j][k] = INT_MAX;
                }
            }
        }
        
        for(int i = 0; i < n; ++i)
        {
            dp[i][i][numbers[i] - '0'] = 0;
        }
        
        for(int len = 2; len <= n; ++len)
        {
            for(int left = 0; left + len - 1 < n; ++left)
            {
                int right = left + len - 1;
                
                string str = numbers.substr(left, len);
                

                string str1 = str;
                    
                while(str1.size() > 1 && str1.front() == '0')
                {
                    str1.erase(str1.begin());
                }
                
                if(stoll(str1) < MAX_SUM)
                {
                    //cout << stoll(str1) << endl;
                    dp[left][right][stoll(str1)] = 0;
                }
                
                
                
                for(int val = 0; val < MAX_SUM; ++val)
                {
                    for(int left_len = 1; left_len < len; ++left_len)
                    {
                        for(int left_val = 0; left_val <= val; ++left_val)
                        {
                            if(dp[left][left + left_len - 1][left_val] != INT_MAX && dp[left + left_len][right][val - left_val] != INT_MAX)
                            {
                                dp[left][right][val] = min(dp[left][right][val], dp[left][left + left_len - 1][left_val] + dp[left + left_len][right][val - left_val] + 1);
                            }
                            
                        }
                    }
                    
                    //cout << dp[left][right][val] << endl;
                }
                
                
            }
        }
        
        return dp[0][n-1][sum] == INT_MAX ? -1 : dp[0][n-1][sum];
        
    }
};

int main()
{
    QuickSums qs;
    
    cout << qs.minSums("99999",100) << endl;
    return 0;
}
