 #include "cart/cart.h"

using namespace cart;
 
void Motors::init_cmds()
{
    sHelp_ = "dual motors commands";

    //----
    add("pwrs", "P0 P1 (set power left/right, -1.0 to 1.0)", 
        [&](CStrs& args)->bool{
            float p0=0,p1=0;
            bool ok = s2d(args[0], p0) && s2d(args[1], p1);
            if(!ok){ log_e("failed to get P0 P1"); return false; }
            return this->setPwrs(p0, p1);
        });
}
