/*
5 5
1 2 5
1 3 2
3 4 1
1 4 6
3 5 5
*/

#include <iostream>
#include <vector>
#include <utility>
using namespace std;

int main()
{
	ios_base::sync_with_stdio(false);
	int N, M;
	cin >> N >> M;

	vector<pair<pair<int,int>, int> > edges(M);
	for(int i = 0; i < M; ++i)
	{
		cin >> edges[i].first.first >> edges[i].first.second >> edges[i].second;
	}

	vector<long long> dists(N + 1, 2e9 + 5);
	
	dists[1] = 0;

	for(int loop = 0; loop < (N - 1); ++loop)
	{
		bool changed = false;
		for(auto edge : edges)
		{
			int start = edge.first.first;
			int end = edge.first.second;
			int weight = edge.second;

			if(dists[start] + weight < dists[end])
			{
				dists[end] = dists[start] + weight;
				changed = true;
			}
		}

		if(changed == false)
		{
			break;
		}
	}

	for(int i = 2; i <= N; ++i)
	{
		cout << (dists[i] == (2e9 + 5) ? 1e9 : dists[i]) << " ";
	}

	return 0;
}Bel