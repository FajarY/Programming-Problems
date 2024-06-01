class Solution {
public:
    int findCenter(vector<vector<int>>& edges) {
        unordered_map<int, unordered_set<int>*> hashmap;

        for(int i = 0; i < edges.size(); i++)
        {
            int left = edges[i][0];
            int right = edges[i][1];

            if(hashmap.find(left) == hashmap.end())
            {
                unordered_set<int>* set = new unordered_set<int>;
                hashmap[left] = set;
            }
            if(hashmap.find(right) == hashmap.end())
            {
                unordered_set<int>* set = new unordered_set<int>;
                hashmap[right] = set;
            }

            hashmap[left]->insert(right);
            hashmap[right]->insert(left);
        }
        
        int max = -1;
        int max_type = -1;
        for(auto i = hashmap.begin(); i != hashmap.end(); i++)
        {
            int type = i->first;
            int count = i->second->size();

            if(count > max)
            {
                max = count;
                max_type = type;
            }
        }

        return max_type;
    }
};