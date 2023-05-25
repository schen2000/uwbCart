#include "sys_ros.h"

using namespace cart;

//-----
bool SysRos::init()
{
    log_i("SysRos init");
    return true;
}
//-----
void SysRos::init_ros()
{

    log_i("SysRos::init_ros()...");
    pub_log_ = node_.create_publisher<std_msgs::msg::String>("/cart/log", 10);
    log_i("SysRos::init_ros() done");

}
