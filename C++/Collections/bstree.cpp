//Created By Kadek Fajar Pramartha Yasodana
//bstree, with underlying container as a contigous array
//Still Buggy, 23/33 Testcase Passed. Bug On Sifting Up & Child

template<typename _T>
class bstree
{
    private:
    struct node
    {
        _T key;
        bool set;
    };

    node* nodes;
    int count;
    int capacity;
    bool is_created = false;
    int (*comparer)(const _T&, const _T&);

    void resize(int minimum, int capacity)
    {
        if(capacity <= minimum)
        {
            capacity = minimum + 1;
        }
        if(is_created)
        {
            node* new_nodes = new node[capacity];
            for(int i = 0; i < this->capacity; i++)
            {
                *(new_nodes + i) = *(nodes + i);
            }
            for(int i = this->capacity; i < capacity; i++)
            {
                node* current = (new_nodes + i);
                current->set = false;
            }

            nodes = new_nodes;

            this->capacity = capacity;
        }
        else
        {
            is_created = true;
            nodes = new node[capacity];

            for(int i = 0; i < capacity; i++)
            {
                node* current = (nodes + i);
                current->set = false;
            }

            count = 0;
            this->capacity = capacity;
        }
    }
    bool safe_add(int start, _T key)
    {
        node* current;
        while(true)
        {
            if(start >= capacity)
            {
                resize(start, capacity * 2);
            }

            current = (nodes + start);
            if(current->set == false)
            {
                current->set = true;
                current->key = key;

                count++;
                return true;
            }

            int compare = comparer(current->key, key);
            if(compare == 0)
            {
                return false;
            }
            else if(compare == -1)
            {
                start = start * 2 + 1;
            }
            else
            {
                start = start * 2 + 2;
            }
        }

        return false;
    }
    int find(int start, _T key)
    {
        node* current;
        while(true)
        {
            if(start >= capacity)
            {
                return -1;
            }

            current = (nodes + start);
            if(!current->set)
            {
                return -1;
            }

            int compare = comparer(current->key, key);
            if(compare == 0)
            {
                return start;
            }
            else if(compare == -1)
            {
                start = start * 2 + 1;
            }
            else
            {
                start = start * 2 + 2;
            }
        }

        return -1;
    }
    int unsafe_find_smallest(int start)
    {
        int index = start;

        node* current = (nodes + index);
        while (true)
        {
            int left = index * 2 + 1;
            if(left >= capacity)
            {
                return index;
            }

            current = (nodes + left);
            if(!current->set)
            {
                return index;
            }
            index = left;
        }

        return -1;
    }
    bool safe_remove(int start, _T key)
    {
        int remove_index = find(start, key);

        if(remove_index == -1)
        {
            return false;
        }

        int left = remove_index * 2 + 1;
        int right = remove_index * 2 + 2;

        if(left >= capacity || right >= capacity)
        {
            int min_resize = left;
            if(right > left)
            {
                min_resize = right;
            }
            resize(min_resize, capacity * 2);
        }

        node* current = (nodes + remove_index);
        node* left_node = (nodes + left);
        node* right_node = (nodes + right);

        if(!left_node->set || !right_node->set)
        {
            if(right_node->set)
            {
                sift_up(right);
            }
            else if(left_node->set)
            {
                sift_up(left);
            }
            else
            {
                current->set = false;
            }
        }
        else
        {
            int smallest = unsafe_find_smallest(right);

            node* small_node = (nodes + smallest);

            current->key = small_node->key;
            small_node->set = false;

            int next_small = smallest * 2 + 2;
            if(next_small < capacity)
            {
                node* next_small_node = (nodes + next_small);

                if(next_small_node->set)
                {
                    sift_up(next_small);
                }
            }
        }

        return true;
    }
    void sift_up(int start)
    {
        int parent = start / 2 - ((start + 1) % 2);
        node* parent_node = (nodes + parent);
        node* current = (nodes + start);
        *parent_node = *current;
        current->set = false;

        sift_child(start, parent);
    }
    void sift_child(int from, int to)
    {
        int from_left = from * 2 + 1;
        int to_left = to * 2 + 1;
        int from_right = from * 2 + 2;
        int to_right = to * 2 + 2;
        
        bool go_right = true;
        if(from_right < capacity)
        {
            node* from_right_node = (nodes + from_right);
            *(nodes + to_right) = *from_right_node;
            if(!from_right_node->set)
            {
                go_right = false;
            }
            from_right_node->set = false;
        }
        else if(to_right < capacity)
        {
            node* to_right_node = (nodes + to_right);
            to_right_node->set = false;
            go_right = false;
        }
        else
        {
            go_right = false;
        }

        bool go_left = true;
        if(from_left < capacity)
        {
            node* from_left_node = (nodes + from_left);
            *(nodes + to_left) = *from_left_node;
            if(!from_left_node->set)
            {
                go_left = false;
            }
            from_left_node->set = false;
        }
        else if(to_left < capacity)
        {
            node* to_left_node = (nodes + to_left);
            to_left_node->set = false;
            go_left = false;
        }
        else
        {
            go_left = false;
        }

        if(go_right)
            sift_child(from_right, to_right);
        if(go_left)
            sift_child(from_left, to_left);
    }

    public:
    bstree(int (*comparer)(const _T&, const _T&))
    {
        this->comparer = comparer;
        resize(10, 10);
    }
    bstree(int (*comparer)(const _T&, const _T&), int start_size)
    {
        this->comparer = comparer;
        resize(10, start_size);
    }
    void set_comparer(int (*comparer)(const _T&, const _T&))
    {
        this->comparer = comparer;
    }
    bool contains(_T key)
    {
        return find(0, key) != -1;
    }
    bool remove(_T key)
    {
        return safe_remove(0, key);
    }
    bool add(_T key)
    {
        return safe_add(0, key);
    }
};