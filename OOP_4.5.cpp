#include <iostream>
#include <stdexcept>  // Для обработки исключений

template <typename T>
class BinaryTree {
   private:
    struct Node {
        T data;
        Node* left;
        Node* right;

        Node(const T& value) : data(value), left(nullptr), right(nullptr) {}
    };

    Node* root;

    // Рекурсивная очистка дерева
    void clear(Node* node) {
        if (node) {
            clear(node->left);
            clear(node->right);
            delete node;
        }
    }

    // Рекурсивное копирование узлов
    Node* copy(Node* otherNode) {
        if (!otherNode) return nullptr;
        Node* newNode = new Node(otherNode->data);
        newNode->left = copy(otherNode->left);
        newNode->right = copy(otherNode->right);
        return newNode;
    }

    // Рекурсивная вставка элемента
    void insert(Node*& node, const T& value) {
        if (!node) {
            node = new Node(value);
        } else {
            if (value < node->data) {
                insert(node->left, value);
            } else {
                insert(node->right, value);
            }
        }
    }

    Node* removeLeaf(Node* node, const T& key) {
        if (!node) return nullptr;
        if (node->data == key) {
            if (!node->left && !node->right) {
                delete node;
                return nullptr;
            }
            return node;
        }

        node->left = removeLeaf(node->left, key);
        node->right = removeLeaf(node->right, key);
        return node;
    }

    // Поиск узла по ключу
    Node* search(Node* node, const T& key) const {
        if (!node) return nullptr;
        if (node->data == key) return node;  // Узел найден
        // Рекурсивный поиск в поддеревьях
        Node* found = search(node->left, key);
        return found ? found : search(node->right, key);
    }

    void printInOrder(Node* node) const {
        if (node) {
            printInOrder(node->left);
            std::cout << node->data << " ";
            printInOrder(node->right);
        }
    }

   public:
    BinaryTree() : root(nullptr) {}  // Конструктор по умолчанию

    // Конструктор с параметром
    BinaryTree(const T& value) : root(new Node(value)) {}

    // Конструктор копирования
    BinaryTree(const BinaryTree& other) : root(copy(other.root)) {}

    // Деструктор
    ~BinaryTree() { clear(); }

    // Оператор присваивания
    BinaryTree& operator=(const BinaryTree& other) {
        if (this != &other) {
            clear();
            root = copy(other.root);
        }
        return *this;
    }

    // Перемещающий конструктор (крадет ресурсы другого объекта)
    BinaryTree(BinaryTree&& other) noexcept : root(other.root) { other.root = nullptr; }

    // Перемещающий оператор присваивания
    BinaryTree& operator=(BinaryTree&& other) noexcept {
        if (this != &other) {
            clear();
            root = other.root;
            other.root = nullptr;
        }
        return *this;
    }

    // Методы работы с деревом
    void initFirstElement(const T& value) {
        if (!root) {
            root = new Node(value);
        }
    }

    // Публичный метод вставки
    void insert(const T& value) { insert(root, value); }

    // Удаление листа по ключу
    bool removeLeaf(const T& key) {
        Node* target = search(root, key);

        if (!target || target->left || target->right) return false;
        root = removeLeaf(root, key);
        return true;
    }

    // Поиск элемента по ключу
    bool search(const T& key) const { return search(root, key) != nullptr; }

    // Вывод элементов дерева
    void print() const {
        printInOrder(root);
        std::cout << std::endl;
    }

    // Очистка дерева
    void clear() {
        clear(root);
        root = nullptr;
    }

    T findLeftmostLeaf() const {
        if (!root) throw std::logic_error("Tree is empty");
        Node* current = root;

        while (current->left || current->right) {
            current = current->left ? current->left : current->right;
        }
        return current->data;
    }
};

int main() {
    BinaryTree<int> tree;
    tree.insert(5);
    tree.insert(3);
    tree.insert(7);
    tree.insert(2);  // Самый левый лист
    tree.insert(4);
    tree.insert(6);
    std::cout << "Leftmost leaf (Example 1): " << tree.findLeftmostLeaf() << std::endl;

    BinaryTree<int> tree2;
    tree2.insert(10);
    tree2.insert(5);
    tree2.insert(15);
    tree2.insert(1);  // Самый левый лист
    tree2.insert(8);
    std::cout << "Leftmost leaf (Example 2): " << tree2.findLeftmostLeaf() << std::endl;

    BinaryTree<int> tree3;
    tree3.insert(10);
    tree3.insert(15);
    tree3.insert(12);
    tree3.insert(17);
    tree3.insert(11);  // Самый левый лист
    std::cout << "Leftmost leaf (Example 3): " << tree3.findLeftmostLeaf() << std::endl;

    std::cin.ignore();
    std::cin.get();
    return 0;
}