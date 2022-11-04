#include <iostream>
#include <vector>
#include <queue>

enum Color { Black, Red };

struct Node {
    int key;  // значение узла
    Color color;  // цвет узла
    Node* parent;  // родитель
    Node* left;  // левый потомок
    Node* right;  // правый потомок
    Node(int k, Color c, Node* p, Node* l, Node* r) : key(k), color(c), parent(p), left(l), right(r) {};
};

class RBTree {
public:
    RBTree();  // Конструктор
    ~RBTree();  // Деструктор

    void insert(int key);  // Вставляем узел со значением key
    void inOrderTraversal();  // Симметричный обход
    void breadthFirstTraversal();  // Обход в ширину
    int leafSum();  // Сумма значений листьев
    double average();  // Среднее арифметическое всех узлов
    void print();  // Печать дерева (с указанием цвета и родителей)

private:
    Node* root;  // Корень дерева

    void rotateLeft(Node* &root, Node* x);  // Левый поворот вокруг x
    void rotateRight(Node* &root, Node* y);  // Правый поворот вокруг y
    void insertFixUp(Node* node);  // Восстановление свойств красно-черного дерева после вставки
    void deleteTree(Node* &node);  // Удаление всех узлов дерева (освобождение памяти)

    void print(Node* node);  // Рекурсивная печать дерева
    void inOrderTraversal(Node* tree);  // Рекурсивный симметричный обход
};

RBTree::RBTree(): root(nullptr) {}

void RBTree::rotateLeft(Node* &root, Node* x) {
    Node* y = x->right;  // узел, который станет левым потомком x
    x->right = y->left;  // левый потомок y становится правым потомком x
    if (y->left) {
        y->left->parent = x;  // родитель x становится родителем левого потомка y
    }

    y->parent = x->parent;  // родитель y становится родителем x
    if (!x->parent) {
        root = y;  // если x - корень, то y становится корнем
    }
    else {
        if (x == x->parent->left) {
            x->parent->left = y;  // если x - левый потомок, то y становится левым потомком
        }
        else {
            x->parent->right = y;  // если x - правый потомок, то y становится правым потомком
        }
    }
    y->left = x;  // x становится левым потомком y
    x->parent = y;  // родитель x становится родителем y
}

void RBTree::rotateRight(Node* &root, Node* y) {
    Node*x = y->left;  // узел, который станет правым потомком y
    y->left = x->right;  // правый потомок x становится левым потомком y
    if (x->right) {
        x->right->parent = y;  // родитель y становится родителем правого потомка x
    }

    x->parent = y->parent;  // родитель x становится родителем y
    if (!y->parent) {
        root = x;  // если y - корень, то x становится корнем
    }
    else {
        if  (y == y->parent->right) {
            y->parent->right = x;  // если y - правый потомок, то x становится правым потомком
        }
        else {
            y->parent->left = x;  // если y - левый потомок, то x становится левым потомком
        }
    }
    x->right = y;  // y становится правым потомком x
    y->parent = x;  // родитель y становится родителем x
}

void RBTree::insert(int key) {
    Node* node = new Node(key, Red, nullptr, nullptr, nullptr);
    Node *x = root;
    Node *y = nullptr;
    while (x) {
        y = x;
        if (node->key > x->key) {  // если ключ вставляемого узла больше ключа текущего узла
            x = x->right;  // идем вправо
        }
        else {  // если ключ вставляемого узла меньше или равен ключу текущего узла
            x = x->left;  // идем влево
        }
    }
    node->parent = y;  // родитель вставляемого узла становится последним пройденным узлом
    if (y) {  // если дерево не пустое
        if (node->key > y->key) {  // если ключ вставляемого узла больше ключа родителя
            y->right = node;  // вставляемый узел становится правым потомком родителя
        }
        else {  // если ключ вставляемого узла меньше или равен ключу родителя
            y->left = node;  // вставляемый узел становится левым потомком родителя
        }
    }
    else {
        root = node;  // если дерево пустое, то вставляемый узел становится корнем
    }
    node->color = Red;  // цвет вставляемого узла - красный
    insertFixUp(node);  // необходимо исправить свойства красно-черного дерева
}

void RBTree::insertFixUp(Node* node) {
    Node* parent;
    parent = node->parent;
    while (node != root && parent->color == Red) {  // пока не дойдем до корня и пока родитель node - красный
        Node* gparent = parent->parent;  // дедушка node
        if (!gparent) {
            break;
        }
        if (gparent->left == parent) {  // если родитель node - левый потомок дедушки
            Node* uncle = gparent->right;  // дядя node
            if (uncle && uncle->color == Red) {  // если дядя node - красный
                parent->color = Black;
                uncle->color = Black;
                gparent->color = Red;
                node = gparent;
                parent = node->parent;
            }
            else {  // если дядя node - черный
                if (parent->right == node) {  // если node - правый потомок родителя
                    rotateLeft(root, parent);  // левый поворот вокруг родителя
                    std::swap(node, parent);
                }
                rotateRight(root, gparent);  // правый поворот вокруг дедушки
                gparent->color = Red;
                parent->color = Black;
                break;
            }
        }
        else {
            Node* uncle = gparent->left;  // дядя node
            if (uncle && uncle->color == Red) {  // если дядя node - красный
                gparent->color = Red;
                parent->color = Black;
                uncle->color = Black;

                node = gparent;
                parent = node->parent;
            }
            else {  // если дядя node - черный
                if (parent->left == node) {  // если node - левый потомок родителя
                    rotateRight(root, parent);  // правый поворот вокруг родителя
                    std::swap(parent, node);
                }
                rotateLeft(root, gparent);  // левый поворот вокруг дедушки
                parent->color = Black;
                gparent->color = Red;
                break;
            }
        }
    }
}

