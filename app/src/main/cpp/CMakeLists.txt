# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

cmake_minimum_required(VERSION 3.22.1)

project("test_cpp")

# Creates your game shared library. The name must be the same as the
# one used for loading in your Kotlin/Java or AndroidManifest.txt files.
add_library(test_cpp SHARED
        main.cpp
        AndroidOut.cpp
        Utility.cpp

        gfx/FrameBuffer.cpp
        gfx/TextConsole.cpp
        gfx/Draw.cpp

        gfx/widget/Widget.cpp
        gfx/widget/LabelWidget.cpp
        gfx/widget/PanelWidget.cpp
        gfx/widget/StatusBarWidget.cpp
        gfx/widget/GroupBoxWidget.cpp
        gfx/widget/MenuBarWidget.cpp
        gfx/widget/PopupMenuWidget.cpp
        gfx/widget/WidgetManager.cpp

        engine/Engine.cpp
        engine/Renderer.cpp
        engine/Input.cpp
        engine/KeyboardBuffer.cpp

        machine/FrameBufferMachine.cpp
        machine/TestMachine.cpp

        machine/z80ex/z80ex.c
        machine/z80ex/z80ex_dasm.c
)

target_compile_definitions(test_cpp PRIVATE
        WORDS_LITTLE_ENDIAN
        Z80EX_API_REVISION=1
        Z80EX_VERSION_MAJOR=1
        Z80EX_VERSION_MINOR=21
        Z80EX_RELEASE_TYPE=""
        Z80EX_VERSION_STR="1.21"
)

# Searches for a package provided by the game activity dependency
find_package(game-activity REQUIRED CONFIG)

# Forces the linker to keep the JNI entry point for GameActivity
set(CMAKE_SHARED_LINKER_FLAGS
        "${CMAKE_SHARED_LINKER_FLAGS} -u Java_com_google_androidgamesdk_GameActivity_initializeNativeCode")

target_include_directories(test_cpp PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/engine
        ${CMAKE_CURRENT_SOURCE_DIR}/gfx
        ${CMAKE_CURRENT_SOURCE_DIR}/gfx/widget
        ${CMAKE_CURRENT_SOURCE_DIR}/machine
        ${CMAKE_CURRENT_SOURCE_DIR}/machine/z80ex
        ${CMAKE_CURRENT_SOURCE_DIR}/machine/z80ex/include
)

# Configure libraries CMake uses to link your target library.
target_link_libraries(test_cpp
        # The game activity
        game-activity::game-activity_static

        # EGL and other dependent libraries required for drawing
        # and interacting with Android system
        EGL
        GLESv3
        jnigraphics
        android
        log)