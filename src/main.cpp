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
// Hauptschleife
// ****************************************************************************************************************************
void loop() { 

  // Regenbogen();
  // Logo();
   
  // HG_Farbe (0, 0, 0);
  // Logo (50,0,0);
  HG_LR (40,0,0,0,0,40,'L',2);                              // Startwert, Endwert nach RGB, Richtung, Schrittgröße 
  
                                                            // Rot-Start,Rot-Ende, Grün-Start,Grün-Ende, Blau-Start,BlauEnde, Richtung, SG 
                                                            // HG_LR (40,0,0,0,0,40,'L',2);  1 Farbe  / Dunkel
                                                            // HG_LR (80,0,0,0,0,80,'L',4);  1 Farbe  / hell
                                                            // HG_LR (40,0,0,0,0,40,'L',4);  2 Farben / Dunkel  
                                                            // HG_LR (80,0,40,0,0,80,'L',4); 3 Farben / hell                
  HG_LR (0,36,0,0,36,0,'K',6);                              // Startwert, Endwert nach RGB, Richtung, Schrittgröße
                                                            //  HG_LR (0,36,0,0,36,0,'K',6);

 
  FastLED.show();
  delay(100);
}