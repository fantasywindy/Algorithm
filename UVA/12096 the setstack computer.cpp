int n;

#include <set>
#include <map>
#include <vector>
#include <stack>
#include <iostream>
#include <algorithm>



using namespace std;


char op[10];

#define ALL(x) x.begin(), x.end()
#define INS(x) inserter(x, x.begin())

class SetStack
{
public:
	typedef set<int> Set;
	map<Set, int> m;
	vector<Set> v;

	stack<int> s;

	SetStack()
	{

	}

	int id(Set x)
	{
		if(m.count(x) != 0)
		{
			return m[x];
		}
		else
		{
			int sz = v.size();
			m[x] = sz;
			v.push_back(x);
			return sz;
		}
	}

	void push()
	{
		//cout << "push" << endl;
		s.push(id(Set()));
	}

	void dup()
	{
		//cout << "dup" << endl;
		s.push(s.top());
	}

	void un()
	{
		//cout << "un" << endl;
		auto r = s.top();
		s.pop();
		auto l = s.top();
		s.pop();

		auto lt = v[l];
		auto rt = v[r];
		Set x;
		set_union(ALL(lt), ALL(rt), INS(x));
		s.push(id(x));
	}

	void intersect()
	{
		//cout << "intersect" << endl;
		auto r = s.top();
		s.pop();
		auto l = s.top();
		s.pop();

		auto lt = v[l];
		auto rt = v[r];
		Set x;
		set_intersection(ALL(lt), ALL(rt), INS(x));
		s.push(id(x));
	}

	void add()
	{
		//cout << "add" << endl;
		auto r = s.top();
		s.pop();
		auto l = s.top();
		s.pop();

		auto lt = v[l];
		auto rt = v[r];
		
		Set x = lt;
		x.insert(id(rt));
		s.push(id(x));
	}

	int top()
	{
		auto tp = s.top();
		auto x = v[tp];
		return x.size();
	}

	int size()
	{
		return s.size();
	}

private:

};

int main()
{
	int t;
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d", &n);
		SetStack ss;

		for(int i = 1; i <= n; ++i)
		{
			scanf("%s", op);
			if(op[0] == 'P')
			{
				ss.push();
			}
			else if(op[0] == 'D')
			{
				ss.dup();
			}
			else if(op[0] == 'A')
			{
				ss.add();
			}
			else if(op[0] == 'U')
			{
				ss.un();
			}
			else
			{
				ss.intersect();
			}

			//cout << "cur s has " << ss.size() << endl;
			cout << ss.top() << endl;
		}
		cout << "***" << endl;
	}
	return 0;
}