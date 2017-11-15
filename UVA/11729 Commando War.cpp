/*

*/

#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;


struct Job
{
	Job(int execute, int brief)
		:execute(execute), brief(brief)
	{

	}

	int execute;
	int brief;
};

int main()
{
	int n;

	int test_id = 1;

	while(scanf("%d", &n) == 1 && n)
	{
		vector<Job> jobs;
		for(int i = 0; i < n; ++i)
		{
			int b;
			int j;
			scanf("%d %d", &b,&j);

			jobs.push_back(Job(j, b));
		}

		sort(jobs.begin(), jobs.end(), [](const Job & l, const Job & r)
		{
			return l.execute > r.execute; 
		});

		int cur = 0;

		int ans = 0;

		for(int k = 0; k < jobs.size(); ++k)
		{
			cur += jobs[k].brief;
			ans = max(ans, cur + jobs[k].execute);
		}

		cout << "Case " << test_id << ": " << ans << endl;

		++test_id;
	}	
	return 0;
}