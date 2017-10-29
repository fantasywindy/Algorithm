#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <climits>
#include <algorithm>
#include <iomanip>


using namespace std;

bool isValid(vector<vector<int> > cur, int i, int j)
{
    for(int r = 0; r <= i; ++r)
    {
        int cnt = count(cur[r].begin(), cur[r].end(), 1);
        if(r < i && cnt != 1)
        {
            return false;
        }
        else if(r == i)
        {
            if(cnt > 1)
            {
                return false;
            }
            else{
                if(j == 2 && cnt != 1)
                {
                    return false;
                }
            }
        }
    }
    
    for(int c = 0; c <= j; ++c)
    {
        int cnt = 0;
        for(int r = 0; r < 3; ++r)
        {
            if(cur[r][c] == 1)
            {
                ++cnt;
            }
        }
        
        if(cnt > 1)
        {
            return false;
        }
        else if(i == 2 && cnt != 1)
        {
            return false;
        }
    }
    
    return true;
}

void dfs(double & max_val, int i, int j, vector<vector<int> > cur, vector<vector<int> > & m, int depth)
{
    
    if(i == 3)
    {
        double val = 0;
        for(int r = 0; r < 3; ++r)
        {
            for(int c = 0; c < 3; ++c)
            {
                if(cur[r][c] != 0)
                {
                    val += m[r][c] * m[r][c];
                }
            }
        }
        
        max_val = max(max_val, sqrt(val));
        return;
    }
    
    if(j == 3)
    {
        dfs(max_val, i + 1, 0, cur, m, depth + 1);
    }
    else
    {
        //j != 3,
        cur[i][j] = 1;
        
        if(isValid(cur, i, j))
        {
            dfs(max_val, i, j + 1, cur, m, depth + 1);
        }
        
        cur[i][j] = 0;
        
        if(isValid(cur, i, j))
        {
            dfs(max_val, i, j + 1, cur, m, depth + 1);
        }
        
    }
}

int main()
{
    ifstream is("input.txt");
    
    ofstream os("output.txt");
    
    vector<vector<int> > m(3, vector<int>(3, 0));
    
    for(int i = 0; i < 3; ++i)
    {
        for(int j = 0; j < 3; ++j)
        {
            is >> m[i][j];
        }
    }
    
    double max_val = 0.0;
    
    vector<vector<int> > cur(3, vector<int>(3, 0));
    
    dfs(max_val, 0, 0, cur, m, 0);
    
    
    os << std::setprecision(6) << std::fixed << max_val << endl;
    
    return 0;
}