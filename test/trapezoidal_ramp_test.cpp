#include <iostream>
#include <eigen3/Eigen/Dense>
#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include "../lib/include/trapezoidal_ramp.hpp"
#include <tuple>
#include <functional>
#define GTEST_COUT std::cerr << "[          ] [ INFO ]"

using namespace testing;
using Eigen::Vector3d;
using Interpolation::TrapezoidalRamp;

const float v_max = 4;
const float a_up = 2;
const float a_down = 1;
const float dt = 1;

TEST(trapezoidal_ramp,calculate_time_offset)
{
    std::tuple<float, float,float> a;
     a = std::make_tuple(2, 3,4);
    TrapezoidalRamp tp;
    tp.set_electrical_constraints(1,1,1);
    tp.set_constraints(v_max,a_up,a_down,dt);
    tp.calculate_cp_at_time(32,9);
    EXPECT_EQ(a,tp.calculate_time_offsets());
}

TEST(trapezoidal_ramp,calculate_ramp_up)
{
    TrapezoidalRamp tp;
    tp.set_electrical_constraints(1,1,1);
    tp.set_constraints(v_max,a_up,a_down,dt);
    tp.calculate_cp_at_time(32,9);
    tp.calculate_time_offsets();
    auto res = tp.calculate_ramp_up_fx(0);
   ASSERT_THAT(res.second, ElementsAre(0, 1, 4));
   ASSERT_THAT(res.first, ElementsAre(0, 1, 2));
}

TEST(trapezoidal_ramp,calculate_ramp_down)
{
    TrapezoidalRamp tp;
    tp.set_electrical_constraints(1,1,1);
    tp.set_constraints(v_max,a_up,a_down,dt);
    tp.calculate_cp_at_time(32,9);
    tp.calculate_time_offsets();
    auto res = tp.calculate_ramp_down_fx(0,v_max);
   ASSERT_THAT(res.second, ElementsAre(3.5,6,7.5,8));
   ASSERT_THAT(res.first, ElementsAre(6,7,8,9));
}

TEST(trapezoidal_ramp,calculate_constant_velocity)
{
    TrapezoidalRamp tp;
    tp.set_electrical_constraints(1,1,1);
    tp.set_constraints(v_max,a_up,a_down,dt);
    tp.calculate_cp_at_time(32,9);
    tp.calculate_time_offsets();
    auto res = tp.calculate_constant_fx(0);
    ASSERT_THAT(res.second, ElementsAre(4,8,12));
    ASSERT_THAT(res.first, ElementsAre(3,4,5));
}

TEST(trapezoidal_ramp,tp_ramp_adaptive_vmax)
{
}

/*
TEST(trapezoidal_ramp,tp_ramp_adaptive_tmax)
{

}
*/

TEST(trapezoidal_ramp,tp_ramp_with_tmax)
{
    TrapezoidalRamp tp;
    tp.set_electrical_constraints(1,1,1);
    tp.set_constraints(v_max,a_up,a_down,dt);
    tp.calculate_cp_at_time(32,9);
    auto u = tp.calculate_cp_and_time(0);

    ASSERT_THAT(u.second, ElementsAre(0, 1, 4, 8, 12, 16, 19.5, 22, 23.5, 24));
    ASSERT_THAT(u.first, ElementsAre(0,1,2,3,4,5,6,7,8,9));
}