class Solution {
public:
    bool* visited;
    int horizontal_size;
    int vertical_size;

    void init_bool_array(int m, int n)
    {
        if(visited != nullptr)
        {
            delete visited;
        }

        visited = new bool[m * n];
        memset(visited, 0, m * n);
        horizontal_size = n;
        vertical_size = m;
    }
    bool is_visited(int m, int n)
    {
        return *(visited + (m * horizontal_size) + n);
    }
    void set_visited(int m, int n)
    {
        *(visited + (m * horizontal_size) + n) = true;
    }
    bool is_valid(int m, int n, vector<vector<char>>& grid)
    {
        return grid[m][n] == '1';
    }
    void check_and_push(queue<pair<int, int>>& open_set, int m, int n, vector<vector<char>>& grid)
    {
        if(m < 0 || n < 0 || m >= vertical_size || n >= horizontal_size)
        {
            return;
        }

        if(is_visited(m, n) || !is_valid(m, n, grid))
        {
            return;
        }

        set_visited(m, n);
        open_set.push(make_pair(m, n));
    }
    bool traverse(int m, int n, vector<vector<char>>& grid)
    {
        if(is_visited(m, n) || !is_valid(m, n, grid))
        {
            return false;
        }

        queue<pair<int, int>> open_set;
        open_set.push(make_pair(m, n));
        set_visited(m, n);

        while(!open_set.empty())
        {
            pair<int, int> current = open_set.front();
            open_set.pop();

            check_and_push(open_set, current.first, current.second - 1, grid);
            check_and_push(open_set, current.first, current.second + 1, grid);
            check_and_push(open_set, current.first - 1, current.second, grid);
            check_and_push(open_set, current.first + 1, current.second, grid);
        }

        return true;
    }
    int numIslands(vector<vector<char>>& grid) {
        init_bool_array(grid.size(), grid[0].size());
        int island_count = 0;

        for(int i = 0; i < vertical_size; i++)
        {
            for(int j = 0; j < horizontal_size; j++)
            {
                if(traverse(i, j, grid))
                {
                    island_count++;
                }
            }
        }

        return island_count;
    }
};