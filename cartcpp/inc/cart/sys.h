#pragma once
#include "ut/cutil.h"

namespace cart{
    using namespace ut;

    //---
    class UWBs{
    public:
    };
    //---
    class Motors{
    public:
    };
    //---- hardware abstraction
    class Sys{
    public:
        struct Cfg{

        }; Cfg cfg_;
        //factor
        static Sp<Sys> create_client(const string& sHost, int port);
        //---
        virtual bool init()=0;
        virtual Motors& getMotors()=0;
        virtual UWBs& getUWBs()=0;
    };

}