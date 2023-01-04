#include "vrp/vrpApp.h"
#include "arm/armLib.h"

using namespace vrp;

void VrpApp::init_cmd()
{
    Cmd::add("arm", mkSp<arm::ArmCmd>());
}

//-----
bool VrpApp::init()
{
    init_cmd();

    return true;
}
