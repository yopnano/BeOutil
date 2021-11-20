#include "LioAna.h"

/*! @brief  Mise à l'échelle analogique
    @param pin analog pin A0 par exemple
    @param LO_DEF borne inférieure valeur 0
    @param HI_LIM borne supérieure valeur 1023
    @param LO_LIM mesure inférieure valeur 0
    @param HI_LIM mesure supérieure valeur 100
    @param offset décalage de la valeur (0 par défaut)
*/
LioAnaIn::LioAnaIn(uint8_t pin, int LO_DEF, int HI_DEF, int LO_LIM, int HI_LIM, int offset)
:   m_pin (pin),
    m_LO_DEF(LO_DEF),
    m_HI_DEF(HI_DEF),
    m_LO_LIM(LO_LIM),
    m_HI_LIM(HI_LIM),
    m_offset(offset),
    m_val (0),
    m_def (false){}


// fonction privée mise à l'échelle
int LioAnaIn::scale(int val, int LO_LIM, int HI_LIM)
{
    //return( ((val / 1023.0) * (HI_LIM - LO_LIM) ) + LO_LIM );
    return (val - m_LO_DEF) * (HI_LIM - LO_LIM) / (m_HI_DEF - m_LO_DEF) + LO_LIM;
}

void LioAnaIn::setup()
{
    pinMode(m_pin, INPUT);
};

void LioAnaIn::main()
{
    int value = bruteVal();
    m_def = (value < m_LO_DEF || value > m_HI_DEF);
    m_val = scale(value, m_LO_LIM, m_HI_LIM);
}










LioAnaOut::LioAnaOut(uint8_t pin, uint8_t csgMin, uint8_t csgMax, uint8_t rampe)
:   m_pidMode(false),
    m_cmd(false),
    m_Km(false),
    m_csg(0),
    m_csgGlobale(0),
    m_csgActuelle(0),
    m_csgMin((csgMin > 0) ? csgMin : 0),
    m_csgMax((csgMax < 1023) ? csgMax : 1023),
    m_rampe(rampe),
    m_pin(pin){}

void LioAnaOut::setup(void)
{   //Setup des IOs
    
    //Verifie si la pin est PWM
    if (digitalPinToTimer(m_pin  ) == NOT_ON_TIMER) {Serial.print (F("LioAnaOut Warning : Pin cmd > ")); Serial.print (m_pin); Serial.println (F(" isn't PWM"));}
    else pinMode(m_pin, OUTPUT);
}

void LioAnaOut::main(void)
{   //Fonction principale
    m_csgGlobale = m_cmd * m_csg;

    //Mode PID
    m_Lrampe.disable(m_pidMode);

    //Si changement de consigne et front rampe => acceleration/deceleration
    m_Lrampe.main(m_csgGlobale, m_csgActuelle, m_rampe);

    //Gestions Km
    m_Km = (m_csgActuelle > m_csgMin && (m_cmd || m_Km));

    //Pilotage des sorties
    analogWrite(m_pin  , m_csgActuelle * m_Km);
}


void LioAnaOut::csg(uint8_t csg)
{
    //Borne la consigne entre 0 et 255
    m_csg = constrain(csg, m_csgMin, m_csgMax);
}



Lrampe::Lrampe() :
m_disabled(false),
m_csgAtteinte(false),
m_lastMillis(0)
{}

void Lrampe::main(uint8_t &csgGlobale, uint8_t &csgActuelle, uint16_t const& rampe)
{
    //Rampes désactivées
    if (m_disabled) csgActuelle = csgGlobale;

    m_csgAtteinte = csgActuelle == csgGlobale;

    //Gestion d'incrémentation
    if (m_csgAtteinte)
    {
        razTimer();
        return;
    }
    else
    {
        if (millis() - m_lastMillis >= rampe)
        {
            razTimer();
            csgActuelle += (csgGlobale > csgActuelle) ? 1 : -1;
        }
    }
}