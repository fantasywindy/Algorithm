/*
 Class:
ZigZag
Method:
longestZigZag
Parameters:
vector <int>
Returns:
int
Method signature:
int longestZigZag(vector <int> sequence)
(be sure your method is public)
*/
#include <vector>
#include <algorithm>
using namespace std;

class ZigZag
{
public:
	int longestZigZag(vector <int> sequence)
	{
		int n = sequence.size();

		if(n <= 1)
		{
			return n;
		}

		vector<int> dp_increasing(n, 1);
		vector<int> dp_decreasing(n, 1);

		dp_increasing[0] = 1;
		dp_decreasing[0] = 1;


		int max_len = 1;
		for(int i = 1; i < n; ++i)
		{
			for(int j = 0; j < i; ++j)
			{
				if(sequence[i] > sequence[j])
				{
					dp_increasing[i] = max(dp_increasing[i], dp_decreasing[j] + 1);
				}
				else if(sequence[i] < sequence[j])
				{
					dp_decreasing[i] = max(dp_decreasing[i], dp_increasing[j] + 1);
				}
			}

			max_len = max(max_len, max(dp_increasing[i], dp_decreasing[i]));
		}

		return max_len;
	}

};