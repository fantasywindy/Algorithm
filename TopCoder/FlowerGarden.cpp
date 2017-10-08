/*
 Class: FlowerGarden
 Method: getOrdering
 Parameters: vector <int>, vector <int>, vector <int>
 Returns: vector <int>
 Method signature: vector <int> getOrdering(vector <int> height, vector <int> bloom, vector <int> wilt)
 (be sure your method is public)
 */
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

struct Flower
{
    int b;
    int w;
    int h;
};


class FlowerGarden
{
public:
    vector <int> getOrdering(vector <int> height, vector <int> bloom, vector <int> wilt)
    {
        int n = height.size();
        
        vector<Flower> flowers;
        
        for(int i = 0 ; i < n; ++i)
        {
            Flower f;
            f.b = bloom[i];
            f.w = wilt[i];
            f.h = height[i];
            flowers.push_back(f);
        }
        
        sort(flowers.begin(), flowers.end(), [](const Flower & l, const Flower & r)
             {
                 return l.h < r.h;
             });
        
        
        vector<Flower> ret;
        ret.push_back(flowers[0]);
        
        for(int i = 1; i < n; ++i)
        {
            auto curFlower = flowers[i];
            
            int index = ret.size() - 1;
            
            while(index >= 0 && overlap(curFlower, ret[index]) == false)
            {
                --index;
            }
            
            ret.insert(ret.begin() + index + 1, curFlower);
        }
        
        vector<int> temp;
        
        for(auto item : ret)
        {
            temp.push_back(item.h);
        }
        
        return temp;
    }
    
    bool overlap(Flower & l, Flower & r)
    {
        return r.b <= l.w && (l.b <= r.w);
    }
};

int main()
{
    vector<int> height = {1,2,3};
    vector<int> bloom = {3,4,6};
    vector<int> wilt = {5,7,7};
    FlowerGarden garden;
    
    auto ret = garden.getOrdering(height, bloom, wilt);
    
    for(auto item : ret)
    {
        cout << item << " ";
    }
    cout << endl;
    
    return 0;
}
