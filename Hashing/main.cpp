#include <iostream>
#include <string>

#include "BankAccount.h"
#include "HashTable.h"

int main() {
    HashTable* table = new HashTable(3);

    int cmd = 1;
    while (cmd) {
        std::cout << "\n1. Вставка\t2. Генерация случайных записей\t3. Удаление\t4. Поиск по ключу\t5. Вывод таблицы\n";
        std::cout << "Введите команду: ";
        std::cin >> cmd;
        switch (cmd) {
            case 1: {
                std::cout << "Создание нового счёта..." << std::endl;
                std::cout << "Введите номер счёта: ";
                int account_number;
                std::cin >> account_number;

                std::cin.sync();  // очистка буфера
                std::cout << "Введите ФИО: ";
                std::string fullname;
                std::getline(std::cin, fullname);

                std::cin.sync();  // очистка буфера
                std::string address;
                std::cout << "Введите адрес: ";
                std::getline(std::cin, address);

                table->insert(new BankAccount(account_number, fullname, address));
                std::cout << "Счёт успешно создан." << std::endl;
            } break;

            case 2: {
                std::cout << "Сколько записей сгенерировать?: ";
                int n;
                std::cin >> n;
                for (int i = 0; i < n; i++) {
                    table->insert(BankAccount::generateRandomAccount());
                }
                std::cout << "Записи успешно сгенерированы и вставлены в таблицу." << std::endl;
            } break;

            case 3: {
                std::cout << "Введите индекс: ";
                int index;
                std::cin >> index;
                if (table->del(index)) {
                    std::cout << "Счёт успешно удалён." << std::endl;
                } else {
                    std::cout << "Счёта с таким индексом не существует." << std::endl;
                }
            } break;

            case 4: {
                std::cout << "Введите номер счёта: ";
                int account_number;
                std::cin >> account_number;
                BankAccount *account = table->search(account_number);
                if (account != nullptr) {
                    account->print();
                } else {
                    std::cout << "Счёт не найден." << std::endl;
                }
            } break;

            case 5:
                table->print();
                break;

            default:
                break;
        }
    }

    return 0;
}
