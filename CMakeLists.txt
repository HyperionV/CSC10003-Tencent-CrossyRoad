cmake_minimum_required(VERSION 3.24)
project(CSC10003_Tencent_CrossyRoad)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")

include_directories(.)

# Path to WinMM.Lib and XAudio2.Lib
link_directories(C:\\Program Files \(x86\)\\Windows Kits\\10\\Lib\\10.0.22621.0\\um\\x64)

# Add XAudio2 and WinMM to the target_link_libraries
add_executable(CSC10003_Tencent_CrossyRoad
        CrossyRoad.cpp
        Game.cpp
        Game.h
        Pixel.cpp
        Pixel.h
        resource.h
        Texture.cpp
        Texture.h
        Utilities.cpp Utilities.h
        Movable.cpp Movable.h
        Sprite.cpp Sprite.h
        Frame.cpp Frame.h
        MenuScreen.cpp
        Player.cpp
        Entity.cpp
        Audio.cpp
        Map.cpp
        Lane.cpp
        Text.cpp Font.cpp Item.cpp Supportive.cpp TrafficLight.cpp Drawable.cpp Drawable.h Event.cpp Event.h TextBox.cpp TextCursor.cpp FileDialog.cpp FileDialog.h)

# Link to GLFW, GLEW, OpenGL, WinMM, and XAudio2
target_link_libraries(CSC10003_Tencent_CrossyRoad PUBLIC
        ${GLFW_LIBRARIES}
        ${GLEW_LIBRARIES}
        ${OPENGL_LIBRARIES}
        "C:/Program Files (x86)/Windows Kits/10/Lib/10.0.22621.0/um/x64/winmm.lib"
        "C:/Program Files (x86)/Windows Kits/10/Lib/10.0.22621.0/um/x64/xaudio2.lib")
