set(CMAKE_CXX_FLAGS_DEBUG_INIT "-Wall")
set(CMAKE_CXX_FLAGS_RELEASE_INIT "-Wall")
project(imgui-sfml-example)
find_package(eCAL REQUIRED)
find_package(Protobuf REQUIRED)

add_executable(${PROJECT_NAME}
  main.cpp
  ImGuiFileDialog.cpp
  imnodes.cpp
  save_load.cpp
  implot.cpp
  implot_items.cpp
  trajectory_planer/trajectory_planer.cpp
#  trajectory_planer/inverse_kinematics.cpp
  )

set(proto_src
  ${CMAKE_CURRENT_SOURCE_DIR}/../proto/gui_types.proto
)
PROTOBUF_TARGET_CPP(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/../proto ${proto_src})


  target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

# Yep, that's it!
target_link_libraries(${PROJECT_NAME}
  PUBLIC
    ImGui-SFML::ImGui-SFML
    lib
    eCAL::core
    protobuf::libprotobuf
)


include(Install.cmake)
