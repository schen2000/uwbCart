#include "cart/cart.h"

using namespace cart;

void CartApp::init_cmd()
{
    assert(p_uwb_!=nullptr);
    Cmd::add("uwb", p_uwb_);
    Cmd::add("io", mkSp<emb::IO_Cmd>());
}

//-----
bool CartApp::init()
{
    log_i("CartApp Init...");
    init_cmd();
    log_i("CartApp Init done");
    return true;
}
