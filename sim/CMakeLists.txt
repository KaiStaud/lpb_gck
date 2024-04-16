set(CMAKE_CXX_FLAGS_DEBUG_INIT "-Wall")
set(CMAKE_CXX_FLAGS_RELEASE_INIT "-Wall")

find_package(eCAL REQUIRED)
find_package(Protobuf REQUIRED)

project(drive-simulator)
add_executable(${PROJECT_NAME}
  main.cpp
)

set(proto_src
    ${CMAKE_CURRENT_SOURCE_DIR}/../proto/gui_types.proto
)
PROTOBUF_TARGET_CPP(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/../proto ${proto_src})



target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

# Yep, that's it!
target_link_libraries(${PROJECT_NAME}
  PUBLIC
    lib
    eCAL::core
    protobuf::libprotobuf
)
