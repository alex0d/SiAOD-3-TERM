#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

map<char, string> codingTable;
map<string, char> encodingTable;

// Узел дерева
struct Node {
    string key;   // Ключ
    Node* left;  // Левый потомок
    Node* right;  // Правый потомок
    Node(string key) : key(key), left(nullptr), right(nullptr) {};
};

// Возвращает вектор пар символ-частота вхождения символа в строку
vector<pair<char, int>> getAlphabet(string s) {
    map<char, int> charCount;
    vector<pair<char, int>> pairs;
    for (char i : s) {
        if (charCount.count(i) == 0) {
            charCount[i] = 1;
        }
        else {
            charCount[i]++;
        }
    }
    copy(charCount.begin(), charCount.end(), back_inserter(pairs));  // Копируем пары в вектор
    sort(pairs.begin(),
         pairs.end(),
         [](pair<char, int> a, pair<char, int> b) { return a.second > b.second; });  // Сортируем по частоте
    return pairs;
}

/*
 * Построение дерева Шеннона-Фано
 *
 * direction - направление движения по дереву
 * pathToCurrent - путь от корня до текущего узла
 * startPos - начальная позиция в алфавите
 * endPos - конечная позиция в афавите
 * alphabet - алфавит
 * current - текущий узел
 */
void builtShannonFanoTree(char direction, string pathToCurrent, int startPos, int endPos, vector<pair<char, int>> alphabet, Node* current) {
    if (direction == '0') {
        current->left = new Node(to_string(direction));
        current = current->left;
    }
    else if (direction == '1') {
        current->right = new Node(to_string(direction));
        current = current->right;
    }

    if (direction != CHAR_MAX) {  // Если не корень
        pathToCurrent += direction;
    }

    if (startPos == endPos) {  // Если в алфавите остался только один символ
        codingTable[alphabet[startPos].first] = pathToCurrent;
        encodingTable.insert(make_pair(pathToCurrent, alphabet[startPos].first));
        return;
    }

    double middleFreq = 0;  // Средняя частота
    for (int i = startPos; i < endPos; i++) {
        middleFreq += alphabet[i].second;
    }
    middleFreq /= 2;

    int middlePos = startPos;  // Позиция символа с частотой, ближайшей к средней
    double sum = 0;
    for (int i = startPos; i < endPos; i++) {
        sum += alphabet[i].second;
        if (sum >= middleFreq) {
            middlePos = i;
            break;
        }
    }

    builtShannonFanoTree('0', pathToCurrent, startPos, middlePos, alphabet, current);  // Построение левого поддерева
    builtShannonFanoTree('1', pathToCurrent, middlePos + 1, endPos, alphabet, current);  // Построение правого поддерева
}

// Декодирование строки
string decode(const string& encodedString) {
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

int main() {
    string originalString = "Far out in the uncharted backwaters of the unfashionable end of the western spiral arm of the Galaxy lies a small unregarded yellow sun. Orbiting this at a distance of roughly ninety-two million miles is an utterly insignificant little blue green planet whose ape-descended life forms are so amazingly primitive that they still think digital watches are a pretty neat idea.";
    cout << "Original string: " << originalString << endl << endl;

    vector<pair<char, int>> alphabet = getAlphabet(originalString);

    Node* ShannonFanoTree = new Node("");
    builtShannonFanoTree(CHAR_MAX, "", 0, alphabet.size() - 1, alphabet, ShannonFanoTree);

    cout << "Coding table:" << endl;
    for (auto i : codingTable) {
        cout << i.first << " - " << i.second << endl;
    }
    std::cout << std::endl;

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

    cout << "\nDecoding: " << decode(encodedString);
    return 0;
}
