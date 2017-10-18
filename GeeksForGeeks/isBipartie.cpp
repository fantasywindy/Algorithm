/*
Please note that it's Function problem i.e.
you need to write your solution in the form of Function(s) only.
Driver Code to call/invoke your function would be added by GfG's Online Judge.*/


/*The function takes an adjacency matrix representation of the graph (g)
and an integer(v) denoting the no of vertices as its arguments.
You are required to complete below method *

1<=T<=100
1<=v<=15
0<=g[][]<=1

*/

bool dfs(int G[][MAX],int V, int i, vector<int> & colors, int color)
{
    colors[i] = color;

    if(G[i][i] == 1)
    {
        return false;
    }

    for(int j = 0; j < V; ++j)
    {
        if(i != j && G[i][j] == 1)
        {
            if(colors[j] == -1)
            {
                if(dfs(G, V, j, colors, color ^ 1) == false)
                {
                    return false;
                }
            }
            else if(colors[j] == colors[i])
            {
                return false;
            }
        }
    }

    return true;
}

bool isBipartite(int G[][MAX],int V)
{
     //Your code here
    vector<int> colors(V, -1);

    for(int i = 0; i < V; ++i)
    {
        if(colors[i] == -1 && dfs(G, V, i, colors, 0) == false)
        {
            return false;
        }
    }

    return true;
}

