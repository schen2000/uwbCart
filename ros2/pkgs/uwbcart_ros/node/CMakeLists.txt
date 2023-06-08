cmake_minimum_required(VERSION 3.5)
project(uwbcart_ros_node)

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)


message(STATUS "utLb_DIR=$ENV{utLib_DIR}")

add_subdirectory(dep/utlib)
add_subdirectory(dep/emblib)
add_subdirectory(cartcpp)

#-----
include_directories( 
    inc
    cartcpp/inc
    ${catkin_INCLUDE_DIRS} 
    $ENV{utLib_DIR}/inc
    $ENV{embLib_DIR}/inc
    )
#---- cart node
FILE(GLOB  SRC_CART_NODE src/*.cpp )
add_executable(cart_node  ${SRC_CART_NODE} )
#target_include_directories(uwbcart_node PUBLIC
#  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
#  $<INSTALL_INTERFACE:include>)

ament_target_dependencies(cart_node geometry_msgs rclcpp std_msgs)


target_link_libraries(cart_node 
    ${catkin_LIBRARIES}
    cartCore
    )



