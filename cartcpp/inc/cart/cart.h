#pragma once
#pragma once
#include "cart/base.h"
#include "cart/uwb_s.h"
#include "emb/embLib.h"

namespace cart{
    using namespace ut;
    
    //------
    class NavMng{
    public:
        struct Cfg{
            struct Anchr{ int id=-1; };
            bool load(const string& sf);
        }; Cfg cfg_;
        bool init();
        struct Data{
        }; 
    protected:
        Data data_;
        
        Sp<emb::UWB> p_uwb_ = nullptr;

    };
    //------
    namespace drive{
        
    }
 
    //-----------
    class CartCmd : public Cmd{
    public:
        bool init();
    protected:
        void init_cmd();
        Sp<uwb::UwbMng> p_uwb_ = mkSp<uwb::UwbMng>();
    };
   
}
