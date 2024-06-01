class comparer
{
    public:
    bool operator() (pair<int, int>& left, pair<int, int>& right)
    {
        return left.second > right.second;
    }
};

class Solution {
public:
    int networkDelayTime(vector<vector<int>>& times, int n, int k) {

        vector<vector<pair<int, int>>> graph = vector<vector<pair<int, int>>>(n + 1);
        for(int i = 0; i < times.size(); i++)
        {
            graph[times[i][0]].push_back(make_pair(times[i][1], times[i][2]));
        }

        vector<int> result = vector<int>(n + 1, INT_MAX);
        vector<bool> visited = vector<bool>(n + 1, false);
        priority_queue<pair<int, int>, vector<pair<int, int>>, comparer> open_set;

        result[k] = 0;
        open_set.push(make_pair(k, 0));

        while(!open_set.empty())
        {
            pair<int, int> current = open_set.top();
            open_set.pop();

            if(visited[current.first])
            {
                continue;
            }
            visited[current.first] = true;

            for(int i = 0; i < graph[current.first].size(); i++)
            {
                pair<int, int> target = graph[current.first][i];

                int cost = target.second + current.second;
                if(!visited[target.first] && result[target.first] > cost)
                {
                    result[target.first] = cost;
                    open_set.push(make_pair(target.first, cost));
                }
            }
        }

        int max_time = -1;
        for(int i = 1; i <= n; i++)
        {
            int val = result[i];
            if(val == INT_MAX)
            {
                return -1;
            }
            if(val > max_time)
            {
                max_time = val;
            }
        }

        return max_time;
    }
};