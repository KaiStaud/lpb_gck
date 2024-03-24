set(CMAKE_CXX_FLAGS_DEBUG_INIT "-Wall")
set(CMAKE_CXX_FLAGS_RELEASE_INIT "-Wall")

add_executable(imgui-sfml-example
  main.cpp
  ImGuiFileDialog.cpp
  imnodes.cpp
  save_load.cpp
  implot.cpp
  implot_items.cpp
  trajectory_planer/trajectory_planer.cpp
#  trajectory_planer/inverse_kinematics.cpp
  )
target_compile_features(imgui-sfml-example PUBLIC cxx_std_17)

# Yep, that's it!
target_link_libraries(imgui-sfml-example
  PUBLIC
    ImGui-SFML::ImGui-SFML
    lib
)


include(Install.cmake)
