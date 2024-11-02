cmake_minimum_required(VERSION 3.12)

set(PROJECT_NAME TypeAhead)
set(SOURCE_FILES WordTree.cpp)
set(HEADER_FILES WordTree.hpp)
set(UNIT_TEST_FILES TestWordTree.cpp)
set(MAIN_FILE main.cpp)

project(${PROJECT_NAME})    

add_executable(${PROJECT_NAME} ${HEADER_FILES} ${SOURCE_FILES} ${MAIN_FILE})
add_executable(UnitTestRunner  ${HEADER_FILES} ${SOURCE_FILES} ${UNIT_TEST_FILES}) 

       
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)
set_property(TARGET UnitTestRunner PROPERTY CXX_STANDARD 20)

if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "/STACK:10000000")
    target_compile_options(${PROJECT_NAME} PRIVATE /W4 /permissive-)
    set_target_properties(UnitTestRunner PROPERTIES LINK_FLAGS "/STACK:10000000")
    target_compile_options(UnitTestRunner PRIVATE /W4 /permissive-)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -pedantic -Wl,--stack,10000000)
    target_compile_options(UnitTestRunner PRIVATE -Wall -Wextra -pedantic -Wl,--stack,10000000)
elseif (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -pedantic -Wl -O3,--stack,10000000)
    target_compile_options(UnitTestRunner PRIVATE -Wall -Wextra -pedantic -Wl -O3,--stack,10000000)
endif()


#Adding Google Test
include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.15.0
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googleTest)
target_link_libraries(UnitTestRunner gtest_main)

#Automatically applying CLANG-FORMAT
find_program(CLANG_FORMAT NAMES clang-format)

unset(SOURCE_FILES_PATHS)
foreach(SOURCE_FILE ${HEADER_FILES} ${SOURCE_FILES} ${UNIT_TEST_FILES} ${MAIN_FILE})
    get_source_file_property(WHERE ${SOURCE_FILE} LOCATION)
    set(SOURCE_FILES_PATHS ${SOURCE_FILES_PATHS} ${WHERE})
endforeach()

add_custom_target(
        ClangFormat
        COMMAND ${CLANG_FORMAT}
        -i
        -style=file
        ${SOURCE_FILES_PATHS})

add_dependencies(${PROJECT_NAME} ClangFormat)

#End of automatically applying CLANG-FORMAT

add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${CMAKE_CURRENT_SOURCE_DIR}/dictionary.txt dictionary.txt
)

