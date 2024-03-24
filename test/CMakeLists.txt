set (CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()
add_executable(tests
inverse_kinematics_test.cpp
trapezoidal_ramp_test.cpp
)

target_link_libraries(tests
pthread
dl
lib
gmock
gtest
gtest_main) 