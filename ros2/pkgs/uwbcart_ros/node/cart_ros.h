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
#include "std_msgs/msg/string.hpp"

namespace cart{
    class CartNode : Cmd{
    public:
        bool run();
    protected:

    };
}
