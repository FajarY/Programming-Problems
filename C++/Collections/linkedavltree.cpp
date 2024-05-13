// ========[AVL Tree]======== //
/*
    Dimodifikasi oleh KADEK FAJAR PRAMARTHA YASODANA, Sumber Modul https://github.com/Algoritma-dan-Pemrograman-ITS/StrukturData/blob/master/For%20C%2B%2B/AVL%20Tree/unique_avltree.cpp
    Support Template
    Beberapa fungsi ada di modul, Inorder (Sorted), Postorder, Preorder (DFS)
    Support Comparer
*/
template <typename T>
struct linkedavltree_standard_index_comparer
{
    int operator()(const T& left, const T& right)
    {
        if (left > right)
        {
            return 1;
        }
        else if (left < right)
        {
            return -1;
        }

        return 0;
    }
};

template <typename T, typename index_comparer = linkedavltree_standard_index_comparer<T>>
class avltree
{
public:
    struct avl_node
    {
        T data;
        avl_node *left, *right;
        int height;
    };

private:
    avl_node *_root;
    unsigned _size;
    int version;
    index_comparer comparer;

    avl_node *_avl_createNode(T value)
    {
        avl_node *newNode = new avl_node;
        newNode->data = value;
        newNode->height = 1;
        newNode->left = newNode->right = NULL;
        return newNode;
    }

    avl_node *_search(avl_node *root, T value)
    {
        while (root != NULL)
        {
            int check = comparer(value, root->data);
            if (check < 0)
                root = root->left;
            else if (check > 0)
                root = root->right;
            else
                return root;
        }
        return root;
    }

    int _getHeight(avl_node *node)
    {
        if (node == NULL)
            return 0;
        return node->height;
    }

    int _max(int a, int b)
    {
        return (a > b) ? a : b;
    }

    avl_node *_rightRotate(avl_node *pivotNode)
    {
        avl_node *newParrent = pivotNode->left;
        pivotNode->left = newParrent->right;
        newParrent->right = pivotNode;

        pivotNode->height = _max(_getHeight(pivotNode->left),
                                 _getHeight(pivotNode->right)) +
                            1;
        newParrent->height = _max(_getHeight(newParrent->left),
                                  _getHeight(newParrent->right)) +
                             1;

        return newParrent;
    }

    avl_node *_leftRotate(avl_node *pivotNode)
    {
        avl_node *newParrent = pivotNode->right;
        pivotNode->right = newParrent->left;
        newParrent->left = pivotNode;

        pivotNode->height = _max(_getHeight(pivotNode->left),
                                 _getHeight(pivotNode->right)) +
                            1;
        newParrent->height = _max(_getHeight(newParrent->left),
                                  _getHeight(newParrent->right)) +
                             1;

        return newParrent;
    }

    avl_node *_leftCaseRotate(avl_node *node)
    {
        return _rightRotate(node);
    }

    avl_node *_rightCaseRotate(avl_node *node)
    {
        return _leftRotate(node);
    }

    avl_node *_leftRightCaseRotate(avl_node *node)
    {
        node->left = _leftRotate(node->left);
        return _rightRotate(node);
    }

    avl_node *_rightLeftCaseRotate(avl_node *node)
    {
        node->right = _rightRotate(node->right);
        return _leftRotate(node);
    }

    int _getBalanceFactor(avl_node *node)
    {
        if (node == NULL)
            return 0;
        return _getHeight(node->left) - _getHeight(node->right);
    }

    avl_node *_insert_avl(avl_node *node, T value)
    {

        if (node == NULL)
            return _avl_createNode(value);

        int check = comparer(value, node->data);
        if (check < 0)
            node->left = _insert_avl(node->left, value);
        else if (check > 0)
            node->right = _insert_avl(node->right, value);

        node->height = 1 + _max(_getHeight(node->left), _getHeight(node->right));

        int balanceFactor = _getBalanceFactor(node);

        if (balanceFactor > 1 && comparer(value, node->left->data) < 0)
            return _leftCaseRotate(node);
        if (balanceFactor > 1 && comparer(value, node->left->data) > 0)
            return _leftRightCaseRotate(node);
        if (balanceFactor < -1 && comparer(value, node->right->data) > 0)
            return _rightCaseRotate(node);
        if (balanceFactor < -1 && comparer(value, node->right->data) < 0)
            return _rightLeftCaseRotate(node);

        return node;
    }

