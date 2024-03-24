#include <iostream>

#include "imgui-SFML.h"
#include "imgui.h"

#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

#include "ImGuiFileDialog.h"
#include "imgui-logging.h"
#include "imnodes.h"
#include "node_editor.h"
#include "implot.h"
#include "../lib/include/inverse_kinematics.hpp"
// Taken from https://github.com/ocornut/imgui/issues/707

void setFancyImguiStyle()
{
    ImGui::GetStyle().FrameRounding = 4.0f;
    ImGui::GetStyle().GrabRounding = 4.0f;

    ImVec4 *colors = ImGui::GetStyle().Colors;
    colors[ImGuiCol_Text] = ImVec4(0.95f, 0.96f, 0.98f, 1.00f);
    colors[ImGuiCol_TextDisabled] = ImVec4(0.36f, 0.42f, 0.47f, 1.00f);
    colors[ImGuiCol_WindowBg] = ImVec4(0.11f, 0.15f, 0.17f, 1.00f);
    colors[ImGuiCol_ChildBg] = ImVec4(0.15f, 0.18f, 0.22f, 1.00f);
    colors[ImGuiCol_PopupBg] = ImVec4(0.08f, 0.08f, 0.08f, 0.94f);
    colors[ImGuiCol_Border] = ImVec4(0.08f, 0.10f, 0.12f, 1.00f);
    colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    colors[ImGuiCol_FrameBg] = ImVec4(0.20f, 0.25f, 0.29f, 1.00f);
    colors[ImGuiCol_FrameBgHovered] = ImVec4(0.12f, 0.20f, 0.28f, 1.00f);
    colors[ImGuiCol_FrameBgActive] = ImVec4(0.09f, 0.12f, 0.14f, 1.00f);
    colors[ImGuiCol_TitleBg] = ImVec4(0.09f, 0.12f, 0.14f, 0.65f);
    colors[ImGuiCol_TitleBgActive] = ImVec4(0.08f, 0.10f, 0.12f, 1.00f);
    colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);
    colors[ImGuiCol_MenuBarBg] = ImVec4(0.15f, 0.18f, 0.22f, 1.00f);
    colors[ImGuiCol_ScrollbarBg] = ImVec4(0.02f, 0.02f, 0.02f, 0.39f);
    colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.20f, 0.25f, 0.29f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.18f, 0.22f, 0.25f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.09f, 0.21f, 0.31f, 1.00f);
    colors[ImGuiCol_CheckMark] = ImVec4(0.28f, 0.56f, 1.00f, 1.00f);
    colors[ImGuiCol_SliderGrab] = ImVec4(0.28f, 0.56f, 1.00f, 1.00f);
    colors[ImGuiCol_SliderGrabActive] = ImVec4(0.37f, 0.61f, 1.00f, 1.00f);
    colors[ImGuiCol_Button] = ImVec4(0.20f, 0.25f, 0.29f, 1.00f);
    colors[ImGuiCol_ButtonHovered] = ImVec4(0.28f, 0.56f, 1.00f, 1.00f);
    colors[ImGuiCol_ButtonActive] = ImVec4(0.06f, 0.53f, 0.98f, 1.00f);
    colors[ImGuiCol_Header] = ImVec4(0.20f, 0.25f, 0.29f, 0.55f);
    colors[ImGuiCol_HeaderHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.80f);
    colors[ImGuiCol_HeaderActive] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
    colors[ImGuiCol_Separator] = ImVec4(0.20f, 0.25f, 0.29f, 1.00f);
    colors[ImGuiCol_SeparatorHovered] = ImVec4(0.10f, 0.40f, 0.75f, 0.78f);
    colors[ImGuiCol_SeparatorActive] = ImVec4(0.10f, 0.40f, 0.75f, 1.00f);
    colors[ImGuiCol_ResizeGrip] = ImVec4(0.26f, 0.59f, 0.98f, 0.25f);
    colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
    colors[ImGuiCol_ResizeGripActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
    colors[ImGuiCol_Tab] = ImVec4(0.11f, 0.15f, 0.17f, 1.00f);
    colors[ImGuiCol_TabHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.80f);
    colors[ImGuiCol_TabActive] = ImVec4(0.20f, 0.25f, 0.29f, 1.00f);
    colors[ImGuiCol_TabUnfocused] = ImVec4(0.11f, 0.15f, 0.17f, 1.00f);
    colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.11f, 0.15f, 0.17f, 1.00f);
    colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
    colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
    colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
    colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
    colors[ImGuiCol_TextSelectedBg] = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
    colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
    colors[ImGuiCol_NavHighlight] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
    colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
    colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
    colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);
}
std::string FileDialog()
{
    std::string filePath = "";
    ImGui::Begin("file dialog");
    // open Dialog Simple
    if (ImGui::Button("Open File Dialog"))
    {
        IGFD::FileDialogConfig config;
        config.path = ".";
        ImGuiFileDialog::Instance()->OpenDialog("ChooseFileDlgKey", "Choose File", ".cpp,.h,.hpp", config);
    }
    // display
    if (ImGuiFileDialog::Instance()->Display("ChooseFileDlgKey"))
    {
        if (ImGuiFileDialog::Instance()->IsOk())
        { // action if OK
            std::string filePathName = ImGuiFileDialog::Instance()->GetFilePathName();
            filePath = ImGuiFileDialog::Instance()->GetCurrentPath();
            // action
        }

        // close
        ImGuiFileDialog::Instance()->Close();
    }
    ImGui::End();
    return filePath;
}

void openDialog(const std::string key, const std::string title, IGFD::FileDialogConfig config)
{
    ImGuiFileDialog::Instance()->OpenDialog(key, title, ".cpp,.h,.txt", config);
}

