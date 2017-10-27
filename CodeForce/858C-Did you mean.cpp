
#include <iostream>
#include <vector>

using namespace std;

int main()
{
	string str;
	cin >> str;

	int n = str.size();

	string vowels = "aeiou";

	vector<int> svec;

	int cons = 0;
	int j = 0;

	while(j < n)
	{
		if(vowels.find(str[j]) != string::npos)
		{
			//vowel
			cons = 0;
			++j;
		}
		else
		{
			//not vowel, constant
			if(cons != 3)
			{
				++cons;
			}
			else
			{
				//no more cons add
			}

			if(cons == 3)
			{
				//to see if three in a row and they are not different
				if(str[j] == str[j-1] && str[j-1] == str[j-2])
				{
					//three in a row is same, then go on
					++j;
				}
				else
				{
					//not valid, break, need to add space here
					svec.push_back(j);
					cons = 0;
				}
			}
			else
			{
				++j;
			}

		}

	}
	string ret = "";

	int start = 0;

	for(auto sp : svec)
	{
		ret += str.substr(start, sp - start);
		start = sp;
	}

	cout << ret << endl;

	return 0;
}