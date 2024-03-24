#pragma once
#include <vector>

namespace example {

    struct Node {
        int id;
        float value;
        float value_y;
        float value_z;

        Node() = default;

        Node(const int i, const float v) : id(i), value(v) { }
    };

void NodeEditorInitialize(const char* savefile);
void NodeEditorLoad(const char* savefile);
void NodeEditorShow();
void NodeEditorShutdown(const char* savefile);
std::vector<Node> NodeEditorExport();
} // namespace example