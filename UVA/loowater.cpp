#include <cstring>
#include <cstdio>
#include <algorithm>
#include <iostream>

using namespace std;


const int MAX_N = 20000 + 5;
const int MAX_M = 20000 + 5;

int N, M;

int heads[MAX_N];
int knights[MAX_M];

void reset()
{
	memset(heads, 0, sizeof(heads));
	memset(knights, 0, sizeof(knights));
}

void solution()
{
	sort(heads + 1, heads + N + 1);
	sort(knights + 1, knights + M + 1);


	int i = 1; 
	int j = 1;

	int money = 0;

	while(i <= N && j <= M)
	{
		while(j <= M && knights[j] < heads[i])
		{
			++j;
		}

		if(j == (M + 1))
		{
			cout << "Loowater is doomed!" << endl;
		}
		else
		{
			money += knights[j];
			++i;
			++j;
		}
	}

	if(i == (N + 1))
	{
		cout << money << endl;
	}
	else
	{
		cout << "Loowater is doomed!" << endl;
	}
}

int main()
{
	while(scanf("%d%d", &N, &M) == 2)
	{
		reset();

		if(N == 0 && M == 0)
		{
			break;
		}

		for(int i = 1; i <= N; ++i)
		{
			scanf("%d", &heads[i]);
		}

		for(int j = 1; j <= M; ++j)
		{
			scanf("%d", &knights[j]);
		}

		solution();
	}

	return 0;
}