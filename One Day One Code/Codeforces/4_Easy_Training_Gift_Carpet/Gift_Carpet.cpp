#include <iostream>
#include <stdlib.h>
#include <string.h>

using namespace std;

int main()
{
    int t;
    
    cin >> t;
    
    for(int i = 0; i < t; i++)
    {
        int n;
        int m;

        cin >> n;
        cin >> m;

        char** arr = (char**)alloca(sizeof(char*) * n);
        for(int i = 0; i < n; i++)
        {
            *(arr + i) = (char*)alloca(m + 1);
            memset(*(arr + i), 0, m + 1);
        }
        for(int i = 0; i < n; i++)
        {
            cin >> *(arr + i);
        }

        char* check = "vika";
        int found = 0;
        for(int i = 0; i < m; i++)
        {
            for(int j = 0; j < n; j++)
            {
                char current = *(*(arr + j) + i);

                if(current == *(check))
                {
                    check = (check + 1);

                    if(*(check) == 0)
                    {
                        found = 1;
                        goto skip;
                    }
                    break;
                }
            }
        }

        skip:
        if(found)
        {
            cout << "YES" << endl;
        }
        else
        {
            cout << "NO" << endl;
        }
    }
}