#include <iostream>
using namespace std;

int main()
{
    int n;
    cin >> n;

    for(int i = 0; i < n; i++)
    {
        char col;
        int row;

        cin >> col;
        cin >> row;

        char current_col;
        int current_row;

        int col_incrementor;
        int row_incrementor;

        for(int i = 0; i < 4; i++)
        {
            current_col = col;
            current_row = row;

            if(i == 0)
            {
                col_incrementor = -1;
                row_incrementor = 0;
            }
            else if(i == 1)
            {
                col_incrementor = 0;
                row_incrementor = 1;
            }
            else if(i == 2)
            {
                col_incrementor = 1;
                row_incrementor = 0;
            }
            else if(i == 3)
            {
                col_incrementor = 0;
                row_incrementor = -1;
            }

            while(true)
            {
                current_col += col_incrementor;
                current_row += row_incrementor;

                if(current_col >= 'a' && current_col <= 'h' && current_row >= 1 && current_row <= 8)
                {
                    cout << current_col << current_row << endl;
                }
                else
                {
                    break;
                }
            }
        }
    }

    return 0;
}