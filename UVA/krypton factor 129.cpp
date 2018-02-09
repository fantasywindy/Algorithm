#include <cstring>
#include <iostream>
#include <string>
#include <cstdio>
#include <cmath>
#include <climits>
#include <algorithm>
#include <numeric>

using namespace std;


const int MAX_LEN = 80 + 5;
const int MAX_L = 26;

int n, L;

bool visited[MAX_L];

int cnt = 0;

void reset()
{
	//memset(visited, 0, sizeof(visited));
	cnt = 0;
}

string ret = "";

bool isValid(const string & str)
{
	int len = str.size();

	if(str.size() == 1)
	{
		return true;
	}


	for(int post = 1; post * 2 <= len; ++post)
	{
		string left = str.substr(len - 2 * post, post);
		string right = str.substr(len - post, post);

		if(left == right)
		{
			return false;
		}
	}

	return true;
}

void dfs(string str)
{
	//cout << "dfs " << str << endl;
	if(isValid(str))
	{
		//cout << str << endl;
		if(str != "")
		{
			++cnt;
		}
		
		if(cnt == n)
		{
			ret = str;
			//cout << "cnt " << cnt << " is " << n << ret << endl;
			return;
		}
		else if(cnt < n)
		{
			for(int i = 0; i < L; ++i)
			{
				str.push_back('A' + i);
				dfs(str);
				str.pop_back();
			}
		}
	}
	else
	{
		return;
	}
}

void solve()
{
	string str = "";
	dfs(str);
	for(int g = 0; g < (MAX_LEN / 4); ++g)
	{
		int s = g * 4;
		int e = std::min((g + 1) * 4, (int)ret.size());

		if(s < ret.size())
		{
			if(g == 0)
			{

			}
			else
			{
				if(g % 16 == 0)
				{
					cout << endl;
				}
				else
				{
					cout << " ";
				}
			}
			cout << ret.substr(s, e - s);
		}
		else
		{
			break;
		}
	}
	cout << endl;
	cout << ret.size() << endl;
}


int main()
{
	while(scanf("%d%d", &n, &L) == 2)
	{
		if(n == 0 && L == 0)
		{
			break;
		}

		reset();

		solve();

		//cout << "******" << endl;
	}

	return 0;
}