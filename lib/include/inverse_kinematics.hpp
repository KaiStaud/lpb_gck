#include <eigen3/Eigen/Dense>
#include <math.h>
#include <utility>
#include <fmt/core.h>
using Eigen::VectorXd;

#define PI 3.14159265


enum class IK_Error
{

    out_of_range = 0,

    ik_solved = 1,

    no_solution_found = 2,

};

struct IK_Result {
    IK_Error error;
    Eigen::Vector3d effektor1;
    Eigen::Vector3d effektor2;
    Eigen::Vector3d effektor3;

    // Overloading the == operator
    bool operator==(const IK_Result& other) const {
        return (error == other.error && 
                effektor1 == other.effektor1 && 
                effektor2 == other.effektor2 &&
                effektor3 == other.effektor3);
    }
};
// Helper Funktionen:
// Formatter specialization for IK_Result
template <>
struct fmt::formatter<IK_Result> {
    constexpr auto parse(format_parse_context& ctx) { return ctx.begin(); }

    template <typename FormatContext>
    auto format(const IK_Result& result, FormatContext& ctx) {
        return format_to(ctx.out(), "IK_Result {{ error: {}, effektor1: {}, effektor2: {}, effektor3: {} }}",
                         result.error, result.effektor1, result.effektor2, result.effektor3);
    }
};
// Geradengleichung aus Vektor bestimmen:
std::pair<double, double> calculate_vector_fx(double m, Eigen::Vector3d v);
std::pair<double, double> calculate_vector_fx(Eigen::Vector3d v, Eigen::Vector3d y);

// Schnittpunkt (intersection) von zwei vektoren bestimmen:
Eigen::Vector3d calculate_intersection(double a, double b, double m, double u);

// Perform a simple IK: If not set, use preset tuple:
IK_Result simple_ik(double sizeof_arm = 4,double num_effectors = 2,Eigen::Vector3d e_r={5,5,0} );
