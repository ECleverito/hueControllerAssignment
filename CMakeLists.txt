
cmake_minimum_required(VERSION 3.16.3)

project(hueControllerAssignment)

enable_language(CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_BINARY_DIR ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

set(SOURCE_FILES main.cpp)

find_package(Poco REQUIRED COMPONENTS Foundation Util Net XML JSON)

SET(Poco_INCLUDE_DIRS "/usr/local/Poco")
set(Poco_LIB_DIR "${POCO_PREFIX}/lib")
set(Poco_LIBS
        "${Poco_LIB_DIR}/libPocoNet.so"
        "${Poco_LIB_DIR}/libPocoUtil.so"
        "${Poco_LIB_DIR}/libPocoFoundation.so"
        "${Poco_LIB_DIR}/libPocoJSON.so")

#[[include_directories(

    ${MY_SRC_INCLUDE}
    ${Poco_INCLUDE_DIRS}
)]]

add_library(httpReqTools httpReqTools.cpp httpReqTools.h)
add_library(JSONparseTools JSONparseTools.cpp JSONparseTools.h)
add_library(lightsDB_Tools lightsDB_Tools.cpp lightsDB_Tools.h)

add_executable(runHueCtrller ${SOURCE_FILES})

target_link_libraries(runHueCtrller PocoJSON PocoFoundation PocoNet httpReqTools JSONparseTools lightsDB_Tools)
target_link_libraries(httpReqTools PocoJSON PocoFoundation PocoNet)
target_link_libraries(JSONparseTools PocoJSON PocoFoundation PocoNet)
