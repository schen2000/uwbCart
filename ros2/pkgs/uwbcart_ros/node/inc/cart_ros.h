/*
   Author: Sherman Chen
   Create Time: 2023-04-26
   Email: schen@simviu.com
   Copyright(c): Simviu Inc.
   Website: https://www.simviu.com
 */
 
#pragma once

#include "cart/cart.h"
#include "rclcpp/rclcpp.hpp"
#include "sys_ros.h"

#include "std_msgs/msg/string.hpp"

namespace cart{
    class CartNode : Cmd, public rclcpp::Node{
    public:
        CartNode();
        using Node::Node;
        //bool run();
    protected:
        void init_cmds();
        void timerCbk();
        rclcpp::TimerBase::SharedPtr timer_;
        rclcpp::Publisher<std_msgs::msg::String>::SharedPtr pub_log_;
        bool start_server();
        std::thread thd_server_;
    };
}
