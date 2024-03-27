#include <iostream>
#include <eigen3/Eigen/Dense>
#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include "../lib/include/virtual_gearbox.hpp"
#define GTEST_COUT std::cerr << "[          ] [ INFO ]"

using namespace testing;

TEST(virtual_gearbox,degree_to_steps)
{
    virtual_gearbox gearbox(200, 1, 1); 
    EXPECT_EQ(gearbox.calculate_degrees(Eigen::Vector3d(5,5,0)),45);
}

TEST(virtual_gearbox,vector_to_steps)
{
    virtual_gearbox gearbox(200, 1, 1); 
    auto d = gearbox.calculate_degrees(Eigen::Vector3d(5,5,0));
    EXPECT_EQ(d,45);
    EXPECT_EQ(gearbox.calculate_steps(45),25);

}