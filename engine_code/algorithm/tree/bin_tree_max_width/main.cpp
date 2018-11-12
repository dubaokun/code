// the max width for the binary tree
// use the recursion to deal it 
// use the circulation to deal it 
// sometime the recurtion idea is not a good idea

#ifndef _BIN_TREE_MAX_DEEP_LENGTH
#define _BIN_TREE_MAX_DEEP_LENGTH

int max(int a, int b) {
    return (a > b? a : b);
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
    int TreeDepthByRecursion(TreeNode * root) {
        if (NULL == root) {
            return 0;
        }
        
        return max(TreeDepthRecursion(root->left), TreeDepthRecursion(root->right)) + 1;
    }
};

#endif
