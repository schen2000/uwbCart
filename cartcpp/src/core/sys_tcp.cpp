#include "cart/sys.h"

using namespace cart;

namespace{
    //---
    class UWBsTcp : public UWBs{
    public:
    };
    //----
    class MotorsTcp : public Motors{
    public:
    };
    //----
    class SysTcp : public Sys{
    public:
        struct Cfg{
            string sHost;
            int port = -1;
        }; Cfg cfg_;
        virtual bool init()override;

        virtual Motors& getMotors()override
            { return motors_; }
        virtual UWBs& getUWBs()override
            { return uwbs_;  }

    protected:
        MotorsTcp motors_;
        UWBsTcp uwbs_;
    };
}


// factory
Sp<Sys> Sys::create_client(const string& sHost, int port)
{
    auto p = mkSp<SysTcp>();
    auto& c = p->cfg_;
    c.sHost = sHost;
    c.port = port;
    return p;
}

//-----
bool SysTcp::init()
{
    
    return true;
}
