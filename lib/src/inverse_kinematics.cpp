#include <eigen3/Eigen/Dense>
#include <math.h>
#include <utility>
#include <iostream>
#include "../include/inverse_kinematics.hpp"
using Eigen::VectorXd;

#define PI 3.14159265

// Helper Funktionen:

// Geradengleichung aus Vektor bestimmen:

std::pair<double, double> calculate_vector_fx(double m, Eigen::Vector3d v)
{

    auto b = v[1] - m * v[0];

    auto fx_params = std::make_pair(m, b);

    return fx_params;
}

std::pair<double, double> calculate_vector_fx(Eigen::Vector3d v, Eigen::Vector3d y)
{
    auto m = (v[1] - y[1]) / (v[0] - y[0]);

    auto b = v[1] - m * v[0];

    auto fx_params = std::make_pair(m, b);

    return fx_params;
}

// Schnittpunkt (intersection) von zwei vektoren bestimmen:

Eigen::Vector3d calculate_intersection(double a, double b, double m, double u)
{

    Eigen::Vector3d i;

    i[0] = (u - b) / (a - m);

    i[1] = a * i[0] + b;
    i[2] = 0;

    return i;
}

// Perform a simple IK: If not set, use preset tuple:
IK_Result simple_ik(double sizeof_arm ,double num_effectors , Eigen::Vector3d e_r)
{
    IK_Result res;
    // Instantiation of a dynamic 3D column vector. Via the subscript operator the values are set to

    Eigen::Vector3d e_2;//(3UL);

    Eigen::Vector3d e_1;//(3UL);

    // Fehlerfaelle pruefen:

    if (e_r.norm()> num_effectors * sizeof_arm)
    {
        res.error = IK_Error::out_of_range;
        return res;
    }

    else

    {

        // Haelfte vom ZielVektor berechnen:

        auto alpha = atan(e_r[1] / e_r[0]);

//        std::cout << "\r\n Alpha [rad] = " << alpha;

        auto y_stuetzvektor = sin(alpha) * (e_r.norm() / 2);

        auto x_stuetzvektor = cos(alpha) * (e_r.norm() / 2);
        ;

        // Normalvektor berechnen:

        auto sizeof_n = sqrt(pow(sizeof_arm, 2) - pow(e_r.norm() / 2, 2));

        // std::cout << "\r\n Zielvektor-Länge=  = " << length(e_r) / 2;
        // std::cout << "\r\n Normalvektor-Länge=  = " << sizeof_n;

        // Jetzt den Winkel zwischen effektor1 und x Achse berechen

        auto beta = alpha + (sizeof_n / (e_r.norm() / 2));

//        std::cout << "\r\n Beta [rad] = " << beta;

        // Koordinaten vom Schnittpunkt des normalenvektors und effektor1:

        e_1[0] = cos(beta) * sizeof_arm;

        e_1[1] = sin(beta) * sizeof_arm;

        // std::cout << "\r\n"
        //           << e_1[0] << " " << e_1[1];

        // Vom Schnittpunkt aus kann der nächste Effektor bestimmt werden:

        auto e_2 = e_r - e_1;

        // TCP wurde bereits übergeben! Nix mehr zu tun!

        res.effektor1 = e_1;
        res.effektor2 = e_r;
        res.error = IK_Error::ik_solved;
        return res;
    }
}