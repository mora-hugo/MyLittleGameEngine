cmake_minimum_required(VERSION 3.26)

#add third party libraries
add_subdirectory(Thirdparty/glfw-3.3.2)			#window opener
add_subdirectory(Thirdparty/glad)				#opengl loader
add_subdirectory(Thirdparty/stb_image)			#loading images
add_subdirectory(Thirdparty/stb_truetype)		#loading ttf files
add_subdirectory(Thirdparty/glm)				#math
add_subdirectory(Thirdparty/imgui-docking)		#gui
add_subdirectory(Thirdparty/json-3.11.3)		#json
add_subdirectory(Thirdparty/spdlog-1.15.1)		#log library
add_subdirectory(ThirdParty/assimp-5.4.3)


project(GameEngine)

set(CMAKE_CXX_STANDARD 20)

# add source files
file(GLOB_RECURSE SOURCES "Src/Platform/*.cpp" "Src/GameLayer/*.cpp", "Src/Editor/*.cpp" "Src/HCLogs/*.cpp")

add_executable(GameEngine ${SOURCES})

#create a resources path for the project
target_compile_definitions(GameEngine PUBLIC RESOURCES_PATH="${CMAKE_CURRENT_SOURCE_DIR}/Resources")

if(MSVC)
    target_compile_options(GameEngine PRIVATE -Wall /Zc:preprocessor)
else ()
    target_compile_options(GameEngine PRIVATE -Wall -Wextra -Wpedantic -Wconversion -Wshadow)
endif ()
#comment to e the editor
add_compile_definitions(HC_EDITOR)

# link cpp libraries
#set(CMAKE_EXE_LINKER_FLAGS "-static")



#add the include directory to the project
target_include_directories(GameEngine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Include/GameLayer)
target_include_directories(GameEngine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Include/Platform)
target_include_directories(GameEngine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Include/Editor)
target_include_directories(GameEngine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Include/HCLogs)

#add the third party libraries to the project
target_link_libraries(GameEngine imgui glad glfw stb_image stb_truetype glm nlohmann_json::nlohmann_json spdlog assimp)


