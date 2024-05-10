class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        vector<int> arr;

        int product_without_zero = 1;
        int zero_count = 0;

        for(int i = 0; i < nums.size(); i++)
        {
            int val = nums[i];
            if(val != 0)
            {
                product_without_zero *= val;
            }
            else
            {
                zero_count++;
            }
        }

        if(zero_count == 0)
        {
            for(int i = 0; i < nums.size(); i++)
            {
                int val = nums[i];
                int product = product_without_zero / val;

                arr.push_back(product);
            }
        }
        else if(zero_count == 1)
        {
            for(int i = 0; i < nums.size(); i++)
            {
                int val = nums[i];
                if(val == 0)
                {
                    arr.push_back(product_without_zero);
                }
                else
                {
                    arr.push_back(0);
                }
            }
        }
        else
        {
            for(int i = 0; i < nums.size(); i++)
            {
                arr.push_back(0);
            }
        }

        return arr;
    }
};