set (Boost_USE_STATIC_LIBS OFF)
find_package (Boost REQUIRED COMPONENTS unit_test_framework)
include_directories (${Boost_INCLUDE_DIRS})

add_executable (Boost_Tests_run test_main.cpp)
target_include_directories(Boost_Tests_run PUBLIC ../src )
target_link_libraries (Boost_Tests_run ${Boost_LIBRARIES})
