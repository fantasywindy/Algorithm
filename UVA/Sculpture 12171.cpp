#include <vector>
#include <queue>
#include <utility>
#include <iostream>
#include <set>
#include <unordered_map>
#include <algorithm>
#include <queue>
#include <cstring>



using namespace std;

#include <fstream>

//#define LOCAL_FILE
#ifdef LOCAL_FILE
fstream fs("/Users/ice/Documents/codeforce/input.txt");
#define input fs
#else
#define input cin

#endif


const int maxn = 50 + 5;
const int maxc = 1000 + 1;

int n;
int x_left[maxn];
int y_left[maxn];
int z_left[maxn];

int x_right[maxn];
int y_right[maxn];
int z_right[maxn];

int nx,ny,nz;

int xs[maxn * 2];
int ys[maxn * 2];
int zs[maxn * 2];

int color[maxn * 2][maxn * 2][maxn * 2];


const int dx[] = {1,-1,0,0,0,0};
const int dy[] = {0,0,1,-1,0,0};
const int dz[] = {0,0,0,0,1,-1};



struct Cell
{
    int x, y, z;
    
    Cell(int x = 0, int y = 0, int z = 0)
    :x(x), y(y), z(z)
    {
        
    }
    
    bool valid() const
    {
        return x >= 0 && x <= nx - 2 && y >= 0 && y <= ny - 2 && z >= 0 && z <= nz - 2;
    }
    
    bool isSolid() const
    {
        return color[x][y][z] == 1;
    }
    
    bool isVisitedAir() const
    {
        return color[x][y][z] == 2;
    }
    
    void setAirVisited() const
    {
        color[x][y][z] = 2;
    }
    
    Cell neighbor(int dir) const
    {
        return Cell(x + dx[dir], y + dy[dir], z + dz[dir]);
    }
    
    int volume() const
    {
        return (xs[x + 1] - xs[x]) * (ys[y + 1] - ys[y]) * (zs[z + 1] - zs[z]);
    }
    
    int area(int dir) const
    {
        if(dx[dir] != 0)
        {
            return (ys[y + 1] - ys[y]) * (zs[z + 1] - zs[z]);
        }
        else if(dy[dir] != 0)
        {
            return (xs[x + 1] - xs[x]) * (zs[z + 1] - zs[z]);
        }
        else
        {
            return (xs[x + 1] - xs[x]) * (ys[y + 1] - ys[y]);
        }
    }
};

void discretize(int * x, int & n)
{
    sort(x, x + n);
    n = unique(x, x + n) - x;
}


void floodfill(int & volume, int & area)
{
    volume = 0;
    area = 0;
    
    Cell c;
    c.setAirVisited();
    
    queue<Cell> q;
    
    q.push(c);
    
    while(!q.empty())
    {
        Cell cur = q.front();
        q.pop();
        
        volume += cur.volume();
        
        for(int dir = 0; dir < 6; ++dir)
        {
            Cell neighbor = cur.neighbor(dir);
            
            if(neighbor.valid() == false)
            {
                continue;
            }
            
            if(neighbor.isSolid())
            {
                area += cur.area(dir);
            }
            else if(neighbor.isVisitedAir() == false)
            {
                neighbor.setAirVisited();
                q.push(neighbor);
            }
        }
    }
    
    volume = maxc * maxc * maxc - volume;
}

int discrete_pos(int v, int * arr, int n)
{
    return lower_bound(arr, arr + n, v) - arr;
}

void test()
{
    int n;
    input >> n;
    
    xs[0] = ys[0] = zs[0] = 0;
    xs[1] = ys[1] = zs[1] = maxc;
    
    nx = ny = nz = 2;
    
    for(int i = 0; i < n; ++i)
    {
        input >> x_left[i] >> y_left[i] >> z_left[i] >> x_right[i] >> y_right[i] >> z_right[i];
        
        x_right[i] += x_left[i];
        y_right[i] += y_left[i];
        z_right[i] += z_left[i];
        
        xs[nx++] = x_left[i];
        xs[nx++] = x_right[i];
        
        ys[ny++] = y_left[i];
        ys[ny++] = y_right[i];
        
        zs[nz++] = z_left[i];
        zs[nz++] = z_right[i];
    }
    
    discretize(xs, nx);
    discretize(ys, ny);
    discretize(zs, nz);
    
    
    memset(color, 0, sizeof(color));
    
    for(int i = 0; i < n; ++i)
    {
        int X0_POS = discrete_pos(x_left[i], xs, nx);
        int X1_POS = discrete_pos(x_right[i], xs, nx);
        
        int Y0_POS = discrete_pos(y_left[i], ys, ny);
        int Y1_POS = discrete_pos(y_right[i], ys, ny);
        
        int Z0_POS = discrete_pos(z_left[i], zs, nz);
        int Z1_POS = discrete_pos(z_right[i], zs, nz);
        
        for(int X = X0_POS; X < X1_POS; ++X)
        {
            for(int Y = Y0_POS; Y < Y1_POS; ++Y)
            {
                for(int Z = Z0_POS; Z < Z1_POS; ++Z)
                {
                    color[X][Y][Z] = 1;
                }
            }
        }
    }
    
    int volume, area;
    
    floodfill(volume, area);
    
    cout << area << " " << volume << endl;
}

int main()
{
    ios_base::sync_with_stdio(false);
    int t;
    
    input >> t;
    
    for(int t1 = 0; t1 < t; ++t1)
    {
        test();
    }
    
    return 0;
    
}
