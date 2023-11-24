cmake_minimum_required(VERSION 3.24)
project(CSC10003_Tencent_CrossyRoad)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

# Path to WinMM.Lib
link_directories(C:\\Program Files \(x86\)\\Windows Kits\\10\\Lib\\10.0.18362.0\\um\\x64)

# Link to GLFW, GLEW and OpenGL
#target_link_libraries(template PUBLIC
#        ${GLFW_LIBRARIES}
#        ${GLEW_LIBRARIES}
#        ${OPENGL_LIBRARIES}
#        ${winMM.Lib})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")

add_executable(CSC10003_Tencent_CrossyRoad
        CrossyRoad.cpp
        Game.cpp
        Game.h
        Pixel.cpp
        Pixel.h
        resource.h
        Texture.cpp
        Texture.h
        Utilities.cpp Utilities.h Movable.cpp Movable.h Sprite.cpp Sprite.h Frame.cpp Frame.h Screen.cpp Player.cpp Entity.cpp Audio.cpp)
