#pragma once
#include "emb/embLib.h"


namespace cart{
    using namespace ut;
    //-----------
    class UwbMng : public Cmd{
    public:
        UwbMng(){ init_cmd(); }
    protected:
        void init_cmd();
        bool init(CStrs& args);
        Sp<emb::Serial> p_serial_ = emb::Serial::create();
    };

    //-----------
    class CartApp : public Cmd{
    public:
        bool init();
    protected:
        void init_cmd();
        Sp<UwbMng> p_uwb_ = mkSp<UwbMng>();
    };
}
