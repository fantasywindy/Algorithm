#include <iostream>
#include <vector>
#include <set>
#include <unordered_map>
using namespace std;


class SegmentTree
{
public:
	void init(int n)
	{
		N = n;
		trees.assign(4 * n, 0);
		lazy.assign(4 * n, 0);
	}

	void update(int l, int r, int val)
	{
		int max_val = query(l, r);

		upd(1, l, r, 0, N, max_val + val);
	}

	int query(int l, int r)
	{
		return qry(1, l, r, 0, N);
	}

private:
	void upd(int id, int x, int y, int l, int r, int val)
	{
		//if current id node has something not updated yet, update it first
		if(lazy[id] != 0)
		{
			trees[id] = max(trees[id], lazy[id]);
			if(r - l >= 2)
			{
				//not leaf node, pass down lazy
				lazy[id * 2] = max(lazy[id * 2], lazy[id]);
				lazy[id * 2 + 1] = max(lazy[id * 2 + 1], lazy[id]);
			}
			//finish passing down lazy, reset itself
			lazy[id] = 0;
		}

		if(x >= r || y <= l)
		{
			return;
		}

		if(l >= x && r <= y)
		{
			//when we got here, the lazy of itself should be taken cared at above code, so we should not worry about it
			//node is totally in range x, y
			trees[id] = max(trees[id], val);
			if(r - l >= 2)
			{
				//not leaf node, pass down lazy
				lazy[id * 2] = max(lazy[id * 2], val);
				lazy[id * 2 + 1] = max(lazy[id * 2 + 1], val);
			}
			return;
		}

		//partially overlap
		int m = l + (r - l) / 2;

		upd(id * 2, x, y, l, m, val);
		upd(id * 2 + 1, x, y, m, r, val);

		//update itself
		trees[id] = max(trees[id * 2], trees[id * 2 + 1]);

	}

	int qry(int id, int x, int y, int l, int r)
	{
		//if current id node has something not updated yet, update it first
		if(lazy[id] != 0)
		{
			trees[id] = max(trees[id], lazy[id]);
			if(r - l >= 2)
			{
				//not leaf node, pass down lazy
				lazy[id * 2] = max(lazy[id * 2], lazy[id]);
				lazy[id * 2 + 1] = max(lazy[id * 2 + 1], lazy[id]);
			}
			//finish passing down lazy, reset itself
			lazy[id] = 0;
		}

		if(x >= r || y <= l)
		{
			return 0;
		}

		if(l >= x && r <= y)
		{
			//when we got here, the lazy of itself should be taken cared at above code, so we should not worry about it
			//node is totally in range x, y
			return trees[id];
		}

		//partially overlap
		int m = l + (r - l) / 2;

		return max(qry(id * 2, x, y, l, m), qry(id * 2 + 1, x, y, m, r));

	}

private:
	vector<int> trees;
	vector<int> lazy;
	int N;
};

class Solution {
public:
    vector<int> fallingSquares(vector<pair<int, int>>& positions) {
        //first because the positions values are so large, and some of them may be duplicate, we can compress all the values

        set<int> pos_t;

        for(auto pos : positions)
        {
        	int l = pos.first;
        	int r = pos.first + pos.second - 1;

        	pos_t.insert(l);
        	pos_t.insert(r);
        }

        int index = 0;

        unordered_map<int, int> pos_m;

        for(auto item : pos_t)
        {
        	pos_m[item] = index++;
        }

        //now index is the count of distinct pos

        SegmentTree T;

        T.init(index);

        vector<int> ret;

        for(auto pos : positions)
        {
        	int l = pos.first;
        	int r = pos.first + pos.second - 1;

        	int l_index = pos_m[l];
        	int r_index = pos_m[r] + 1;
        	int val = pos.second;

        	T.update(l_index, r_index, val);

        	//query the max of the tree

        	ret.push_back(T.query(0, index));
        }

        return ret;
    }
};