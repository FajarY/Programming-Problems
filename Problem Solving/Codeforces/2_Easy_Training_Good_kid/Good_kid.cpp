#include <iostream>

using namespace std;

int main()
{
    int t;
    cin >> t;

    for(int i = 0; i < t; i++)
    {
        int n;
        cin >> n;

        int arr[n];

        int lowest = INT_MAX;
        int lowest_index = -1;

        for(int j = 0; j < n; j++)
        {
            int val;
            cin >> val;

            arr[j] = val;

            if(val < lowest)
            {
                lowest = val;
                lowest_index = j;
            }
        }

        arr[lowest_index] += 1;

        int product = 1;
        for(int j = 0; j < n; j++)
        {
            product *= arr[j];
        }
       cout << product << endl;
    }
}