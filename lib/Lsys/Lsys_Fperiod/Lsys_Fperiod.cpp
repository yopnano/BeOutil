#include "Lsys_Fperiod.h"

// Constructeur
Lsys_Fperiod::Lsys_Fperiod(uint32_t periodMs)
:   Dlay(periodMs / 2),
    lastMillis(millis()),
    clk(false){}

bool Lsys_Fperiod::clock()
{
    if (millis() - lastMillis >= Dlay)
    {
        lastMillis += Dlay;
        clk = !clk; // toggle clock
    }
    return clk;
}