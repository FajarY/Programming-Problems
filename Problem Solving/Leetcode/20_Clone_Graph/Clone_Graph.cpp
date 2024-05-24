/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> neighbors;
    Node() {
        val = 0;
        neighbors = vector<Node*>();
    }
    Node(int _val) {
        val = _val;
        neighbors = vector<Node*>();
    }
    Node(int _val, vector<Node*> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};
*/

class Solution {
public:
    Node* cloneGraph(Node* node) {
        if(node == nullptr)
        {
            return node;
        }
        
        queue<pair<Node*, Node*>> open_set;
        unordered_map<Node*, Node*> kvp_set;

        Node* root_node = new Node(node->val);
        open_set.push(make_pair(node, root_node));
        kvp_set[node] = root_node;

        while(!open_set.empty())
        {
            pair<Node*, Node*> current = open_set.front();
            open_set.pop();

            Node* real_node = current.first;
            Node* copy_node = current.second;

            for(int i = 0; i < real_node->neighbors.size(); i++)
            {
                Node* real_node_neighbor = real_node->neighbors[i];

                Node* copy_node_neighbor = nullptr;
                if(kvp_set.find(real_node_neighbor) == kvp_set.end())
                {
                    copy_node_neighbor = new Node(real_node_neighbor->val);
                    kvp_set[real_node_neighbor] = copy_node_neighbor;

                    open_set.push(make_pair(real_node_neighbor, copy_node_neighbor));
                }
                else
                {
                    copy_node_neighbor = kvp_set[real_node_neighbor];
                }

                copy_node->neighbors.push_back(copy_node_neighbor);
            }
        }

        return root_node;
    }
};