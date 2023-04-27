project(rostest)
cmake_minimum_required(VERSION 3.4)


message(STATUS "utLb_DIR=$ENV{utLib_DIR}")
message(STATUS "vsnLb_DIR=$ENV{vsnLib_DIR}")

find_package (Eigen3 3.3 REQUIRED NO_MODULE)

#----- submodules
add_subdirectory(dep/utlib)
add_subdirectory(dep/emblib)
add_subdirectory(cartcpp)

#-----
include_directories( 
    inc
    ${catkin_INCLUDE_DIRS} 
    ${OpenCV_INCLUDE_DIRS} 
    $ENV{utLib_DIR}/inc
    $ENV{embLib_DIR}/inc
    ${EIGEN3_INCLUDE_DIR}
    common
    vrpcpp/inc
    vsnLib/inc
    )



#---- cart node
FILE(GLOB  SRC_CART_NODE *.cpp )
add_executable(vision_node  ${SRC_VISION} )
target_link_libraries(vision_node 
    ${catkin_LIBRARIES}
    ${OpenCV_LIBRARIES}
    vrpCore
    )


#---- cam server node
FILE(GLOB  SRC_CAMSVR camserver/*.cpp src/common/*.cpp)
add_executable(camserver_node  ${SRC_CAMSVR} )
target_link_libraries(camserver_node 
    ${catkin_LIBRARIES}
    vsnLib
    )
