/*
Polycarp is in really serious trouble — his house is on fire! It's time to save the most valuable items. Polycarp estimated that it would take ti seconds to save i-th item. In addition, for each item, he estimated the value of di — the moment after which the item i will be completely burned and will no longer be valuable for him at all. In particular, if ti ≥ di, then i-th item cannot be saved.

Given the values pi for each of the items, find a set of items that Polycarp can save such that the total value of this items is maximum possible. Polycarp saves the items one after another. For example, if he takes item a first, and then item b, then the item a will be saved in ta seconds, and the item b — in ta + tb seconds after fire started.

Input
The first line contains a single integer n (1 ≤ n ≤ 100) — the number of items in Polycarp's house.

Each of the following n lines contains three integers ti, di, pi (1 ≤ ti ≤ 20, 1 ≤ di ≤ 2 000, 1 ≤ pi ≤ 20) — the time needed to save the item i, the time after which the item i will burn completely and the value of item i.

Output
In the first line print the maximum possible total value of the set of saved items. In the second line print one integer m — the number of items in the desired set. In the third line print m distinct integers — numbers of the saved items in the order Polycarp saves them. Items are 1-indexed in the same order in which they appear in the input. If there are several answers, print any of them.
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>


using namespace std;


const int MAX_N = 100 + 5;
const int MAX_T = 20 + 5;
const int MAX_D = 2000 + 5;
const int MAX_P = 20 + 5;

struct DP
{
	DP()
	{
		val = 0;
		selected.clear();
	}
	int val;
	vector<int> selected;
};

bool operator<(const DP & l, const DP & r)
{
	return l.val < r.val;
}

DP dp[MAX_N][MAX_D];



struct Item
{
	Item(int t, int d, int p, int id)
	:t(t), d(d), p(p), id(id)
	{

	}

	int t, d, p, id;
};


int main()
{
	ios_base::sync_with_stdio(false);

	int n;

	cin >> n;

	vector<Item> items;


	int ti, di, pi;
	for(int i = 1; i <= n; ++i)
	{
		cin >> ti >> di >> pi;
		items.push_back(Item(ti, di, pi, i));
	}

	sort(items.begin(), items.end(), [](const Item & l, const Item & r)
	{
		return l.d < r.d;
	});

	int deadline = items.back().d;

	for(int i = 1; i <= n; ++i)
	{
		for(int t = 0; t <= deadline; ++t)
		{
			//not save item i
			dp[i][t] = max(dp[i-1][t], dp[i][t - 1]);

			//save item i;
			if(t < items[i-1].d && t >= items[i-1].t)
			{
				DP temp = dp[i-1][t - items[i-1].t];
				temp.val += items[i-1].p;
				temp.selected.push_back(items[i-1].id);

				if(dp[i][t] < temp)
				{
					dp[i][t] = temp;
				}
			}

		}
	}

	cout << dp[n][deadline].val << endl;

	cout << dp[n][deadline].selected.size() << endl;

	for(auto item : dp[n][deadline].selected)
	{
		cout << item << " ";
	}

	cout << endl;

	return 0;

}