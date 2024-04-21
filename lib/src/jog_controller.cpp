#include "../include/jog_controller.hpp"

/*
Use a off-the-shelf dualshock controller to move an drive.
Jogging only allowed, when an SMI ( Supervised-Motion-Observer Image )
*/
namespace SupervisedMotionController
{
Error Check(Image img, SupervisedParameter params)
{
}
} // namespace SupervisedMotionController
namespace Jogging
{
/*  Forward Movement +V_max = +255 , V_min = 0 */
/*  Backward Movement -V_max = -255, V_min = 0 */
/* Rauschen um Nullposition soll keine Bewegung sein */
void enable_deadband()
{
}
void calibrate_controller()
{
}
/* setting: speed,acceleration etc... */
void load_drive_config()
{
}
int calculate_jog_position(const int sps, const int steps_t0, const int dt)
{
    return sps * dt + steps_t0;
}

} // namespace Jogging