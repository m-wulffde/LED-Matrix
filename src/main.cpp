// -----------------------------------------------
// Projekt: LED Matrix mit Tischtennisbällen groß
// -----------------------------------------------
// Verion 0.1.1  Einfache Funktion von Links 
// Verion 0.1.2  Einfache Funktion in die Mitte

#include <Arduino.h>
#include <FastLED.h>
#include <Declaration.c>
#include <Background.c>


void setup() {
  Serial.begin(115200);
  Serial.println("Start");
  FastLED.addLeds <NEOPIXEL, DATA_PIN> (LEDs, NUM_LEDS)   // FastLED die Definitionen mitteilen
    .setCorrection(TypicalLEDStrip)                       // Regenbogen
    .setDither(Helligkeit < 255);                         // Regenbogen
  FastLED.setBrightness(Helligkeit);                      // Stellen Sie die Master-Helligkeitsregelung ein
}

// Hintergrund Farbe setzen und anzeigen
void HG_Farbe ( short R, short G, short B ) {
  for(int i = 0; i < NUM_LEDS; i++) {
    LEDs[i] = CRGB(R,G,B);
  }
  // FastLED.show();
}



// ****************************************************************************************************************************
// Regenbogen - Hintergrund
// Diese Funktion zeichnet Regenbogen mit einem sich ständig ändernden,
// stark variierender Parametersatz.
void Regenbogen() 
{
  static uint16_t PseudoZeit = 0;
  static uint16_t LetzteMSec = 0;
  static uint16_t Farbton16 = 0;
 
  uint8_t sat8 = beatsin88( 87, 220, 250);
  uint8_t brightdepth = beatsin88( 341, 96, 224);
  uint16_t brightnessthetainc16 = beatsin88( 203, (25 * 256), (40 * 256));
  uint8_t msmultiplier = beatsin88(147, 23, 60);

  uint16_t hue16 = Farbton16;
  uint16_t hueinc16 = beatsin88(113, 1, 3000);
  
  uint16_t ms = millis();
  uint16_t deltams = ms - LetzteMSec;
  LetzteMSec  = ms;
  PseudoZeit += deltams * msmultiplier;
  Farbton16  += deltams * beatsin88( 400, 5,9);
  uint16_t brightnesstheta16 = PseudoZeit;
  
  for( uint16_t i = 0 ; i < NUM_LEDS; i++) {
    hue16 += hueinc16;
    uint8_t hue8 = hue16 / 256;

    brightnesstheta16  += brightnessthetainc16;
    uint16_t b16 = sin16( brightnesstheta16  ) + 32768;

    uint16_t bri16 = (uint32_t)((uint32_t)b16 * (uint32_t)b16) / 65536;
    uint8_t bri8 = (uint32_t)(((uint32_t)bri16) * brightdepth) / 65536;
    bri8 += (255 - brightdepth);
    
    CRGB NeueFarbe = CHSV( hue8, sat8, bri8);
    
    uint16_t LED_Nr = i;
    LED_Nr = (NUM_LEDS-1) - LED_Nr;
    
    nblend( LEDs[LED_Nr], NeueFarbe, 64);
  }
}

// ****************************************************************************************************************************
// Zeichen anzeigen
// Logo M W 
const int Digits [2] [11] =
{
  {6,5,12,11,21,22,30,29,39,40,50},   
  {14,15,25,26,34,33,43,44,52,51,57},
};

void Logo(){

  CRGB LED[2];
  LED[1] = LEDs[54];
  // LED[2] = LEDs[10];

  HG_Farbe (15, 0, 15);
  
  for (int i = 0 ; i < 11 ; i++) {
    LEDs[(Digits[0][i])] = LED[1];
   // LEDs[(Digits[1][i])] = LED[2];
  }
  //LEDs[6] = CRGB(200,0,200);
}

// ****************************************************************************************************************************
// Hauptschleife
// ****************************************************************************************************************************
void loop() { 
/*
for(int i = 0; i < NUM_LEDS; i++) {
    LEDs[i] = CRGB(0,0,100);
    FastLED.show();
    delay(1);
  }

for(int i = 0; i < NUM_LEDS; i++) {
    LEDs[i] = CRGB(100,0,0);
    FastLED.show();
    delay(1);
  }
*/
  // Regenbogen();
  // Logo();
   
  // HG_Farbe (0, 0, 0);
  // HG_LR (40,0,0,0,0,40,'L',2);                           // Startwert, Endwert nach RGB, Richtung, Schrittgröße 
  
                                                            // Rot-Start,Rot-Ende, Grün-Start,Grün-Ende, Blau-Start,BlauEnde, Richtung, SG 
                                                            // HG_LR (40,0,0,0,0,40,'L',2);  1 Farbe  / Dunkel
                                                            // HG_LR (80,0,0,0,0,80,'L',4);  1 Farbe  / hell
                                                            // HG_LR (40,0,0,0,0,40,'L',4);  2 Farben / Dunkel  
                                                            // HG_LR (80,0,40,0,0,80,'L',4); 3 Farben / hell                
  HG_LR (0,36,0,0,36,0,'K',6);                              // Startwert, Endwert nach RGB, Richtung, Schrittgröße
                                                            //  HG_LR (0,36,0,0,36,0,'K',6);

 
  // FastLED.show();
  // delay(10000);
}