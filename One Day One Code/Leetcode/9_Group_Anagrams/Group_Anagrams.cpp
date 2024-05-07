class Solution {
public:
    unsigned int get_hash_char(char character)
    {
        const unsigned int prime = 31;
        unsigned int char_as_int = (int)character;
        unsigned int val = prime * char_as_int + (unsigned int)(char_as_int ^ (char_as_int > 32));

        return val;
    }
    unsigned int get_hash(string str)
    {
        int len = str.length();
        unsigned int total = 1;

        for(int i = 0; i < len; i++)
        {
            total *= get_hash_char(str[i]);
        }

        return total;
    }
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        
        unordered_map<unsigned int, vector<string>> hashmap;

        for(int i = 0; i < strs.size(); i++)
        {
            unsigned int hash = get_hash(strs[i]);

            if(hashmap.find(hash) != hashmap.end())
            {
                vector<string> current = hashmap[hash];
                current.push_back(strs[i]);

                hashmap[hash] = current;
            }
            else
            {
                vector<string> add;
                add.push_back(strs[i]);

                hashmap[hash] = add; 
            }
        }

        vector<vector<string>> arr;

        for(auto it = hashmap.begin(); it != hashmap.end(); it++)
        {
            arr.push_back(it->second);
        }

        return arr;
    }
};