
/*
    ref: https://github.com/ros2/turtlebot2_demo/blob/master/turtlebot2_follower/src/follower.cpp#L133
    
*/
#include "sys_ros.h"

using namespace cart;

namespace{
    struct LC{
        struct MotorCfg{
            float turn_scl = 5;
            float spd_scl = 2;
        }; MotorCfg motor_cfg;
    }; LC lc_;
}
//----
void Motors_ros::init_ros_node()
{
    pub_ = node_.create_publisher<geometry_msgs::msg::Twist>("/cmd_vel", 10);

}
//----
bool Motors_ros::setPwrs(double p0, double p1)
{
    geometry_msgs::msg::Twist m;
    auto& mc = lc_.motor_cfg;
    double turn = (p0 - p1)*mc.turn_scl;
    double spd = (p0+p1)* mc.spd_scl;

    return true;
}


//-----
void SysRos::init_cmds()
{
    sHelp_ = "SysRos commands";
    
    pUWBs_ = mkSp<UWBs_ros>();
    pMotors_ = mkSp<Motors_ros>(node_);
    Cmd::add("uwb",     pUWBs_);
    Cmd::add("motors",  pMotors_);
}
//-----
bool SysRos::init()
{
    log_i("SysRos init");
    init_ros_node();
    return true;
}
//-----
void SysRos::init_ros_node()
{

    log_i("SysRos::init_ros()...");

    log_i("SysRos::init_ros() done");

}
