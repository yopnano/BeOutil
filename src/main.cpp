#include "Global.cpp"

int tempo1s = 0;
int g7 = 0;
bool mem = 0;

void setup()
{
  Modsetup();
  moteur.pidMode(false);
  moteur.keepEnable(false);
  moteur.csgAuto(255); //150
}

void loop()
{  
  
  // fonction main des méthodes
  sys.main();
  ModMain();

// Test de moteur codeur
  
  //double vitesse = codeur.vitesseAbs() * 0.233;


  if (sys.ft1Hz()) tempo1s ++;


  if (g7 == 0)
  {
    tempo1s = 0;
    g7 = 1;
  }

  if (g7 == 1 && tempo1s >= 1)
  {
    tempo1s = 0;
    g7 = 2;
  }

  if (g7 == 2 && tempo1s >= 1)
  {
    tempo1s = 0;
    g7 = 0;
  }

  if (!moteur.running())
  {
    moteur.step(mem ? 5000 : -5000);
    mem = !mem;
  } 
}