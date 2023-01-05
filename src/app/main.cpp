#include "cart/cart.h"

using namespace cart;
using namespace ut;

int main(int argc, char ** argv)
{
    string s(argv[0]);
    log_i("--- run : "+s);
    log_i("cur_dir:"+sys::pwd());
    bool ok = true;
    
    CartApp app; 
    ok &= app.init();
    if(ok)
        ok &= app.run(argc, argv);
    if(ok) log_i("  OK, done!");
    else log_e("Failed");
    return ok?0:1;
}
