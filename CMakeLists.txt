cmake_minimum_required(VERSION 3.10)
project(CatInvaders)

set(CMKAE_CXX_STANDARD 17)
set(CMKAE_CXX_STANDARD_REQUIRED ON)

find_package(OpenGL REQUIRED)
find_package(SFML COMPONENTS System Window Graphics Audio REQUIRED)
find_package(ImGui-SFML REQUIRED)
find_package(imgui REQUIRED)
find_package(nlohmann_json REQUIRED)

file(GLOB_RECURSE SOURCES "src/*.cpp")

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src")

target_link_libraries(${PROJECT_NAME}
    SFML::Graphics
    SFML::Window
    SFML::System
    SFML::Audio
    OpenGL::GL
    imgui::imgui
    ImGui-SFML::ImGui-SFML
    nlohmann_json::nlohmann_json
)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_CURRENT_SOURCE_DIR}/res"
    "$<TARGET_FILE_DIR:${PROJECT_NAME}>/res"
)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory
        "$<TARGET_FILE_DIR:${PROJECT_NAME}>/saves"
)
