# CMake generated Testfile for 
# Source directory: D:/writtenprogramms/LAB_OS_1_employee_sys/tests
# Build directory: D:/writtenprogramms/LAB_OS_1_employee_sys/tests/build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
if(CTEST_CONFIGURATION_TYPE MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
  add_test(all_tests "D:/writtenprogramms/LAB_OS_1_employee_sys/tests/build/Debug/tests_runner.exe")
  set_tests_properties(all_tests PROPERTIES  _BACKTRACE_TRIPLES "D:/writtenprogramms/LAB_OS_1_employee_sys/tests/CMakeLists.txt;67;add_test;D:/writtenprogramms/LAB_OS_1_employee_sys/tests/CMakeLists.txt;0;")
elseif(CTEST_CONFIGURATION_TYPE MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
  add_test(all_tests "D:/writtenprogramms/LAB_OS_1_employee_sys/tests/build/Release/tests_runner.exe")
  set_tests_properties(all_tests PROPERTIES  _BACKTRACE_TRIPLES "D:/writtenprogramms/LAB_OS_1_employee_sys/tests/CMakeLists.txt;67;add_test;D:/writtenprogramms/LAB_OS_1_employee_sys/tests/CMakeLists.txt;0;")
elseif(CTEST_CONFIGURATION_TYPE MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
  add_test(all_tests "D:/writtenprogramms/LAB_OS_1_employee_sys/tests/build/MinSizeRel/tests_runner.exe")
  set_tests_properties(all_tests PROPERTIES  _BACKTRACE_TRIPLES "D:/writtenprogramms/LAB_OS_1_employee_sys/tests/CMakeLists.txt;67;add_test;D:/writtenprogramms/LAB_OS_1_employee_sys/tests/CMakeLists.txt;0;")
elseif(CTEST_CONFIGURATION_TYPE MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
  add_test(all_tests "D:/writtenprogramms/LAB_OS_1_employee_sys/tests/build/RelWithDebInfo/tests_runner.exe")
  set_tests_properties(all_tests PROPERTIES  _BACKTRACE_TRIPLES "D:/writtenprogramms/LAB_OS_1_employee_sys/tests/CMakeLists.txt;67;add_test;D:/writtenprogramms/LAB_OS_1_employee_sys/tests/CMakeLists.txt;0;")
else()
  add_test(all_tests NOT_AVAILABLE)
endif()
subdirs("googletest_build")