void RBTree::print() {
    if (!root) {
        std::cout << "Элементов нет." << std::endl;
        return;
    }

    print(root);
}

void RBTree::print(Node* node) {
    if (!node) {
        return;
    }

    if (!node->parent) {
        std::cout << node->key << " - корень" << std::endl;
    }
    else if(node->parent->left == node) {
        if (node->color == Red) {
            std::cout << "\033[91m" << node->key << "\033[0m" << " - левый потомок " << node->parent->key << std::endl;
        }
        else {
            std::cout << node->key << " - левый потомок " << node->parent->key << std::endl;
        }
    }
    else {
        if (node->color == Red) {
            std::cout << "\033[91m" << node->key << "\033[0m" << " - правый потомок " << node->parent->key << std::endl;
        }
        else {
            std::cout << node->key << " - правый потомок " << node->parent->key << std::endl;
        }
    }
    print(node->left);
    print(node->right);
}

void RBTree::inOrderTraversal() {
    if (!root) {
        std::cout << "Элементов нет." << std::endl;
        return;
    }

    inOrderTraversal(root);  // запускаем рекурсивную функцию
}

void RBTree::inOrderTraversal(Node* tree) {
    if (tree) {
        inOrderTraversal(tree->left);  // рекурсивно обходим левое поддерево
        std::cout << tree->key << " ";  // выводим корень
        inOrderTraversal(tree->right);  // рекурсивно обходим правое поддерево
    }
}

void RBTree::breadthFirstTraversal() {
    if (!root) {
        std::cout << "Элементов нет." << std::endl;
        return;
    }

    std::queue<Node*> q;  // очередь для обхода
    q.push(root);
    while (!q.empty()) {
        Node* node = q.front();
        q.pop();
        std::cout << node->key << " ";
        if (node->left) {
            q.push(node->left);
        }
        if (node->right) {
            q.push(node->right);
        }
    }
}

int RBTree::leafSum() {
    if (!root) {
        std::cout << "Элементов нет." << std::endl;
        return 0;
    }

    int sum = 0;

    std::queue<Node*> q;
    q.push(root);
    while (!q.empty()) {
        Node* node = q.front();
        q.pop();
        if (node->left) {
            q.push(node->left);
        }
        if (node->right) {
            q.push(node->right);
        }
        if (!node->left && !node->right) {  // если узел - лист
            sum += node->key;
        }
    }
    return sum;
}

double RBTree::average() {
    if (!root) {
        std::cout << "Элементов нет." << std::endl;
        return 0;
    }

    int sum = 0;
    int count = 0;

    std::queue<Node*> q;
    q.push(root);
    while (!q.empty()) {
        Node* node = q.front();
        q.pop();
        if (node->left) {
            q.push(node->left);
        }
        if (node->right) {
            q.push(node->right);
        }
        sum += node->key;
        count++;
    }
    return (double) sum / count;
}

RBTree::~RBTree() {
    deleteTree(root);
}

void RBTree::deleteTree(Node* &node) {
    if (!node) {
        return;
    }
    deleteTree(node->left);
    deleteTree(node->right);

    delete node;
    node = nullptr;
}

int main() {
    RBTree tree;

    int cmd = 1;
    while (cmd) {
        std::cout << "\n1. Вставить множество элементов\t" <<
                    "2. Вставить элемент\t" <<
                    "3. Симметричный обход\t" <<
                    "4. Обход в ширину\t" <<
                    "5. Найти сумму значений листьев\t" <<
                    "6. Найти среднее арифметическое всех узлов\t"
                    "7. Вывести дерево\n";
        std::cout << "Введите команду: ";
        std::cin >> cmd;

        switch (cmd) {
            case 1: {
                int n;
                std::cout << "Введите количество элементов: ";
                std::cin >> n;
                std::cout << "Введите элементы: ";
                for (int i = 0; i < n; i++) {
                    int key;
                    std::cin >> key;
                    tree.insert(key);
                }
                std::cout << "Множество элементов успешно вставлено." << std::endl;
                break;
            }
            case 2: {
                int key;
                std::cout << "Введите элемент: ";
                std::cin >> key;
                tree.insert(key);
                std::cout << "Элемент успешно вставлен." << std::endl;
                break;
            }
            case 3: {
                tree.inOrderTraversal();
                std::cout << std::endl;
                break;
            }
            case 4: {
                tree.breadthFirstTraversal();
                std::cout << std::endl;
                break;
            }
            case 5: {
                std::cout << "Сумма значений листьев: " << tree.leafSum() << std::endl;
                break;
            }
            case 6: {
                std::cout << "Среднее арифметическое всех узлов: " << tree.average() << std::endl;
                break;
            }
            case 7:
                tree.print();
                break;
            default:
                break;
        }
    }

    return 0;
}
