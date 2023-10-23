cmake_minimum_required(VERSION 3.24)
project(CSC10003_Tencent_CrossyRoad)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

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
        Utilities.cpp Utilities.h Movable.cpp Movable.h Sprite.cpp Sprite.h Frame.cpp Frame.h)
