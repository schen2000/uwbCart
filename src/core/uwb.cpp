#include "cart/cart.h"

using namespace cart;

void UwbMng::init_cmd()
{
    Cmd::sHelp_ = "uwb init|st";

    Cmd::add("st", mkSp<Cmd>("show status",
    [&](CStrs& args)->bool{ 
        return true;
    }));

    Cmd::add("init", mkSp<Cmd>("init port=PORT baud=BAUD",
    [&](CStrs& args)->bool{ 
        return init(args);
    }));
}
//----

bool UwbMng::init(CStrs& args)
{
    
    StrTbl kv; parseKV(args, kv);
    string s_port = lookup(kv, "port");
    string s_baud = lookup(kv, "baud");
    int baud=-1;
    if(!s2d(s_baud, baud))
    {
        log_e("baud incorrect");
        return false;
    }
    //----
    assert(p_serial_!=nullptr);
    if(!p_serial_->open(s_port, baud))
        return false;
    return true;
}
