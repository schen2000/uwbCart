#include "sys_ros.h"
#include "geometry_msgs/Twist.h"

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
bool Motors_ros::setPwrs(double p0, double p1)
{
    geometry_msgs::Twist m;
    auto& mc = lc_.motor_cfg;
    double turn = (p0 - p1)*mc.turn_scl;
    double spd = (p0+p1)* mc.spd_scl;

    return true;
}


//-----
void SysRos::init_cmds()
{
    sHelp_ = "SysRos commands";
    add("uwb", mkSp<UWBs_ros>());
    add("motors", mkSp<UWBs_motors>(node_));
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
    pub_ = this->create_publisher<geometry_msgs::Twist::String>("/cmd_vel", 10);

    log_i("SysRos::init_ros() done");

}
