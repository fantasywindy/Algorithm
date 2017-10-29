/*
 Class: Mortgage
 Method: monthlyPayment
 Parameters: int, int, int
 Returns: int
 Method signature: int monthlyPayment(int loan, int interest, int term)
 (be sure your method is public)
 Limits
 Time limit (s): 840.000
 Memory limit (MB): 64
 Constraints
 - loan will be between 100 and 2,000,000,000, inclusive.
 - interest will be between 1 and 1,000,000, inclusive.
 - term will be between 1 and 1000, inclusive.
 */

#include <iostream>
using namespace std;


class Mortgage
{
public:
    int monthlyPayment(int loan, int interest, int term)
    {
        double rate = interest / 10.0 / 12.0 / 100.0;
        
        int months = term * 12;
        
        int iteration = 0;
        
        int low = 0;
        
        int high = loan;
        
        while(iteration < 100)
        {
            int mid = low + (high - low) / 2;
            
            //if payment is too little, then we cannot pay off on time, the loan will remain
            
            //if payment is too much, then we will pay too much.
            
            //there must be one point we just paid off
            
            if(isPaidGreaterOrEqualThanLoan(loan, rate, months, mid))
            {
                high = mid;
            }
            else
            {
                low = mid + 1;
            }
            
            ++iteration;
        }
        
        return low + (high - low) / 2;
    }
    
    bool isPaidGreaterOrEqualThanLoan(int loan, double rate, int months, int payment)
    {
        
        int remain = loan;
        
        for(int m = 0; m < months; ++m)
        {
            remain -= payment;
            
            if(remain <= 0.0)
            {
                return true;
            }
            
            double new_remain = remain * (1.0 + rate);
            
            int new_int_remain = new_remain;
            
            if(new_int_remain * 1.0 < new_remain)
            {
                new_int_remain += 1;
            }
            
            remain = new_int_remain;
            
        }
        
        return false;
    }
};

int main()
{
    Mortgage mg;
    int ret = mg.monthlyPayment(1000, 50, 1);
    cout << ret << endl;
    return 0;
}
