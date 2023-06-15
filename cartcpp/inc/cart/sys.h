#pragma once
#include "ut/cutil.h"

namespace cart{
    using namespace ut;

    //---
    class UWBs : public Cmd{
    public:
        using Cmd::Cmd;
    };
    //---
    class Motors : public Cmd{
    public:
        Motors(){ init_cmds(); }
        // power -1 to 1
        virtual bool setPwrs(double p0, double p1){ return false; };
    protected:
        void init_cmds();
    };
    //---- hardware abstraction
    class Sys : public Cmd{
    public:
        using Cmd::Cmd;
        Sys(){ init_cmds(); }
        struct Cfg{

        }; Cfg cfg_;
        //factor
        static Sp<Sys> create_client(const string& sHost, int port);
        //---
        virtual bool init()=0;

    protected:
        Sp<UWBs>    pUWBs_ = nullptr;
        Sp<Motors>  pMotors_ = nullptr;

        void init_cmds();
        bool init(CStrs& args);
    };

}