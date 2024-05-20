class Solution {
public:
    int search(vector<int>& nums, int target) {
        int left = 0;
        int right = nums.size() - 1;

        int half = (left + right) / 2;

        while(left < right)
        {
            int val = nums[half];

            if(val == target)
            {
                return half;
            }

            if(val < target)
            {
                left = half + 1;
            }
            else
            {
                right = half - 1;
            }

            half = (left + right) / 2;
        }

        int last = nums[half];
        if(last == target)
        {
            return half;
        }
        return -1;
    }
};