#include "../include/trapezoidal_ramp.hpp"
#include "math.h"
namespace Interpolation{

            void TrapezoidalRamp::set_constraints(float v_max, float a_max_up, float a_max_down)
            {

            }
            
            void TrapezoidalRamp::set_mechanical_constraints(float vector_length)
            {

            }
            
            // Convert 3d-vector to circular position
            void TrapezoidalRamp::calculate_cp_at_time(Eigen::Vector3d v, float t_ms){
                float alpha = atan(v[1] / v[0]); 
                next_cp = spr * uspr * alpha / dpr; 
                
            }
            
            void TrapezoidalRamp::set_electrical_constraints(int steps_per_revolution, int microsteps_per_step, int degree_per_revolution ){
               spr = steps_per_revolution;
               uspr = microsteps_per_step;
               dpr = degree_per_revolution;
            }
            
            int TrapezoidalRamp::get_circular_position()
            {
                return next_cp;
            }

}