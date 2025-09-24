#include "employee.h"
#include <windows.h>
#include <locale.h>
#include <iostream>
#include <vector>
#include <string>
#include <cstring>

using namespace std;

int main(int argc, char* argv[]) {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Rus");

    if (argc < 3) {
        cout << "Использование: Creator <имя_файла> <количество>\n";
        return 1;
    }

    string filename = argv[1];
    int n = atoi(argv[2]);
    if (n <= 0) {
        cout << "Неверное количество записей\n";
        return 1;
    }

    vector<Employee> v;
    v.reserve(n);

    for (int i = 0; i < n; ++i) {
        Employee e{};
        cout << "ID сотрудника: ";
        cin >> e.num;
        cout << "Имя (до 9 символов): ";
        {
            string name;
            cin >> name;
            // копируем до 9 символов и гарантируем нуль-терминатор
            memset(e.name, 0, sizeof(e.name));
            strncpy_s(e.name, name.c_str(), _TRUNCATE);
        }
        cout << "Часы работы: ";
        cin >> e.hours;
        v.push_back(e);
    }

    try {
        write_employees_to_file(filename, v);
    } catch (const exception& ex) {
        cout << "Ошибка при записи файла: " << ex.what() << "\n";
        return 1;
    }

    cout << "Файл создан: " << filename << "\n";
    return 0;
}
