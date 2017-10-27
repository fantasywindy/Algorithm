/*
 There are n cities numbered from 1 to n in Berland. Some of them are connected by two-way roads. Each road has its own length — an integer number from 1 to 1000. It is known that from each city it is possible to get to any other city by existing roads. Also for each pair of cities it is known the shortest distance between them. Berland Government plans to build k new roads. For each of the planned road it is known its length, and what cities it will connect. To control the correctness of the construction of new roads, after the opening of another road Berland government wants to check the sum of the shortest distances between all pairs of cities. Help them — for a given matrix of shortest distances on the old roads and plans of all new roads, find out how the sum of the shortest distances between all pairs of cities changes after construction of each road.
 
 Input
 The first line contains integer n (2 ≤ n ≤ 300) — amount of cities in Berland. Then there follow n lines with n integer numbers each — the matrix of shortest distances. j-th integer in the i-th row — di, j, the shortest distance between cities i and j. It is guaranteed that di, i = 0, di, j = dj, i, and a given matrix is a matrix of shortest distances for some set of two-way roads with integer lengths from 1 to 1000, such that from each city it is possible to get to any other city using these roads.
 
 Next line contains integer k (1 ≤ k ≤ 300) — amount of planned roads. Following k lines contain the description of the planned roads. Each road is described by three space-separated integers ai, bi, ci (1 ≤ ai, bi ≤ n, ai ≠ bi, 1 ≤ ci ≤ 1000) — ai and bi — pair of cities, which the road connects, ci — the length of the road. It can be several roads between a pair of cities, but no road connects the city with itself.
 
 Output
 Output k space-separated integers qi (1 ≤ i ≤ k). qi should be equal to the sum of shortest distances between all pairs of cities after the construction of roads with indexes from 1 to i. Roads are numbered from 1 in the input order. Each pair of cities should be taken into account in the sum exactly once, i. e. we count unordered pairs.
 */
#include <vector>
#include <iostream>


using namespace std;

#include <fstream>

//#define LOCAL_FILE
#ifdef LOCAL_FILE
fstream fs("/Users/ice/Documents/codeforce/input.txt");
#define input fs
#else
#define input cin

#endif

int floyd(vector<vector<long long> > & graph, int p, int q)
{
    int n = graph.size();
    
    for(int i = 0; i < n; ++i)
    {
        for(int j = 0; j < n; ++j)
        {
            if(graph[i][p] + graph[p][q] + graph[q][j] < graph[i][j])
            {
                graph[i][j] = graph[i][p] + graph[p][q] + graph[q][j];
            }
            
            if(graph[i][q] + graph[q][p] + graph[p][j] < graph[i][j])
            {
                graph[i][j] =graph[i][q] + graph[q][p] + graph[p][j];
            }
        }
    }
    
//    for(int k = 0; k < n; ++k)
//    {
//        for(int i = 0; i < n; ++i)
//        {
//            for(int j = 0; j < n; ++j)
//            {
//                if(graph[i][k] + graph[k][j] < graph[i][j])
//                {
//                    graph[i][j] = graph[i][k] + graph[k][j];
//                }
//            }
//        }
//    }
    
    
    long long sum = 0;
    for(int i = 0; i < n; ++i)
    {
        for(int j = 0; j < i; ++j)
        {
            sum += graph[i][j];
        }
    }
    
    return sum;
}

int main()
{
    ios_base::sync_with_stdio(false);
    int n;
    input >> n;
    
    vector<vector<long long> > graph(n, vector<long long>(n, 0));
    
    
    for(int i = 0; i < n; ++i)
    {
        for(int j = 0; j < n; ++j)
        {
            input >> graph[i][j];
        }
    }
    
    int roads = 0;
    input >> roads;
    
    long long lastOutput = floyd(graph, 0, 1);
    
    for(int road = 1; road <= roads; ++road)
    {
        long long a, b, c;
        
        input >> a >> b >> c;
        
        
        if(c < graph[a-1][b-1])
        {
            graph[a-1][b-1] = c;
            graph[b-1][a-1] = c;
            lastOutput = floyd(graph, a - 1, b - 1);
        }
        else
        {
            //do nothing;
        }
       
        cout << lastOutput << endl;
        
    }
    
    cout << endl;
    
    return 0;
}