/*
 Input
 The first line of input contains N (1 ≤ N ≤ 106), L (2 ≤ L ≤ 105) and M (2 ≤ M ≤ 100), the number of cities in each layer, the number of layers and the number that travelling cost should be divisible by, respectively.
 
 Second, third and fourth line contain N integers each denoting costs 0 ≤ cost ≤ M from entry point to the first layer, costs between adjacent layers as described above, and costs from the last layer to the exit point.
 
 Output
 Output a single integer, the number of paths Doctor G. can take which have total cost divisible by M, modulo 109 + 7.
 
 Example
 input
 2 3 13
 4 6
 2 1
 3 4
 output
 2
 */
#include <iostream>
#include <vector>
#include <assert.h>
#include <fstream>
using namespace std;

const long long MOD = 1e9 + 7;
const long long MOD2 = static_cast<long long>(MOD) * MOD;
int N;
int L;
int M;

#define LOCAL_FILE




class Matrix
{
public:
    Matrix(const vector<vector<long long> > & vec)
    :mat(vec),
    rows(vec.size()),
    cols(vec[0].size())
    {
        
    }
    
    bool isIdentity() const
    {
        return rows == cols;
    }
    
    static Matrix Identity(int n)
    {
        vector<vector<long long> > ret(n, vector<long long>(n, 0));
        
        for(int i = 0; i < n; ++i)
        {
            ret[i][i] = 1;
        }
        
        return Matrix(ret);
    }
    
    
public:
    vector<vector<long long> > mat;
    int rows;
    int cols;
};

Matrix operator*(const Matrix & l, const Matrix & r)
{
    assert(l.cols == r.rows);
    
    vector<vector<long long> > ret(l.rows, vector<long long>(r.cols, 0));
    
    for(int i = 0; i < l.rows; ++i)
    {
        for(int j = 0; j < r.cols; ++j)
        {
            long long temp = 0;
            for(int k = 0; k < l.cols; ++k)
            {
                temp += l.mat[i][k] * 1ll * r.mat[k][j];
                while(temp >= MOD2)
                {
                    temp -= MOD2;
                }
            }
            
            ret[i][j] = temp % MOD;
        }
    }
    
    return Matrix(ret);
}



static Matrix pow(int n, const Matrix & input)
{
    assert(input.isIdentity());
    Matrix ret = Matrix::Identity(input.rows);
    
    Matrix m = input;
    
    while(n)
    {
        if(n & 1)
        {
            ret = ret * m;
        }
        
        m = m * m;
        
        n = n >> 1;
    }
    
    return ret;
}



int main()
{

#ifdef LOCAL_FILE
    fstream fs("/Users/ice/Desktop/input.txt");
#define input fs
#else
#define input cin
    
#endif
    
    ios_base::sync_with_stdio(false);
    input >> N >> L >> M;
    
    vector<long long> first_costs(N, 0);
    for(int i = 0; i < N; ++i)
    {
        input >> first_costs[i];
    }
    
    vector<long long> middle_costs(N, 0);
    for(int i = 0; i < N; ++i)
    {
        input >> middle_costs[i];
    }
    
    vector<long long> last_costs(N, 0);
    for(int i = 0; i < N; ++i)
    {
        input >> last_costs[i];
    }
    
    vector<long long> fCosts(M, 0);
    for(int i = 0; i < N; ++i)
    {
        ++fCosts[first_costs[i] % M];
    }
    
    vector<long long> mCosts(M, 0);
    for(int i = 0; i < N; ++i)
    {
        ++mCosts[middle_costs[i] % M];
    }
    
    vector<long long> lCosts(M, 0);
    
    for(int i = 0; i < N; ++i)
    {
        ++lCosts[(middle_costs[i] + last_costs[i]) % M];
    }
    
    
    vector<vector<long long> > middle_vec(M, vector<long long>(M, 0));
    
    for(int r = 0; r < M; ++r)
    {
        vector<long long> row;
        
        int start = (M - r) % M;
        
        for(int c = 0; c < M; ++c)
        {
            int cur = (start + c) % M;
            middle_vec[r][c] = mCosts[cur];
        }
    }
    
    Matrix trans_mat(middle_vec);
    
    Matrix first_mat(vector<vector<long long> >(1, fCosts));
    
    Matrix pre_last_mat = first_mat * pow(L - 2, trans_mat);
    
    vector<long long> pre_last_dp = pre_last_mat.mat[0];
    
    vector<long long> ret(M, 0);
    
    for(int i = 0; i < M; ++i)
    {
        for(int j = 0; j < M; ++j)
        {
            ret[(i + j) % M] = (ret[(i + j) % M] + pre_last_dp[i] * 1ll * lCosts[j]) % MOD;
        }
    }
    
    cout << ret[0] << endl;
    
    return 0;
    
}
