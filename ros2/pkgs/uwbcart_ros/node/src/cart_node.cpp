#include "cart_ros.h"

using namespace cart;
CartNode::CartNode():Node("cart_node")
{
    init_cmds();

    //----
    pub_msg_ = this->create_publisher<std_msgs::msg::String>("hello_topic", 10);
    timer_ = this->create_wall_timer(
    500ms, std::bind(&CartNode::timerCbk, this));
}
//----
void CartNode::timerCbk()
{
    //---- test msg
    static int cnt_ = 0;
    auto message = std_msgs::msg::String();
    message.data = "Hello, world! " + std::to_string(cnt_++);
    pub_msg_->publish(message);    
}

//-----
void CartNode::init_cmds()
{

}



//-----
int main(int argc, char ** argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<CartNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();
}
