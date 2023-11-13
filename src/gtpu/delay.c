#include "delay.h"

int Tdelay_lvl = 0;

int get_Tdelay_lvl(){
    return Tdelay_lvl;
}

void set_Tdelay_lvl(int val){
    Tdelay_lvl = val;
}