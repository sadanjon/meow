include(cmake/gmock.cmake)

add_executable(unit_tests test/all_unit_tests.cpp test/math_test.cpp src/math.cpp src/math.h)

include_directories(${GMOCK_INCLUDE_DIRS} ${GTEST_INCLUDE_DIRS})
target_link_libraries(unit_tests ${GMOCK_LIBRARIES})

add_test(NAME unit 
         COMMAND unit_tests)

