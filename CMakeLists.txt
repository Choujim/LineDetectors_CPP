cmake_minimum_required(VERSION 3.5)
project(LSD LANGUAGES C CXX)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()
message("Build type: " ${CMAKE_BUILD_TYPE})

set(CMAKE_CXX_FLAGS_DEBUG "-std=c++11 -O0 -Wall -g -ggdb")
set(CMAKE_CXX_FLAGS_RELEASE "-std=c++11 -O3")
set(CMAKE_C_FLAGS_DEBUG "-std=c99 -O0")
set(CMAKE_C_FLAGS_RELEASE "-std=c99 -O3")


# OpenCV
find_package(OpenCV 3 REQUIRED)


set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
# for Windows
if(WIN32)    
    set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
else()
    set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
endif()

if(WIN32)
    link_directories(${PROJECT_SOURCE_DIR}/bin)
elseif(UNIX)
    link_directories(${PROJECT_SOURCE_DIR}/lib)
endif()


include_directories(
    ${PROJECT_SOURCE_DIR}/original
    ${PROJECT_SOURCE_DIR}/include
    ${OpenCV_INCLUDE_DIRS}
)

set(LSD_LIBC_NAME "lsd_c")
add_library(${LSD_LIBC_NAME} STATIC ./original/lsd.c)


file(GLOB SOURCES "./src/*.cpp")
add_library(${PROJECT_NAME} SHARED
    ${SOURCES}
)
target_link_libraries(${PROJECT_NAME}
    ${LSD_LIBC_NAME}
    ${OpenCV_LIBS}
)


# build specific Example
add_executable(lsd_call_example ./original/lsd_call_example.c)
target_link_libraries(lsd_call_example ${LSD_LIBC_NAME})

set(EX_1_NAME "test_lsd")
add_executable(${EX_1_NAME} ./Examples/${EX_1_NAME}.cpp)
target_link_libraries(${EX_1_NAME} ${PROJECT_NAME})