    avl_node *_findMinNode(avl_node *node)
    {
        avl_node *currNode = node;
        while (currNode && currNode->left != NULL)
            currNode = currNode->left;
        return currNode;
    }

    avl_node *_remove_avl(avl_node *node, T value)
    {
        if (node == NULL)
            return node;
        int check = comparer(value, node->data);
        if (check > 0)
            node->right = _remove_avl(node->right, value);
        else if (check < 0)
            node->left = _remove_avl(node->left, value);
        else
        {
            avl_node *temp;
            if ((node->left == NULL) || (node->right == NULL))
            {
                temp = NULL;
                if (node->left == NULL)
                    temp = node->right;
                else if (node->right == NULL)
                    temp = node->left;

                if (temp == NULL)
                {
                    temp = node;
                    node = NULL;
                }
                else
                    *node = *temp;

                delete temp;
            }
            else
            {
                temp = _findMinNode(node->right);
                node->data = temp->data;
                node->right = _remove_avl(node->right, temp->data);
            }
        }

        if (node == NULL)
            return node;

        node->height = _max(_getHeight(node->left), _getHeight(node->right)) + 1;

        int balanceFactor = _getBalanceFactor(node);

        if (balanceFactor > 1 && _getBalanceFactor(node->left) >= 0)
            return _leftCaseRotate(node);

        if (balanceFactor > 1 && _getBalanceFactor(node->left) < 0)
            return _leftRightCaseRotate(node);

        if (balanceFactor < -1 && _getBalanceFactor(node->right) <= 0)
            return _rightCaseRotate(node);

        if (balanceFactor < -1 && _getBalanceFactor(node->right) > 0)
            return _rightLeftCaseRotate(node);

        return node;
    }
    void __do_inorder(void (*function)(avl_node *), avl_node *current)
    {
        if (current != NULL)
        {
            __do_inorder(function, current->left);
            function(current);
            __do_inorder(function, current->right);
        }
    }
    void __do_postorder(void (*function)(avl_node *), avl_node *current)
    {
        if (current != NULL)
        {
            __do_postorder(function, current->left);
            __do_postorder(function, current->right);
            function(current);
        }
    }
    void __do_preorder(void (*function)(avl_node *), avl_node *current)
    {
        if (current != NULL)
        {
            function(current);
            __do_preorder(function, current->left);
            __do_preorder(function, current->right);
        }
    }
    static void delete_node(avl_node* node)
    {
        delete node;
    }

public:
    avltree()
    {
        _root = NULL;
        _size = 0U;
        comparer = index_comparer();
    }
    ~avltree()
    {
        __do_postorder(delete_node);
    }
    bool isEmpty()
    {
        return _root == NULL;
    }
    bool find(T value)
    {
        avl_node *temp = _search(_root, value);
        if (temp == NULL)
            return false;

        if (temp->data == value)
            return true;
        else
            return false;
    }
    bool insert(T value)
    {
        if (!find(value))
        {
            _root = _insert_avl(_root, value);
            version++;
            _size++;
            return true;
        }
        return false;
    }
    bool remove(T value)
    {
        if (find(value))
        {
            _root = _remove_avl(_root, value);
            version++;
            _size--;
            return true;
        }
        return false;
    }
    // Sorted
    void do_inorder_sorted(void (*function)(avl_node *))
    {
        __do_inorder(function, _root);
    }
    void do_postorder(void (*function)(avl_node *))
    {
        __do_postorder(function, _root);
    }
    void do_preorder_dfs(void (*function)(avl_node *))
    {
        __do_preorder(function, _root);
    }
    avl_node *unsafe_get_root()
    {
        return _root;
    }
};