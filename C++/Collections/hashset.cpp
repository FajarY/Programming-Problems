//Created By Kadek Fajar Pramartha Yasodana
//Hashset Implementation, with underlying container as a contigous array
#include <functional>

template<typename _Key>
class hashset
{
    private:
    struct hashset_node
    {
        _Key key;
        int next; //Cache Next To Make It Fast
    };
    
    int all_count = 0;
    int bucket_size = 15;
    int current_bucket_counts;
    bool is_created = false;
    int* counts;
    int* next_avalaibles;
    hashset_node* nodes;
    std::hash<_Key> hasher;

    void resize(int size)
    {
        if(!is_created)
        {
            is_created = true;

            current_bucket_counts = size;
            counts = new int[bucket_size];
            next_avalaibles = new int[bucket_size];
            for(int i = 0; i < bucket_size; i++)
            {
                *(counts + i) = 0;
                *(next_avalaibles + i) = 0;
            }

            nodes = new hashset_node[bucket_size * current_bucket_counts];
        }
        else
        {
            hashset_node* new_nodes = new hashset_node[bucket_size * size];

            for(int i = 0; i < bucket_size; i++)
            {
                hashset_node* old_node_offset = (nodes + i * current_bucket_counts);
                hashset_node* new_node_offset = (new_nodes + i * size);

                int count = *(counts + i);
                int current_old_index = 0;
                for(int j = 0; j < count; j++)
                {
                    hashset_node* left = (old_node_offset + current_old_index);
                    current_old_index = left->next;

                    hashset_node* right = (new_node_offset + j);
                    right->key = left->key;
                    
                    if(j == count - 1)
                    {
                        *(next_avalaibles + i) = j + 1;
                    }
                    else
                    {
                        right->next = j + 1;
                    }
                }
            }

            current_bucket_counts = size;
            delete[] nodes;
            nodes = new_nodes;
        }
    }
    int find(_Key key)
    {
        size_t hash_code = hasher(key);
        hash_code %= bucket_size;

        hashset_node* check_nodes = (nodes + hash_code * current_bucket_counts);
        int count = *(counts + hash_code);
        
        int current_index = 0;
        for(int i = 0; i < count; i++)
        {
            hashset_node* check_node = (check_nodes + current_index);

            if(check_node->key == key)
            {
                return hash_code * current_bucket_counts + current_index;
            }

            current_index = check_node->next;
        }

        return -1;
    }
    void make_compact(size_t hash_code)
    {
        hashset_node* slice_nodes = (nodes + hash_code * current_bucket_counts);
        int count = *(counts + hash_code);

        int current_index = 0;
        for(int i = 0; i < count; i++)
        {
            hashset_node* current = (slice_nodes + current_index);
            current_index = current->next;

            hashset_node* compact_pos = (slice_nodes + i);
            compact_pos->key = current->key;
            compact_pos->next = i + 1;
        }
        *(next_avalaibles + hash_code) = count;
    }
    bool safe_add(_Key key)
    {
        size_t hash_code = hasher(key);
        hash_code %= bucket_size;

        hashset_node* check_nodes = (nodes + hash_code * current_bucket_counts);
        int count = *(counts + hash_code);
        
        int current_index = 0;
        int last_index = -1;
        for(int i = 0; i < count; i++)
        {
            hashset_node* check_node = (check_nodes + current_index);

            if(check_node->key == key)
            {
                return false;
            }

            last_index = current_index;
            current_index = check_node->next;
        }

        //Fails
        int* next_index = (next_avalaibles + hash_code);
        if(*next_index == current_bucket_counts)
        {
            if(count == current_bucket_counts)
            {
                resize(current_bucket_counts * 2);
                check_nodes = (nodes + hash_code * current_bucket_counts);
            }
            else
            {
                make_compact(hash_code);
            }
        }

        hashset_node* current = (check_nodes + *next_index);
        current->key = key;

        if(last_index != -1)
        {
            hashset_node* last = (check_nodes + last_index);
            last->next = *next_index;
        }

        *next_index += 1;
        *(counts + hash_code) += 1;

        all_count++;

        return true;
    }
    bool safe_remove(_Key key)
    {
        size_t hash_code = hasher(key);
        hash_code %= bucket_size;

        hashset_node* check_nodes = (nodes + hash_code * current_bucket_counts);
        int count = *(counts + hash_code);
        
        int current_index = 0;
        int last_index = -1;

        for(int i = 0; i < count; i++)
        {
            hashset_node* check_node = (check_nodes + current_index);

            if(check_node->key == key)
            {
                if(current_index == *(next_avalaibles + hash_code) - 1)
                {
                    *(next_avalaibles + hash_code) = current_index;
                }
                else if(last_index != -1)
                {
                    int next_index = check_node->next;

                    check_node = (check_nodes + last_index);
                    check_node->next = next_index;
                }
                else if(count > 1)
                {
                    int next_index = check_node->next;
                    hashset_node* next_from_first = (check_nodes + next_index);

                    check_node->key = next_from_first->key;
                    check_node->next = next_from_first->next;
                }
                else
                {
                    *(next_avalaibles + hash_code) = 0;
                }

                *(counts + hash_code) -= 1;
                all_count--;

                return true;
            }

            last_index = current_index;
            current_index = check_node->next;
        }

        return false;
    }

    public:
    int get_count()
    {
        return all_count;
    }
    hashset()
    {
        resize(10);
    }
    hashset(int bucket_size, int capacity_each)
    {
        this->bucket_size = bucket_size;
        resize(capacity_each);
    }
    ~hashset()
    {
        delete[] counts;
        delete[] nodes;
        delete[] next_avalaibles;
    }
    bool contains(_Key key)
    {
        return find(key) != -1;
    }
    void add(_Key key)
    {
        safe_add(key);
    }
    bool remove(_Key key)
    {
        return safe_remove(key);
    }
    struct set_iterator
    {
        private:
        hashset_node* nodes;
        int* counts;
        int current_bucket_count;
        int bucket_size;
        int current_bucket;
        int current_count;
        int current_index;

        public:
        set_iterator(hashset_node* nodes, int* counts, int bucket_size, int current_bucket_count)
        {
            this->nodes = nodes;
            this->counts = counts;
            this->bucket_size = bucket_size;
            this->current_bucket_count = current_bucket_count;

            current_index = 0;
            current_bucket = 0;
            current_count = 0;

            for(int i = 0; i < bucket_size; i++)
            {
                int count = *(counts + i);
                if(count != 0)
                {
                    current_bucket = i;
                    current_index = 0;
                    current_count = count;
                    break;
                }
            }
        }
        bool is_empty()
        {
            return current_count == 0;
        }
        _Key get_data()
        {
            hashset_node* node = (nodes + (current_bucket * current_bucket_count) + current_index);

            return node->key;
        }
        bool next()
        {
            if(current_count == 0)
            {
                return false;
            }
            
            current_count--;

            if(current_count == 0)
            {
                for(int i = current_bucket + 1; i < bucket_size; i++)
                {
                    int count = *(counts + i);

                    if(count != 0)
                    {
                        current_bucket = i;
                        current_index = 0;
                        current_count = count;
                        break;
                    }
                }

                return false;
            }

            hashset_node* current = (nodes + (current_bucket * current_bucket_count) + current_index);
            current_index = current->next;

            return true;
        }
    };
    set_iterator create_iterator()
    {
        set_iterator iterator = set_iterator(nodes, counts, bucket_size, current_bucket_counts);

        return iterator;
    }
};