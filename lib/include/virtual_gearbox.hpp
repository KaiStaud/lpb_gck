#include <eigen3/Eigen/Dense>
#include <math.h>

class virtual_gearbox
{
public:
    virtual_gearbox(int steps_per_rev, int microsteps_per_step, float gear_ratio)
        : steps_per_revolution(steps_per_rev), mirosteps_per_step(microsteps_per_step), gear_ratio(gear_ratio) {}


    float calculate_degrees(Eigen::Vector3d v);
    float calculate_steps(float degrees);

private:
    int steps_per_revolution;
    int mirosteps_per_step;
    float gear_ratio;
};