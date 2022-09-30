#include <iostream>
#include <iomanip>

#include "HashTable.h"
#include "BankAccount.h"

HashTable::HashTable(int initial_capacity) {
    this->capacity = initial_capacity;
    number_of_elements = 0;
    table = new BankAccount*[capacity];
    for (int i = 0; i < capacity; i++) {
        table[i] = nullptr;
    }
}

int HashTable::hash(int key) {
    return key % capacity;
}

void HashTable::insert(BankAccount* account) {
    if ((float) (number_of_elements + 1) / capacity > 0.75) {
        rehash();
    }

    int h = hash(account->getAccountNumber());
    for (int i = 0; i < capacity; i++) {
        int index = h + i * C;

        if (index >= capacity) {
            rehash();
            h = hash(account->getAccountNumber());
            i = 0;
            continue;
        }

        if (table[index] == nullptr) {
            table[index] = account;
            number_of_elements++;
            return;
        }
    }
}

BankAccount* HashTable::search(int key) {
    int h = hash(key);
    for (int i = 0; i < capacity; i++) {
        int index = h + i * C;
        if (index >= capacity) {
            return nullptr;
        }
        if (table[index] != nullptr && table[index]->getAccountNumber() == key) {
            return table[index];
        }
    }
    return nullptr;
}

bool HashTable::del(int index) {
    if (index < 0 || index >= capacity) {
        return false;
    }
    if (table[index] != nullptr) {
        delete table[index];
        table[index] = nullptr;
        number_of_elements--;
        return true;
    }
    return false;
}

void HashTable::rehash() {
    BankAccount** old_table = table;
    int old_capacity = capacity;
    capacity *= 2;
    number_of_elements = 0;
    table = new BankAccount*[capacity];
    for (int i = 0; i < capacity; i++) {
        table[i] = nullptr;
    }
    for (int i = 0; i < old_capacity; i++) {
        if (old_table[i] != nullptr) {
            insert(old_table[i]);
        }
    }
    delete[] old_table;

    std::cout << "# Выполнено рехеширование. Размер таблицы: " << old_capacity << " -> " << capacity << std::endl;
}

void HashTable::print() {
    std::cout << "+- Индекс -+- Номер счета -+-------------- ФИО --------------+-------------- Адрес ------------+" << std::endl;
    for (int i = 0; i < capacity; i++) {
        if (table[i] != nullptr) {
            std::cout << "| " << std::setw(8) << i << " | " << std::setw(13) << table[i]->getAccountNumber() << " | " << std::setw(31) << table[i]->getFullname() << " | " << std::setw(31) << table[i]->getAddress() << " |" << std::endl;
        }
    }
    std::cout << "+----------+---------------+---------------------------------+---------------------------------+" << std::endl;
    std::cout << "# Коэффициент заполнения: " << (float) number_of_elements / capacity << std::endl;
}