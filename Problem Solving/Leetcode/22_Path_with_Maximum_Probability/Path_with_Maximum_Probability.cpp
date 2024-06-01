class comparer
{
    public:
    bool operator() (pair<int, double>& left, pair<int, double>& right) const
    {
        return left.second < right.second;
    }
};

class Solution {
public:
    double maxProbability(int n, vector<vector<int>>& edges, vector<double>& succProb, int start_node, int end_node) {
        vector<vector<pair<int, double>>> graph = vector<vector<pair<int, double>>>(n);
        for(int i = 0; i < edges.size(); i++)
        {
            double cost = succProb[i];
            int left = edges[i][0];
            int right = edges[i][1];

            graph[left].push_back(make_pair(right, cost));
            graph[right].push_back(make_pair(left, cost));
        }
        vector<double> result = vector<double>(n, 0);
        
        result[start_node] = 1.0;
        vector<bool> visited = vector<bool>(n, false);
        priority_queue<pair<int, double>, vector<pair<int, double>>, comparer> open_set;

        open_set.push(pair<int, double>(start_node, result[start_node]));

        while(!open_set.empty())
        {
            pair<int, double> current = open_set.top();
            open_set.pop();

            if(visited[current.first])
            {
                continue;
            }

            for(int i = 0; i < graph[current.first].size(); i++)
            {
                pair<int, double> target = graph[current.first][i];

                if(visited[target.first])
                {
                    continue;
                }

                double chance = current.second * target.second;
                if(chance > result[target.first])
                {
                    open_set.push(make_pair(target.first, chance));
                    result[target.first] = chance;
                }
            }
        }

        return result[end_node];
    }
};