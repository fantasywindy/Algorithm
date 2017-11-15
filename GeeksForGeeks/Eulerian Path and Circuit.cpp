/*
Eulerian Path is a path in graph that visits every edge exactly once. 
Eulerian Circuit is an Eulerian Path which starts and ends on the same vertex. 
The task is to find that there exists the Euler Path or circuit or none.

Input:
First line consists of test cases T. 
First line of every test case consists of 2 integers V and E, denoting the number of vertex and edges. 
Second line of every test case consists of 2*E spaced integers denoting the edge connected.

Output:
Return the int value to print 1 if Euler path exists print 2 if Euler cycle exists else 0.

Constraints:
1<=T<=100
1<=V,E<=100

Example:
Input:
1
5 6
1 0 0 2 2 1 0 3 3 4
Output:
1
*/

/*
Please note that it's Function problem i.e.
you need to write your solution in the form of Function(s) only.
Driver Code to call/invoke your function would be added by GfG's Online Judge.*/


/*Complete the function below*/


bool Graph::isConnected()
{
	bool visited[V];

	memset(visited, 0, sizeof(visited));
	
	DFSUtil(0, visited);

	for(int i = 0; i < V; ++i)
	{
		if(visited[i] == false)
		{
			return false;
		}
	}

	return true;
}

int isEulerianUtil(list<int> * adj, int V)
{
	int oddDegreeCnt = 0;

	for(int i = 0; i < V; ++i)
	{
		int degree = adj[i].size();
		if(degree % 2 == 0)
		{

		}
		else
		{
			++oddDegreeCnt;
		}
	}

	if(oddDegreeCnt == 0)
	{
		return 2;
	}
	else if(oddDegreeCnt == 2)
	{
		return 1;
	}

	return 0;
}

int Graph::isEulerian()
{
	//first let's see if the graph is connected
	bool connected = isConnected();

	if(connected == false)
	{
		return 0;
	}

	return isEulerianUtil(adj, V);

}











