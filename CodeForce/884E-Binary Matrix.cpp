#include <vector>
#include <iostream>
using namespace std;

class UnionFind
{
public:
UnionFind(int n)
	{
		p.assign(n, -1);
		for(int i = 0; i < n; ++i)
		{
			p[i] = i;
		}
	}

	bool connected(int i, int j)
	{
		return find(i) == find(j);
	}

	int find(int i)
	{
		int root = i;
		while(p[root] != root)
		{
			root = p[root];
		}

		while(i != root)
		{
			int pi = p[i];
			p[i] = root;
			i = pi;
		}

		return root;
	}

	void merge(int i, int j)
	{
		int pi = find(i);
		int pj = find(j);

		p[pi] = pj;

	}
private:
	vector<int> p;

};

int main()
{
	ios_base::sync_with_stdio(false);
	int n;
	int m;

	cin >> n >> m;

	UnionFind row1(m);
	vector<int> a1(m);

	int ret = 0;

	for(int i = 0; i < n; ++i)
	{
		vector<int> a2(m);

		string s;
		cin >> s;


		for(int k = 0; k < s.size(); ++k)
		{
			char c = s[k];

			int val = 0;
			if(c >= '0' && c <= '9')
			{
				val = c - '0';
			}
			else if(c >= 'A' && c <= 'F')
			{
				val = c - 'A' + 10;
			}

			for(int bit = 0; bit < 4; ++bit)
			{
				a2[4 * k + bit] = ((val & (1 << (3 - bit))) == 0) ? 0 : 1;
			}
		}

		//visited stands for the visited status of row1, if -1 means this col has not been connected by any element from row2
		//else it means the one of the col in row2 that connects to the same col in row1

		UnionFind row2(m);

		vector<int> visited(m, -1);

		for(int j = 0; j < m; ++j)
		{
			if(a2[j] == 1)
			{
				if(a1[j] == 1)
				{
					int fj = row1.find(j);

					if(visited[fj] == -1)
					{
						visited[fj] = j;
					}
					else
					{
						row2.merge(j, visited[fj]);
					}
				}
			}
		}

		//row1 will be discarded, so those who doesn't have any connections to row2 should be put into result
		for(int j = 0; j < m; ++j)
		{
			if(a1[j] == 1 && visited[row1.find(j)] == -1)
			{
				++ret;
				//to avoid to be counted again
				visited[row1.find(j)] = -2;
			}
		}

		for(int j = 1; j < m; ++j)
		{
			if(a2[j] == 1 && a2[j-1] == 1)
			{
				row2.merge(j, j - 1);
			}
		}

		row1 = row2;
		a1 = a2;

	}

	vector<bool> visited(m, false);
	for(int j = 0; j < m; ++j)
	{
		if(a1[j] == 1 && visited[row1.find(j)] == false)
		{
			++ret;
			visited[row1.find(j)] = true;
		}
	}

	cout << ret << endl;
	return 0;

}