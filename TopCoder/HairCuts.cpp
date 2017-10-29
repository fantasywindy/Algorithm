/*
 Class: HairCuts
 Method: maxCut
 Parameters: vector <string>, string
 Returns: double
 Method signature: double maxCut(vector <string> enter, string lastExit)
 (be sure your method is public)
 
 Limits
 Time limit (s): 840.000
 Memory limit (MB): 64
 Notes
 - The returned value must be accurate to within a relative or absolute value of 1E-9.
 
 Constraints
 - lastExit and all elements of enter are formatted as described in the statement.
 - enter contains between 1 and 50 elements, inclusive.
 - Each hh in enter will equal "09","10","11","12","01","02","03", or "04.
 - The hh in lastExit will equal "09","10","11","12","01",...,"05", or "06".
 - Each time will have mm equal to "00","01",...,"58", or "59".
 - lastExit will be a time that is later than every enter time.
 */

#include <string>
#include <vector>
#include <algorithm>
#include <iostream>


using namespace std;


class HairCuts
{
public:
    
    double strToTime(const string & str)
    {
        int hour = stoi(str.substr(0, 2));
        int min = stoi(str.substr(3, 2));
        
        if(hour < 9)
        {
            hour += 12;
        }
        
        double min_val = hour * 60 + min;
        return min_val;
    }
    
    double maxCut(vector <string> enter, string lastExit)
    {
        vector<double> client_enter_minutes;
        
        for(auto str : enter)
        {
            client_enter_minutes.push_back(strToTime(str));
        }
        
        
        double last_exit_minutes = strToTime(lastExit);
        
        sort(client_enter_minutes.begin(), client_enter_minutes.end());
        
        
        double low = 0.0;
        
        double high = 10000.0;
        
        
        int iteration = 0;
        
        while(iteration < 500)
        {
            double mid = low + (high - low) / 2;
            
            //if longest is too short, then gap between clients will be not satisfied
            //if longest is too long, then gap between clients will be satisfied
            
            
            if(satisfy(client_enter_minutes, last_exit_minutes, mid))
            {
                high = mid;
            }
            else
            {
                low = mid;
            }
            
            ++iteration;
        }
        
        double ret = low + (high - low) / 2;
        
        if((5.0 - ret) > 1e-9)
        {
            return -1;
        }
        
        return low + (high - low) / 2;
    }
    
    bool satisfy(vector<double>  client_enter_minutes, double exit_time, double longest_cut)
    {
        double free = 0.0;
        
        for(int i = 0; i < client_enter_minutes.size(); ++i)
        {
            free = max(free, client_enter_minutes[i]);
            free += longest_cut;
        }
       
        return free >= exit_time;
    }
};