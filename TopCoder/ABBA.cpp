/*
Problem Statement
One day, Jamie noticed that many English words only use the letters A and B. Examples of such words include "AB" (short for abdominal), "BAA" (the noise a sheep makes), "AA" (a type of lava), and "ABBA" (a Swedish pop sensation).


Inspired by this observation, Jamie created a simple game. You are given two s: initial and target. The goal of the game is to find a sequence of valid moves that will change initial into target. There are two types of valid moves:

Add the letter A to the end of the string.
Reverse the string and then add the letter B to the end of the string.
Return "Possible" (quotes for clarity) if there is a sequence of valid moves that will change initial into target. Otherwise, return "Impossible".

Definition
Class: ABBA
Method: canObtain
Parameters: string, string
Returns: string
Method signature: string canObtain(string initial, string target)
(be sure your method is public)
*/

#include <unordered_map>
#include <string>
#include <algorithm>

using namespace std;

class ABBA
{
public:
	string canObtain(string initial, string target)
	{
		bool ret = dfs(initial, target);

		return ret ? "Possible" : "Impossible";
	}

	bool dfs(const string & initial, const string & target)
	{
		if(initial.size() > target.size())
		{
			return false;
		}

		if(initial == target)
		{
			return true;
		}

		if(target.back() == 'A')
		{
			if(dfs(initial, target.substr(0, target.size() - 1)))
			{
				return cache[initial][target] = true;
			}
		}

		if(target.back() == 'B')
		{
			string r_target = target.substr(0, target.size() - 1);
			reverse(r_target.begin(), r_target.end());
			if(dfs(initial, r_target))
			{
				return cache[initial][target] = true;
			}
		}

		return cache[initial][target] = false;
	}

private:
	unordered_map<string, unordered_map<string, bool>> cache;
};

