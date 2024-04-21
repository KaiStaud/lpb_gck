/*
Use a off-the-shelf dualshock controller to move an drive.
Jogging only allowed, when an SMI ( Supervised-Motion-Observer Image )
*/
namespace SupervisedMotionController
{
struct Image
{
    float schleppfehler;
    float schlepp_zeit;
};
struct SupervisedParameter
{
    int position;
};
enum class Error
{
    OK,
    Error
};

Error Check(Image img, SupervisedParameter params);
} // namespace SupervisedMotionController
namespace Jogging
{
/*  Forward Movement +V_max = +255 , V_min = 0 */
/*  Backward Movement -V_max = -255, V_min = 0 */
/* Rauschen um Nullposition soll keine Bewegung sein */
void calibrate_controller();
void enable_deadband();

/* setting: speed,acceleration etc... */
void load_drive_config();
int calculate_jog_position(const int sps, const int steps_t0, const int dt);
} // namespace Jogging