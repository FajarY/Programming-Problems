//Created By Kadek Fajar Pramartha Yasodana
//Hashmap Implementation, with underlying container as a contigous array
#include <functional>
#include <iostream>

template<typename _Key, typename _Value>
class hashmap
{
    private:
    struct hashmap_node
    {
        _Key key;
        _Value value;
        int next; //Cache Next To Make It Fast
    };
    
    int all_count = 0;
    int bucket_size = 15;
    int current_bucket_counts;
    bool is_created = false;
    int* counts;
    int* next_avalaibles;
    hashmap_node* nodes;
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

            nodes = new hashmap_node[bucket_size * current_bucket_counts];
        }
        else
        {
            hashmap_node* new_nodes = new hashmap_node[bucket_size * size];

            for(int i = 0; i < bucket_size; i++)
            {
                hashmap_node* old_node_offset = (nodes + i * current_bucket_counts);
                hashmap_node* new_node_offset = (new_nodes + i * size);

                int count = *(counts + i);
                int current_old_index = 0;
                for(int j = 0; j < count; j++)
                {
                    hashmap_node* left = (old_node_offset + current_old_index);
                    current_old_index = left->next;

                    hashmap_node* right = (new_node_offset + i);
                    right->key = left->key;
                    right->value = left->value;
                    
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

        hashmap_node* check_nodes = (nodes + hash_code * current_bucket_counts);
        int count = *(counts + hash_code);
        
        int current_index = 0;
        for(int i = 0; i < count; i++)
        {
            hashmap_node* check_node = (check_nodes + current_index);

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
        hashmap_node* slice_nodes (nodes + hash_code * current_bucket_counts);
        int count = *(counts + hash_code);

        int current_index = 0;
        for(int i = 0; i < count; i++)
        {
            hashmap_node* current = (slice_nodes + current_index);
            current_index = current->next;

            hashmap_node* compact_pos = (slice_nodes + i);
            compact_pos->key = current->key;
            compact_pos->value = current->value;
            
            if(i != count - 1)
            {
                compact_pos->next = i + 1;
            }
            else
            {
                *(next_avalaibles + hash_code) = i + 1;
            }
        }
    }
    bool safe_add(_Key key, _Value value)
    {
        size_t hash_code = hasher(key);
        hash_code %= bucket_size;

        hashmap_node* check_nodes = (nodes + hash_code * current_bucket_counts);
        int count = *(counts + hash_code);
        
        int current_index = 0;
        int last_index = -1;
        for(int i = 0; i < count; i++)
        {
            hashmap_node* check_node = (check_nodes + current_index);

            if(check_node->key == key)
            {
                check_node->value = value;
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

        hashmap_node* current = (check_nodes + *next_index);
        current->key = key;
        current->value = value;

        if(last_index != -1)
        {
            hashmap_node* last = (check_nodes + last_index);
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

        hashmap_node* check_nodes = (nodes + hash_code * current_bucket_counts);
        int count = *(counts + hash_code);
        
        int current_index = 0;
        int last_index = -1;

        for(int i = 0; i < count; i++)
        {
            hashmap_node* check_node = (check_nodes + current_index);

            if(check_node->key == key)
            {
                if(current_index == *(next_avalaibles + hash_code) - 1)
                {
                    *(next_avalaibles + hash_code) = current_index;
                }
                else
                {
                    int next_index = check_node->next;

                    check_node = (check_nodes + last_index);
                    check_node->next = next_index;
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
    bool safe_set(_Key key, _Value value)
    {
        int index = find(key);

        if(index != -1)
        {
            hashmap_node* current = (nodes + index);
            current->value = value;
            return true;
        }

        return false;
    }

    public:
    int get_count()
    {
        return all_count;
    }
    hashmap()
    {
        resize(10);
    }
    hashmap(int bucket_size, int capacity_each)
    {
        this->bucket_size = bucket_size;
        resize(capacity_each);
    }
    ~hashmap()
    {
        delete[] counts;
        delete[] nodes;
        delete[] next_avalaibles;
    }
    bool contains_key(_Key key)
    {
        return find(key) != -1;
    }
    bool try_get_value(_Key key, _Value* value)
    {
        int index = find(key);

        if(index != -1)
        {
            hashmap_node* node = (nodes + index);
            *value = node->value;
            return true;
        }

        return false;
    }
    _Value get_or_default(_Key key)
    {
        int index = find(key);

        if(index != -1)
        {
            hashmap_node* node = (nodes + index);
            return node->value;
        }

        return _Value();
    }
    void add(_Key key, _Value value)
    {
        safe_add(key, value);
    }
    bool set(_Key key, _Value value)
    {
        return safe_set(key, value);
    }
    bool remove(_Key key)
    {
        return safe_remove(key);
    }
    struct map_iterator
    {
        private:
        hashmap_node* nodes;
        int* counts;
        int current_bucket_count;
        int bucket_size;
        int current_bucket;
        int current_count;
        int current_index;

        public:
        map_iterator(hashmap_node* nodes, int* counts, int bucket_size, int current_bucket_count)
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
        std::pair<_Key, _Value> get_data()
        {
            hashmap_node* node = (nodes + (current_bucket * current_bucket_count) + current_index);

            return std::pair<_Key, _Value>(node->key, node->value);
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

            hashmap_node* current = (nodes + (current_bucket * current_bucket_count) + current_index);
            current_index = current->next;

            return true;
        }
    };
    map_iterator create_iterator()
    {
        map_iterator iterator = map_iterator(nodes, counts, bucket_size, current_bucket_counts);

        return iterator;
    }
};

//Testing Purpose
void test_hashmap_int_int()
{
    hashmap<int, int> map;

    while(true)
    {
        char command;
        
        std::cin >> command;
        int key, value;

        if(command == 'a')
        {
            std::cin >> key >> value;
            map.add(key, value);
        }
        else if(command == 'r')
        {
            std::cin >> key;
            bool succeed = map.try_get_value(key, &value);

            std::cout << succeed << " " << value << std::endl;
        }
        else if(command == 's')
        {
            std::cin >> key >> value;

            std::cout << map.set(key, value) << std::endl;
        }
        else if(command == 'm')
        {
            std::cin >> key;

            std::cout << map.remove(key) << std::endl;
        }
        else if(command == 'p')
        {
            hashmap<int, int>::map_iterator iterator = map.create_iterator();
            while (!iterator.is_empty())
            {
                std::cout << iterator.get_data().first << " " << iterator.get_data().second << std::endl;
                iterator.next();
            }
        }
        else
        {
            break;
        }
    }

    return 0;
}