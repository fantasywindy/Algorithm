#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <climits>
#include <algorithm>


using namespace std;

int main()
{
	ifstream is("input.txt");

	ofstream os("output.txt");

	int n = 0;
	is >> n;

	vector<int> p(n, 0);
	vector<int> t(n, 0);


	for(int i = 0; i < n; ++i)
	{
		is >> p[i];
	}

	for(int i = 0; i < n; ++i)
	{
		is >> t[i];
	}

	int pt_index = 0;

	int tp_index = 0;

	int use_p = 0;

	int use_t = 0;

	int max_ability = 0;


	for(int i = 0; i < n; ++i)
	{
		if(p[i] > t[i])
		{
			if(p[pt_index] - t[pt_index] > p[i] - t[i])
			{
				pt_index = i;
			}
			++use_p;
		}
		else 
		{
			if(t[tp_index] - p[tp_index] > t[i] - p[i])
			{
				tp_index = i;
			}
			++use_t;
		}

		max_ability += max(p[i], t[i]);

	}


	if(use_p == 0)
	{
		//all use t, we should pick one that t has the least difference with p, mean t - p is the smallest
		max_ability += (p[tp_index] - t[tp_index]);
	}
	

	if(use_t == 0)
	{
		//all use p, we should pick one that p has the least difference with t, mean p - t is the smallest
		max_ability += (t[pt_index] - p[pt_index]);
	}

	os << max_ability << endl;

	return 0;
}