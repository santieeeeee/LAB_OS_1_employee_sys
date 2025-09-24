#pragma once
#include <string>
#include <vector>
#include <fstream>

struct Employee {
    int num;
    char name[10];
    double hours;
};

// Binary IO
void write_employee(std::ofstream& out, const Employee& e);
bool read_employee(std::ifstream& in, Employee& e);

// File helpers
void write_employees_to_file(const std::string& path, const std::vector<Employee>& v);
std::vector<Employee> read_employees_from_file(const std::string& path);

// Report helpers
std::vector<Employee> sort_by_num(std::vector<Employee> v);
std::string make_report_text(const std::string& binFilename, const std::vector<Employee>& v, double rate);
void write_report_to_file(const std::string& path, const std::string& text);
