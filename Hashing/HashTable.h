#pragma once

#include <iostream>
#include <iomanip>

#include "BankAccount.h"

class HashTable {
private:
    BankAccount** table;  // массив указателей на объекты класса BankAccount
    int capacity;  // размер массива table
    int number_of_elements;  // количество элементов в массиве table
    static const int C = 1;  // шаг перебора

public:
    HashTable(int initial_capacity);

    int hash(int key);  // хэш-функция

    void insert(BankAccount* account);  // вставка записи в таблицу

    BankAccount* search(int key);  // поиск записи в таблице по ключу

    bool del(int index);  // удаление записи из таблицы по её индексу

    void rehash(); // рехеширование

    void print(); // вывод таблицы
};
