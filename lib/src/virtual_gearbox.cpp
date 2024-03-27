#include "../include/virtual_gearbox.hpp"
#include <numbers>
#include <iostream>
    float virtual_gearbox::calculate_degrees(Eigen::Vector3d v)
    {
        float d = atan(v[1]/v[0])*360/(2*std::numbers::pi);
        return d;
    }


    float virtual_gearbox::calculate_steps(float degrees) {
        return (degrees / 360.0) * steps_per_revolution * mirosteps_per_step * gear_ratio;
    }