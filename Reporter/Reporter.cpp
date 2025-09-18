#include <windows.h>
#include <locale.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

struct employee {
    int num;
    char name[10];
    double hours;
};

int main(int argc, char* argv[]) {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Rus");

    if (argc < 4) {
        cout << "Использование: Reporter <бинарник> <отчёт.txt> <ставка>\n";
        return 1;
    }

    const char* binfile = argv[1];
    const char* txtfile = argv[2];
    double rate = atof(argv[3]);

    ifstream in(binfile, ios::binary);
    if (!in.is_open()) {
        cout << "Не удалось открыть бинарный файл " << binfile << "\n";
        return 1;
    }

    vector<employee> v;
    employee e;
    while (in.read(reinterpret_cast<char*>(&e), sizeof(e))) {
        v.push_back(e);
    }
    in.close();

    sort(v.begin(), v.end(), [](auto& a, auto& b) {
        return a.num < b.num;
        });

    ofstream out(txtfile);
    out << "Отчёт по файлу \"" << binfile << "\"\n";
    out << "ID   Имя       Часы   Зарплата\n";
    out << "--------------------------------\n";
    for (auto& emp : v) {
        double salary = emp.hours * rate;
        out << emp.num << "    "
            << emp.name << "      "
            << emp.hours << "      "
            << salary << "\n";
    }
    out.close();
    return 0;
}
