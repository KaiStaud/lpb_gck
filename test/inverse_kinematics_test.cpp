#include <iostream>
#include "../lib/include/inverse_kinematics.hpp"
#include <eigen3/Eigen/Dense>
#include <gtest/gtest.h>
#define GTEST_COUT std::cerr << "[          ] [ INFO ]"

using Eigen::Vector3d;
TEST(ik,two_links)
{

    Vector3d t1{0, 0, 5};
    Vector3d t2{5, 5, 5};
    Vector3d t3{0, 5, 5};
    Vector3d t4{5, 0, 5};

    auto res1 = calculate_vector_fx(t1, t2);
//    INFO(res1.first << " " << res1.second << "\r\n");
    auto res2 = calculate_vector_fx(t3, t4);
//    INFO(res2.first << " " << res2.second << "\r\n");
    auto intersection = calculate_intersection(res1.first, res1.second, res2.first, res2.second);
    //    INFO(intersection[0] << " " << intersection[1]);
    auto res = simple_ik(4, 2, Vector3d(5, 5, 0)); 
    EXPECT_EQ(res.error,IK_Error::ik_solved);
}

TEST(ik,intersections_two_vectors)
{

    Vector3d t1{0, 0, 5};
    Vector3d t2{5, 5, 5};
    Vector3d t3{0, 5, 5};
    Vector3d t4{5, 0, 5};

    auto res1 = calculate_vector_fx(t1, t2);
//  INFO(res1.first << " " << res1.second << "\r\n");
    auto res2 = calculate_vector_fx(t3, t4);
//  INFO(res2.first << " " << res2.second << "\r\n");
    auto intersection = calculate_intersection(res1.first, res1.second, res2.first, res2.second);
//  INFO(intersection[0] << " " << intersection[1]);
    auto pair1 = std::make_pair<double, double>(1, 0);
    auto pair2 = std::make_pair<double, double>(-1, 5);
    EXPECT_EQ(res1,pair1);
    EXPECT_EQ(res2,pair2);
    EXPECT_EQ(intersection,Eigen::Vector3d(2.5, 2.5, 0));

}

void test_approx_equal(IK_Result should_be, IK_Result is, float acceptable_delta)
{
    for(int i=0;i<3;i++)
    {
        ASSERT_NEAR(should_be.effektor1[i],is.effektor1[i],acceptable_delta);
        ASSERT_NEAR(should_be.effektor2[i],is.effektor2[i],acceptable_delta);
    }
}

TEST(ik,simple_ik)
{
    Vector3d vnode_start{5, 5, 0};
    Vector3d vnode_middle{4, 6, 0};
    Vector3d vnode_middle2{1, 7, 0};
    Vector3d vnode_end{3, 7, 0};

    Vector3d t4{5, 0, 5};

    IK_Result result_start = 
    {
        .error = IK_Error::ik_solved,
        .effektor1 = Eigen::Vector3d(1.01381 ,3.86939,0),
        .effektor2 = Eigen::Vector3d(5,5,0),
        .effektor3 = Eigen::Vector3d(0,0,0)
    };

        IK_Result result_middle = 
    {
        .error = IK_Error::ik_solved,
        .effektor1 = Eigen::Vector3d(0.429642,3.97686,0),
        .effektor2 = Eigen::Vector3d(4,6,0),
        .effektor3 = Eigen::Vector3d(0,0,0)
    };

            IK_Result result_middle2 = 
    {
        .error = IK_Error::ik_solved,
        .effektor1 = Eigen::Vector3d(-1.51059, 3.7038,0),
        .effektor2 = Eigen::Vector3d(1,7,0),
        .effektor3 = Eigen::Vector3d(0,0,0)
    };

            IK_Result result_end = 
    {
        .error = IK_Error::ik_solved,
        .effektor1 = Eigen::Vector3d( 0.332647,3.98614,0),
        .effektor2 = Eigen::Vector3d(3,7,0),
        .effektor3 = Eigen::Vector3d(0,0,0)
    };

    test_approx_equal(result_start,simple_ik(4,2,vnode_start),0.00001);
    test_approx_equal(result_middle,simple_ik(4,2,vnode_middle),0.00001);
    test_approx_equal(result_middle2,simple_ik(4,2,vnode_middle2),0.00001);
    test_approx_equal(result_end,simple_ik(4,2,vnode_end),0.00001);

}