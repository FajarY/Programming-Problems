#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <string.h>

using namespace std;

struct fish_data
{
    int power;
    int prey;
    int predator;

    fish_data()
    {

    }
    fish_data(int in_power, int in_prey, int in_predator)
    {
        power = in_power;
        prey = in_prey;
        predator = in_predator;
    }
};

struct comparer
{
    bool operator() (fish_data left, fish_data right)
    {
        return right.power > left.power;
    }
};

int main()
{
    int n;
    int a;
    int b;
    fish_data* fish = (fish_data*)malloc(sizeof(fish_data) * 200001);
    memset(fish, 0, sizeof(fish_data) * 200001);
    int copy[200001];

    unordered_map<int, int> index;

    cin >> n >> a >> b;
    for(int i = 0; i < n; i++)
    {
        int val;
        cin >> val;
        (fish + i)->power = val;
        copy[i] = val;
    }

    sort(fish, fish + n, comparer());
    for(int i = 0; i < n; i++)
    {
        index.insert_or_assign(fish[i].power, i);
    }
    for(int i = 0; i < n; i++)
    {
        fish_data* fish_ptr = fish + i;
        int val = fish_ptr->power;

        int loop = i;
        while(true)
        {
            loop++;
            if(loop >= n)
            {
                break;
            }

            fish_data* other_fish_data = fish + loop;
            int diff = other_fish_data->power - val;
            if(diff >= a)
            {
                if(diff >= b)
                {
                    break;
                }
                else
                {
                    fish_ptr->predator++;
                    other_fish_data->prey++;
                }
            }
        }
    }
    for(int i = 0; i < n; i++)
    {
        fish_data* current = (fish + index[copy[i]]);
        cout << current->predator << " " << current->prey << endl;
    }
}