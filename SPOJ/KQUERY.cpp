/*
Input
5
5 1 2 3 4
3
2 4 1
4 4 4
1 5 2 

Output
2
0
3 


*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
using namespace std;


class SegmentTree
{
public:
	void init(int n)
	{
		N = n;
		trees.assign(n * 4, 0);
	}

	int sum(int l, int r)
	{
		return query(1, l, r, 0, N);
	}

	void update(int idx)
	{
		upd(1, idx, 0, N);
	}

private:

	void upd(int id, int idx, int l, int r)
	{
		if(r - l < 2)
		{
			trees[id] = 1;
			return;
		}

		int mid = l + (r - l) / 2;
		if(idx >= mid)
		{
			upd(id * 2 + 1, idx, mid, r);
		}
		else
		{
			upd(id * 2, idx, l, mid);
		}

		trees[id] = trees[id * 2] + trees[id * 2 + 1];
		return;
	}

	int query(int id, int x, int y, int l, int r)
	{
		if(x >= r || y <= l)
		{
			return 0;
		}

		if(l >= x && r <= y)
		{
			return trees[id];
		}

		int mid = l + (r - l) / 2;
		
		return query(id * 2, x, y, l, mid) + query(id * 2 + 1, x, y, mid, r);
	}


private:
	vector<int> trees;
	int N;

};

struct Action
{
	int start;
	int end;
	int type; //0 query 1 update
	int val;
	int originalIndex;
};

int main()
{
	ios_base::sync_with_stdio(false);

	vector<Action> actions;

	int n;
	cin >> n;

	int val = 0;
	for(int i = 0; i < n; ++i)
	{
		cin >> val;
		Action a;
		a.type = 1;
		a.val = val;
		a.originalIndex = i;
		actions.push_back(a);
	}

	int q;
	cin >> q;
	int query_start, query_end, query_val;
	for(int i = 0; i < q; ++i)
	{
		cin >> query_start >> query_end >> query_val;
		Action a;
		a.start = query_start - 1;
		a.end = query_end - 1;
		a.type = 0;
		a.val = query_val;
		a.originalIndex = i;
		actions.push_back(a);
	}


	sort(actions.begin(), actions.end(), [](const Action & l, const Action & r)
	{
		//if vals equal, first try query then try update
		return l.val > r.val ||(l.val == r.val && l.type < r.type);
	});


	SegmentTree T;
	T.init(n);

	vector<int> ret(q, 0);

	for(auto action : actions)
	{
		if(action.type == 0)
		{
			//query
			ret[action.originalIndex] = T.sum(action.start, action.end + 1);
		}
		else
		{
			//update 
			T.update(action.originalIndex);
		}
	}


	for(auto r : ret)
	{
		cout << r << '\n';
	}

	return 0;

}