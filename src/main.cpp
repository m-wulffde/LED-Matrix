// -----------------------------------------------
// Projekt: LED Matrix mit Tischtennisbällen groß
// -----------------------------------------------
// Verion 0.1.1  Einfache Funktion von Links 

#include <Arduino.h>
#include <FastLED.h>

#define DATA_PIN 2                            // 1  *** Datenpin an dem der Strip hängt
#define NUM_LEDS 290                          // 61 *** Anzahl der LED's
#define Helligkeit 100                        // Regenbogen Helligkeit, max: 255
#define Spalten 39                            // Spalten Anzahl
#define SpaltenLED 10                         // LED Anzahl pro Spalte
CRGB LEDs[NUM_LEDS];                          // Das LED-Array
short LEDMatrixL [Spalten] [SpaltenLED] = {   // LED-Matrix von links
  {  1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
  {  0,  2, -1, -1, -1, -1, -1, -1, -1, -1},
  {  4,  6,  8, -1, -1, -1, -1, -1, -1, -1},
  {  3,  5,  7,  9, -1, -1, -1, -1, -1, -1},
  { 11, 13, 15, 17, 19, -1, -1, -1, -1, -1},
  { 10, 12, 14, 16, 18, 20, -1, -1, -1, -1},
  { 22, 24, 26, 28, 30, 32, 34, -1, -1, -1},
  { 21, 23, 25, 27, 29, 31, 33, 35, -1, -1},
  { 37, 39, 41, 43, 45, 47, 49, 51, 53, -1},
  { 36, 38, 40, 42, 44, 46, 48, 50, 52, 54},
  { 56, 58, 60, 62, 64, 66, 68, 70, 72, -1},
  { 55, 57, 59, 61, 63, 65, 67, 69, 71, 73},
  { 75, 77, 79, 81, 83, 85, 87, 89, 91, -1},
  { 74, 76, 78, 80, 82, 84, 86, 88, 90, 92},
  { 94, 96, 98,100,102,104,106,108,110, -1},
  { 93, 95, 97, 99,101,103,105,107,109,111},
  {113,115,117,119,121,123,125,127,129, -1},
  {112,114,116,118,120,122,124,126,128,130},
  {132,134,136,138,140,142,144,146,148, -1},
  {131,133,135,137,139,141,143,145,147,149},
  {151,153,155,157,159,161,163,165,167, -1},
  {150,152,154,156,158,160,162,164,166,168},
  {170,172,174,176,178,180,182,184,186, -1},
  {169,171,173,175,177,179,181,183,185,187},
  {189,191,193,195,197,199,201,203,205, -1},
  {188,190,192,194,196,198,200,202,204,206},
  {208,210,212,214,216,218,220,222,224, -1},
  {207,209,211,213,215,217,219,221,223,225},
  {227,229,231,233,235,237,239,241,243, -1},
  {226,228,230,232,234,236,238,240,242,244},
  {245,247,249,251,253,255,257,259,261, -1},
  {246,248,250,252,254,256,258,260, -1, -1},
  {262,264,266,268,270,272,274, -1, -1, -1},
  {263,265,267,269,271,273, -1, -1, -1, -1},
  {275,277,279,281,283, -1, -1, -1, -1, -1},
  {276,278,280,282, -1, -1, -1, -1, -1, -1},
  {284,286,288, -1, -1, -1, -1, -1, -1, -1},
  {285,287, -1, -1, -1, -1, -1, -1, -1, -1},
  {289, -1, -1, -1, -1, -1, -1, -1, -1, -1}
};

#define Kreise 5                              // Kreise Anzahl
#define KreiseLED 24                          // LED Anzahl pro Kreise 
short LEDMatrixK [Kreise] [KreiseLED] = {     // LED-Matrix nach Innen
  { 0, 1, 2, 8, 9,18,27,36,45,54,53,59,58,60,56,55,47,46,37,28,19,10, 3, 4},
  { 6, 7,16,17,26,35,44,52,51,57,49,48,38,29,20,11,12, 5,-1,-1,-1,-1,-1,-1},
  {14,15,25,34,43,42,50,40,39,30,21,13,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {23,24,33,41,31,22,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {32,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1}
};



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
// Hintergrund von links nach rechts einmal ausgeben
void HG_LR (short Rstart, short Rende, short Gstart, short Gende, short Bstart, short Bende, char Richtung, short SG ) {
  short Rot = Rstart;
  short Gruen = Gstart;
  short Blau = Bstart;
  boolean Rb = false;
  boolean Gb = false;
  boolean Bb = false;
  short SK = 0;
  short AnzLED =0;
  
  if (Rstart > Rende) Rb = true;                       // Startwert hoch oder runter zählen
  if (Gstart > Gende) Gb = true;                       // Startwert hoch oder runter zählen
  if (Bstart > Bende) Bb = true;                       // Startwert hoch oder runter zählen

  if (Richtung == 'L') {                               // Von Links nach Rechts Verschieben
    SK = Spalten;
    AnzLED = SpaltenLED;    
  }
  if (Richtung == 'K') {                               // Von Aussen nach Innen Verschieben
    SK = Kreise;
    AnzLED = KreiseLED;
  }

  for(int V = 0; V < 40; V++){                         // Verschiebungen
    for(int i = 0; i < SK; i++){                       // Spalte / Kreise
                                                       // Farbberechnung
        if (Rstart != Rende ) {                        // Rot verändern ?
          if (Rb) {
            Rot -= SG;
            if (Rot == Rende or Rot == Rstart) {
              Rb = false;
            }
          } else {
            Rot += SG;
            if (Rot == Rende or Rot == Rstart) {
              Rb = true;
            }
          }
        } 
        if (Gstart != Gende ) {                        // Grün verändern ?
          if (Gb) {
            Gruen -= SG;
            if (Gruen == Gende or Gruen == Gstart) {
              Gb = false;
            }
          } else {
            Gruen += SG;
            if (Gruen == Gende or Gruen == Gstart) {
              Gb = true;
            }
          }
        } 
        if (Bstart != Bende ) {                        // Blau verändern ?
          if (Bb) {
            Blau -= SG;
            if (Blau == Bende or Blau == Bstart) {
              Bb = false;
            }
          } else {
            Blau += SG; 
            if (Blau == Bende or Blau == Bstart) {
              Bb = true;
            }
          }
        } 
      for(int j = 0; j < AnzLED; j++){                    // LED's
        if (Richtung == 'L') {    
          LEDs[LEDMatrixL[i][j]] = CRGB(Rot,Gruen,Blau);  // einzelne LED setzen
        }
        if (Richtung == 'K') {    
          LEDs[LEDMatrixK[i][j]] = CRGB(Rot,Gruen,Blau);  // einzelne LED setzen
        }
        FastLED.show();
        delay(1);
      }
      // FastLED.show();
      // delay(2);
    }
    // FastLED.show();
    // delay(100);
  }
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
  Regenbogen();
  // Logo();
   
  // HG_Farbe (0, 0, 0);
  HG_LR (40,0,0,0,0,40,'L',2);                              // Startwert, Endwert nach RGB, Richtung, Schrittgröße 
  
                                                            // Rot-Start,Rot-Ende, Grün-Start,Grün-Ende, Blau-Start,BlauEnde, Richtung, SG 
                                                            // HG_LR (40,0,0,0,0,40,'L',2);  1 Farbe  / Dunkel
                                                            // HG_LR (80,0,0,0,0,80,'L',4);  1 Farbe  / hell
                                                            // HG_LR (40,0,0,0,0,40,'L',4);  2 Farben / Dunkel  
                                                            // HG_LR (80,0,40,0,0,80,'L',4); 3 Farben / hell                
  // HG_LR (0,18,0,0,18,0,'K',6);                           // Startwert, Endwert nach RGB, Richtung, Schrittgröße
  delay(100);
  FastLED.show();
}