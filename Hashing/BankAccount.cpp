#include <iostream>
#include <string>

#include "BankAccount.h"

const char* SAMPLE_SURNAMES[] = {
        "Ivanov", "Petrov", "Sidorov", "Vasilev", "Nikolaev"
};

const char* SAMPLE_NAMES[] = {
        "Ivan", "Petr", "Sidor", "Vasiliy", "Nikolay"
};

const char* SAMPLE_PATRONYMIC[] = {
        "Ivanovich", "Petrovich", "Sidorovich", "Vasilievich", "Nikolaevich"
};

const char* SAMPLE_CITIES[] = {
        "Moscow", "St. Petersburg", "Novosibirsk", "Yekaterinburg", "Kazan"
};

const char* SAMPLE_STREETS[]{
        "Lenina", "Pushkina", "Kirova", "Pobedy", "Gagarina"
};

BankAccount::BankAccount(int account_number, const std::string& fullname, const std::string& address) {
    this->account_number = account_number;
    this->fullname = fullname;
    this->address = address;
}

int BankAccount::getAccountNumber() const {
    return account_number;
}

const std::string& BankAccount::getFullname() const {
    return fullname;
}

const std::string& BankAccount::getAddress() const {
    return address;
}

void BankAccount::print() {
    std::cout << "Account number: " << account_number << std::endl;
    std::cout << "Full name: " << fullname << std::endl;
    std::cout << "Address: " << address << std::endl;
}

BankAccount* BankAccount::generateRandomAccount() {
    int account_number = (rand() * rand()) % 9'000'000 + 1'000'000;  // Счет - семизначное число
    std::string fullname(SAMPLE_SURNAMES[rand() % 5]);
    fullname += " ";
    fullname += SAMPLE_NAMES[rand() % 5];
    fullname += " ";
    fullname += SAMPLE_PATRONYMIC[rand() % 5];

    std::string address(SAMPLE_CITIES[rand() % 5]);
    address += ", ";
    address += SAMPLE_STREETS[rand() % 5];
    address += ", ";
    address += std::to_string(rand() % 100);

    return new BankAccount(account_number, fullname, address);
}
