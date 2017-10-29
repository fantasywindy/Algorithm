#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <climits>
#include <algorithm>
#include <iomanip>
#include <string>



using namespace std;

long long calc(vector<string> & vec, vector<pair<int, int> > & charPos)
{
	if(vec.size() == 0)
	{
		return 0;
	}

	string withoutSpace = "";
	for(auto line : vec)
	{
		for(char c : line)
		{
			if(c != ' ' && c != '\n' && c != '\t')
			{
				withoutSpace.push_back(c);
			}
		}
	}

	if(withoutSpace.empty())
	{
		return 0;
	}




	long long ret = 0;

	for(int i = 1; i < withoutSpace.size(); ++i)
	{
		ret += max(abs(charPos[withoutSpace[i]].first - charPos[withoutSpace[i-1]].first), abs(charPos[withoutSpace[i]].second - charPos[withoutSpace[i-1]].second));
	}


	return ret;
}

int main()
{
    ifstream is("input.txt");
    
    ofstream os("output.txt");

    int W;
    int H;

    is >> W >> H;

    int i = 0;

    vector<pair<int, int> > charPos(150, {0, 0});

    char c;
    while(i < W * H)
    {
    	is >> c;
    	int row = i / W;
    	row = H - row;

    	int col = i % W;
    	++col;

    	charPos[c] = {col, row};
    	++i;


    }

    string line;
    getline(is, line);

    long long best_val = numeric_limits<long long>::max();
    string best_lan = "";

    while(getline(is, line))
    {
    	string lan = line;
    	
    	getline(is, line);

    	//skip the template header

    	vector<string> lan_temp;
    	while(getline(is, line))
    	{
    		if(line == "%TEMPLATE-END%")
    		{
    			break;
    		}
    		else
    		{
    			lan_temp.push_back(line);
    		}
    	}

    	long long val = calc(lan_temp, charPos);


    	if(val < best_val)
    	{
    		best_lan = lan;
    		best_val = val;
    	}


    }

    os << best_lan << endl;

    os << best_val << endl;

    return 0;
}