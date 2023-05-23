#pragma once
#pragma once
#include "cart/sys.h"
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
        CartCmd(){ init_cmds(); }

    protected:
        Sp<Sys> p_sys_ = nullptr;
        void init_cmds();
        bool init(CStrs& args);
    };
   
}
