/*
 Class: Jewelry
 Method: howMany
 Parameters: vector <int>
 Returns: long long
 Method signature: long long howMany(vector <int> values)
 (be sure your method is public)
 */
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

const int max_total_values = 1000 * 30;
const int max_n = 30;

long long forward_ways[max_n + 1][max_total_values + 1];

long long backward_ways[max_n + 1][max_total_values + 1];

long long comb[max_n + 1][max_n + 1];


class Jewelry
{
public:
    
    void combination()
    {
        for(int i = 0; i <= max_n; ++i)
        {
            comb[0][i] = 0;
        }
        
        comb[0][0] = 1;
        
        for(int i = 1; i <= max_n; ++i)
        {
            comb[i][0] = 1;
            for(int j = 0; j <= max_n; ++j)
            {
                comb[i][j] = comb[i-1][j] + comb[i-1][j-1];
            }
        }
    }
    
    void calc_ways(vector<int> & values, long long ways[max_n + 1][max_total_values + 1])
    {
        ways[0][0] = 1;
        for(int i = 1; i <= values.size(); ++i)
        {
            ways[i][0] = 1;
            for(int j = 1; j <= max_total_values; ++j)
            {
                ways[i][j] = ways[i-1][j];
                if(j >= values[i - 1])
                {
                    ways[i][j] += ways[i-1][j - values[i-1]];
                }
            }
        }
    }
    
    
    long long howMany(vector <int> values)
    {
        int n = values.size();
        
        sort(values.begin(), values.end());
        
        calc_ways(values, forward_ways);
        
        reverse(values.begin(), values.end());
        
        calc_ways(values, backward_ways);
        
        reverse(values.begin(), values.end());
        
        combination();
        
        //
        
        long long ret = 0;
        
        int i = 0;
        
        while(i < n)
        {
            int p = i;
            
            while(p < n && values[p] == values[i])
            {
                ++p;
            }
            
            int repeated = p - i;
            
            for(int c = 1; c <= repeated; ++c)
            {
                for(int val = c * values[i]; val <= max_total_values; ++val)
                {
                    ret += forward_ways[i][val - c * values[i]] * comb[repeated][c] * backward_ways[n - i - c][val];
                }
            }
            
            i = p;
        }
        
        return ret;
        
    }
};