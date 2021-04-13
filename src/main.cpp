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