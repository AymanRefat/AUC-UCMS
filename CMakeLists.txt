cmake_minimum_required(VERSION 3.29)
project(UCMS)

set(CMAKE_AUTOUIC ON)  # Enable automatic UIC
set(CMAKE_AUTOMOC ON)  # Enable automatic MOC
set(CMAKE_AUTORCC ON)  # Enable automatic RCC

# Add your UI file
set(SOURCES
        main.cpp
        mainwindow.cpp
        email.cpp
        event.cpp
        student.cpp
        admin.cpp
        mainwindow.cpp
        user.cpp
        app.cpp
        courserepository.cpp
        activityrepository.cpp
)

set(HEADERS
        mainwindow.h
        email.h
        event.h
        student.h
        admin.h
        app.h
)

set(UI_FILES
        mainwindow.ui
        course.cpp
)

# Add executable
add_executable(UCMS ${SOURCES} ${HEADERS} ${UI_FILES})


include_directories(.)

add_executable( main.cpp
        mainwindow.cpp
        mainwindow.h
        email.h
        email.cpp
        event.cpp
        event.h
        mainwindow.ui
        student.cpp
        student.h
        admin.cpp
        admin.h

)



set(CMAKE_PREFIX_PATH "/Users/ayman/Qt/6.7.2/macos" CACHE STRING "Path to Qt6 installation")

# Find the required Qt6 packages, including Multimedia
find_package(Qt6 REQUIRED COMPONENTS Core Widgets Gui Multimedia)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Link the Qt6 libraries to your executable, including Multimedia
target_link_libraries(${PROJECT_NAME} Qt6::Core Qt6::Widgets Qt6::Gui Qt6::Multimedia)

# Include directories for Qt6
target_include_directories(${PROJECT_NAME} PRIVATE ${Qt6Core_INCLUDE_DIRS} ${Qt6Widgets_INCLUDE_DIRS} ${Qt6Gui_INCLUDE_DIRS} ${Qt6Multimedia_INCLUDE_DIRS})
