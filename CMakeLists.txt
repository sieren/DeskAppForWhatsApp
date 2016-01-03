cmake_minimum_required(VERSION 3.2)

project (DeskApp)


if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
  if (${CMAKE_CL_64} MATCHES 0)
    message (STATUS "MSVC 64 Bit: ${CMAKE_CL_64}")
    set(CMAKE_PREFIX_PATH "C:\\Qt\\5.5\\msvc2013\\")
  else(${CMAKE_CL_64} MATCHES 0)
    set(CMAKE_PREFIX_PATH "C:\\Qt\\5.5\\msvc2013_64\\")
  endif(${CMAKE_CL_64} MATCHES 0)
else(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    set(CMAKE_PREFIX_PATH "~/Qt/5.5/clang_64/")
endif(${CMAKE_SYSTEM_NAME} MATCHES "Windows")


# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# Find the QtWidgets library
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Network)
find_package(Qt5WebKitWidgets)
find_package(Qt5Declarative)
find_package(Qt5WebSockets REQUIRED)

add_definitions(-DGLEW_STATIC)
# The Qt5Widgets_INCLUDES also includes the include directories for
# dependencies QtCore and QtGui
include_directories(${Qt5Widgets_INCLUDES})

# We need add -DQT_WIDGETS_LIB when using QtWidgets in Qt 5.
add_definitions(${Qt5Widgets_DEFINITIONS})

# qt5_wrap_ui(UI_HEADERS mainwindow.ui)
qt5_add_resources(UI_RESOURCES src/deskapp.qrc)

add_subdirectory(src src-binary)
set(SRC_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/src)

file(GLOB_RECURSE FILES_WP RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ${SRC_ROOT}/*.mm ${SRC_ROOT}/*.cpp ${SRC_ROOT}/*.h ${SRC_ROOT}/*.hpp)

set(MACOSX_BUNDLE_ICON_FILE DeskApp.icns)
set(MACOSX_BUNDLE_INFO_FILE Info.plist)
SET_SOURCE_FILES_PROPERTIES(
  DeskApp.icns
  PROPERTIES
  MACOSX_PACKAGE_LOCATION Resources
  )

  if(APPLE)
   find_library(SPARKLE_FRAMEWORK Sparkle)
    FIND_LIBRARY(COCOA_LIBRARY Cocoa)
    add_executable(DeskApp MACOSX_BUNDLE src/DeskApp.icns ${UI_HEADERS} ${UI_RESOURCES} ${FILES_WP})
    set_target_properties(DeskApp PROPERTIES MACOSX_BUNDLE_INFO_PLIST
      ${SRC_ROOT}/Info.plist)
   
  elseif(WIN32)
    add_executable(DeskApp WIN32 ${UI_HEADERS} ${UI_RESOURCES} ${FILES_WP})
  elseif(UNIX)
    add_executable(DeskApp ${FILES_WP})
  endif()
  
if (APPLE)
  target_link_libraries(
      DeskApp
      ${SPARKLE_FRAMEWORK}
      ${Qt5Core_QTMAIN_LIBRARIES}
      ${COCOA_LIBRARY})
else()
  target_link_libraries(
      DeskApp
      ${Qt5Core_QTMAIN_LIBRARIES})
endif()

if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    set_target_properties(DeskApp PROPERTIES LINK_FLAGS_DEBUG "/SUBSYSTEM:WINDOWS")
    set_target_properties(DeskApp PROPERTIES LINK_FLAGS_RELEASE "/SUBSYSTEM:WINDOWS")
    target_link_libraries(DeskApp ${Qt5Widgets_LIBRARIES} Qt5::Widgets) 
    get_target_property(QtCore_location Qt5::Core LOCATION)
endif(${CMAKE_SYSTEM_NAME} MATCHES "Windows")

qt5_use_modules(DeskApp Widgets Network WebEngineWidgets WebSockets WebKitWidgets WebChannel)

