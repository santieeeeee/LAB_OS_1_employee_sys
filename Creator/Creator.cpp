    #include <windows.h>
    #include <locale.h>
    #include <iostream>
    #include <fstream>
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

        if (argc < 3) {
            cout << "Использование: Creator <имя_файла> <количество>\n";
            return 1;
        }

        const char* filename = argv[1];
        int n = atoi(argv[2]);

        ofstream out(filename, ios::binary);
        if (!out.is_open()) {
            cout << "Ошибка при создании файла " << filename << "\n";
            return 1;
        }

        for (int i = 0; i < n; i++) {
            employee e;
            cout << "ID сотрудника: ";
            cin >> e.num;
            cout << "Имя (до 9 символов): ";
            cin >> e.name;
            cout << "Часы работы: ";
            cin >> e.hours;
            out.write(reinterpret_cast<char*>(&e), sizeof(e));
        }
        out.close();
        return 0;
    }
