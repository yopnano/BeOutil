#include "Global.h"
//Instances
ledTor led(LED_BUILTIN);


// Lctrl_MoteurPWM moteur[] 
// {    
//     //Lctrl_MoteurPWM (11, 10, 40, 7),
//     //Lctrl_MoteurPWM (9, 5, 40, 10)
// };

//Lctrl_Servo moteur(8, Lctrl_Servo::Mode_vitessePos, 50, 15, 170);
Lctrl_MoteurPWM moteur(10, 11, Lctrl_MoteurPWM::Mode_auto, 40, 255, 10);
//Lctrl_DriveS500 moteur(2,3,4,5,6,Lctrl_DriveS500::Mode_auto,40);
//Lctrl_Brushless_2sens moteur (10, Lctrl_Brushless_1sens::Mode_auto, 70, 1000, 1500, 2000);

Lcom_RX_433MHz rxModule (2);

void Modsetup(void)
{
    Serial.begin(9600);
    PrintProject();
    //for (auto &&iMoteur : moteur) iMoteur.setup();
    moteur.setup();
    rxModule.setup();
}

void ModMain(void)
{
    //for (auto &&iMoteur : moteur) iMoteur.main();
    moteur.main();
    rxModule.main();
}