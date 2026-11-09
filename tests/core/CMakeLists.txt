# Core Tests

file(GLOB SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.c")

create_test_exes(${SOURCES})
