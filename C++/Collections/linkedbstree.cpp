// ========[BST Tree]======== //
/*
    Dimodifikasi oleh KADEK FAJAR PRAMARTHA YASODANA, Sumber Modul https://github.com/Algoritma-dan-Pemrograman-ITS/StrukturData/blob/master/For%20C%2B%2B/Binary%20Search%20Tree/unique_binary_search_tree.cpp
    Support Template
    Beberapa fungsi ada di modul, Inorder (Sorted), Postorder, Preorder (DFS)
    Support Comparer
*/
#define NULL __null

template <typename T>
struct linkedbstree_standard_index_comparer
{
    int operator()(const T &left, const T &right)
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

template <typename T, typename index_comparer = linkedbstree_standard_index_comparer<T>>
class linkedbstree
{
public:
    struct linkedbstree_node
    {
        T data;
        linkedbstree_node *left, *right;
    };

private:
    linkedbstree_node *_root;
    unsigned _size;
    int version;
    index_comparer comparer;

    linkedbstree_node *_bst_createNode(T value)
    {
        linkedbstree_node *newNode = new linkedbstree_node;
        newNode->data = value;
        newNode->left = newNode->right = NULL;
        return newNode;
    }

    linkedbstree_node *_search(linkedbstree_node *root, T value)
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

    linkedbstree_node *_insert_BST(linkedbstree_node *node, T value)
    {

        if (node == NULL)
            return _bst_createNode(value);

        int check = comparer(value, node->data);
        if (check < 0)
            node->left = _insert_BST(node->left, value);
        else if (check > 0)
            node->right = _insert_BST(node->right, value);

        return node;
    }

    linkedbstree_node *_findMinNode(linkedbstree_node *node)
    {
        linkedbstree_node *currNode = node;
        while (currNode && currNode->left != NULL)
            currNode = currNode->left;
        return currNode;
    }

    linkedbstree_node *_remove_BST(linkedbstree_node *node, T value)
    {
        if (node == NULL)
            return node;
        int check = comparer(value, node->data);
        if (check > 0)
            node->right = _remove_BST(node->right, value);
        else if (check < 0)
            node->left = _remove_BST(node->left, value);
        else
        {
            linkedbstree_node *temp;
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
                node->right = _remove_BST(node->right, temp->data);
            }
        }

        if (node == NULL)
            return node;

        return node;
    }
    void __do_inorder(void (*function)(linkedbstree_node *), linkedbstree_node *current)
    {
        if (current != NULL)
        {
            __do_inorder(function, current->left);
            function(current);
            __do_inorder(function, current->right);
        }
    }
    void __do_postorder(void (*function)(linkedbstree_node *), linkedbstree_node *current)
    {
        if (current != NULL)
        {
            __do_postorder(function, current->left);
            __do_postorder(function, current->right);
            function(current);
        }
    }
    void __do_preorder(void (*function)(linkedbstree_node *), linkedbstree_node *current)
    {
        if (current != NULL)
        {
            function(current);
            __do_preorder(function, current->left);
            __do_preorder(function, current->right);
        }
    }
    static void _delete_node(linkedbstree_node* node)
    {
        delete node;
    }

public:
    linkedbstree()
    {
        _root = NULL;
        _size = 0U;
        comparer = index_comparer();
    }
    ~linkedbstree()
    {
        do_preorder_dfs(_delete_node);
    }
    bool is_empty()
    {
        return _root == NULL;
    }
    bool find(T value)
    {
        linkedbstree_node *temp = _search(_root, value);
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
            _root = _insert_BST(_root, value);
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
            _root = _remove_BST(_root, value);
            version++;
            _size--;
            return true;
        }
        return false;
    }
    // Sorted
    void do_inorder_sorted(void (*function)(linkedbstree_node *))
    {
        __do_inorder(function, _root);
    }
    void do_postorder(void (*function)(linkedbstree_node *))
    {
        __do_postorder(function, _root);
    }
    void do_preorder_dfs(void (*function)(linkedbstree_node *))
    {
        __do_preorder(function, _root);
    }
    linkedbstree_node *unsafe_get_root()
    {
        return _root;
    }
};