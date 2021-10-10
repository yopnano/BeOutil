#include "Lsys_Fimpulse.h"

// Constructeur
Lsys_Fimpulse::Lsys_Fimpulse(uint32_t periodMs)
:   Dlay(periodMs),
    lastMillis(millis())
{}

bool Lsys_Fimpulse::pulse()
{
    bool ft = millis() - lastMillis >= Dlay;

    if (ft) lastMillis += Dlay;

    return ft;
}