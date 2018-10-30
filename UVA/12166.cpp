#include <iostream>
#include <cstdio>
#include <cstring>
#include <map>
using namespace std;

typedef long long LL;

int main()
{
	ios::sync_with_stdio(false);

	int T;
	cin >> T;
	while(T--)
	{
		//cout << "Test start " << T << endl;
		string line;
		cin >> line;
		int depth = 0;

		int i = 0;
		int allNodesCnt = 0;

		map<LL, int> cnt;


		while(i < line.size())
		{

			if(line[i] == '[')
			{
				++depth;
				++i;
			}
			else if(line[i] == ']')
			{
				--depth;
				++i;
			}
			else if(isdigit(line[i]))
			{
				string valstr;
				while(i < line.size() && isdigit(line[i]))
				{
					valstr.push_back(line[i]);
					++i;
				}
				//cout << "got valstr " << valstr << endl;
				LL val = stoll(valstr);
				++allNodesCnt;
				val = val << depth;
				cnt[val]++;
			}
			else
			{
				++i;
			}
		}

		int ans = -1;

		for(auto p : cnt)
		{
			ans = max(ans, p.second);
		}

		ans = allNodesCnt - ans;
		cout << ans << endl;
	}
	return 0;
}