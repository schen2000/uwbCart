#pragma once

#include "cart/sys.h"
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include <geometry_msgs/msg/twist.hpp>

namespace cart{

    class UWBs_ros : public UWBs{
    public:
        using UWBs::UWBs;

    };
    //-----
    class Motors_ros : public Motors{
    public:
        //typedef geometry_msgs::msg::Twist TwistMsg;
        Motors_ros(rclcpp::Node& n):node_(n)
            { init_ros_node(); }
        virtual bool setPwrs(double p0, double p1)override;
    protected:
        rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr pub_;
        rclcpp::Node& node_;
        void init_ros_node();
    };

    //----
    class SysRos: public Sys
    {
    public:
        using Sys::Sys;
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