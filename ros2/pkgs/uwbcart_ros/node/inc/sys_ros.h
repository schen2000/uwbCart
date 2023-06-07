#pragma once

#include "cart/sys.h"
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

namespace cart{

    class UWBs_ros : public UWBs{
    public:

    };
    class Motors_ros : public Motors{
    public:
        Motors_ros(rclcpp::Node& n):node_(n)
        virtual bool setPwrs(double p0, double p1)override;
    protected:
        rclcpp::Publisher<std_msgs::msg::String>::SharedPtr pub_;
        rclcpp::Node& node_;

    };

    //----
    class SysRos: public Sys
    {
    public:
        SysRos(rclcpp::Node& n):node_(n)
        {  init_cmds(); }
        using Sys::Sys;
        virtual bool init()override;
    
    
    protected:
        rclcpp::Node& node_;
        void init_ros_node();
        void init_cmds();


    };
}