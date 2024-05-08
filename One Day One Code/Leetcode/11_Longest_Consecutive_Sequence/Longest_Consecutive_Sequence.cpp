class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        if(nums.size() == 0)
        {
            return 0;
        }

        sort(nums.begin(), nums.end());

        int longest_count = 0;
        int current_count = 0;
        int last_num = nums[0] - 2;

        for(int i = 0; i < nums.size(); i++)
        {
            int val = nums[i];
            if(last_num == val)
            {
                continue;
            }
            else if((last_num + 1) != val)
            {
                if(current_count > longest_count)
                {
                    longest_count = current_count;
                }
                current_count = 1;
                last_num = val;
            }
            else
            {
                current_count++;
                last_num = val;
            }
        }

        if(current_count > longest_count)
        {
            longest_count = current_count;
        }

        return longest_count;
    }
};