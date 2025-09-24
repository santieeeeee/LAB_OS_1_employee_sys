#include "employee.h"
#include <windows.h>
#include <locale.h>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Rus");

    if (argc < 4) {
        cout << "Использование: Reporter <бинарник> <отчёт.txt> <ставка>\n";
        return 1;
    }

    string binfile = argv[1];
    string txtfile = argv[2];
    double rate = atof(argv[3]);

    vector<Employee> v;
    try {
        v = read_employees_from_file(binfile);
    } catch (const exception& ex) {
        cout << "Ошибка при чтении бинарного файла: " << ex.what() << "\n";
        return 1;
    }

    v = sort_by_num(std::move(v));
    string report = make_report_text(binfile, v, rate);

    try {
        write_report_to_file(txtfile, report);
    } catch (const exception& ex) {
        cout << "Ошибка при записи отчёта: " << ex.what() << "\n";
        return 1;
    }

    cout << "Отчёт создан: " << txtfile << "\n";
    return 0;
}
