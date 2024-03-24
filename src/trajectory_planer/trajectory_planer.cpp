#include <eigen3/Eigen/Dense>
#include <vector>

#include "trajectory_planer.hpp"
#include "../../lib/include/inverse_kinematics.hpp"
#include "../node_editor.h"
#include "../implot.h"
using Eigen::VectorXd;

/* Load trajectory from .data-file */
void load_trajectory()
{

}

struct trajectory_set{
    std::vector<Eigen::Vector3d> joint1;
    std::vector<Eigen::Vector3d> joint2; 
};

void plot_trajectories(std::vector<example::Node> Nodes,int length){
static int last_size;
std::vector< Eigen::Vector3d > instructions;
    for(int i=0;i<Nodes.size();i++)
    {
        Eigen::Vector3d vector(
        Nodes[i].value,
        Nodes[i].value_y,
        Nodes[i].value_z);      
        instructions.push_back(vector);        
    }
    float x[10];
    float y[10];
    
    float x1[10];
    float y1[10];
    float x2[10];
    float y2[10];
    
    for(int i=0;i<length;i++)
    {
        x[i]= Nodes[i].value;
        y[i] =Nodes[i].value_y;

        Eigen::Vector3d v(Nodes[i].value,Nodes[i].value_y,0);
        IK_Result res= simple_ik(4,2,v);
        x1[i]= res.effektor1[0];
        y1[i]= res.effektor1[1];
        x2[i]= res.effektor2[0];
        y2[i]= res.effektor2[1];
    }

if (ImPlot::BeginPlot("tcp")) 
{
        ImPlot::PlotScatter("1st effektor",x,y,length);

}
    ImPlot::EndPlot();

if (ImPlot::BeginPlot("e1")) 
{
        ImPlot::PlotScatter("1st effektor",x1,y1,length);

}
    ImPlot::EndPlot();


if (ImPlot::BeginPlot("e2")) 
{
    
    ImPlot::PlotScatter("2nd effektor",x2,y2,length);

}
    ImPlot::EndPlot();
}