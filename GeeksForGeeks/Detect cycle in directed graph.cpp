/*
Please note that it's Function problem i.e.
you need to write your solution in the form of Function(s) only.
Driver Code to call/invoke your function would be added by GfG's Online Judge.*/


/*
The structure of the class is as follows 
which contains an integer V denoting the no 
of vertices and a list of adjacency vertices.
class Graph
{
    int V;
    list<int> *adj;
public :
    Graph(int V);
    void addEdge(int v,int w);
    bool isCyclic();
};
*/
/*You are required to complete this method*/

bool hasCycle(int cur, vector<bool> & visited, vector<bool> & onStack, list<int> * adj)
{
	visited[cur] = true;
	onStack[cur] = true;

	for(int next : adj[cur])
	{
		if(visited[next] == false)
		{
			if(hasCycle(cur, visited, onStack, adj) == true)
			{
				return true;
			}
		}
		else 
		{
			if(onStack[next] == true)
			{
				return true;
			}
		}
	}

	onStack[cur] = false;

	return false;
}

bool Graph :: isCyclic()
{
//Your code here
	vector<bool> visited(V, false);
	vector<bool> onStack(V, false);

	for(int i = 0; i < V; ++i)
	{
		if(visited[i] == false)
		{
			if(hasCycle(i, visited, onStack, adj) == true)
			{
				return true;
			}
		}
	}

	return false;
}