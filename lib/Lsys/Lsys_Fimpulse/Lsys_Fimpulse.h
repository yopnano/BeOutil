#ifndef DEF_Lsys_Fimpulse
#define DEF_Lsys_Fimpulse

#include <Arduino.h>

class Lsys_Fimpulse
{
    // Attributs publics
    public:
        /*! @brief Front sur une periode en ms.
            @see Lsys_Fperiod.
            @param periodMs  Periode de temps de pulsation en millisecondes */
        Lsys_Fimpulse(uint32_t periodMs);

        /*! @brief  Signal sur periode.
            @param periodMs  Periode de temps de basculement en millisecondes */
        bool pulse();
        
        /*!  @brief  Reset de la periode. */
        void restart() {lastMillis = millis();}
        
        /*! @brief  Changement de la periode.
            @param periodMs nouvelle periode en millisecondes */
        void changePeriod(uint32_t periodMs) {Dlay = periodMs;}

    private:
        unsigned int Dlay;
        unsigned long lastMillis;
};
#endif