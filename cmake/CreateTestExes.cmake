# Creates Test Executables for the Test Runner

function(create_test_exes)
    set(SOURCES ${ARGN})
    foreach (SOURCE IN LISTS SOURCES)
        message(STATUS "Source: ${SOURCE}")

        cmake_path(GET SOURCE STEM EXE)
        message(STATUS "Executable: ${EXE}")

        string(REPLACE "_" ";" WORDS ${EXE})

        set(TEST_NAME "")
        foreach (WORD IN LISTS WORDS)
            message(STATUS "Word: ${WORD}")
            string(SUBSTRING ${WORD} 0 1 FIRST)
            string(SUBSTRING ${WORD} 1 -1 REST)
            string(TOUPPER ${FIRST} FIRST)
            string(APPEND TEST_NAME "${FIRST}${REST}")
        endforeach ()
        message(STATUS "Test name: ${TEST_NAME}")

        add_executable(${EXE})
        target_sources(${EXE} PRIVATE
                ${SOURCE})
        target_link_libraries(${EXE} PRIVATE
                ${CLIB}
                unity)
        add_test(NAME ${TEST_NAME} COMMAND ${EXE})
    endforeach ()
endfunction()