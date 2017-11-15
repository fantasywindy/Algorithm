/*
10129 Play on Words
Some of the secret doors contain a very interesting word puzzle. The team of archaeologists has to solve
it to open that doors. Because there is no other way to open the doors, the puzzle is very important
for us.
There is a large number of magnetic plates on every door. Every plate has one word written on
it. The plates must be arranged into a sequence in such a way that every word begins with the same
letter as the previous word ends. For example, the word ‘acm’ can be followed by the word ‘motorola’.
Your task is to write a computer program that will read the list of words and determine whether it
is possible to arrange all of the plates in a sequence (according to the given rule) and consequently to
open the door.
Input
The input consists of T test cases. The number of them (T) is given on the first line of the input file.
Each test case begins with a line containing a single integer number N that indicates the number of
plates (1 ≤ N ≤ 100000). Then exactly N lines follow, each containing a single word. Each word
contains at least two and at most 1000 lowercase characters, that means only letters ‘a’ through ‘z’ will
appear in the word. The same word may appear several times in the list.
Output
Your program has to determine whether it is possible to arrange all the plates in a sequence such that
the first letter of each word is equal to the last letter of the previous word. All the plates from the
list must be used, each exactly once. The words mentioned several times must be used that number of
times.
If there exists such an ordering of plates, your program should print the sentence ‘Ordering is
possible.’. Otherwise, output the sentence ‘The door cannot be opened.’
Sample Input
3
2
acm
ibm
3
acm
malform
mouse
2
ok
ok
Sample Output
The door cannot be opened.
Ordering is possible.
The door cannot be opened.
*/

#include <vector>
#include <iostream>
#include <string>
#include <cstring>


using namespace std;

int out[26];

int in[26];

vector<int> G[26];


void dfs(int i, vector<bool> & visited)
{
	visited[i] = true;

	for(auto j : G[i])
	{
		if(visited[j] == false)
		{
			dfs(j, visited);
		}
	}
}

bool isConnected()
{
	vector<bool> visited(26, false);

	for(int i = 0; i < 26; ++i)
	{
		if((out[i] != 0 || in[i] != 0) && visited[i] == false)
		{
			dfs(i, visited);
			break;
		}
	}

	for(int i = 0; i < 26; ++i)
	{
		if((out[i] != 0 || in[i] != 0) && visited[i] == false)
		{
			return false;
		}
	}

	return true;
}


void test(int t)
{

	memset(out, 0, sizeof(out));
	memset(in, 0, sizeof(in));
	for(int i = 0; i < 26; ++i)
	{
		G[i].clear();
	}

	int n;
	cin >> n;

	string plate;
	for(int p = 0; p < n; ++p)
	{
		cin >> plate;

		char s = plate.front();
		char d = plate.back();

		++out[s - 'a'];

		++in[d - 'a'];

		G[s - 'a'].push_back(d - 'a');
		G[d - 'a'].push_back(s - 'a');
	}

	bool canConnect = false;
	if(isConnected() == false)
	{
		canConnect = false;
	}
	else
	{
		//see if the degree satisfy

		int diffCnt = 0;

		int outGTin = 0;

		int inGTout = 0;

		for(int i = 0; i < 26; ++i)
		{
			if(out[i] == in[i])
			{
				continue;
			}
			else
			{
				++diffCnt;
				if(diffCnt > 2)
				{
					canConnect = false;
					break;
				}

				if(abs(out[i] - in[i]) != 1)
				{
					canConnect = false;
					break;
				}

				if(out[i] > in[i])
				{
					outGTin = 1;
				}

				if(in[i] > out[i])
				{
					inGTout = 1;
				}

			}
		}


		if(diffCnt == 2)
		{
			if(outGTin == 1 && inGTout == 1)
			{
				canConnect = true;
			}
			else
			{
				canConnect = false;
			}
		}
		else if(diffCnt == 0)
		{
			canConnect = true;
		}
		else
		{
			canConnect = false;
		}

	}

	//cout << t << " ";

	if(canConnect == true)
	{
		cout << "Ordering is possible." << endl;
	}
	else
	{
		cout << "The door cannot be opened." << endl;
	}
}

int main()
{
	ios_base::sync_with_stdio(false);
	int t;
	cin >> t;

	for(int t1 = 0; t1 < t; ++t1)
	{
		test(t1);
	}

	return 0;
}