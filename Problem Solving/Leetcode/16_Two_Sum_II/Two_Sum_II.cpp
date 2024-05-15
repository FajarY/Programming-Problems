class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {
        int left = 0;
        int right = numbers.size() - 1;

        vector<int> answer;
        while(true)
        {
            int val = numbers[left] + numbers[right];
            cout << left << " " << right << endl;

            if(val < target)
            {
                left++;
            }
            else if(val > target)
            {
                right--;
            }
            else
            {
                answer.push_back(left + 1);
                answer.push_back(right + 1);

                return answer;
            }
        }


        return answer;
    }
};