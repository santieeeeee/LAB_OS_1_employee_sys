#include <windows.h>
#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>

using namespace std;

// Функция запускает внешнюю программу и ждёт её завершения
void runProcess(const char* cmd) {
    STARTUPINFOA si;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);

    PROCESS_INFORMATION pi;

    if (!CreateProcessA(
        nullptr,
        (LPSTR)cmd,
        nullptr, nullptr,
        FALSE,
        0,
        nullptr,
        nullptr,
        &si,
        &pi))
    {
        cout << "Не удалось запустить: " << cmd << "\n";
        exit(1);
    }

    WaitForSingleObject(pi.hProcess, INFINITE);

    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
}

struct Employee {
    int num;
    char name[10];
    double hours;
};

int main() {

    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Rus");
    char binFile[100];
    int count;
    cout << "Имя бинарного файла: ";
    cin >> binFile;
    cout << "Сколько записей: ";
    cin >> count;

    char cmd1[200];
    sprintf(cmd1, "Creator %s %d", binFile, count);
    runProcess(cmd1);

    cout << "\nСодержимое бинарника:\n";
    ifstream in(binFile, ios::binary);
    Employee e;
    while (in.read((char*)&e, sizeof(e))) {
        cout << e.num << " " << e.name << " " << e.hours << "\n";
    }
    in.close();

    char reportFile[100];
    double rate;
    cout << "\nИмя файла отчёта: ";
    cin >> reportFile;
    cout << "Ставка за час: ";
    cin >> rate;

    char cmd2[200];
    sprintf(cmd2, "Reporter %s %s %.2f", binFile, reportFile, rate);
    runProcess(cmd2);

    cout << "\nОтчёт:\n";
    ifstream rep(reportFile);
    string line;
    while (getline(rep, line)) {
        cout << line << "\n";
    }
    rep.close();

    return 0;
}
