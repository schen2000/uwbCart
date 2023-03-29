#pragma once
#include "emb/embLib.h"


namespace cart{
    using namespace ut;
    //-------
    namespace uwb
    {
        struct Frm
        {
            char        header[6]{'C','m','d','M',':','4'};
            uint8_t     len=0;
            uint32_t    timer=0;
            uint16_t    tagid=0;
            uint16_t    ancid=0;
            uint8_t     seq=0;
            uint8_t     mask=0;
            int32_t     rawrange[8];
            uint8_t     Kalman_enable = 0;
            int32_t     Kalman_range[8];
            uint8_t     pos_enable=0;
            uint8_t     pos_dimen=0; // 1:2d, 2:3d
            uint8_t     pos_ancmask=0;
            uint8_t     Coord_valid=0;
            struct{
                float x=0;
                float y=0;
                float z=0;
            }pos_loc;
            uint8_t     check_xor=0;
            uint8_t     foot=0; // "\r\n"

            string str()const;
        };
        //-----------
        class UwbMng : public Cmd{
        public:
            UwbMng(){ init_cmd(); }
        protected:
            struct Cntx{
                bool isOn = false;
            }; Cntx cntx_;

            void init_cmd();
            bool init(CStrs& args);
            bool run_at(CStrs& args);
            bool run_frms(CStrs& args);
            Sp<emb::Serial> p_serial_ = emb::Serial::create();
        };
    }
 
    //-----------
    class CartCmd : public Cmd{
    public:
        bool init();
    protected:
        void init_cmd();
        Sp<uwb::UwbMng> p_uwb_ = mkSp<uwb::UwbMng>();
    };
   
}
