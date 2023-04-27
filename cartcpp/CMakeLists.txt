project(cart)
cmake_minimum_required(VERSION 3.4)

SET(CMAKE_CXX_STANDARD 17)

message(STATUS "utLb_DIR=$ENV{utLib_DIR}")
message(STATUS "embLb_DIR=$ENV{embLib_DIR}")

include_directories(
    inc 
    ${EIGEN3_INCLUDE_DIR}
    $ENV{utLib_DIR}/inc
    $ENV{embLib_DIR}/inc
    /opt/dep/local/include
    /usr/include/jsoncpp

    )


#---- 
FILE(GLOB  SRC_CORE src/core/*.cpp)
add_library(cartCore ${SRC_CORE} )
target_link_libraries(cartCore   
    utLib
    -fPIC
    pthread
    )


#--- app
FILE(GLOB  SRC_APP src/app/*.cpp)
add_executable(cartApp ${SRC_APP})
target_link_libraries(cartApp   
	cartCore 
	embLib
	#-lpigpio
	#	-lstdc++fs
	)

