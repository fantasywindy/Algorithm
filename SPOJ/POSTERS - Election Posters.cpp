/*
Sample input:
1
5
1 4
2 6
8 10
3 4
7 10

Sample output:
4

*/
#include <iostream>
#include <vector>
#include <unordered_map>
#include <set>

using namespace std;



class SegmentTree
{
public:
	void init(int n)
	{
		lazy.assign(4 * n, 0);
		N = n;
	}

	void paint(int color, int l, int r)
	{
		return update(1, color, l, r, 0, N);
	}

	int count()
	{
		query(1, 0, N);
		return t.size();
	}

private:
	void update(int id, int color, int x, int y, int l, int r)
	{
		if(x >= r || y <= l)
		{
			return;
		}

		if(l >= x && r <= y)
		{
			lazy[id] = color;
			return;
		}

		shift(id);
		int mid = l + (r - l) / 2;
		update(id * 2, color, x, y, l, mid);
		update(id * 2 + 1, color, x, y, mid, r);
	}

	void shift(int id)
	{
		if(lazy[id])
		{
			lazy[id * 2] = lazy[id * 2 + 1] = lazy[id];
		}
		lazy[id] = 0;
	}

	void query(int id, int l, int r)
	{
		if(lazy[id] != 0)
		{
			t.insert(lazy[id]);
			return;
		}

		if(r - l < 2)
		{
			return;
		}

		int mid = l + (r - l) / 2;
		query(id * 2, l, mid);
		query(id * 2 + 1, mid, r);

	}

private:
	int N;
	vector<int> lazy;
	set<int> t;
};

int main()
{
	ios_base::sync_with_stdio(false);

	int t = 0;
	cin >> t;
	for(int i = 0; i < t; ++i)
	{

		int pn = 0;
		cin >> pn;

		vector<pair<int, int> > posters(pn);
		set<int> vals;
		for(int j = 0; j < pn; ++j)
		{
			cin >> posters[j].first >> posters[j].second;
			vals.insert(posters[j].first);
			vals.insert(posters[j].second);
		}

		unordered_map<int, int> valToIndexMap;
		int index = 0;
		for(auto item : vals)
		{
			valToIndexMap[item] = index++;
		}

		SegmentTree T;
		T.init(vals.size());

		int color = 1;
		for(auto poster : posters)
		{
			int start = valToIndexMap[poster.first];
			int end = valToIndexMap[poster.second];

			T.paint(color, start, end + 1);
			++color;
		}

		cout << T.count() << '\n';
	}

	return 0;
}