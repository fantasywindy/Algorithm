/*
Petya learned a new programming language CALPAS. A program in this language always takes one non-negative integer and returns one non-negative integer as well.

In the language, there are only three commands: apply a bitwise operation AND, OR or XOR with a given constant to the current integer. A program can contain an arbitrary sequence of these operations with arbitrary constants from 0 to 1023. When the program is run, all operations are applied (in the given order) to the argument and in the end the result integer is returned.

Petya wrote a program in this language, but it turned out to be too long. Write a program in CALPAS that does the same thing as the Petya's program, and consists of no more than 5 lines. Your program should return the same integer as Petya's program for all arguments from 0 to 1023.

Input
The first line contains an integer n (1 ≤ n ≤ 5·105) — the number of lines.

Next n lines contain commands. A command consists of a character that represents the operation ("&", "|" or "^" for AND, OR or XOR respectively), and the constant xi 0 ≤ xi ≤ 1023.

Output
Output an integer k (0 ≤ k ≤ 5) — the length of your program.

Next k lines must contain commands in the same format as in the input.

Examples
input
3
| 3
^ 2
| 1
output
2
| 3
^ 2
input
3
& 1
& 3
& 5
output
1
& 1
input
3
^ 1
^ 2
^ 3
output
0
Note
You can read about bitwise operations in https://en.wikipedia.org/wiki/Bitwise_operation.

Second sample:

Let x be an input of the Petya's program. It's output is ((x&1)&3)&5 = x&(1&3&5) = x&1. So these two programs always give the same outputs.
*/

#include <iostream>
#include <vector>

using namespace std;

int main()
{
	ios_base::sync_with_stdio(false);

	int ops;

	cin >> ops;

	int v1_before = 0x0;
	int v2_before = 0b1111111111;

	int v1_after = v1_before;
	int v2_after = v2_before;


	for(int i = 0; i < ops; ++i)
	{
		char c;
		int val;

		cin >> c >> val;

		if(c == '|')
		{
			v1_after |= val;
			v2_after |= val;
		}
		else if(c == '&')
		{
			v1_after &= val;
			v2_after &= val;
		}
		else
		{
			v1_after ^= val;
			v2_after ^= val;
		}
	}

	vector<int> bits1;  // 0->0 1->0
	vector<int> bits2;  // 0->0 1->1
	vector<int> bits3;  // 0->1 1->0
	vector<int> bits4;  // 0->1 1->1

	for(int i = 0; i < 10; ++i)
	{
		int v1_bit = (v1_after & (1 << i)) >> i;

		int v2_bit = (v2_after & (1 << i)) >> i;

		if(v1_bit == 0 && v2_bit == 0)
		{
			bits1.push_back(i);
		}
		else if(v1_bit == 0 && v2_bit == 1)
		{
			bits2.push_back(i);
		}
		else if(v1_bit == 1 && v2_bit == 0)
		{
			bits3.push_back(i);
		}
		else if(v1_bit == 1 && v2_bit == 1)
		{
			bits4.push_back(i);
		}
	}

	int mask_a = 0;
	int mask_b = 0;
	int mask_c = 0;

	//0->0 1->0
	//&0 |0 ^0



	//0->0 1->1
	//&1 |0 ^0

	for(auto i : bits2)
	{
		mask_a |= (1 << i);
	}


	//0->1 1->0
	//&1 |0 ^1

	for(auto i : bits3)
	{
		mask_a |= (1 << i);

		mask_c |= (1 << i);
	}

	//0->1 1->1
	//&1 |1 ^0

	for(auto i : bits4)
	{
		mask_a |= (1 << i);
		mask_b |= (1 << i);
	}

	//int cnt = 0;
	// if(mask_a != 0)
	// {
	// 	++cnt;
	// }

	// if(mask_b != 0)
	// {
	// 	++cnt;
	// }

	// if(mask_c != 0)
	// {
	// 	++cnt;
	// }

	cout << 3 << endl;

//	if(mask_a != 0)
//	{
		cout << '&' << " " << mask_a << endl;
//	}

//	if(mask_b != 0)
//	{
		cout << "|" << " " << mask_b << endl;
//	}

//	if(mask_c != 0)
//	{
		cout << "^" << " " << mask_c << endl;
 //	}

 	return 0;
}