class Solution {
public:

    struct node
    {
        int key;
        int value;
    };

    int BUCKET_SIZE = 15;
    int current_bucket_count;
    node* arr;
    int* bucket_counts;

    void init_hashmap()
    {
        current_bucket_count = 0;
        bucket_counts = (int*)malloc(sizeof(int) * BUCKET_SIZE);
        memset(bucket_counts, 0, sizeof(int) * BUCKET_SIZE);

        resize(10);
    }
    void resize(int target_bucket_count)
    {
        node* new_arr = (node*)malloc(sizeof(node) * target_bucket_count * BUCKET_SIZE);
        for(int i = 0; i < BUCKET_SIZE; i++)
        {
            int current_count = *(bucket_counts + i);

            if(current_count > 0)
            {
                int new_offset = i * target_bucket_count;
                int old_offset = i * current_bucket_count;

                memcpy((void*)(new_arr + new_offset), (void*)(arr + old_offset), sizeof(node) * current_count);
            }
        }
        if(arr != NULL)
        {
            free(arr);
        }
        arr = new_arr;
        current_bucket_count = target_bucket_count;
    }
    bool has_key_and_modify(int key, int* out_int, int adder)
    {
        int index = get_hash_code(key) % BUCKET_SIZE;

        int count = *(bucket_counts + index);
        node* check = (arr + (index * current_bucket_count));
        for(int i = 0; i < count; i++)
        {
            int get_key = (check + i)->key;
            if(get_key == key)
            {
                (check + i)->value += adder;

                if(out_int != NULL)
                {
                    *(out_int) = (check + i)->value;
                }
                return true;
            }
        }

        return false;
    }
    unsigned int get_hash_code(int val)
    {
        return abs(val);
    }
    void add(int key, int value)
    {
        int index = get_hash_code(key) % BUCKET_SIZE;

        int count = *(bucket_counts + index);

        if(count == current_bucket_count)
        {
            resize(current_bucket_count * 2);
        }

        node* check = (arr + (index * current_bucket_count) + count);
        check->key = key;
        check->value = value;

        *(bucket_counts + index) = count + 1;
    }
    static bool node_compare(const node& left, const node& right)
    {
        return left.value > right.value;
    }
    vector<int> topKFrequent(vector<int>& nums, int k) {
        vector<int> ret;

        init_hashmap();

        for(int i = 0; i < nums.size(); i++)
        {
            int current = nums[i];
            if(!has_key_and_modify(current, NULL, 1))
            {
                add(current, 1);
            }
        }

        vector<node> nodes_unsorted;

        for(int i = 0; i < BUCKET_SIZE; i++)
        {
            int count = *(bucket_counts + i);

            node* start_arr = (arr + (i * current_bucket_count));
            for(int j = 0; j < count; j++)
            {
                node* current = (start_arr + j);
                nodes_unsorted.push_back(*current);
            }
        }

        sort(nodes_unsorted.begin(), nodes_unsorted.end(), node_compare);

        for(int i = 0; i < k; i++)
        {
            ret.push_back(nodes_unsorted[i].key);
        }

        return ret;
    }
};