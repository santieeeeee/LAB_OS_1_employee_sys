#include "employee.h"
#include <gtest/gtest.h>
#include <cstdio>
#include <vector>
#include <fstream>

TEST(EmployeeIOTest, WriteThenRead) {
    std::string tmp = "test_employees.bin";
    std::vector<Employee> v{
        {2, "Bob", 40.0},
        {1, "Alice", 36.5}
    };
    write_employees_to_file(tmp, v);
    auto read_v = read_employees_from_file(tmp);
    EXPECT_EQ(read_v.size(), v.size());
    EXPECT_EQ(read_v[0].num, 2);
    EXPECT_STREQ(read_v[0].name, "Bob");
    EXPECT_DOUBLE_EQ(read_v[1].hours, 36.5);
    std::remove(tmp.c_str());
}

TEST(SortTest, ByNum) {
    std::vector<Employee> v{
        {10, "X", 1.0},
        {3, "Y", 2.0},
        {7, "Z", 3.0}
    };
    auto sorted = sort_by_num(v);
    ASSERT_EQ(sorted.size(), 3u);
    EXPECT_EQ(sorted[0].num, 3);
    EXPECT_EQ(sorted[1].num, 7);
    EXPECT_EQ(sorted[2].num, 10);
}

TEST(ReportFormatting, SalaryCalculation) {
    std::vector<Employee> v{
        {1, "Ann", 10.0},
        {2, "Ben", 5.5}
    };
    double rate = 2.0;
    std::string r = make_report_text("data.bin", v, rate);
    // Check that calculated salaries appear
    EXPECT_NE(r.find("20.00"), std::string::npos);
    EXPECT_NE(r.find("11.00"), std::string::npos);
}
