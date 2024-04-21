#include "../lib/include/jog_controller.hpp"
#include <eigen3/Eigen/Dense>
#include <gtest/gtest.h>
#include <iostream>
#define GTEST_COUT std::cerr << "[          ] [ INFO ]"

using Eigen::Vector3d;
TEST(fk, error_in_bound)
{
    SupervisedMotionController::Image img{
        .schleppfehler = 0,
        .schlepp_zeit = 1,
    };

    const float dt = 1;
    const int steps_t0 = 10;
    /* Set steps per second */
    const int sps = 100;
    /* Calculate amount of moved steps during dt */
    const int steps_t1 = sps * dt + steps_t0;
    SupervisedMotionController::SupervisedParameter state{.position = steps_t1};
    /* Check if position error is in bound */
    EXPECT_EQ(steps_t1, 110);
    //EXPECT_TRUE(SupervisedMotionController::Check(img, state));
}
