#include "employee.h"
#include <algorithm>
#include <sstream>
#include <iomanip>
#include <stdexcept>

void write_employee(std::ofstream& out, const Employee& e) {
    out.write(reinterpret_cast<const char*>(&e), sizeof(e));
}

bool read_employee(std::ifstream& in, Employee& e) {
    return static_cast<bool>(in.read(reinterpret_cast<char*>(&e), sizeof(e)));
}

void write_employees_to_file(const std::string& path, const std::vector<Employee>& v) {
    std::ofstream out(path, std::ios::binary);
    if (!out) throw std::runtime_error("cannot open file for writing: " + path);
    for (auto const& e : v) write_employee(out, e);
}

std::vector<Employee> read_employees_from_file(const std::string& path) {
    std::vector<Employee> v;
    std::ifstream in(path, std::ios::binary);
    if (!in) throw std::runtime_error("cannot open file for reading: " + path);
    Employee e;
    while (read_employee(in, e)) v.push_back(e);
    return v;
}

std::vector<Employee> sort_by_num(std::vector<Employee> v) {
    std::sort(v.begin(), v.end(), [](const Employee& a, const Employee& b){
        return a.num < b.num;
    });
    return v;
}

std::string make_report_text(const std::string& binFilename, const std::vector<Employee>& v, double rate) {
    std::ostringstream ss;
    ss << "Отчёт по файлу \"" << binFilename << "\"\n";
    ss << "ID   Имя       Часы   Зарплата\n";
    ss << "--------------------------------\n";
    ss << std::fixed << std::setprecision(2);
    for (auto const& emp : v) {
        double salary = emp.hours * rate;
        ss << std::setw(4) << emp.num << " "
           << std::setw(10) << emp.name << " "
           << std::setw(6) << emp.hours << " "
           << std::setw(8) << salary << "\n";
    }
    return ss.str();
}

void write_report_to_file(const std::string& path, const std::string& text) {
    std::ofstream out(path);
    if (!out) throw std::runtime_error("cannot open file for writing: " + path);
    out << text;
}
