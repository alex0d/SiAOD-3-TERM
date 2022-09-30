#pragma once

#include <string>

// Массивы для генерации случайных данных
extern const char* SAMPLE_SURNAMES[];  // массив фамилий
extern const char* SAMPLE_NAMES[];  // массив имен
extern const char* SAMPLE_PATRONYMIC[];  // массив отчеств
extern const char* SAMPLE_CITIES[];  // массив городов
extern const char* SAMPLE_STREETS[];  // массив улиц

class BankAccount {
private:
    int account_number;  // номер счета
    std::string fullname;  // ФИО
    std::string address;  // адрес

public:
    BankAccount(int account_number, const std::string& fullname, const std::string& address);

    int getAccountNumber() const;  // получить номер счета

    const std::string &getFullname() const;  // получить ФИО

    const std::string &getAddress() const;  // получить адрес

    void print();  // вывести информацию о счете

    static BankAccount* generateRandomAccount();  // сгенерировать случайный счет
};

