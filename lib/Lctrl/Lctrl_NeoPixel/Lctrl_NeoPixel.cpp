#include "Lctrl_NeoPixel.h"


Lctrl_NeoPixel::Lctrl_NeoPixel() :
    Adafruit_NeoPixel(),
    m_autoShow(false)
    {}

Lctrl_NeoPixel::Lctrl_NeoPixel(uint16_t NumberOfPixels, uint8_t Pin, neoPixelType TypeOfPixel, bool autoUpdate) :
    Adafruit_NeoPixel(NumberOfPixels, Pin, TypeOfPixel),
    m_autoShow(autoUpdate)
    {}


/*!
 * @param aDrawFromBottom - false: Bar is top down, i.e. it starts at the highest pixel index
 */
void Lctrl_NeoPixel::drawBar(uint16_t aBarLength, uint32_t aColor, bool aDrawFromBottom, uint8_t wait)
{
    for (uint16_t i = 0; i < numLEDs; i++)
    {
        bool tDrawPixel;
        if (aDrawFromBottom) {
            tDrawPixel = (i < aBarLength);
        } else {
            tDrawPixel = (i >= (numLEDs - aBarLength));
        }
        if (tDrawPixel) {
            setPixelColor(i, aColor);
        } else {
            // Clear pixel
            setPixelColor(i, 0, 0, 0);
        }
        updateStrip(wait);
    }
}

/*!
 * @brief Remplace le strip entier d'une couleur
 * @param aColor color ex : strip.color(r,g,b)
 * @param wait delay (ms)
 */
void Lctrl_NeoPixel::colorWipe(uint32_t aColor, uint8_t wait)
{
    for(uint16_t i = 0 ; i < numPixels() ; i++)
    {
        setPixelColor(i, aColor);
        updateStrip(wait);
    }
}

void Lctrl_NeoPixel::fillWithRainbow(uint8_t aWheelStartPos, uint8_t wait, bool aStartAtTop)
{
    uint16_t tWheelIndexHighResolution = aWheelStartPos << 8; // upper byte is the integer part used for Wheel(), lower byte is the fractional part
    uint16_t tWheelIndexHighResolutionDelta = 0x10000 / numLEDs;
    for (uint16_t i = 0; i < numLEDs; i++)
    {
        if (aStartAtTop)
        {
            setPixelColor(numLEDs - i, Wheel(tWheelIndexHighResolution >> 8));
        } else {
            setPixelColor(i, Wheel(tWheelIndexHighResolution >> 8));
        }
        tWheelIndexHighResolution += tWheelIndexHighResolutionDelta;
        updateStrip(wait);
    }
}

/*!
 *@brief Fonction qui ajoute un pixel avec un scrolling rainbow
 *@param DelayToPlace delais entre chaque positionnement
 *@param scrollSpeed delais du scrolling
 */
void Lctrl_NeoPixel::fillWithRainbowDefil(uint16_t DelayToPlace, uint8_t scrollSpeed)
{
    for (size_t i = numPixels(); i > 0 ; i--)
    {
        uint16_t cycleTime = (i * scrollSpeed);
        rainbowDefil(i, scrollSpeed);
        if (cycleTime < DelayToPlace) delay(DelayToPlace - cycleTime);
    }
    
}

/*!
 *@brief Fonction qui donne qui défile une led avec effet rainbow
 *@param posFinale led qui restera allumée à la fin du scrolling
 *@param wait delais du scrolling
 */
void Lctrl_NeoPixel::rainbowDefil(uint16_t posFinale, uint8_t wait)
{
    if(posFinale == 0) posFinale = this->numPixels();
    for(uint16_t pos = 0 ; pos < posFinale ; pos++)
    {
      unsigned char WheelPos =  (pos * 255) / numPixels(); //Calcul une valeur de 0 à 255 en fonction de la position
      setPixelColor(pos, Wheel(WheelPos)); // allume la bonne couleur de led en f(x) de la position
      setPixelColor(pos-1, 0); // on éteint la led précedente (pour l'effet de scroll) 
      show(); // actualise les leds
      delay(wait); // temps de passage d'une led à l'autre
    }
}


void Lctrl_NeoPixel::fadeBrightness(uint8_t wait)
{
    for (uint8_t b = getBrightness() ; b > 0 ; b--)
    {
        setBrightness(b);
        show();
        delay(wait);
    }
    clear();
    show();
}


// Entrer une valeur de 0 à 255 pour obtenir une couleur correspondante.
// Transitions des couleurs 0 = red -> green -> blue -> back to red = 255.
uint32_t Lctrl_NeoPixel::Wheel(uint8_t aWheelPos) {
    aWheelPos = 255 - aWheelPos;
    if (aWheelPos < 85)
    {
        return Color(255 - (aWheelPos * 3), 0, aWheelPos * 3);
    } else if (aWheelPos < 170) {
        aWheelPos -= 85;
        return Color(0, aWheelPos * 3, 255 - (aWheelPos * 3));
    } else {
        aWheelPos -= 170;
        return Color(aWheelPos * 3, 255 - (aWheelPos * 3), 0);
    }
}


void Lctrl_NeoPixel::updateStrip(uint16_t wait)
{
    if (m_autoShow) show();
    if (wait) delay(wait);
}