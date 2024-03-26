#include "interpolation.hpp"

namespace Interpolation{
    
    class TrapezoidalRamp:public IInterpolationBuilder
    {

        public:
            TrapezoidalRamp();
            std::pair<std::vector<float>,std::vector<float>> calculate_cp_and_time(float cp_0);
            std::pair<std::vector<float>,std::vector<float>> calculate_constant_fx(float cp_0);
            std::pair<std::vector<float>,std::vector<float>> calculate_ramp_down_fx(float cp_0,float v_0);
            std::pair<std::vector<float>,std::vector<float>> calculate_ramp_up_fx(float cp_0);
            std::tuple<float,float,float>  calculate_time_offsets();


            void set_constraints(float v_max, float a_max_up, float a_max_down,float dt) override;
            virtual void set_mechanical_constraints(float vector_length) override;
            void set_electrical_constraints(int steps_per_revolution, int microsteps_per_step, int degree_per_revolution ) override;
            // Convert 3d-vector to circular position
            virtual void calculate_cp_at_time(float set_cp, float t_ms) override;            
            virtual int get_circular_position() override;
        float v_max, a_max_up, a_max_down;
        float dt_start, dt_end, dt_c,dt;
        float t_s_offset, t_e_offset, t_c_offset;
        float t_ramp_start;
        float vector_length;
        int spr, uspr, dpr;
        int next_cp;
    
    };
}