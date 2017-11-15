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
*/

#include <iostream>
using namespace std;


bool isOne(int val, int bit)
{
	return (val & (1 << bit)) != 0;
}

int main()
{
	int lines;
	cin >> lines;

	int start1 = 0;
	int start2 = 0x3FF;

	int end1 = start1;
	int end2 = start2;


	for(int line = 1; line <= lines; ++line)
	{
		char c;
		int val;
		cin >> c >> val;

		if(c == '|')
		{
			end1 = end1 | val;
			end2 = end2 | val;
		}
		else if(c == '&')
		{
			end1 = end1 & val;
			end2 = end2 & val;
		}
		else
		{
			end1 = end1 ^ val;
			end2 = end2 ^ val;
		}
	}

	int andval = 0;
	int orval = 0;
	int xorval = 0;

	for(int i = 0; i < 10; ++i)
	{
		//0->0  1->0
		if(isOne(end1, i) == false && isOne(end2, i) == false)
		{
			andval = andval | (1 << i);
			orval = orval | (1 << i);
			xorval = xorval | (1 << i);
		}
		//0->1 1->1
		else if(isOne(end1, i) == true && isOne(end2, i) == true)
		{
			andval = andval | (1 << i);
			orval = orval | (1 << i);
		}
		//0->1 1->0
		else if(isOne(end1, i) == true && isOne(end2, i) == false)
		{
			andval = andval | (1 << i);
			xorval = xorval | (1 << i);
		}
		//0->0 1->1
		else if(isOne(end1, i) == false && isOne(end2, i) == true)
		{
			andval = andval | (1 << i);
		}
	}

	cout << 3 << endl;

	cout << "& " << andval << endl;
	cout << "| " << orval << endl;
	cout << "^ " << xorval << endl;
	return 0;


}