#pragma once
#include "emb/embLib.h"


namespace cart{
    using namespace ut;
    //-----------
    class CartApp : public Cmd{
    public:
        bool init();
    protected:
        void init_cmd();
    };
}
