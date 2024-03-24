#include <eigen3/Eigen/Dense>
#include <vector>
#include "../node_editor.h"

using Eigen::VectorXd;
using example::Node;
struct Trajectory_Transform
{
    std::vector<Eigen::Vector3d> instructions_joint1;
    std::vector<Eigen::Vector3d> instructions_joint2;
};

/* Load trajectory from .data-file */
void load_trajectory();

/* Add a trajectory to plot */
void plot_trajectories(std::vector<example::Node> Nodes,int length);