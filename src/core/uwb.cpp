#include "cart/cart.h"

using namespace cart;

void UwbMng::init_cmd()
{
    Cmd::sHelp_ = "UWB device cmds, [init|st]";

    Cmd::add("st", mkSp<Cmd>("show status",
    [&](CStrs& args)->bool{ 
        return true;
    }));

    Cmd::add("init", mkSp<Cmd>("port=PORT baud=BAUD",
    [&](CStrs& args)->bool{ 
        return init(args);
    }));

    Cmd::add("at", mkSp<Cmd>("AT commands of UWB, ('at help')",
    [&](CStrs& args)->bool{ 
        return run_at(args);
    }));

}
//----
bool UwbMng::run_at(CStrs& args)
{
    if(!cntx_.isOn)
    {
        log_e("UWB device not init");
        return false;
    }
    else if(args.size()==0)
    {
        log_e("Empty at cmd provided");
        return false;
    }
    string scmd = args[0];
    
    assert(p_serial_!=nullptr);
    
    auto& srl = *p_serial_;
    srl.write(scmd +"\r\n");

    sys::sleep(1);

    string sln;
    if(!srl.readln(sln))
    {
        log_e("No reponse from device");
        return false;
    }    
    log_i(sln);

    return true;
}

//----

bool UwbMng::init(CStrs& args)
{
    log_i("UWB init...");

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
    
    //----
    // AT cmd getver
    auto& srl = *p_serial_;
    srl.write("getver\r\n");
    string sln;
    sys::sleep(1);
    if(!srl.readln(sln))
    {
        log_e("No reponse from device");
        return false;
    }
    log_i("AT cmd 'getver':");
    log_i(sln);

    //----
    cntx_.isOn = true;
    log_i("UWB init OK");
    return true;
}
