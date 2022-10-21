#pragma once

#include <iostream>
#include <iomanip>

template <typename T>
class HashTable {
private:
    std::pair<T, int>* data;  // массив пар ключ-значение
    int capacity;  // размер массива data
    int number_of_elements;  // количество элементов в массиве data
    static const int C = 1;  // шаг перебора

public:
    HashTable(int initial_capacity) {
        this->capacity = initial_capacity;
        number_of_elements = 0;
        data = new std::pair<T, int>[capacity];
        for (int i = 0; i < capacity; i++) {
            // заполняем массив пустыми значениями
            data[i] = std::make_pair(T(), -1);
        }
    }

    int hash(const T& entry) {  // хэш-функция
        int hash = 0;
        for (int i = 0; i < entry.size(); i++) {
            // обратный полиномиальный хэш
            // 71 - простое число
            hash = hash * 71 + entry[i];
        }
        return hash % capacity;
    };

    void insert(const T& entry, int value) {  // вставка записи в таблицу
        if ((float) (number_of_elements + 1) / capacity > 0.75) {
            rehash();
        }

        int h = hash(entry);
        for (int i = 0; i < capacity; i++) {
            int index = h + i * C;

            if (index >= capacity) {
                rehash();
                h = hash(entry);
                i = 0;
                continue;
            }

            if (data[index].second == -1) {
                data[index].first = entry;
                data[index].second = value;
                number_of_elements++;
                return;
            }
        }
    };

    int get(const T& entry) {  // поиск записи в таблице по ключу
        int h = hash(entry);
        for (int i = 0; i < capacity; i++) {
            int index = h + i * C;
            if (index >= capacity) {
                return -1;
            }
            if (data[index].first == entry) {
                return data[index].second;
            }
        }
        return -1;
    };

    bool set(const T& entry, int value) {  // изменение значения записи по ключу
        int h = hash(entry);
        for (int i = 0; i < capacity; i++) {
            int index = h + i * C;
            if (index >= capacity) {
                return false;
            }
            if (data[index].first == entry) {
                data[index].second = value;
                return true;
            }
        }
        return false;
    };

    bool del(const T& entry) {  // удаление записи из таблицы по ключу
        int h = hash(entry);
        for (int i = 0; i < capacity; i++) {
            int index = h + i * C;
            if (index >= capacity) {
                return false;
            }
            if (data[index].second != -1) {
                data[index].second = -1;
                number_of_elements--;
                return true;
            }
        }
        return false;
    };

    void rehash() {  // рехеширование
        std::pair<T, int>* old_data = data;
        int old_capacity = capacity;
        capacity *= 2;
        number_of_elements = 0;
        data = new std::pair<T, int>[capacity];
        for (int i = 0; i < capacity; i++) {
            data[i] = std::make_pair(T(), -1);
        }
        for (int i = 0; i < old_capacity; i++) {
            if (old_data[i].second != -1) {
                // вставляем в новую таблицу все элементы из старой
                insert(old_data[i].first, old_data[i].second);
            }
        }
        delete[] old_data;

//        std::cout << "# Выполнено рехеширование. Размер таблицы: " << old_capacity << " -> " << capacity << std::endl;
    };

    void print() {  // вывод таблицы
        std::cout << "+- Индекс -+----------- Строка -----------+- Количество -+" << std::endl;
        for (int i = 0; i < capacity; i++) {
            if (data[i].second != -1) {
                std::cout << "| " << std::setw(8) << i << " | " << std::setw(28) << data[i].first << " | " << std::setw(12) << data[i].second << " |" << std::endl;
            }
        }
        std::cout << "+----------+------------------------------+--------------+" << std::endl;
//        std::cout << "# Коэффициент заполнения: " << (float) number_of_elements / capacity << std::endl;
    };
};
