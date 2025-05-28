#include <iostream>
#include <vector>
#include <stdexcept>

using namespace std;

struct TreeNode 
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

TreeNode* insert(TreeNode* root, int val) // логика заполнения
{
    if (!root) return new TreeNode(val);
    if (val < root->val) 
        root->left = insert(root->left, val);
    else 
        root->right = insert(root->right, val);
    return root;
}

TreeNode* buildTree(const vector<int>& nums) // заполнение
{
    TreeNode* root = nullptr;
    for (int num : nums) 
        root = insert(root, num);
    return root;
}

int findLeftmostLeaf(TreeNode* root) 
{
    if (!root) throw invalid_argument("Tree is empty");
    TreeNode* current = root;
    while (true) {
        if (current->left) 
            current = current->left;
        else if (current->right) 
            current = current->right;
        else 
            return current->val;
    }
}

void inOrder(TreeNode* root) 
{
    if (!root) return;
    inOrder(root->left);
    cout << root->val << " ";
    inOrder(root->right);
}

int main() {
    vector<int> nums = {1, 3, 7, 5, 4};
    TreeNode* root = buildTree(nums);
    
    cout << "In-order traversal: ";
    inOrder(root);
    cout << "\nLeftmost leaf value: " << findLeftmostLeaf(root) << endl;
    
    cin.ignore(); // Игнорирование пустой строки
    cin.get();    // Для того, чтобы не закрывался консольный окно при запуске программ

    return 0;
}