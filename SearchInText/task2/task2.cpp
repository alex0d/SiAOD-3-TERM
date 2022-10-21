#include <iostream>
#include <vector>
#include "Windows.h"

#include "HashTable.h"

// Построение списка стоп-символов для шаблона pattern
std::vector<size_t> badCharHeuristic(const std::string& pattern) {
    std::vector<size_t> badChar(256, pattern.size());  // инициализируем все символы значениями pattern.size()
    for (size_t i = 0; i < pattern.size() - 1; i++) {
        // Записываем в badChar индекс последнего вхождения символа (с конца)
        badChar[pattern[i]] = pattern.size() - i - 1;
    }
    return badChar;
}

// Алгоритма Бойера-Мура-Хорспула
int count_substr(const std::string& text, const std::string& pattern) {
    int occurrences = 0;

    std::vector<size_t> badChar = badCharHeuristic(pattern);  // список стоп-символов
    size_t i = pattern.size() - 1;  // индекс в строке text, начиная с которого ищем вхождение шаблона pattern

    while (i < text.size()) {
        size_t j = pattern.size() - 1;  // индекс в шаблоне pattern
        while (j > 0 && text[i] == pattern[j]) {  // сравниваем символы с конца
            i--;
            j--;
        }
        if (j == 0 && text[i] == pattern[j]) {
            // шаблон pattern полностью совпал с подстрокой text[i : i + pattern.size()]
            occurrences++;
            i += 2 * pattern.size() - 1;  // переходим к следующему возможному вхождению шаблона
        } else {
            i += badChar[text[i]];  // сдвигаемся на расстояние, равное стоп-символу
        }
    }
    return occurrences;
}

int main() {
    SetConsoleCP(1251);  // установка кодировки Windows-1251 в потоке ввода
    SetConsoleOutputCP(1251);  // установка кодировки Windows-1251 в потоке вывода

    std::string text;
    std::cout << "Введите текст: ";
    std::getline(std::cin, text);

    int n;
    std::cout << "Введите количество шаблонов: ";
    std::cin >> n;

    HashTable<std::string> patterns(n);  // хеш-таблица шаблонов

    std::string pattern;
    for (int i = 0; i < n; i++) {
        std::cout << "Введите шаблон " << i + 1 << ": ";
        std::cin >> pattern;
        int occurrences = count_substr(text, pattern);  // количество вхождений шаблона в текст
        patterns.insert(pattern, occurrences);  // добавляем шаблон в хеш-таблицу
    }

    patterns.print();

    return 0;
}