std::string rDialog(const std::string key)
{
    if (ImGuiFileDialog::Instance()->Display(key))
    {
        if (ImGuiFileDialog::Instance()->IsOk())
        { // action if OK
            std::string filePathName = ImGuiFileDialog::Instance()->GetFilePathName();
            // filePath = ImGuiFileDialog::Instance()->GetCurrentPath();
            // action
        }

        // close
        ImGuiFileDialog::Instance()->Close();
    }
}


std::vector<example::Node> nodes; 

void plot_drives(std::vector<example::Node> Nodes,int length){
    static ExampleAppLog log;
    log.Draw("title");

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
    
        if(Nodes.size() > last_size)
        {
            log.AddLog("----- IK Report -----\r\n");
            for(int i=0;i<length;i++)
            {
              log.AddLog("----- Node %i -----\n",i);
              log.AddLog("E1 : x={%f},y={%f},z={%f}\n",i,x1[i],y1[i],0);
              log.AddLog("E2 : x={%f},y={%f},z={%f}\r\n",i,x2[i],y2[i],0);
            }
        }
    }
    last_size = Nodes.size();
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



void Demo_MultipleAxes() {
float x_data[1000] ;
float y_data[1000] ;

for (int i=0;i<1000;i++)
{
    x_data[i]=i;
    y_data[i]=std::rand() %10;
}
//    ImPlot::PlotLine("My Line Plot", x_data, y_data, 1000);
    if(nodes.size() > 0)
      plot_drives(nodes,nodes.size());
    

}

int main()
{
    sf::RenderWindow window{sf::VideoMode(640, 480), "ImGui + SFML = <3"};
    window.setFramerateLimit(60);

    ImGui::SFML::Init(window);

    auto &io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    auto fancyFont = io.Fonts->AddFontFromFileTTF("/hdd/pbuilding/lpb-workspace/imgui-sfml-fetchcontent/resources/fonts/hubballi-regular.ttf", 20);
    if (!ImGui::SFML::UpdateFontTexture())
    {
        std::cerr << "No luck\n";
    }

    setFancyImguiStyle();

    sf::Clock deltaClock{};
    while (window.isOpen())
    {
        sf::Event event{};
        while (window.pollEvent(event))
        {
            ImGui::SFML::ProcessEvent(window, event);

            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        ImGui::SFML::Update(window, deltaClock.restart());

        static ImVec4 circleColor{1.0f, 0.0f, 1.0f, 0.5f};
        static float circleRadius = 100.f;
        static std::size_t circlePoints = 30;

        sf::CircleShape shape{circleRadius, circlePoints};
        shape.setFillColor(circleColor);

        static ImVec2 viewportSize{700, 700};
        sf::RenderTexture rt{};
        rt.create(viewportSize.x, viewportSize.y);

        rt.clear(sf::Color::Black);
        rt.draw(shape);
        ImGui::SetNextWindowSize(ImVec2(500, 400), ImGuiCond_FirstUseEver);
        ImGui::PushFont(fancyFont);
        ImGui::DockSpaceOverViewport();
        using namespace IGFD;
        IGFD::FileDialogConfig config;
        config.path = ".";
        // Main menu bar
        if (ImGui::BeginMainMenuBar())
        {
            if (ImGui::BeginMenu("File"))
            {
                ImGui::SetNextWindowSize(ImVec2(500, 400));
                if (ImGui::MenuItem("Open", "Ctrl+O"))
                {
                    ImGuiFileDialog::Instance()->OpenDialog("ChooseFileDlgKey", "Choose File", ".ini", config);
                }
                if (ImGui::MenuItem("Save", "Ctrl+S"))
                {
                    ImGuiFileDialog::Instance()->OpenDialog("SaveFileDlgKey", "Save File", ".ini", config);
                }
                if (ImGui::MenuItem("Exit", "Alt+F4"))
                {
                }
                ImGui::EndMenu();
            }
            ImGui::EndMainMenuBar();
        }

        // Update and render ImGuiFileDialog
        if (ImGuiFileDialog::Instance()->Display("ChooseFileDlgKey"))
        {
            if (ImGuiFileDialog::Instance()->IsOk())
            { // action if OK
                std::string filePathName = ImGuiFileDialog::Instance()->GetFilePathName();
                example::NodeEditorInitialize(filePathName.c_str());
                example::NodeEditorLoad(filePathName.c_str());
            }

            // close
            ImGuiFileDialog::Instance()->Close();
        }
        if (ImGuiFileDialog::Instance()->Display("SaveFileDlgKey"))
        {
            if (ImGuiFileDialog::Instance()->IsOk())
            { // action if OK
                std::string filePathName = ImGuiFileDialog::Instance()->GetFilePathName();
                example::NodeEditorShutdown(filePathName.c_str());
                // filePath = ImGuiFileDialog::Instance()->GetCurrentPath();
                // action
            }
            ImGuiFileDialog::Instance()->Close();
        }
        if (ImGui::Begin("Trajectory Plotter"))
        {
            ImPlot::CreateContext();
            Demo_MultipleAxes();
        }
        ImGui::End();

        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.f, 0.f));
        if (ImGui::Begin("Viewport"))
        {
            viewportSize = ImGui::GetWindowSize();
            ImGui::Image(rt);
        }
        ImGui::End();

        if (ImGui::Begin("Node Editor"))
        {
            ImNodes::CreateContext();
            example::NodeEditorInitialize("save_load.ini");
            example::NodeEditorShow();
            nodes = example::NodeEditorExport();
        }
        ImGui::End();

        ImGui::PopStyleVar();
        ImGui::PopFont();

        window.clear();
        window.draw(shape);
        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();

    return 0;
}
