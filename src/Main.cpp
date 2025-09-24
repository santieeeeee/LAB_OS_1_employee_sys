#include "employee.h"
#include <windows.h>
#include <locale.h>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

static void runProcessAndWait(const string& exe, const string& args) {
    // формируем командную строку: "Exe" args
    string cmdline = "\"" + exe + "\" " + args;

    STARTUPINFOA si;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    PROCESS_INFORMATION pi;
    ZeroMemory(&pi, sizeof(pi));

    // CreateProcessA модифицирует строку, поэтому делаем копию
    vector<char> cmdbuf(cmdline.begin(), cmdline.end());
    cmdbuf.push_back('\0');

    if (!CreateProcessA(
        nullptr,
        cmdbuf.data(),
        nullptr, nullptr,
        FALSE,
        0,
        nullptr,
        nullptr,
        &si,
        &pi))
    {
        throw runtime_error("Не удалось запустить: " + cmdline);
    }

    WaitForSingleObject(pi.hProcess, INFINITE);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Rus");

    string binFile;
    int count = 0;
    cout << "Имя бинарного файла: ";
    cin >> binFile;
    cout << "Сколько записей: ";
    cin >> count;

    try {
        runProcessAndWait("Creator.exe", "\"" + binFile + "\" " + to_string(count));
    } catch (const exception& ex) {
        cout << ex.what() << "\n";
        return 1;
    }

    cout << "\nСодержимое бинарника:\n";
    try {
        auto v = read_employees_from_file(binFile);
        for (const auto& e : v) {
            cout << e.num << " " << e.name << " " << e.hours << "\n";
        }
    } catch (const exception& ex) {
        cout << "Не удалось прочитать бинарный файл: " << ex.what() << "\n";
    }

    string reportFile;
    double rate = 0.0;
    cout << "\nИмя файла отчёта: ";
    cin >> reportFile;
    cout << "Ставка за час: ";
    cin >> rate;

    try {
        runProcessAndWait("Reporter.exe", "\"" + binFile + "\" \"" + reportFile + "\" " + to_string(rate));
    } catch (const exception& ex) {
        cout << ex.what() << "\n";
        return 1;
    }

    cout << "\nОтчёт:\n";
    ifstream rep(reportFile);
    if (!rep) {
        cout << "Не удалось открыть файл отчёта: " << reportFile << "\n";
        return 1;
    }
    string line;
    while (getline(rep, line)) {
        cout << line << "\n";
    }
    rep.close();

    return 0;
}
