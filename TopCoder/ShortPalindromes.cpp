/*
 
 A palindrome is a String that is spelled the same forward and backwards.
 Given a String base that may or may not be a palindrome,
 we can always force base to be a palindrome by adding letters to it.
 For example, given the word "RACE",
 we could add the letters "CAR" to its back to get "RACECAR" (quotes for clarity only).
 However, we are not restricted to adding letters at the back.
 For example, we could also add the letters "ECA" to the front to get "ECARACE".
 In fact, we can add letters anywhere in the word, so we could also get "ERCACRE" by adding an 'E' at the beginning,
 a 'C' after the 'R', and another 'R' before the final 'E'.
 Your task is to make base into a palindrome by adding as few letters as possible and return the resulting String.
 When there is more than one palindrome of minimal length that can be made,
 return the lexicographically earliest (that is, the one that occurs first in alphabetical order).
 
 
 Definition
 
 Class: ShortPalindromes
 Method: shortest
 Parameters: string
 Returns: string
 Method signature: string shortest(string base)
 (be sure your method is public)
 
 
 Constraints
 -	base contains between 1 and 25 characters, inclusive.
 -	Every character in base is an uppercase letter ('A'-'Z').
 */

#include <string>
#include <vector>
#include <iostream>

using namespace std;


class ShortPalindromes
{
public:
    string shortest(string base)
    {
        int n = base.size();
        
        vector<vector<string> > dp(n, vector<string>(n, ""));
        
        for(int i = 0; i < n; ++i)
        {
            dp[i][i] = string(1, base[i]);
        }
        
        for(int i = 0; i + 1 < n; ++i)
        {
            dp[i][i+1] = (base[i] == base[i+1] ? base.substr(i, 2) : min(string(1, base[i]) + string(1, base[i+1]) + string(1, base[i]),
                                                                         string(1, base[i+1]) + string(1, base[i]) + string(1, base[i+1])));
        }
        
        for(int len = 3; len <= n; ++len)
        {
            for(int left = 0; left + len - 1 < n; ++left)
            {
                int right = left + len - 1;
                
                
                if(base[left] == base[right])
                {
                    string temp = string(1, base[left]) + dp[left+1][right-1] + string(1, base[right]);
                    if(dp[left][right] == "")
                    {
                        dp[left][right] = temp;
                    }
                    else
                    {
                        if(dp[left][right].size() > temp.size())
                        {
                            dp[left][right] = temp;
                        }
                        else if(dp[left][right].size() == temp.size() && dp[left][right] > temp)
                        {
                            dp[left][right] = temp;
                        }
                    }
                }
                
                string add_left = string(1, base[right]) + dp[left][right-1] + string(1, base[right]);
                string add_right = string(1, base[left]) + dp[left + 1][right] + string(1, base[left]);
                
                string temp;
                if(add_left.size() < add_right.size())
                {
                    temp = add_left;
                }
                else if(add_left.size() > add_right.size())
                {
                    temp = add_right;
                }
                else{
                    temp = min(add_left, add_right);
                    
                }
                if(dp[left][right] == "")
                {
                    dp[left][right] = temp;
                }
                else
                {
                    if(dp[left][right].size() > temp.size())
                    {
                        dp[left][right] = temp;
                    }
                    else if(dp[left][right].size() == temp.size() && dp[left][right] > temp)
                    {
                        dp[left][right] = temp;
                    }
                }
                
            }
            
            
        }
        
        return dp[0][n-1];
        
    }
};

int main()
{
    ShortPalindromes sp;
    cout << sp.shortest("TOPCODER") << endl;
    return 0;
}
