#include <cstring>
#include <string>
#include <vector>
#include <numeric>
#include <algorithm>
#include <set>
#include <iostream>


using namespace std;

int out[26];


int in[26];


int G[26][26];

int N;

const int MAX_C = 1000 + 5;

char word[MAX_C];

set<int> chars;

int visited[26];

void dfs(int i)
{
	visited[i] = 1;
	for(int j = 0; j < 26; ++j)
	{
		if(visited[j] == 0 && G[i][j] == 1)
		{
			dfs(j);
		}
	}
}

bool isConnected()
{

	int s = *chars.begin();
	dfs(s);
	for(auto item : chars)
	{
		if(visited[item] == false)
		{
			return false;
		}
	}

	return true;
}

bool isEuler()
{
	vector<int> in_minus_out;
	for(int i = 0; i < 26; ++i)
	{
		if(in[i] != out[i])
		{
			if(abs(in[i] - out[i]) != 1)
			{
				return false;
			}
			else
			{
				in_minus_out.push_back(in[i] - out[i]);
			}
		}
		else
		{
			//do nothing;
		}
	}

	if(in_minus_out.size() != 2 && in_minus_out.size() != 0)
	{
		return false;
	}
	else
	{
		int sum = accumulate(in_minus_out.begin(), in_minus_out.end(), 0);

		if(sum != 0)
		{
			return false;
		}

		return true;
	}
}


void reset()
{
	memset(in, 0, sizeof(in));
	memset(out, 0, sizeof(out));
	memset(word, 0, sizeof(word));
	memset(G, 0, sizeof(G));
	chars.clear();
	memset(visited, 0, sizeof(visited));

}

int main()
{
	int T;
	scanf("%d", &T);

	for(int t = 0; t < T; ++t)
	{
		reset();
		scanf("%d", &N);

		for(int i = 0; i < N; ++i)
		{
			scanf("%s", word);
			string str = word;
			int sc = str[0] - 'a';
			int ec = str[str.size() - 1] - 'a';
			G[sc][ec] = 1;
			G[ec][sc] = 1;
			++out[sc];
			++in[ec];
			chars.insert(sc);
			chars.insert(ec);
		}

		bool ret = false;

		if(isConnected() == false)
		{
			ret = false; 
		}
		else
		{
			//see if the degree satisfy
			ret = isEuler();
		}

		cout << (ret ? "Ordering is possible." : "The door cannot be opened." ) << endl;
	}

	return 0;

}



