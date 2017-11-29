#include <vector>
#include <cstdio>
#include <cstring>
#include <iostream>


using namespace std;
 

const int MAX_N = 100 + 5;

int G[MAX_N][MAX_N];

int N;

vector<int> pts[MAX_N][2];

int dp[MAX_N][MAX_N];

//0 is to put color 0
//1 is to put color 1

int visited[MAX_N];

bool ok;

void dfsUtil(int, int , int, int);

int cnt;

void dfs()
{
	for(int i = 1; i <= N; ++i)
	{
		visited[i] = -1;
	}

	ok = true;

	cnt = 0;
	for(int i = 1; i <= N; ++i)
	{
		if(visited[i] == -1)
		{
			int color = 0;
			int parent = -1;
			dfsUtil(i, parent, color, cnt + 1);
			++cnt;
		}
	}

	// for(int i = 1; i <= cnt; ++i)
	// {
	// 	cout << "set " << i << endl;
	// 	cout << "color 0 ";
	// 	for(auto item : pts[i][0])
	// 	{
	// 		cout << item << " ";
	// 	}
	// 	cout << endl;

	// 	cout << "color 1 ";
	// 	for(auto item : pts[i][1])
	// 	{
	// 		cout << item << " ";
	// 	}
	// 	cout << endl;
	// }
}

void dfsUtil(int i, int parent, int color, int setid)
{
	if(ok == false)
	{
		return;
	}

	visited[i] = color;

	pts[setid][color].push_back(i);

	for(int j = 1; j <= N; ++j)
	{
		if(i == j || j == parent || G[i][j] == 1)
		{
			continue;
		}

		if(visited[j] == -1)
		{
			dfsUtil(j, i, 1 ^ color, setid);
		}
		else
		{
			if(visited[j] == color)
			{
				ok = false;
				return;
			}
		}
	}
}

void calc();


void solution()
{
	//first we need to get the set of unconnected points;
	dfs();

	if(ok == false)
	{
		cout << "No solution" << endl;
		return;
	}

	calc();
}

void calc()
{
	int aa = pts[1][0].size();
	int bb = pts[1][1].size();

	dp[1][aa] = 1;
	dp[1][bb] = 2;

	for(int i = 2; i <= cnt; ++i)
	{
		aa = pts[i][0].size();
		bb = pts[i][1].size();

		for(int j = 0; j < MAX_N; ++j)
		{
			if(j >= aa && dp[i-1][j - aa])
			{
				dp[i][j] = 1;
			}

			if(j >= bb && dp[i-1][j - bb])
			{
				dp[i][j] = 2;
			}
		}
	}

	aa = N / 2;

	while(aa >= 0)
	{
		if(dp[cnt][aa] && aa != 0)
		{
			break;
		}

		if(dp[cnt][N - aa] && (N - aa) != 0)
		{
			aa = N - aa;
			break;
		}

		--aa;
	}

	vector<int> team1;


	int temp_visited[MAX_N];

	memset(temp_visited, 0, sizeof(temp_visited));

	for(int i = cnt; i >= 1; --i)
	{
		int f = dp[i][aa] - 1;

		int sz = pts[i][f].size();

		for(auto k : pts[i][f])
		{
			temp_visited[k] = 1;
			team1.push_back(k);
		}

		aa -= sz;
	}

	cout << team1.size();
	for(auto item : team1)
	{
		cout << " " << item; 
	}

	cout << endl;

	cout << N - team1.size();

	for(int k = 1; k <= N; ++k)
	{
		if(temp_visited[k] == 0)
		{
			cout << " " << k;
		}
	}

	cout << endl;
}

void reset()
{
	memset(G, 0, sizeof(G));
	memset(pts, 0, sizeof(pts));
	memset(dp, 0, sizeof(dp));
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

		if(t != 0)
		{
			cout << endl;
		}

		for(int u = 1; u <= N; ++u)
		{
			int v;
			while(scanf("%d", &v) == 1 && v)
			{
				G[u][v] = 1;
			}
		}

		for(int u = 1; u <= N; ++u)
		{
			for(int v = 1; v <= N; ++v)
			{
				if(G[u][v] == 0)
				{
					G[v][u] = 0;
				}
			}
		}


		solution();
	}

	return 0;
}