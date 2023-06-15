#include "cart/cart.h"
#include "cart/uwb_JL.h"

using namespace cart;

void CartCmd::init_cmds()
{
    //--- experiment JiuLing UWB-S series
    //Cmd::add("uwb_JL", mkSp<JL::UwbMng>());
    //---
    //Cmd::add("emb", mkSp<emb::EmbCmd>());
    add("init", "sys=[tcp|hw] [host=HOST port=PORT]", 
    [&](CStrs& args)->bool
        {  return this->init(args); });

}

//-----
bool CartCmd::init(CStrs& args)
{
    bool ok = true;
    log_i("CartCmd Init...");
    KeyVals kvs(args);

    //--- init sys (TCP)
    string sSys = kvs["sys"];
    if(sSys=="tcp")
    {
        string sHost = kvs["host"];
        int port=-1; kvs.get("port", port);
        p_sys_ = Sys::create_client(sHost, port);
        ok &= p_sys_->init();
    }
    //---- init sys (HW)
    //else if(sSys=="hw")

    else{
        log_e("Unkown sys type:'"+sSys+"'");
        return false;
    }
    
    Cmd::add("sys", p_sys_);
    //---
    if(ok) log_i("CartCmd Init done");
    else log_e("CartCmd init failed");
    return ok;
}
