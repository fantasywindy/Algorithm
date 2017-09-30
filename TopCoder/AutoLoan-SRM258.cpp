#include <iostream>
#include <cmath>
#include <limits>

using namespace std;



/*
 Class: AutoLoan
 Method: interestRate
 Parameters: double, double, int
 Returns: double
 Method signature: double interestRate(double price, double monthlyPayment, int loanTerm)
 
 
 2000
 510
 4
 Returns: 9.56205462458368
 
 */

class AutoLoan
{
public:
    double interestRate(double price, double monthlyPayment, int loanTerm)
    {
        double rate = 0.0;
        
        double low = 0.0;
        
        double high = 1.0;
        
        double lastRate = 0.0;
        
        while(true)
        {
            double mid = low + (high - low) / 2.0;
            
            if(stillRemain(price, monthlyPayment, loanTerm, mid))
            {
                high = mid;
            }
            else
            {
                low = mid;
            }
            
            if(abs(lastRate - mid) <= numeric_limits<double>::epsilon())
            {
                break;
            }
            else
            {
                lastRate = mid;
            }
        }
        
        return low * 12 * 100.0;
    }
    
    bool stillRemain(double price, double monthlyPayment, int loanTerm, double rate)
    {
        double balance = price;
        for(int i = 0; i < loanTerm; ++i)
        {
            balance = balance + balance * rate - monthlyPayment;
        }
        
        //if rate is too high, then after loanTerm, and loan is still not finished
        if(balance <= numeric_limits<double>::epsilon())
        {
            return false;
        }
        else
        {
            return true;
        }
    }
    
};

int main()
{
    AutoLoan loan;
    cout << loan.interestRate(2000.0, 510.0, 4) << endl;
    return 0;
}
