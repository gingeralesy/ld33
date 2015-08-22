project(LD33)
cmake_minimum_required(VERSION 2.8)
aux_source_directory(. SRC_LIST)

include_directories(
  "C:\\devel\\include"
)
link_directories(
  "C:\\devel\\lib"
)

add_executable(${PROJECT_NAME} ${SRC_LIST})

target_link_libraries(${PROJECT_NAME}
                      sfml-main
                      sfml-system
                      sfml-window
                      sfml-graphics)
