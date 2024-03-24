/*
Interface Header for interpolating set-positions:

Implementations in the following headers:
- trapezoidal_ramp.hpp
- six_point_ramp.hpp
- s_shaped_curve.hpp
- splined_curve.hpp

*/

#include <eigen3/Eigen/Dense>

namespace Interpolation
{
    class IInterpolationBuilder
    {
        public:
            virtual void set_constraints(float v_max, float a_max_up, float a_max_down) = 0;
            virtual void set_mechanical_constraints(float vector_length) = 0;
            // Convert 3d-vector to circular position
            virtual void calculate_cp_at_time(Eigen::Vector3d v, float t_ms) = 0;
            virtual void set_electrical_constraints(int steps_per_revolution, int microsteps_per_step, int degree_per_revolution ) = 0;
            virtual int get_circular_position() = 0;
    };
}
