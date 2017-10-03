/*
Given an adjacency matrix representation of a graph g having 0 based index your task is to complete the function isBipartite which returns true if the graph is a bipartite graph else returns false.

Input:
The first line of input contains an integer T denoting the no of test cases. Then T test cases follow. Each test case contains an integer v denoting the no of vertices of the graph then in the next line are v*v space separated values of the adjacency matrix representation of the graph g.

Output:
For each test case in a new line output will be 1 if the graph is bipartite else 0.

Constraints:
1<=T<=100
1<=v<=15
0<=g[][]<=1

Example(To be used only for expected output):
Input:
2
4
0 1 0 1 1 0 1 0 0 1 0 1 1 0 1 0
3
0 1 0 0 0 1 1 0 0
Output:
1
0

*/

/*
Please note that it's Function problem i.e.
you need to write your solution in the form of Function(s) only.
Driver Code to call/invoke your function would be added by GfG's Online Judge.*/


/*The function takes an adjacency matrix representation of the graph (g)
and an integer(v) denoting the no of vertices as its arguments.
You are required to complete below method */
bool isBipartite(int G[][MAX],int V)
{
     //Your code here
	vector<int> colors(V, -1);

	
}