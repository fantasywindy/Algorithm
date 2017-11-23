
/*
 
 
 
 */

#include <utility>
#include <vector>
#include <iostream>
#include <algorithm>




#define all(a) (a).begin(), (a).end()
#define sz(a) (int)(a).size()
#define pb push_back

using namespace std;


#include <fstream>

#define LOCAL_FILE
#ifdef LOCAL_FILE
fstream fs("/Users/ice/Documents/codeforce/input.txt");
#define input fs
#else
#define input cin

#endif



struct building
{
    double x0;
    double y0;
    double x1;
    double y1;
    double h;
    int id;
};

bool operator<(const building & l, const building & r)
{
    return l.x0 < r.x0 || (l.x0 == r.x0 && l.y0 < r.y0);
}

bool inRange(vector<building>& buildings, int i, int x)
{
    return buildings[i].x0 <= x && x <= buildings[i].x1;
}

bool visible(vector<building> & buildings, int i, int x)
{
    if(inRange(buildings, i, x) == false)
    {
        return false;
    }
    
    for(int k = 0; k < buildings.size(); ++k)
    {
        if(k == i)
        {
            continue;
        }
        
        if(inRange(buildings, k, x) == true && buildings[k].height >= buildings[i].height && buildings[k].left_y < buildings[i].left_y)
        {
            return false;
        }
    }
    
    return true;
}

void calc(vector<building> & buildings, int test_id)
{
    vector<double> t;
    
    for(auto b : buildings)
    {
        t.push_back(b.left_x);
        t.push_back(b.left_x + b.width);
    }
    
    sort(buildings.begin(), buildings.end());
    
    sort(t.begin(), t.end());
    
    auto it = unique(t.begin(), t.end());
    
    t.erase(it, t.end());
    
    vector<int> vis_building;
    
    //vis_building.push_back(buildings[0].id);
    
    for(int i = 0; i < buildings.size(); ++i)
    {
        bool canSee = false;
        for(int j = 0; j + 1 < t.size(); ++j)
        {
            if(visible(buildings, i, (t[j] + t[j+1]) / 2.0))
            {
                canSee = true;
                break;
            }
        }
        
        if(canSee)
        {
            vis_building.push_back(buildings[i].id);
        }
    }
    
    if(test_id != 1)
    {
        cout << endl;
    }
    
    cout << "For map #" << test_id << ", the visible buildings are numbered as follows:" << endl;
    
    cout << vis_building[0];
    
    for(int i = 1; i < vis_building.size(); ++i)
    {
        cout << " " << vis_building[i];
    }
    
    cout << endl;
}

bool test(int test_id)
{
    int n;
    input >> n;
    
    if(n == 0)
    {
        return false;
    }
    
    vector<building> buildings;
    
    for(int i = 0; i < n; ++i)
    {
        building b;
        input >> b.left_x >> b.left_y >> b.width >> b.depth >> b.height;
        b.id = i + 1;
        buildings.push_back(b);
    }
    
    calc(buildings, test_id);
    
    return true;
    
}

int main()
{
    ios_base::sync_with_stdio(false);
    
    int test_id = 1;
    while(test(test_id))
    {
        ++test_id;
    }
    
    return 0;
}



