/*
 Class: SortEstimate
 Method: howMany
 Parameters: int, int
 Returns: double
 Method signature: double howMany(int c, int time)
 (be sure your method is public)
 */
#include <cmath>
#include <limits>
#include <iostream>

using namespace std;

class SortEstimate
{
public:
    double howMany(int c, int time)
    {
        double low = 0.0;
        double high = 2000000000;
        
        int iterations = 0;
        
        //nums too many we will use too much time, nums too little, we will use too little time
        while(iterations < 100)
        {
            double mid = low + (high - low) / 2;
            
            double ret = log10(mid) / log10(2) * c * mid;
            
            if(ret >= time)
            {
                high = mid;
            }
            else
            {
                low = mid;
            }
            ++iterations;
        }
        
        return (low + high) / 2.0;
    }
};

int main()
{
    SortEstimate s;
    cout << s.howMany(37, 12392342) << endl;
    return 0;
}
