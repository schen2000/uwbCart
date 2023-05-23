#include "cart/cart.h"

using namespace cart;
using namespace uwbs;

namespace{
    struct LC{
        bool en_init_testCmd = false;
    }; LC lc_;
}


//-----
string Frm::str()const
{
    stringstream s;
    s << "{";
    s << "len:" << (int)len;
    s << ", timer:" << (int)timer;
    s << ", tagid:" << (int)tagid;
    s << ", ancid:" << (int)ancid;
    s << ", seq:" << (int)seq;
    s << ", \nrawrang:[";
    
    int i=0;
    for(auto& r : rawrange)
    {
        if(i!=0) s << ", ";
        s << r;
        i++;
    }
    s << "]\n";
    s << "}";        
    return s.str();

}

//----

void UwbMng::init_cmd()
{
    Cmd::sHelp_ = "UWB device cmds";

    Cmd::add("frms", mkSp<Cmd>("(read frms)",
    [&](CStrs& args)->bool{ 
        run_frms(args);
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

    //sys::sleep(1);

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
    if(lc_.en_init_testCmd)
    {
        auto& srl = *p_serial_;
        srl.write("getver\r\n");
        string sln;
        //sys::sleep(1);
        if(!srl.readln(sln))
        {
            log_e("No reponse from device");
            return false;
        }
        log_i("AT cmd 'getver':");
        log_i(sln);
    }

    //----
    cntx_.isOn = true;
    log_i("UWB init OK");
    return true;
}

//----
bool UwbMng::run_frms(CStrs& args)
{
    assert(p_serial_!=nullptr);
    auto& srl = *p_serial_;
    int i=0;
    while(1)
    {
        Frm frm;
        auto p = reinterpret_cast<uint8_t*>(&frm);
        Buf b(p, sizeof(Frm));
        srl.readFrm("CmdM:4", b);
        log_i("Frm:" + to_string(i));
        log_i(frm.str());
        log_i("Frm end\n");
        i++;
    }
    return true;
}

