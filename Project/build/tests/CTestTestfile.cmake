# CMake generated Testfile for 
# Source directory: D:/writtenprogramms/LAB_OS_1_employee_sys/Project/tests
# Build directory: D:/writtenprogramms/LAB_OS_1_employee_sys/Project/build/tests
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
if(CTEST_CONFIGURATION_TYPE MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
  add_test(RunAllUnitTests "D:/writtenprogramms/LAB_OS_1_employee_sys/Project/build/bin/Debug/UnitTests.exe")
  set_tests_properties(RunAllUnitTests PROPERTIES  _BACKTRACE_TRIPLES "D:/writtenprogramms/LAB_OS_1_employee_sys/Project/tests/CMakeLists.txt;23;add_test;D:/writtenprogramms/LAB_OS_1_employee_sys/Project/tests/CMakeLists.txt;0;")
elseif(CTEST_CONFIGURATION_TYPE MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
  add_test(RunAllUnitTests "D:/writtenprogramms/LAB_OS_1_employee_sys/Project/build/bin/Release/UnitTests.exe")
  set_tests_properties(RunAllUnitTests PROPERTIES  _BACKTRACE_TRIPLES "D:/writtenprogramms/LAB_OS_1_employee_sys/Project/tests/CMakeLists.txt;23;add_test;D:/writtenprogramms/LAB_OS_1_employee_sys/Project/tests/CMakeLists.txt;0;")
elseif(CTEST_CONFIGURATION_TYPE MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
  add_test(RunAllUnitTests "D:/writtenprogramms/LAB_OS_1_employee_sys/Project/build/bin/MinSizeRel/UnitTests.exe")
  set_tests_properties(RunAllUnitTests PROPERTIES  _BACKTRACE_TRIPLES "D:/writtenprogramms/LAB_OS_1_employee_sys/Project/tests/CMakeLists.txt;23;add_test;D:/writtenprogramms/LAB_OS_1_employee_sys/Project/tests/CMakeLists.txt;0;")
elseif(CTEST_CONFIGURATION_TYPE MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
  add_test(RunAllUnitTests "D:/writtenprogramms/LAB_OS_1_employee_sys/Project/build/bin/RelWithDebInfo/UnitTests.exe")
  set_tests_properties(RunAllUnitTests PROPERTIES  _BACKTRACE_TRIPLES "D:/writtenprogramms/LAB_OS_1_employee_sys/Project/tests/CMakeLists.txt;23;add_test;D:/writtenprogramms/LAB_OS_1_employee_sys/Project/tests/CMakeLists.txt;0;")
else()
  add_test(RunAllUnitTests NOT_AVAILABLE)
endif()
subdirs("../_deps/catch2-build")
