class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        
        int left_index;
        int right_index;

        for(int i = 0; i < nums.size() - 1; i++)
        {
            left_index = i;
            int left = nums[i];
            for(int j = i + 1; j < nums.size(); j++)
            {
                right_index = j;
                int right = nums[j];

                if((left + right) == target)
                {
                    goto skip;
                }
            }
        }

        skip:
        vector<int> arr;
        arr.push_back(left_index);
        arr.push_back(right_index);

        return arr;
    }
};