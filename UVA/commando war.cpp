#include <iostream>
#include <cstdio>
#include <cstring> 
#include <vector>
#include <algorithm>

using namespace std;


struct Soldier
{
	Soldier(int b = 0, int j = 0)
	:b(b), j(j)
	{

	}

	int b, j;
};

vector<Soldier> vec;

void solution(int test_id)
{
	int cur = 0;
	int finish = 0;

	for(auto item : vec)
	{
		int b = item.b;
		int j = item.j;

		cur += b;

		finish = max(finish, cur + j);
	}

	cout << "Case " << test_id << ": " << finish << endl;
}

void reset()
{
	vec.clear();
}

int main()
{
	int N;

	int test_id = 1;

	while(scanf("%d", &N) == 1 && N)
	{
		reset();

		int b, j;
		for(int i = 0; i < N; ++i)
		{
			scanf("%d%d", &b, &j);
			vec.push_back(Soldier(b, j));
		}

		sort(vec.begin(), vec.end(), [](const Soldier & l, const Soldier & r)
		{
			return l.j > r.j;
		});

		solution(test_id);

		++test_id;
	}

	return 0;
}