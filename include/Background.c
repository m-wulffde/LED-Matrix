// ****************************************************************************************************************************
// Hintergrund Farbe setzen und anzeigen
// ****************************************************************************************************************************
void HG_Farbe ( short R, short G, short B ) {
  for(int i = 0; i < NUM_LEDS; i++) {
    LEDs[i] = CRGB(R,G,B);
  }
  // FastLED.show();
}

// ****************************************************************************************************************************
// Hintergrund von links nach rechts einmal ausgeben
// ****************************************************************************************************************************
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
        // FastLED.show();
        // delay(1);
      }
       FastLED.show();
       delay(300);
    }
    // FastLED.show();
    // delay(100);
  }
}

// ****************************************************************************************************************************
// Regenbogen - Hintergrund
// Diese Funktion zeichnet Regenbogen mit einem sich ständig ändernden,
// stark variierender Parametersatz.
// ****************************************************************************************************************************
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
