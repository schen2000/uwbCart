#include "cart/sys.h"
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

namespace cart{

    class UWBs_ros : public UWBs{
    public:

    };
    class Motors_ros : public Motors{
    public:
    };

    //----
    class SysRos: public Sys
    {
    public:
        SysRos(rclcpp::Node& n):node_(n)
        {  init_ros(); }
        using Sys::Sys;
        virtual bool init()override;
    //    virtual Motors& SysRos::getMotors()override{ return motors_; }
    //    virtual UWBs& SysRos::getUWBs()override{ return uwbs_; }

    protected:
        rclcpp::Node& node_;
        void init_ros();

        UWBs_ros    uwbs_;
        Motors_ros  motors_;

        rclcpp::Publisher<std_msgs::msg::String>::SharedPtr pub_log_;

    };
}