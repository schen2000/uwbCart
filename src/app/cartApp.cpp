#include "cart/cart.h"

using namespace cart;

void CartApp::init_cmd()
{

}

//-----
bool CartApp::init()
{
    log_i("CartApp Init...");
    init_cmd();
    log_i("CartApp Init done");
    return true;
}
