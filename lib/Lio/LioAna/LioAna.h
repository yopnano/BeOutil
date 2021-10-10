#ifndef LioAna_h
#define LioAna_h

#include <Arduino.h>

class LioAnaIn
{

  public:
    LioAnaIn(uint8_t pin, int m_LO_DEF = 0, int m_HI_DEF = 1023, double LO_LIM = 0, double HI_LIM = 100, double offset = 0.0);

    void    setup(void);
    void    main(void);

    bool    def (void) const { return m_def; }
    double  val (void) const { return m_val; }

    int     bruteVal(void) const { return analogRead(m_pin); }

  private:
    uint8_t m_pin;

    int     m_LO_DEF;
    int     m_HI_DEF;

    double  m_LO_LIM;
    double  m_HI_LIM;
    double  m_offset;

    short   m_val;
    bool    m_def;
    
    double  scale(double val, double LO_LIM, double HI_LIM);
};


class Lrampe
{
private:
    void razTimer() {m_lastMillis = millis();}
    
    bool m_disabled;
    bool m_csgAtteinte;

    unsigned long m_lastMillis;

public:
    //Constructeur
    Lrampe();

    //Accesseurs
    //! @return True si consigne atteinte
    bool csgAtteinte(void) const {return m_csgAtteinte;}

    //Manipulateur
    //! @brief Désactivation rampes @param Boolean
    void disable(bool Disable) {m_disabled = Disable;}

    //Méthodes
    //! @brief Gestion de la consigne
    void main(uint8_t &csgGlobale, uint8_t &csgActuelle, uint16_t const& rampe);
};


class LioAnaOut
{
public:
  LioAnaOut(uint8_t pin, uint8_t csgMin = 0, uint8_t csgMax = 255, uint8_t rampe = 10);

  void    setup(void);
  void    main(void);
  void    pidMode(bool enable) {m_pidMode = enable;}

  void    cmd(bool enable) {m_cmd = enable;}
  bool    cmd(void) const {return m_cmd;}

  void    csg(uint8_t csg);
  uint8_t csg(void) const {return m_csg;}
  uint8_t csgActuelle(void) const {return m_csgActuelle;}

  void    rampe(uint8_t newVal) {m_rampe = newVal;}
  uint8_t rampe(void) const {return m_rampe;}

  void toggle(void) {m_cmd = !m_cmd;}

private:
  bool m_pidMode;
  bool m_cmd;
  bool m_Km;

  uint8_t m_csg;
  uint8_t m_csgGlobale, m_csgActuelle;
  uint8_t m_csgMin, m_csgMax;
  uint8_t m_rampe;
  uint8_t m_pin;
  
  Lrampe m_Lrampe;
};


#endif