#include <iostream>
#include <string>


std::string cpp_keywords[] = {
        "namespace", "signed", "wchar_t", "dynamic_cast", "char16_t", "alignof", "using",
        "try", "const", "switch", "char32_t", "asm", "bitand", "case", "decltype",
        "char", "inline", "bool", "volatile", "typedef", "sizeof", "true",
        "and_eq", "bitor", "static_cast", "double", "goto", "break", "throw",
        "virtual", "register", "mutable", "delete", "union", "catch", "long",
        "continue", "if", "reinterpret_cast", "float", "return", "protected",
        "not_eq", "alignas", "or", "while", "explicit", "void", "and", "class",
        "short", "extern", "noexcept", "false", "not", "int", "default", "new",
        "static_assert", "export", "constexpr", "this", "do", "thread_local", "compl",
        "operator", "or_eq", "friend", "for", "enum", "public", "static",
        "const_cast", "xor_eq", "xor", "typeid", "struct", "typename", "nullptr",
        "auto", "else", "unsigned", "private", "template"
};

int cpp_keywords_size = 84;

void bubbleSort(std::string arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                std::string temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void printArray(std::string *array, int size) {
    for (int i = 0; i < size; i++) {
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;
}

int main() {
    std::cout << "Before sorting:" << std::endl;
    printArray(cpp_keywords, cpp_keywords_size);
    std::cout << std::endl;

    bubbleSort(cpp_keywords, cpp_keywords_size);

    std::cout << "After sorting:" << std::endl;
    printArray(cpp_keywords, cpp_keywords_size);

    return 0;
}