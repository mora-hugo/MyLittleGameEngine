cmake_minimum_required(VERSION 3.26)

#add third party libraries
add_subdirectory(Thirdparty/glfw-3.3.2)			#window oppener
add_subdirectory(Thirdparty/glad)				#opengl loader
add_subdirectory(Thirdparty/stb_image)			#loading immaged
add_subdirectory(Thirdparty/stb_truetype)		#loading ttf files
add_subdirectory(Thirdparty/glm)				#math
add_subdirectory(Thirdparty/imgui-docking)		#gui

project(GameEngine)

set(CMAKE_CXX_STANDARD 20)

# add source files
file(GLOB_RECURSE SOURCES "Src/Platform/*.cpp" "Src/GameLayer/*.cpp")

add_executable(GameEngine ${SOURCES})

#create a resources path for the project
target_compile_definitions(GameEngine PUBLIC RESOURCES_PATH="${CMAKE_CURRENT_SOURCE_DIR}/Resources")

target_compile_options(GameEngine PRIVATE -Wall -Wextra -Wpedantic -Wconversion -Wshadow)


# uncomment this line to remove the imgui docking
#add_compile_definitions(REMOVE_IMGUI)

#add the include directory to the project
target_include_directories(GameEngine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Include/GameLayer)
target_include_directories(GameEngine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Include/Platform)

#add the third party libraries to the project
target_link_libraries(GameEngine imgui glad glfw stb_image stb_truetype glm)



