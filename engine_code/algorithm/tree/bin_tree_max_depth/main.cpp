// the max depth for the binary tree
// use the recursion to deal it 
// use the circulation to deal it 
// sometime the recurtion idea is not a good idea

#ifndef _BIN_TREE_MAX_DEEP_LENGTH
#define _BIN_TREE_MAX_DEEP_LENGTH

#include <stdio.h>
#include <queue>

int max(int a, int b) {
    return (a > b? a: b);
}

struct TreeNode {
    int value;
    struct TreeNode *left;
    struct TreeNode *right;
    TreeNode(int x) :
            value(x), left(NULL), right(NULL) {
    }
};

class Solution {
public:
    Solution() {};
    virtual ~Solution() {};

public:
    int TreeWidth(TreeNode * root) {
        if (NULL == root) {
            return 0;
        }
    
        std::queue<TreeNode *> level_node_queue;
        level_node_queue.push_back(root);
        int max_width_total = 0; 
        int max_width_level = 0;

        while(!level_node_queue.empty()) {
            max_width_level = level_node_queue.size();
            max_width_total = max(max_width_total, max_width_level);
            
            for (int i = 0; i < max_width_level; ++i) {
                auto node = level_node_queue.pop_front();
                if (!node->left) level_node_queue.push_back(node->left);
                if (!node->right) level_node_queue.push+_back(node->right); 
            }
        }
               
        return max_width_total;
    }
};

#endif
