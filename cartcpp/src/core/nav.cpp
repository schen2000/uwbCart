#include "cart/cart.h"
#include "json/json.h"

using namespace cart;
using namespace uwb;

//----
bool NavMng::Cfg::load(const string& sf)
{
   
    ifstream ifs(sf);
    if(!ifs)
    {
        log_ef(sf);
        return false;
    }
    bool ok = true;
    /*
    //----
    try{
        Json::Reader rdr;
        Json::Value jd;
        rdr.parse(ifs, jd);
        auto& jtop = jd["nav"];
        //--- cam
        sCam = jtop["cam"].asString();
        //--- debug
        {
            auto& j = jtop["debug"];
            dbg.frm_save = j["frm_save"].asInt();
        }
        enVis = jtop["enVis"].asBool();
        //---- yoke
        auto& jy = jtop["yoke"];
        ok &= s2v(jy["t_mh"].asString(), yoke.t_mh);
        ok &= s2v(jy["t_hg"].asString(), yoke.t_hg);

    }
    catch(exception& e)
    {
        log_e("exception caught:"+string(e.what()));
        return false;
    }
    */
    //---
    if(!ok)
        log_e(" Vision::cfg::load() json parsing failed");
    return ok;
}
