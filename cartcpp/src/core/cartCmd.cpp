#include "cart/cart.h"

using namespace cart;

void CartCmd::init_cmd()
{
    assert(p_uwb_!=nullptr);
    Cmd::add("uwb", p_uwb_);
    Cmd::add("emb", mkSp<emb::EmbCmd>());
}

//-----
bool CartCmd::init()
{
    log_i("CartCmd Init...");
    init_cmd();
    log_i("CartCmd Init done");
    return true;
}
