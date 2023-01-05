project(cart)
cmake_minimum_required(VERSION 3.4)

SET(CMAKE_CXX_STANDARD 14)


add_subdirectory(dep/emblib)

message(STATUS "embLb_DIR=$ENV{embLib_DIR}")


include_directories(
    inc 
    ${EIGEN3_INCLUDE_DIR}
    $ENV{embLib_DIR}/inc
    /opt/dep/local/include
    /usr/include/jsoncpp

    )


#---- 
FILE(GLOB  SRC_CORE src/core/*.cpp)
add_library(cartCore ${SRC_CORE} )
target_link_libraries(cartCore   
    -fPIC
    pthread
    )


#--- vrpApp
FILE(GLOB  SRC_APP src/app/*.cpp)
add_executable(cartApp ${SRC_APP})
target_link_libraries(cartApp   cartCore embLib)

