#include <string>
#include <iostream>
using namespace std;

bool isCons(char c)
{
	static string vowels = "aeiou";
	return vowels.find(c) == string::npos;
}

bool isSame(string str, int i)
{
	return str[i-2] == str[i-1] && str[i-1] == str[i];
}

int main()
{
	ios_base::sync_with_stdio(false);
	string str;
	cin >> str;

	int i = 0;

	int n = str.size();

	string vowels = "aeiou";

	int cons_cnt = 0;

	string ret = "";

	while(i < n)
	{
		if(isCons(str[i]))
		{
			++cons_cnt;
			//cout << str[i] << " " << cons_cnt << endl;

			if(cons_cnt >= 3)
			{
				if(isSame(str, i))
				{
					//it is ok
					ret.push_back(str[i]);
					++i;
				}
				else
				{
					//cannot use this char
					ret.push_back(' ');
					ret.push_back(str[i]);
					++i;
					cons_cnt = 1;
				}
			}
			else
			{
				ret.push_back(str[i]);
				++i;
			}
		}
		else
		{
			ret.push_back(str[i]);
			++i;
			cons_cnt = 0;
		}
	}

	cout << ret << endl;

	return 0;
}