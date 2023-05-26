#include "cart_ros.h"
#include "sys_ros.h"

using namespace cart;

namespace{
    struct LCfg{
        int server_port = 1666;
    }; LCfg lc_;
}

//----
CartNode::CartNode():Node("cart_node")
{
    RCLCPP_INFO_ONCE(this->get_logger(), "CartNode construct...");

    init_cmds();

    //--- log msg publish
    pub_log_ = this->create_publisher<std_msgs::msg::String>("/cart/log", 10);
    utlog::setCallbk([&](CStr& s){
        auto msg = std_msgs::msg::String();
        msg.data = s;
        pub_log_->publish(msg);    
    });
    //----
    
    timer_ = this->create_wall_timer(
    500ms, std::bind(&CartNode::timerCbk, this));
    
    //--- start cmd server
    start_server();

    //--- done
    RCLCPP_INFO_ONCE(this->get_logger(), "CartNode construct done.");
}
//----
void CartNode::timerCbk()
{
    //---- test msg
    static int cnt_ = 0;
}

//-----
void CartNode::init_cmds()
{
    sHelp_ = "(cart node cmds)";
    Cmd::add("sys", mkSp<SysRos>(*this));
}
//----
bool CartNode::start_server()
{
    thd_server_ = std::thread([&]{
        int port = lc_.server_port;
        log_d("CartNode::start_server(), port="+to_string(port));
        Cmd::run_server(port);
    });
    thd_server_.detach();
    return true;
}


//-----
int main(int argc, char ** argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<CartNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();
}
