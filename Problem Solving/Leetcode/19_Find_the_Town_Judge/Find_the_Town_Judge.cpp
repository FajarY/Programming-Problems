class Solution {
public:
    int findJudge(int n, vector<vector<int>>& trust) {
        
        vector<pair<int, int>> graph = vector<pair<int, int>>(n + 1);

        for(int i = 0; i < trust.size(); i++)
        {
            vector<int> node = trust[i];
            pair<int, int> from = graph[node[0]];
            pair<int, int> to = graph[node[1]];

            from.first += 1;
            to.second += 1;

            graph[node[0]] = from;
            graph[node[1]] = to;
        }

        for(int i = 1; i <= n; i++)
        {
            pair<int, int> data = graph[i];

            if(data.first == 0 && data.second == (n - 1))
            {
                return i;
            }
        }

        return -1;
    }
};