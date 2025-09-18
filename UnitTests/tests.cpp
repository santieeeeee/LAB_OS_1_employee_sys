// tests.cpp

#define CATCH_CONFIG_MAIN
#include "catch_amalgamated.hpp"

#include <sstream>
#include <string>
#include <iomanip>
#include <cmath>

struct employee {
    int num;
    char name[10];
    double hours;
};

TEST_CASE("Binary serialization/deserialization of employee") {
    employee e1;
    e1.num = 42;
    std::strcpy(e1.name, "Ivan");
    e1.hours = 8.5;

    std::stringstream ss(std::ios::binary | std::ios::in | std::ios::out);
    ss.write(reinterpret_cast<char*>(&e1), sizeof(e1));

    employee e2;
    ss.seekg(0);
    ss.read(reinterpret_cast<char*>(&e2), sizeof(e2));

    REQUIRE(e2.num == 42);
    REQUIRE(std::string(e2.name) == "Ivan");
    REQUIRE(e2.hours == Approx(8.5));
}


double calcSalary(const employee& emp, double rate) {
    return emp.hours * rate;
}

TEST_CASE("Salary calculation is hours * rate") {
    employee emp{ 7, "Olga", 10.25 };
    REQUIRE(calcSalary(emp, 0.0) == Approx(0.0));
    REQUIRE(calcSalary(emp, 1.0) == Approx(10.25));
    REQUIRE(calcSalary(emp, 2.5) == Approx(25.625));
}

std::string formatReportLine(const employee& emp, double rate) {
    std::ostringstream out;
    out << std::left << std::setw(4) << emp.num
        << std::setw(10) << emp.name
        << std::right << std::setw(7) << emp.hours
        << std::setw(10) << (emp.hours * rate);
    return out.str();
}

TEST_CASE("Report line formatting matches expected layout") {
    employee emp{ 3, "Petya", 12.0 };
    double rate = 5.0;

    std::string line = formatReportLine(emp, rate);

    REQUIRE(line.find("3") == 0);
    REQUIRE(line.find("Petya") == 4);
    REQUIRE(line.find("12") != std::string::npos);
    REQUIRE(line.find("60") != std::string::npos);

    REQUIRE(line.size() == 31);
}
