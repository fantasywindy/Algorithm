#include <cstdio>
#include <cstring>
#include <iostream>
#include <sstream>
using namespace std;


const int MAX_S = 8;

const int MAX_N = 20 + 100 + 5;

const int INF = 1000000000;

int S, M, N;

int canTeach[MAX_N];

int salary[MAX_N];

int d[MAX_N][1 << MAX_S][1 << MAX_S];

int dp(int i, int s0, int s1, int s2)
{
	if(i == (M + N))
	{
		return s2 == ((1 << S) - 1) ? 0 : INF;
	}

	int &ans = d[i][s1][s2];
	if(ans >= 0)
	{
		return ans;
	}

	ans = INF;

	if(i >= M)
	{
		//applicants, no use i
		ans = dp(i + 1, s0, s1, s2);
	}

	// use i
	int m0 = s0 & canTeach[i]; //m0 is those subjects no one teach before
	int m1 = canTeach[i] & s1; //m1 is those subjects that one teach teach before
	s0 = s0 ^ m0;
	s1 = (s1 ^ m1) | m0;
	s2 = s2 | m1;

	ans = min(ans, salary[i] + dp(i + 1, s0, s1, s2));

	return ans;
}


int main()
{
	ios_base::sync_with_stdio(false);
	string line;
	while(getline(cin, line))
	{
		stringstream ss(line);

		ss >> S >> M >> N;

		if(S == 0)
		{
			break;
		}

		for(int i = 0; i < (M + N); ++i)
		{
			getline(cin, line);
			stringstream ss(line);
			ss >> salary[i];

			canTeach[i] = 0;
			int x;
			while(ss >> x)
			{
				canTeach[i] |= (1 << (x - 1));
			}
		}

		memset(d, -1, sizeof(d));

		cout << dp(0, ((1 << S) - 1), 0, 0) << "\n";
	}

	return 0;
}

