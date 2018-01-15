cmake_minimum_required(VERSION 2.8.3)
project(step_voice_libs)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
    std_msgs
)

find_path(LIBESPEAK_INCLUDE_DIRS
          NAMES speak_lib.h
          HINTS /usr/include/espeak)
find_library(LIBESPEAK_LIBRARIES
             NAMES espeak
             HINTS /usr/lib/ /usr/x86_64-linux-gnu/
             PATH_SUFFIXES lib)

catkin_package(
    INCLUDE_DIRS include
    LIBRARIES step_voice_libs
    CATKIN_DEPENDS roscpp std_msgs
    DEPENDS libespeak-dev LIBESPEAK
)

include_directories(
    ${catkin_INCLUDE_DIRS}
    ${LIBESPEAK_INCLUDE_DIRS}
    include
)

add_library(step_voice_libs SHARED
    src/voice.cpp
)

target_link_libraries(step_voice_libs
  ${catkin_LIBRARIES}
  ${LIBESPEAK_LIBRARIES}
)

add_dependencies(step_voice_libs ${catkin_EXPORTED_TARGETS})

install(TARGETS step_voice_libs
    ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
    LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
    RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)
