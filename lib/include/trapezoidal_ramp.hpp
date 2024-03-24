#include "interpolation.hpp"

namespace Interpolation{
    
    class TrapezoidalRamp:public IInterpolationBuilder
    {
            virtual void set_constraints(float v_max, float a_max_up, float a_max_down) override;
            virtual void set_mechanical_constraints(float vector_length) override;
            void set_electrical_constraints(int steps_per_revolution, int microsteps_per_step, int degree_per_revolution ) override;
            // Convert 3d-vector to circular position
            virtual void calculate_cp_at_time(Eigen::Vector3d v, float t_ms) override;            
            virtual int get_circular_position() override;
        float v_max, a_max_up, a_max_down;
        float vector_length;
        int spr, uspr, dpr;
        int next_cp;
    
    };
}