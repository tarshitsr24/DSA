class Solution {
public:
    int ans = 0;

    pair<int, int> dfs(TreeNode* root) {
        if (root == nullptr) {
            return {0, 0};
        }

        // Get sum and count from left subtree
        pair<int, int> left = dfs(root->left);

        // Get sum and count from right subtree
        pair<int, int> right = dfs(root->right);

        // Current subtree
        int sum = root->val + left.first + right.first;
        int count = 1 + left.second + right.second;

        // Check average
        if (root->val == sum / count) {
            ans++;
        }

        return {sum, count};
    }

    int averageOfSubtree(TreeNode* root) {
        dfs(root);
        return ans;
    }
};