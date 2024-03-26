#include "../include/trapezoidal_ramp.hpp"
#include "math.h"
#include <iostream>
namespace Interpolation{

            TrapezoidalRamp::TrapezoidalRamp()
            {
                t_ramp_start=0;
            }
            void TrapezoidalRamp::set_constraints(float v_max, float a_max_up, float a_max_down,float dt)
            {
                this->v_max = v_max;
                this->a_max_up = a_max_up;
                this->a_max_down = a_max_down;
                this->dt = dt;
                
            }
            
            void TrapezoidalRamp::set_mechanical_constraints(float vector_length)
            {

            }
            
            // Convert 3d-vector to circular position
            void TrapezoidalRamp::calculate_cp_at_time(float set_cp, float t_ms){
                //float alpha = atan(v[1] / v[0]); 
                next_cp = spr * uspr * set_cp / dpr; 
                
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

            std::tuple<float,float,float> TrapezoidalRamp::calculate_time_offsets()
            {
                dt_start = v_max / a_max_up;
                dt_end = v_max / a_max_down;
                float s_c = next_cp - ( 0.5 * a_max_up * dt_start* dt_start) - ( 0.5 * a_max_up * dt_end* dt_end);
                dt_c = s_c / v_max;
                return {dt_start,dt_c,dt_end};  
            }

            std::pair<std::vector<float>,std::vector<float>> TrapezoidalRamp::calculate_ramp_up_fx(float cp_0)
            {
                std::vector<float>cp_up, t_up;
                int i,t;
                for(i=0;i<=(dt_start/dt);i++)
                {
                    t = i;
                    cp_up.push_back(cp_0 + 0.5*(a_max_up *t*t)); 
                    t_up.push_back(t_ramp_start + t);
                }
                return std::make_pair(t_up,cp_up);
            }

            std::pair<std::vector<float>,std::vector<float>> TrapezoidalRamp::calculate_ramp_down_fx(float cp_0,float v_0)
            {
                std::vector<float> t_down, cp_down;
                int i,t;
                for(int i=1;i<=(dt_end/dt);i++)
                {
                    t = i;
                    cp_down.push_back(cp_0 + v_0*t - 0.5*(a_max_down *t*t));
                    t_down.push_back(t_ramp_start + dt_start + dt_c + t);
                }
                return std::make_pair(t_down,cp_down);

            }

            std::pair<std::vector<float>,std::vector<float>> TrapezoidalRamp::calculate_constant_fx(float cp_0)
            {
                 std::vector<float> t_c, cp_c;
                int i,t;
                for(i=1;i<=(dt_c/dt);i++)
                {
                    t = i;
                    cp_c.push_back(cp_0 +v_max * t);
                    t_c.push_back(t_ramp_start+dt_start+t);
                }
                return std::make_pair(t_c,cp_c);
            }

            std::pair<std::vector<float>,std::vector<float>> TrapezoidalRamp::calculate_cp_and_time(float cp_0)
            {
                calculate_time_offsets();
                auto u = calculate_ramp_up_fx(0);
                auto c = calculate_constant_fx(u.second.back());
                auto d = calculate_ramp_down_fx(c.second.back(),v_max);

                u.first.insert( u.first.end(), c.first.begin(), c.first.end() );
                u.first.insert(u.first.end(),d.first.begin(),d.first.end());

                u.second.insert( u.second.end(), c.second.begin(), c.second.end() );
                u.second.insert(u.second.end(),d.second.begin(),d.second.end());

                return u;
            }

}