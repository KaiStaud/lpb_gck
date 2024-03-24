#include "node_editor.h"

#include "imnodes.h"
#include <imgui.h>

#include <algorithm>
#include <cassert>
#include <filesystem>
#include <fstream>
#include <ios> // for std::streamsize
#include <iostream>
#include <stddef.h>
#include <vector>

namespace fs = std::filesystem;

namespace example {
namespace {


    struct Link {
        int id;
        int start_attr, end_attr;
    };

    class SaveLoadEditor {
    public:
        SaveLoadEditor() : nodes_(), links_(), current_id_(0) { }

        void show()
        {
            ImGui::TextUnformatted("A -- add node");
            ImGui::TextUnformatted(
                "Close the executable and rerun it -- your nodes should be exactly "
                "where you left them!");

            ImNodes::BeginNodeEditor();

            if (ImGui::IsWindowFocused(ImGuiFocusedFlags_RootAndChildWindows) && ImNodes::IsEditorHovered() && ImGui::IsKeyReleased(ImGuiKey_A)) {
                const int node_id = ++current_id_;
                ImNodes::SetNodeScreenSpacePos(node_id, ImGui::GetMousePos());
                nodes_.push_back(Node(node_id, 0.f));
            }

            for (Node& node : nodes_) {
                ImNodes::BeginNode(node.id);

                ImNodes::BeginNodeTitleBar();
                ImGui::TextUnformatted("node");
                ImNodes::EndNodeTitleBar();
/* X */
                ImNodes::BeginInputAttribute(node.id << 8);
                ImGui::TextUnformatted("x");
                ImNodes::EndInputAttribute();

                ImNodes::BeginStaticAttribute(node.id << 16);
                ImGui::PushItemWidth(120.f);
                ImGui::DragFloat("x", &node.value, 0.01f);
                ImGui::PopItemWidth();
                ImNodes::EndStaticAttribute();

/* Y */
                ImNodes::BeginInputAttribute(node.id << 8);
                ImGui::TextUnformatted("y");
                ImNodes::EndInputAttribute();

                ImNodes::BeginStaticAttribute(node.id << 16);
                ImGui::PushItemWidth(120.f);
                ImGui::DragFloat("y", &node.value_y, 0.01f);
                ImGui::PopItemWidth();
                ImNodes::EndStaticAttribute();
/* Z */
                ImNodes::BeginInputAttribute(node.id << 8);
                ImGui::TextUnformatted("z");
                ImNodes::EndInputAttribute();

                ImNodes::BeginStaticAttribute(node.id << 16);
                ImGui::PushItemWidth(120.f);
                ImGui::DragFloat("value", &node.value_z, 0.01f);
                ImGui::PopItemWidth();
                ImNodes::EndStaticAttribute();

                ImNodes::BeginOutputAttribute(node.id << 24);
                float text_width = ImGui::CalcTextSize("output").x;
                ImGui::Indent(120.f + ImGui::CalcTextSize("value").x - text_width);
                ImGui::TextUnformatted("output");
                ImNodes::EndOutputAttribute();

                ImNodes::EndNode();
            }

            for (const Link& link : links_) {
                ImNodes::Link(link.id, link.start_attr, link.end_attr);
            }

            ImNodes::EndNodeEditor();

            {
                Link link;
                if (ImNodes::IsLinkCreated(&link.start_attr, &link.end_attr)) {
                    link.id = ++current_id_;
                    links_.push_back(link);
                }
            }

            {
                int link_id;
                if (ImNodes::IsLinkDestroyed(&link_id)) {
                    auto iter = std::find_if(links_.begin(), links_.end(), [link_id](const Link& link) -> bool {
                        return link.id == link_id;
                    });
                    assert(iter != links_.end());
                    links_.erase(iter);
                }
            }
        }
        void replaceIniWithBytes(fs::path& filePath)
        {
            // Check if the file path ends with ".ini"
            if (filePath.extension() == ".ini") {
                // Replace the extension with ".bytes"
                filePath.replace_extension(".bytes");
            }
        }
        void
        save(const char* savefile)
        {
            fs::path ini_file = savefile; // Example file path
            //std::string ini_extension = ".ini"; // Example extension
            //ini_file += ini_extension;
            // Save the internal imnodes state
            ImNodes::SaveCurrentEditorStateToIniFile(ini_file.c_str());
            ini_file.replace_extension(".bytes");
            // Dump our editor state as bytes into a file
            std::fstream fout(
                ini_file.c_str(), std::ios_base::out | std::ios_base::binary | std::ios_base::trunc);

            // copy the node vector to file
            const size_t num_nodes = nodes_.size();
            fout.write(
                reinterpret_cast<const char*>(&num_nodes),
                static_cast<std::streamsize>(sizeof(size_t)));
            fout.write(
                reinterpret_cast<const char*>(nodes_.data()),
                static_cast<std::streamsize>(sizeof(Node) * num_nodes));

            // copy the link vector to file
            const size_t num_links = links_.size();
            fout.write(
                reinterpret_cast<const char*>(&num_links),
                static_cast<std::streamsize>(sizeof(size_t)));
            fout.write(
                reinterpret_cast<const char*>(links_.data()),
                static_cast<std::streamsize>(sizeof(Link) * num_links));

            // copy the current_id to file
            fout.write(
                reinterpret_cast<const char*>(&current_id_), static_cast<std::streamsize>(sizeof(int)));
        }

        void load(const char* savefile)
        {
            fs::path ini_file = savefile; // Example file path
            //std::string ini_extension = ".ini"; // Example extension
            //ini_file += ini_extension;
            // Load the internal imnodes state
            ImNodes::LoadCurrentEditorStateFromIniFile(ini_file.c_str()); //);"savefile.ini");
            ini_file.replace_extension(".bytes");

            // Load our editor state into memory
            std::fstream fin(ini_file.c_str(), std::ios_base::in | std::ios_base::binary);

            if (!fin.is_open()) {
                return;
            }

            // copy nodes into memory
            size_t num_nodes;
            fin.read(reinterpret_cast<char*>(&num_nodes), static_cast<std::streamsize>(sizeof(size_t)));
            nodes_.resize(num_nodes);
            fin.read(
                reinterpret_cast<char*>(nodes_.data()),
                static_cast<std::streamsize>(sizeof(Node) * num_nodes));

            // copy links into memory
            size_t num_links;
            fin.read(reinterpret_cast<char*>(&num_links), static_cast<std::streamsize>(sizeof(size_t)));
            links_.resize(num_links);
            fin.read(
                reinterpret_cast<char*>(links_.data()),
                static_cast<std::streamsize>(sizeof(Link) * num_links));

            // copy current_id into memory
            fin.read(reinterpret_cast<char*>(&current_id_), static_cast<std::streamsize>(sizeof(int)));
        }

        std::vector<Node> nodes_;

    private:
        std::vector<Link> links_;
        int current_id_;
    };

    static SaveLoadEditor editor;
} // namespace

void NodeEditorInitialize(const char* savefile)
{
    ImNodes::GetIO().LinkDetachWithModifierClick.Modifier = &ImGui::GetIO().KeyCtrl;
    ImNodes::PushAttributeFlag(ImNodesAttributeFlags_EnableLinkDetachWithDragClick);
    //    editor.load(savefile);
}

void NodeEditorShow() { editor.show(); }

void NodeEditorShutdown(const char* savefile)
{
    ImNodes::PopAttributeFlag();
    editor.save(savefile);
}

void NodeEditorLoad(const char* savefile)
{
    editor.load(savefile);
}

std::vector<Node> NodeEditorExport()
{
    return editor.nodes_;
}
} // namespace example
