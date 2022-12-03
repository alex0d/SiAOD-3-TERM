#include <iostream>
#include <string>
#include <queue>
#include <unordered_map>

using namespace std;

// Узел дерева
struct Node {
    char ch;  // Символ
    int freq;  // Частота
    Node* left;  // Левый потомок
    Node* right;  // Правый потомок

    Node(char ch, int freq) : ch(ch), freq(freq), left(nullptr), right(nullptr) {}
    Node(char ch, int freq, Node* left, Node* right) : ch(ch), freq(freq), left(left), right(right) {}
};

// Функция рекурсивно проходит по дереву и заполняет таблицу кодов
void encode(Node* root, string str, unordered_map<char, string>& codingTable) {
    if (root == nullptr) {
        return;
    }

    if (!root->left && !root->right) {  // Лист
        codingTable[root->ch] = str;
    }

    encode(root->left, str + "0", codingTable);  // Проходим по левому поддереву
    encode(root->right, str + "1", codingTable);  // Проходим по правому поддереву
}

// Строит дерево Хаффмана и возвращает его корень
Node* buildHuffmanTree(const string& originalString) {
    unordered_map<char, int> freq;  // Частота символов
    for (char ch : originalString) {
        freq[ch]++;
    }

    struct comp {
        bool operator()(Node* l, Node* r) {
            return l->freq > r->freq;
        }
    };
    priority_queue<Node*, vector<Node*>, comp> queue;  // Очередь с приоритетом

    for (auto pair : freq) {
        // Создаем листы (символы) и добавляем в очередь
        queue.push(new Node(pair.first, pair.second));
    }

    while (queue.size() != 1) {
        // Берем два элемента с наименьшей частотой
        Node* left = queue.top(); queue.pop();
        Node* right = queue.top();	queue.pop();

        // Создаем новый узел с суммой частот и добавляем в очередь
        int sum = left->freq + right->freq;
        queue.push(new Node('\0', sum, left, right));
    }


    return queue.top();
}

// Декодирование строки
string decode(const string& encodedString, const unordered_map<char, string>& codingTable) {
    unordered_map<string, char> encodingTable;
    for (auto& [ch, code] : codingTable) {
        encodingTable[code] = ch;
    }

    string currentCode;
    string decodedString;

    for (char c : encodedString) {
        currentCode += c;
        if (encodingTable.find(currentCode) != encodingTable.end()) {
            decodedString += encodingTable[currentCode];
            currentCode = "";
        }
    }
    return decodedString;
}

// Huffman coding algorithm
int main() {
    string originalString = "Far out in the uncharted backwaters of the unfashionable end of the western spiral arm of the Galaxy lies a small unregarded yellow sun. Orbiting this at a distance of roughly ninety-two million miles is an utterly insignificant little blue green planet whose ape-descended life forms are so amazingly primitive that they still think digital watches are a pretty neat idea.";
    cout << "Original string: " << originalString << endl << endl;

    Node* root = buildHuffmanTree(originalString);

    unordered_map<char, string> codingTable;
    encode(root, "", codingTable);

    cout << "Coding table:" << endl;
    for (auto pair : codingTable) {
        cout << pair.first << " - " << pair.second << '\n';
    }
    cout << endl;

    cout << "String encoded by the Shannon-Fano method: ";
    string encodedString;
    for (char c : originalString) {
        encodedString += codingTable[c];
        cout << codingTable[c] << " ";  // Вывод кодов символов через пробел
    }
    cout << endl;

    cout << "\nBefore compression: " << originalString.length() * 8 << " bits" << endl;
    cout << "After compression: " << encodedString.length() << " bits" << endl;
    cout << "Compression ratio: " << (double)encodedString.length() / (originalString.length() * 8) << endl;

    cout << "\nDecoding: " << decode(encodedString, codingTable);

    return 0;
}