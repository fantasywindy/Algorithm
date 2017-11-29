#include <vector>
#include <iostream>
#include <string>
#include <cstring>


using namespace std;

int out[26];

int in[26];

vector<int> G[26];


void dfs(int i, vector<bool> & visited)
{
	visited[i] = true;

	for(auto j : G[i])
	{
		if(visited[j] == false)
		{
			dfs(j, visited);
		}
	}
}

bool isConnected()
{
	vector<bool> visited(26, false);

	for(int i = 0; i < 26; ++i)
	{
		if((out[i] != 0 || in[i] != 0) && visited[i] == false)
		{
			dfs(i, visited);
			break;
		}
	}

	for(int i = 0; i < 26; ++i)
	{
		if((out[i] != 0 || in[i] != 0) && visited[i] == false)
		{
			return false;
		}
	}

	return true;
}


void test(int t)
{

	memset(out, 0, sizeof(out));
	memset(in, 0, sizeof(in));
	for(int i = 0; i < 26; ++i)
	{
		G[i].clear();
	}

	int n;
	cin >> n;

	string plate;
	for(int p = 0; p < n; ++p)
	{
		cin >> plate;

		char s = plate.front();
		char d = plate.back();

		++out[s - 'a'];

		++in[d - 'a'];

		G[s - 'a'].push_back(d - 'a');
		G[d - 'a'].push_back(s - 'a');
	}

	bool canConnect = false;
	if(isConnected() == false)
	{
		canConnect = false;
	}
	else
	{
		//see if the degree satisfy

		int diffCnt = 0;

		int outGTin = 0;

		int inGTout = 0;

		for(int i = 0; i < 26; ++i)
		{
			if(out[i] == in[i])
			{
				continue;
			}
			else
			{
				++diffCnt;
				if(diffCnt > 2)
				{
					canConnect = false;
					break;
				}

				if(abs(out[i] - in[i]) != 1)
				{
					canConnect = false;
					break;
				}

				if(out[i] > in[i])
				{
					outGTin = 1;
				}

				if(in[i] > out[i])
				{
					inGTout = 1;
				}

			}
		}


		if(diffCnt == 2)
		{
			if(outGTin == 1 && inGTout == 1)
			{
				canConnect = true;
			}
			else
			{
				canConnect = false;
			}
		}
		else if(diffCnt == 0)
		{
			canConnect = true;
		}
		else
		{
			canConnect = false;
		}

	}

	//cout << t << " ";

	if(canConnect == true)
	{
		cout << "Ordering is possible." << endl;
	}
	else
	{
		cout << "The door cannot be opened." << endl;
	}
}

int main()
{
	ios_base::sync_with_stdio(false);
	int t;
	cin >> t;

	for(int t1 = 0; t1 < t; ++t1)
	{
		test(t1);
	}

	return 0;
}