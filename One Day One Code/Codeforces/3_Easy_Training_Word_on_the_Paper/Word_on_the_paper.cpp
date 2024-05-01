#include <iostream>
#include <stdlib.h>

using namespace std;

int main()
{
    char** arr = (char**)alloca(sizeof(char*) * 8);
    for(int i = 0; i < 8; i++)
    {
        *(arr + i) = (char*)alloca(8);
    }

    int t;
    cin >> t;

    for(int i = 0; i < t; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            char* current = *(arr + j);
            for(int k = 0; k < 8; k++)
            {
                char val;
                cin >> val;
                *(current + k) = val;
            }
        }
        for(int j = 0; j < 8; j++)
        {
            for(int k = 0; k < 8; k++)
            {
                char val = *(*(arr + k) + j);
                if(val != '.')
                {
                    cout << val;
                }
            }
        }
        cout << endl;
    }
}