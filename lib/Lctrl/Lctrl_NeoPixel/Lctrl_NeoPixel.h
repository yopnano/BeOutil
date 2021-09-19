#ifndef Lctrl_NeoPixel_h
#define Lctrl_NeoPixel_h

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

class Lctrl_NeoPixel: public Adafruit_NeoPixel
{
public:
    Lctrl_NeoPixel();
    Lctrl_NeoPixel(uint16_t NumberOfPixels, uint8_t Pin, neoPixelType TypeOfPixel, bool autoUpdate = true);
    
    void autoUpdate(bool enable) {m_autoShow = enable;}

    void drawBar(uint16_t aBarLength, uint32_t aColor, bool aDrawFromBottom = true, uint8_t wait = 0);
    void colorWipe(uint32_t aColor, uint8_t wait = 0);
    void fillWithRainbow(uint8_t aWheelStartPos, uint8_t wait = 0, bool aStartAtTop = false);
    void fillWithRainbowDefil(uint16_t DelayToPlace = 1000, uint8_t scrollSpeed = 50);
    void rainbowDefil(uint16_t posFinale = 0, uint8_t wait = 50);
    
    void fadeBrightness(uint8_t wait = 10);

    //Static functions
    static uint32_t Wheel(uint8_t aWheelPos);
protected:
    void updateStrip(uint16_t wait);
    bool m_autoShow;
};

#endif