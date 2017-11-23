#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <cstdio>
#include <cstring>

using namespace std;


const int MAX_N = 200 + 5;

vector<int> subs[MAX_N];

int n;

const int MAX_C = 100 + 5;

char employee[MAX_C];

char boss[MAX_C];

unordered_map<string, int> nameToIdxMap;

int getImployeeIdx(string name)
{
	int sz = nameToIdxMap.size();
	if(nameToIdxMap.find(name) == nameToIdxMap.end())
	{
		nameToIdxMap[name] = sz;
		//cout << "add " << name << " idx " << sz << endl;
		return sz;
	}
	else
	{
		return nameToIdxMap[name];
	}
}

void addEmployee(string name, string boss)
{
	int idx = getImployeeIdx(name);

	int boss_idx = getImployeeIdx(boss);

	subs[boss_idx].push_back(idx);
}



//g[i] the maximum set has i

//g_unique[i] the uniqueness of g[i]

//f[i] the maximum set does not has i

//f_unique[i] the uniqueness of f[i]

int g[MAX_N];

int g_unique[MAX_N];

int f[MAX_N];

int f_unique[MAX_N];


void dfs(int i)
{
	if(subs[i].size() == 0)
	{
		g[i] = 1;
		f[i] = 0;
		g_unique[i] = 1;
		f_unique[i] = 1;
		return;
	}

	int invite_self = 1;
	int unique_invite_self = 0;
	int not_invite_self = 0;
	int unique_not_invite_self = 0;
	for(int subord : subs[i])
	{
		//invite i
		dfs(subord);
		invite_self += f[subord];
		unique_invite_self += f_unique[subord];
		if(f[subord] == g[subord])
		{
			not_invite_self += f[subord];
		}
		else
		{
			if(f[subord] > g[subord])
			{
				not_invite_self += f[subord];
				unique_not_invite_self += f_unique[subord];
			}
			else
			{
				not_invite_self += g[subord];
				unique_not_invite_self += g_unique[subord];
			}
		}


	}

	f[i] = not_invite_self;
	g[i] = invite_self;

	g_unique[i] = (unique_invite_self == subs[i].size()) ? 1 : 0;
	f_unique[i] = (unique_not_invite_self == subs[i].size()) ? 1 : 0;
}

void solution()
{
	dfs(0);
	int g_max = g[0];
	int f_max = f[0];

	int g_only = g_unique[0];

	int f_only = f_unique[0];

	int max_val = max(g_max, f_max);
	int only = 0;
	if(g_max == f_max)
	{
		only = 0;
	}
	else
	{
		if(g_max > f_max)
		{
			only = g_only;
		}
		else
		{
			only = f_only;
		}
	}

	cout << max_val << " " << (only == 1 ? "Yes" : "No") << endl;

	
}

void reset()
{

	for(auto & vec : subs)
	{
		vec.clear();
	}

	memset(employee, 0, sizeof(employee));

	memset(boss, 0, sizeof(boss));

	nameToIdxMap.clear();

	memset(g, 0, sizeof(g));

	memset(g_unique, 0, sizeof(g_unique));

	memset(f, 0, sizeof(f));

	memset(f_unique, 0, sizeof(f_unique));

}

int main()
{
	while(scanf("%d", &n) == 1 && n)
	{
		reset();
		scanf("%s", boss);
		string boss_str = boss;
		getImployeeIdx(boss_str);

		for(int i = 1; i <= n - 1; ++i)
		{
			scanf("%s%s", employee, boss);
			string boss_str = boss;
			string em_str = employee;
			addEmployee(em_str, boss_str);
		}

		// for(int k = 0; k <= n; ++k)
		// {
		// 	cout << " k " << k << endl;
		// 	for(auto item : subs[k])
		// 	{
		// 		cout << item << " ";
		// 	}
		// 	cout << endl;
		// }

		solution();
	}

	return 0;
}