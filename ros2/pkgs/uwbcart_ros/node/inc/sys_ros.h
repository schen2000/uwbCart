#include "cart/sys.h"

namespace cart{

    class UWBs_ros : public UWBs{
    public:

    };
    class Motors_ros : public Motors{
    public:
    };

    //----
    class SysRos: public Sys
    {
    public:
        using Sys::Sys;
        virtual bool init()override;
    //    virtual Motors& SysRos::getMotors()override{ return motors_; }
    //    virtual UWBs& SysRos::getUWBs()override{ return uwbs_; }

    protected:
        UWBs_ros    uwbs_;
        Motors_ros  motors_;
    };
}