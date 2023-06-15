#include "cart/sys.h"

using namespace cart;
//---
void Sys::init_cmds()
{
    add("init", "(init system)", 
    [&](CStrs& args)->bool
        {  return this->init(); });
}
//----
