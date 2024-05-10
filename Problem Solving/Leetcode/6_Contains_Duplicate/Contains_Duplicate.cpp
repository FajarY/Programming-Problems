class Solution {
public:

    vector<int>** check;
    int bucket_size = 50;

    void init()
    {
        check = (vector<int>**)malloc(sizeof(vector<int>*) * bucket_size);
        for(int i = 0; i < bucket_size; i++)
        {
            *(check + i) = new vector<int>;
        }
    }

    bool contains(int number)
    {
        int hash_bucket = abs(number) % bucket_size;

        vector<int>* arr = *(check + hash_bucket);
        for(int i = 0; i < arr->size(); i++)
        {
            int current = (*arr)[i];
            if(current == number)
            {
                return true;
            }
        }

        return false;
    }
    void add_to_bucket(int number)
    {
        int hash_bucket = abs(number) % bucket_size;

        vector<int>* arr = *(check + hash_bucket);
        arr->push_back(number);
    }
    
    bool containsDuplicate(vector<int>& nums) {
        init();

        for(int i = 0; i < nums.size(); i++)
        {
            int current = nums[i];

            if(contains(current))
            {
                return true;
            }
            else
            {
                add_to_bucket(current);
            }
        }

        return false;
    }
};