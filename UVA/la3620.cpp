#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

const int INF = 1e9;

int nrows, ncols;

int G[10][10];

// 3^10
int memo[9][9][59049];


struct State
{
	int up[9];
	int left;

	int encode() const
	{
		int key = left;
		for(int i = 0; i < ncols; ++i)
		{
			key = key * 3 + up[i];
		}
		return key;
	}

	bool next(int row, int col, int U, int D, int L, int R, State & T) const
	{
		if(row == nrows - 1 && D != 0) return false;
		if(col == ncols - 1 && R != 0) return false;

		int must_left = (col > 0 && left != 0);
		int must_up = (row > 0 && up[col] != 0);

		if((must_left && L != left) || (!must_left && L != 0)) return false;

		if((must_up && U != up[col]) || (!must_up && U != 0)) return false;

		if(must_left && must_up && left != up[col]) return false;


		for(int i = 0; i < ncols; ++i)
		{
			T.up[i] = up[i];
		}
		T.up[col] = D;
		T.left = R;
		return true;
	}
};


int rec(int row, int col, const State & S)
{
	if(col == ncols) { col = 0; row++; }
	if(row == nrows) { return 0; }

	int key = S.encode();

	int & res = memo[row][col][key];

	if(res >= 0) return res;

	res = INF;

	State T;

	if(G[row][col] <= 1)
	{
		if(S.next(row, col, 0, 0, 0, 0, T))
		{
			res = min(res, rec(row, col + 1, T));
		}

		if(G[row][col] == 0)
		{
			for(int t = 1; t <= 2; ++t)
			{
				if(S.next(row, col, t, t, 0, 0, T)) res = min(res, rec(row, col + 1, T) + 2);
				if(S.next(row, col, t, 0, t, 0, T)) res = min(res, rec(row, col + 1, T) + 2);
				if(S.next(row, col, t, 0, 0, t, T)) res = min(res, rec(row, col + 1, T) + 2);
				if(S.next(row, col, 0, t, t, 0, T)) res = min(res, rec(row, col + 1, T) + 2);
				if(S.next(row, col, 0, t, 0, t, T)) res = min(res, rec(row, col + 1, T) + 2);
				if(S.next(row, col, 0, 0, t, t, T)) res = min(res, rec(row, col + 1, T) + 2);
			}
		}
	}
	else
	{
		int t = G[row][col] - 1;

		if(S.next(row, col, t, 0, 0, 0, T)) res = min(res, rec(row, col + 1, T) + 1);
		if(S.next(row, col, 0, t, 0, 0, T)) res = min(res, rec(row, col + 1, T) + 1);
		if(S.next(row, col, 0, 0, t, 0, T)) res = min(res, rec(row, col + 1, T) + 1);
		if(S.next(row, col, 0, 0, 0, t, T)) res = min(res, rec(row, col + 1, T) + 1);
	}
	return res;
}

int main()
{
	while(scanf("%d%d", &nrows, &ncols) == 2 && nrows && ncols)
	{
		for(int i = 0; i < nrows; ++i)
		{
			for(int j = 0; j < ncols; ++j)
			{
				scanf("%d", &G[i][j]);
			}
		}

		State S;
		memset(&S, 0, sizeof(S));

		memset(memo, -1, sizeof(memo));

		int ans = rec(0, 0, S);

		if(ans == INF) ans = 0;

		cout << ans / 2 << endl;
	}

	return 0;
}

