#ifndef DEF_Lsys_Fperiod
#define DEF_Lsys_Fperiod

#include <Arduino.h>

class Lsys_Fperiod
{
    // Attributs publics
    public:
        /*! @brief  Horloge basculante sur une periode en ms.
            @see Lsys_Fimpulse.
            @param periodMs  Periode de temps de l'horloge / 2 en millisecondes */
        Lsys_Fperiod(uint32_t periodMs);

        /*! @brief  Signal d'horloge basculant sur demi-periode.
            @param periodMs  Periode de temps de basculement en millisecondes */
        bool clock();
        
        /*!  @brief  Reset de la periode. */
        void restart() {lastMillis = millis();}
        
        /*! @brief  Changement de la periode.
            @param periodMs nouvelle periode en millisecondes */
        void changePeriod(uint32_t periodMs) {Dlay = periodMs / 2;}

    private:
        unsigned long Dlay;
        unsigned long lastMillis;
        bool clk;

};
#endif