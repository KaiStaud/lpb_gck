#include <iostream>
#include <eigen3/Eigen/Dense>
#include <gtest/gtest.h>

#define GTEST_COUT std::cerr << "[          ] [ INFO ]"

using Eigen::Vector3d;

TEST(interpolation,tp_ramp_no_tmax)
{

}

TEST(interpolation,tp_ramp_adaptive_vmax)
{

}

TEST(interpolation,tp_ramp_adaptive_tmax)
{

}

TEST(interpolation,tp_ramp_with_tmax)
{
    Vector3d vnode_start{5, 5, 0};
    Vector3d vnode_middle{4, 6, 0};
    Vector3d vnode_middle2{1, 7, 0};
    Vector3d vnode_end{3, 7, 0};
}