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

   //     virtual Motors& getMotors()override
    //        { return motors_; }
   //     virtual UWBs& getUWBs()override
     //       { return uwbs_;  }

    protected:
        socket::Client clnt_;
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
    log_i("SysTcp init...");
    clnt_.connect(cfg_.sHost, cfg_.port);
    if(clnt_.isConnected())
    {
        log_i("SysTcp connection ok");
        return true;
    }
    log_e("SysTcp connection init failed.");
    return false;
}
